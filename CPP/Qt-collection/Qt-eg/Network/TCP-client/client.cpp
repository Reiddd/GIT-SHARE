#include "client.h"
#include <QtWidgets>
#include <QtNetwork/QHostInfo>  // QHostInfo provides static functions for host name lookups
#include <QtNetwork/QNetworkConfigurationManager>

Client::Client(QWidget *parent)
    : QDialog         (parent),
      hostCombo       (new QComboBox),
      portLineEdit    (new QLineEdit),
      getFortuneButton(new QPushButton(tr("GetFortune"))),
      tcpSocket       (new QTcpSocket(this))
{
/* ------- GUI ------- */

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    hostCombo->setEditable(true);

/* ------- host name ------- */

    QString name = QHostInfo::localHostName();                                                        // QString QHostInfo::localHostName()
    if(!name.isEmpty()){
        hostCombo->addItem(name);
        QString domain = QHostInfo::localDomainName();                                                // QString QHostInfo::localDomainName()
        if(!domain.isEmpty())
            hostCombo->addItem(name + QChar('.') + domain);
    }
    if(name != QLatin1String("localhost"))
        hostCombo->addItem(QString("localhost"));

/* ------- ip address ------- */

    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();                          // QString QNetworkInterface::allAddresses()
    for(int i=0; i<ipAddressesList.size(); i++){
        if(!ipAddressesList.at(i).isLoopback())                                                       // QHostAddress::isLoopback() || QHostAddress::isMulticast() || QHostAddress::isNull() || QHostAddress::isEqual()
            hostCombo->addItem(ipAddressesList.at(i).toString());                                     // QString QHostAddress::toString()
    }
    for(int i=0; i<ipAddressesList.size(); i++){
        if(ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }

/* ------- port ------- */

    portLineEdit->setValidator(new QIntValidator(1, 65535, this));                                    /* QIntValidator(int minimum, int maximum, QObject* parent=Q_NULLPTR)
                                                                                                         QLineEdit::setValidator() */

/* ------- data stream / socket ------- */

    in.setDevice(tcpSocket);                                                                          /* QDataStream::setDevice(QIODevice* d) d == 0 will unset the current I/O device.
                                                                                                         QDataStream::device() returns the currently using device or 0 if no device is set.

                                                                                                         QAbstractSocket inherits QIODevice.
                                                                                                      */
    in.setVersion(QDataStream::Qt_5_7);                                                               // QDataStream::setVersion(QDataStream::Version)

/* ------- network configuration session ------- */

    QNetworkConfigurationManager manager;
    if(manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired){
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const   QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        QNetworkConfiguration config = manager.configurationFromIdentifier(id);                       // QNetworkConfiguration QNetworkConfigurationManager::configurationFromIdentifier(QString& id)
        if((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered){
            config = manager.defaultConfiguration();                                                  // QNetworkConfiguration QNetworkConfigurationManager::defaultConfiguration()
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, &QNetworkSession::opened,                                             // void QNetworkSession::opened
                this          , &Client::sessionOpened);

        networkSession->open();                                                                       // void QNetworkSession::open()
    }

/* ------- GUI ------- */

    QLabel* hostLabel = new QLabel(tr("&Server name:"));
    hostLabel->setBuddy(hostCombo);
    QLabel* portLabel = new QLabel(tr("&Server port:"));
    portLabel->setBuddy(portLineEdit);

    statusLabel = new QLabel(tr("This example requires"
                                "you run the Fortune Server example as well."));
    statusLabel->setText(tr("Opening network session."));

    getFortuneButton->setDefault(true);                                                               // default button is which will respond when you push Enter.
    getFortuneButton->setEnabled(false);

    QPushButton*      quitButton = new QPushButton(tr("Quit"));
    QDialogButtonBox* buttonBox  = new QDialogButtonBox;                                              // QDialogButtonBox is a widget presents buttons in a layout that is appropriate to the current widget style.
    buttonBox->addButton(getFortuneButton, QDialogButtonBox::ActionRole);                             // QDialogButtonBox::addButton(QPushButton* button, QDilogButtonBox::ButtonRole role)
    buttonBox->addButton(quitButton      , QDialogButtonBox::RejectRole);                             /* QDialogButtonBox::YesRole    : a "Yes" like button.
                                                                                                         QDialogButtonBox::NoRole     : a "No" like button.
                                                                                                         QDialogButtonBox::ActionRole : click on this will cause changes to elements in the dialog.
                                                                                                         QDialogButtonBox::RejectRole : cancel the dialog (CANCEL).
                                                                                                         QDialogButtonBox::AcceptRole : accecpt the dialog (OK).*/

    connect(hostCombo       , &QComboBox::editTextChanged,
            this            , &Client::enableGetFortuneButton);
    connect(portLineEdit    , &QLineEdit::textChanged,
            this            , &Client::enableGetFortuneButton);
    connect(getFortuneButton, &QAbstractButton::clicked,
            this            , &Client::requestNewFortune);
    connect(quitButton      , &QAbstractButton::clicked,
            this            , &QWidget::close);
    connect(tcpSocket       , &QIODevice::readyRead,                                                  // QIODevice::readyRead() is a signal sent every time the new data is ready to be read.
            this            , &Client::readFortune);
    connect(tcpSocket       , SIGNAL(error(QAbstractSocket::SocketError)),
            this            , SLOT(displayError(QAbstractSocket::SocketError)));                                                 /* our slot requires a QAbstractSocket::SocketError object, so we need the second version above, to ensure Qt chose that one, we need QOverload
                                                                                                             before Qt 5.0 -> QOverload<required_arg1_type, required_arg2_type, ...>::of(func_name)
                                                                                                             after  Qt 5.0 -> QOverload<required_arg1_type, required_arg2_type, ...>(func_name) */

    QGridLayout* mainLayout = nullptr;
    if(QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()){
        QVBoxLayout* outerVerticalLayout   = new QVBoxLayout(this);
        outerVerticalLayout  ->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
        QHBoxLayout* outerHorizontalLayout = new QHBoxLayout;
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        QGroupBox*   groupBox              = new QGroupBox(QGuiApplication::applicationDisplayName());

        mainLayout = new QGridLayout(groupBox);
        outerHorizontalLayout->addWidget(groupBox);
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        outerVerticalLayout  ->addLayout(outerHorizontalLayout);
        outerVerticalLayout  ->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    }
    else mainLayout = new QGridLayout(this);

    mainLayout->addWidget(hostLabel   , 0, 0);
    mainLayout->addWidget(hostCombo   , 0, 1);
    mainLayout->addWidget(portLabel   , 1, 0);
    mainLayout->addWidget(portLineEdit, 1, 1);
    mainLayout->addWidget(statusLabel , 2, 0, 1, 2);
    mainLayout->addWidget(buttonBox   , 3, 0, 1, 2);

    setWindowTitle(QGuiApplication::applicationDisplayName());
    portLineEdit->setFocus();
}


Client::~Client()
{

}


void Client::requestNewFortune()
{
    getFortuneButton->setEnabled(false);
    tcpSocket->abort();                                        /* QAbstractSocket::abort()
                                                                      aborts the current connection and resets the socket immediately.
                                                                      closes the connection and discards any pending data in the write buffer.

                                                                  QAbstractSocket::disconnectFromHost()
                                                                      attempts to close the connection.
                                                                      it will wait until all pending data are writen and send the QAbstractSocket::disconnected signal
                                                               */
    tcpSocket->connectToHost(hostCombo    -> currentText(),    // QString QComboBox::currentText() || QString QLineEdit::text()
                             portLineEdit -> text().toInt());  /* QTcpSocket::connectToHost(const QString& hostName                            , quint16 port,
                                                                                            QIODevice::OpenMode openMode = QIODevice::ReadWrite, QAbstractSocket::NetworkLayerProtocol protocol = QAbstractSocket::AnyIPProtocol)
                                                                  QTcpSocket::connectToHost(const QHostAddress hostAddress                     , quint16 port,
                                                                                            QIODevice::OpenMode openMode = QIODevice::ReadWrite, QAbstractSocket::NetworkLayerProtocol protocol = QAbstractSocket::AnyIPProtocol)*/
}


void Client::readFortune()
{
    in.startTransaction();                                        /* QIODevice::startTRansaction()
                                                                         starts a new read transaction on the device.
                                                                         it defines a start point of a sequence of operations.
                                                                         call { bool QIODevice::commitTransaction() } or {bool QIODevice::rollbackTransaction() } to finish the operation sequence. */
    QString nextFortune;
    in >> nextFortune;

    if(!in.commitTransaction())
        return;

    if(nextFortune == currentFortune){
        QTimer::singleShot(0, this, &Client::requestNewFortune);  // QTimer::singleShot(millSecond, receiver, receiver_SLOT)
        return;
    }

    currentFortune = nextFortune;
    statusLabel->setText(currentFortune);
    getFortuneButton->setEnabled(true);
}


void Client::displayError(QAbstractSocket::SocketError socketError){
    switch(socketError){
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this,
                                tr("Fortune Client"),
                                tr("The host was not found. "
                                   "Please check the host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this,
                                 tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port settings are correct."));
        break;
    default:
        QMessageBox::information(this,
                                tr("Fortune Client"),
                                tr("The following error occurred: %1").arg(tcpSocket->errorString()));  // QString QTcpSocket::errorString()
    }
}


void Client::enableGetFortuneButton()
{
    getFortuneButton->setEnabled((!networkSession || networkSession->isOpen()) &&
                                 !hostCombo->currentText().isEmpty() &&
                                 !portLineEdit->text().isEmpty());
}


void Client::sessionOpened()
{
    QNetworkConfiguration config = networkSession->configuration();                                 // QNetworkConfiguration       QNetworkSession::configuration()
    QString id;
    if(config.type() == QNetworkConfiguration::UserChoice)                                          // QNetworkConfiguration::Type QNetworkConfiguration::type()
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();  // Qvariant                    QNetworkSession::sessionProperty(QString key)
    else
        id = config.identifier();                                                                   // QString                     QNetworkConfiguration::identifier()

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkCnfiguration"), id);
    settings.endGroup();

    statusLabel->setText(tr("This examples requires you run the "
                            "Fortune Server example as well."));

    enableGetFortuneButton();
}
