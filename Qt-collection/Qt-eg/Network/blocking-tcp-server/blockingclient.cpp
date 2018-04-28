#include "blockingclient.h"
#include <QtNetwork/QNetworkInterface>

BlockingClient::BlockingClient(QWidget *parent)
    : QWidget(parent)
{
/* ------- ip address ------- */

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for(int i=0; i<ipAddressesList.size(); i++){
        if(ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()){
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    if(ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

/* ------- gui ------- */

    hostLabel = new QLabel(tr("&Server name:"), this);
    portLabel = new QLabel(tr("S&erver Port:"), this);

    hostLineEdit = new QLineEdit(ipAddress, this);
    portLineEdit = new QLineEdit(this);
    portLineEdit->setValidator(new QIntValidator(1, 65535, this));
    portLineEdit->setFocus();

    hostLabel->setBuddy(hostLineEdit);
    portLabel->setBuddy(portLineEdit);

    statusLabel = new QLabel(tr("run the fortune server together."), this);
    statusLabel->setWordWrap(true);

    getFortuneButton = new QPushButton(tr("Get Fortune"), this);
    getFortuneButton->setDefault(true);
    getFortuneButton->setEnabled(false);

    quitButton = new QPushButton(tr("Quit"), this);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton(getFortuneButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton      , QDialogButtonBox::RejectRole);

    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addWidget(hostLabel   , 0, 0);
    mainLayout->addWidget(hostLineEdit, 0, 1);
    mainLayout->addWidget(portLabel   , 1, 0);
    mainLayout->addWidget(portLineEdit, 1, 1);
    mainLayout->addWidget(statusLabel , 2, 0, 1, 2);
    mainLayout->addWidget(buttonBox   , 3, 0, 1, 2);

    setLayout(mainLayout);
    setWindowTitle(tr("Blocking Fortune Client"));

/* ------- signal to slot ------- */

    connect(getFortuneButton, SIGNAL(clicked()),
            this            , SLOT(requestNewFortune));

    connect(quitButton      , SIGNAL(clicked()),
            this            , SLOT(close()));

    connect(hostLineEdit    , SIGNAL(textChanged(QString)),
            this            , SLOT(enableGetFortuneButton()));

    connect(portLineEdit    , SIGNAL(textChanged(QString)),
            this            , SLOT(enableGetFortuneButton()));

    connect(&thread         , SIGNAL(newFortune(QString)),
            this            , SLOT(showFortune(QString)));

    connect(&thread         , SIGNAL(error(int, QString)),
            this            , SLOT(displayError(int, QString)));
}


BlockingClient::~BlockingClient()
{

}


void BlockingClient::requestNewFortune()
{
    getFortuneButton->setEnabled(false);
    thread.requestNewFortune(hostLineEdit->text(),
                             portLineEdit->text().toInt());
}


void BlockingClient::showFortune(const QString& fortune)
{
    if(fortune == currentFortune){
        requestNewFortune();
        return;
    }

    currentFortune = fortune;
    statusLabel->setText(fortune);
    getFortuneButton->setEnabled(true);
}


void BlockingClient::displayError(int socketError, const QString& message)
{
    switch(socketError){
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Blocking Fortune Client"),
                                 tr("Host not found. Please check the host and port settings."));
        break;

    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Blocking Fortune Client"),
                                 tr("The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct."));
        break;

    default:
        QMessageBox::information(this, tr("Blocking Fortune Client"),
                                 tr("The following error occured: %1.").arg(message));
    }

    getFortuneButton->setEnabled(true);
}


void BlockingClient::enableGetFortuneButton()
{
    bool enable(!hostLineEdit->text().isEmpty() && !portLineEdit->text().isEmpty());
    getFortuneButton->setEnabled(enable);
}
