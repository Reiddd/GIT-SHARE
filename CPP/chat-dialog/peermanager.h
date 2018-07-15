#ifndef PEERMANAGER_H
#define PEERMANAGER_H

#include <QObject>
#include <QByteArray>
#include <QList>
#include <QTimer>
#include <QUdpSocket>

class Client;
class Connection;

class PeerManager : public QObject
{
    Q_OBJECT
public:
    PeerManager(Client* client);                                 /* 1. set username to system's USER or HOSTNAME using QProcessEnvironment
                                                                    2. if QProcessEnvironment can't provide information, set username to Unknown
                                                                    3. bind the broadcastSocket
                                                                    4. broadcastTimer.timeout()    -> sendBroadcastDatagram()
                                                                       broadcastSocket.readyRead() -> readBroadcastDatagram()
                                                                    5. updateAddresses()                                                          */

    void       setServerPort(int port);
    QByteArray userName() const;                                 /* 1. return username */
    void       startBroadcasting();                              /* 1. start broadcastTimer */
    bool       isLocalHostAddress(const QHostAddress& address);

signals:
    void newConnection(Connection* connection);

private slots:
    void sendBroadcastDatagram();                                /* 1. construct a datagram: username@serverPort
                                                                    2. send the datagram to all address in broadcastAddresses
                                                                    3. if there are any writeDatagram() fail, uppdateAddresses() */
    void readBroadcastDatagram();                                /* 1. check whether there are any pending datagram sent to broadcastSocket
                                                                    2. read the datagram, filter out username and port
                                                                    3. check whether the client has connection with that host, if not, update client's connection list and emit newConnection()*/

private:
    void updateAddresses();                                      /* 1. clear broadcastAddresses and ipAddresses
                                                                    2. loop through all network address entries, add their broadcast addresses into broadcastAddresses, ip addresses to ipAddresses */

    Client*             client;
    QList<QHostAddress> broadcastAddresses;
    QList<QHostAddress> ipAddresses;
    QUdpSocket          broadcastSocket;
    QTimer              broadcastTimer;      // send broadcast messages every BroadcastInterval millseconds.
    QByteArray          username;            // system's USER or HOSTNAME.
    int                 serverPort;
};

#endif // PEERMANAGER_H
