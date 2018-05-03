#include "peermanager.h"
#include "client.h"
#include "connection.h"
#include <QProcessEnvironment>
#include <QNetworkInterface>

static const qint32   BroadcastInterval =  2000;
static const unsigned broadcastPort     = 45000;

PeerManager::PeerManager(Client* client)
    : QObject(client)
{
    this->client = client;

    QStringList envVariables;
    envVariables << "USERNAME" << "USER" << "USERDOMAIN" << "HOSTNAME" << "DOMAINNAME";

    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    for(QString& variable : envVariables){
        if(environment.contains(variable)){
            username = environment.value(variable).toUtf8();
            break;
        }
    }

    if(username.isEmpty())
        username = "unknown";

    updateAddresses();
    serverPort = 0;

    broadcastSocket.bind(QHostAddress::Any, broadcastPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(&broadcastSocket, SIGNAL(readyRead()),
            this            , SLOT(readBroadcastDatagram()));

    broadcastTimer.setInterval(BroadcastInterval);
    connect(&broadcastTimer, SIGNAL(timeout()),
            this           , SLOT(sendBroadcastDatagram()));
}


void PeerManager::setServerPort(int port)
{
    serverPort = port;
}


QByteArray PeerManager::userName() const
{
    return username;
}


void PeerManager::startBroadcasting()
{
    broadcastTimer.start();
}


bool PeerManager::isLocalHostAddress(const QHostAddress& address)
{
    for(QHostAddress& localAddress : ipAddresses){
        if(address == localAddress)
            return true;
    }
    return false;
}


void PeerManager::sendBroadcastDatagram()
{
    QByteArray datagram(username);
    datagram.append('@');                                                          // void       QByteArray::append(QString)
    datagram.append(QByteArray::number(serverPort));                               // QByteArray QByteArray::number()

    bool validBroadcastAddress = true;
    for(QHostAddress& address : broadcastAddresses){
        if(broadcastSocket.writeDatagram(datagram, address, broadcastPort) == -1)
            validBroadcastAddress = false;
    }

    if(!validBroadcastAddress)
        updateAddresses();
}


void PeerManager::readBroadcastDatagram()
{
    while(broadcastSocket.hasPendingDatagrams()){
        QHostAddress senderIp;
        quint16      senderPort;
        QByteArray   datagram;
        datagram.resize(broadcastSocket.pendingDatagramSize());
        if(broadcastSocket.readDatagram(datagram.data(), datagram.size(), &senderIp, &senderPort) == -1)
            continue;

        QList<QByteArray> list = datagram.split('@');
        if(list.size() != 2)
            continue;

        int senderServerPort = list.at(1).toInt();
        if(isLocalHostAddress(senderIp) && senderServerPort == serverPort)
            continue;

        if(!client->hasConnection(senderIp)){
            Connection* connection = new Connection(this);
            emit newConnection(connection);
            connection->connectToHost(senderIp, senderServerPort);
        }
    }
}


void PeerManager::updateAddresses()
{
    broadcastAddresses.clear();
    ipAddresses.clear();

    // equals to for(QHostAddress& ip : QNetworkInterface::allAddresses())
    for(QNetworkInterface& interface : QNetworkInterface::allInterfaces())                        // QList<QNetworkInterface>    QNetworkInterface::allInterfaces()
        for(QNetworkAddressEntry entry : interface.addressEntries()){                             /* QList<QNetworkAddressEntry> QNetworkInterface::addressEntries()
                                                                                                     QNetworkAddressEntry contains one IP address and it's relavant netmask, broadcast address */
            QHostAddress broadcastAddress = entry.broadcast();                                    // QHostAddress                QNetworkAddressEntry::broadcast()
            if(broadcastAddress != QHostAddress::Null && entry.ip() != QHostAddress::LocalHost){
                broadcastAddresses << broadcastAddress;
                ipAddresses        << entry.ip();                                                 // QHostAddress                QNetworkAddressEntry::ip()
            }
        }
}
