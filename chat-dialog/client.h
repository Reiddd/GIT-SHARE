#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QAbstractSocket>
#include <QHash>
#include <QHostAddress>
#include "server.h"

class PeerManager;

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client();

    void    sendMessage(const QString& message);                                     /* 1. send messages to every host connected to localhost in peers */
    QString nickName() const;                                                        /* 1. return peerManager->userName() */
    bool    hasConnection(const QHostAddress& senderIp, int senderPort = -1) const;  /* 1. search for socket to specified host and port in peers */

signals:
    void newMessage(const QString& from, const QString& message);
    void newParticipant(const QString& nick);
    void participantLeft(const QString& nick);

private slots:
    void newConnection(Connection* connection);                                      /* 1. update peers
                                                                                        2. emit newParticipant() to ChatDialog to update GUI. */
    void connectionError(QAbstractSocket::SocketError socketError);                  /* 1. remove sockets with errors peers */
    void disconnected();                                                             /* 1. remove sockets disconnected in peers */
    void readyForUse();                                                              /* 1. catch the sender, which is a Connection object, connect it's newMessage signal to ChatDialog
                                                                                        2. add the socket into peers                                                                    */

private:
    void removeConnection(Connection* connection);

    PeerManager*                          peerManager;
    Server                                server;
    QMultiHash<QHostAddress, Connection*> peers;        // tcp sockets of all hosts connected to localhost
};

#endif // CLIENT_H
