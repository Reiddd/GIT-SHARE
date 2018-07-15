#include "server.h"
#include <QtWidgets>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QTcpSocket>
#include <QtCore>

Server::Server(QWidget *parent)
    : QDialog(parent),
      statusLabel(new QLabel)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    statusLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

    QNetworkConfigurationManager manager;
    if(manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired){  /* QNetworkConfigurationManager::capabilities()
                                                                                               it returns capabilities supported by current platform.

                                                                                           QNetworkConfigurationManager::CanStartAndStopInterfaces || QNetworkConfigurationManager::DirectConnectionRouting
                                                                                           QNetworkConfigurationManager::SystemSessionSupport      || QNetworkConfigurationManager::ApplicationLevelRoaming
                                                                                           QNetworkCOnfigurationManager::ForcedRoaming             || QNetworkConfigurationManager::DataStatistics
                                                                                           QNetworkConfigurationManager::NetworkSessionRequired

                                                                                           if QNetworkConfigurationManager::NetworkSessionRequired is set, a QNetworkSession object is required before network operation.
                                                                                         */
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        /* QLatin1String:
               suppose str is a QString object, str == "cpp-str" is much faster than str == QString("cpp-str").
               this is because many QString's function has a override cpp-str version.
               but if the application defines QT_NO_CAST_FROM_ASCLL, cpp-str can't be implicitly cast to QString, but use QString("cpp_str") to do a explicit convertion slow down the application.
               this is why we need QLatin1String("cpp-str") to wrap cpp-str, it speed up the application and prevent the implicit convertion problem.
               QLatin1String("cpp-str") should be used at where a cpp-str is implicitly converted to a QString.

           QSettings:
               it provides persistent platform-independent application settings. users normally expect an application to remember its settings( like window size, positions, options ... ).
               QSettings::setValue(key_string, QVariant) sets the key-value on heap, call QSettings::sync() to commit your changes to permanent storage.
               QSettings::value(key_string, value_if_nonExist) returns a QVariant, use { QVariant::toInt() || QVariant::toString() || QVariant::value<T>() } to explicitly convert it.
               QSettings::contains(key_string) returns true if key_string exists, else false.
               QSettings::allKeys() returns a list of all keys.
               QSettings::remove(key_string) removes specified key.
               QSettings::clear() removes all keys.

               enum Scope{ UserScope,   // store settings in a location specific to the current user( user/home/ ).
                           SystemScope  // all users have access to the settings. }
        */
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered){  /* QNetworkConfiguration::Undefined  || QNetworkConfiguration::Defined
                                                                                                           QNetworkConfiguration::Discovered || QNetworkConfiguration::Active */
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, &QNetworkSession::opened,
                this          , &Server::sessionOpened);

        statusLabel->setText(tr("Opening network session."));
        networkSession->open();
    }
    else sessionOpened();

    fortunes<< tr("You've been leading a dog's life. Stay off the furniture.")  // QVector<T>::operator<<(const T& value) || QVector<T>::operator<<(const QVector<T>& other)
            << tr("You've got to think about tomorrow.")
            << tr("You will be surprised by a loud noise.")
            << tr("you will feel hungry again in another hour.")
            << tr("You might have mail.")
            << tr("You cannot kill time without injuring eternity.")
            << tr("Computers are not intelligent. They only think ther are.");

    QPushButton* quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);
    connect(quitButton, &QPushButton::clicked,
            this      , &QDialog::close);
    connect(tcpServer , &QTcpServer::newConnection,
            this      , &Server::sendFortune);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout* mainLayout = nullptr;
    if(QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()){  /* QStyleHints* QGuiApplication::styleHints()

                                                                                                                  QStyleHints encapsulate a set of platform dependent properties.
                                                                                                                      QStyleHints::mouseDoubleClickInterval()  || QStyleHints::mousePressAndHoldInterval()
                                                                                                                      QStyleHints::showIsFullScreen()          || QStyleHints::showIsMaximized()
                                                                                                                      QStyleHints::passwordMaskCharacter()     || QStypleHInts::passwordMaskDelay()*/
        QVBoxLayout* outerVerticalLayout   = new QVBoxLayout(this);
        outerVerticalLayout  ->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));  // QSpaceItem provides blank space in a layout.
        QHBoxLayout* outerHorizontalLayout = new QHBoxLayout();
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        QGroupBox*   groupBox              = new QGroupBox(QGuiApplication::applicationDisplayName());              // QGuiApplication::applicationDisplayName() returns the application's name.
        mainLayout                         = new QVBoxLayout(groupBox);
        outerHorizontalLayout->addWidget(groupBox);
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        outerVerticalLayout  ->addLayout(outerHorizontalLayout);
        outerVerticalLayout  ->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    }
    else mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);

    setWindowTitle(QGuiApplication::applicationDisplayName());
}


Server::~Server()
{

}


void Server::sessionOpened()
{
    if(networkSession){
        QNetworkConfiguration config = networkSession->configuration();  // QNetworkSession::configuration() returns the configuration this session use.
        QString id;
        if(config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();  /* QNetworkSession::sessionProperty(const QString& key)
                                                                                                           QNetworkSession::setSessionProperty(const QString& key, const& QVariant& value)
                                                                                                           key:
                                                                                                               ActiveConfiguration    : returns the configuration's identifier if QNetworkSession::isOpen() returns true, else an empty string.
                                                                                                               UserChoiceConfiguration: returns the configuration's identifier if QNetworkSession::isOpen() && QNetworkConfiguration::type() == QNetworkConfiguration::UserChoice.
                                                                                                               ConnectInBackground    : the user won't be asked when no connection can be established if this property is set to true. it's set to false by default.
                                                                                                               AutoCloseSessionTimeout: holds the timeout in millseconds for the session to polling to keep its state up to date. if it's set to -1, the session won't close automaticlly. it's set to -1 by default.
                                                                                                        */
        else id = config.identifier();  // QNetworkConfiguration::identifier()

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen()){
        QMessageBox::critical(this, tr("Fortune Server"), tr("Unable to start the server: %1.").arg(tcpServer->errorString()));  // QString(" %1 + %2 = %3").arg(1).arg(2).arg(1+2)
        close();
        return;
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();  // QList<QHostAddress> QNetworkInterface::allAddresses() returns all IP address found on the host machine.
    for(int i=0; i<ipAddressList.size(); i++){
        if(ipAddressList.at(i) != QHostAddress::LocalHost && ipAddressList.at(i).toIPv4Address()){  // qint32 QHostAddress::toIPv4Address(), the return value is valid if QHostAddress::protocol() == QAbstractSocket::IPv4Protocol.
                                                                                                    /* QHostAddress::LocalHost -> QHostAddress("127.0.0.1")       || QHostAddress::LocalHostIPv6 -> QHostAddress("::1")
                                                                                                       QHostAddress::AnyIPv4   -> QHostAddress("0.0.0.0")         || QHostAddress::AnyIPv6       -> QHostAddress("::")
                                                                                                       QHostAddress::Broadcast -> QHostAddress("255.255.255.255") || QHostAddress::Null          -> QHostAddress() */
            ipAddress = ipAddressList.at(i).toString();
            break;
        }
    }
    if(ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    statusLabel->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"                                    // QTcpServer::serverAddress()
                            "Run the Fortune Client example now.").arg(ipAddress).arg(tcpServer->serverPort()));  // QTcpServer::serverPort()
}


void Server::sendFortune()
{
    QByteArray block;                                                   // QByteArray is an array of raw bytes, it's often used with QDataStream and QTcpSocket to transfer bytes.
    QDataStream out(&block, QIODevice::WriteOnly);                      // QDataStream(QByteArray* array, QIODevice::OpenMode mode)
    out.setVersion(QDataStream::Qt_5_7);                                // QDataStream::setVersion(QDataStream::Version version) for data serialization format. better declare it.

    out<< fortunes[std::rand() % fortunes.size()];

    QTcpSocket* clientConnection = tcpServer->nextPendingConnection();  /* QTcpSocket* QTcpServer::nextPendingConnection() returns a pending connection if there is one, else returns 0.
                                                                           the QTcpSocket* object returned is considered as the child of QTcpServer, so it will be deleted when the QTcpServer instance is deleted. */
    connect(clientConnection, &QAbstractSocket::disconnected,           // QAbstractSocket::disconnected()
            clientConnection, &QObject::deleteLater);

    clientConnection->write(block);
    clientConnection->disconnectFromHost();
}
