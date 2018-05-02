#include "server.h"

Server::Server(QObject* parent)
    : QTcpServer(parent)
{
    listen(QHostAddress::Any);
}


void Server::incomingConnection(qintptr socketDescriptor)  // socketDescriptor is the base implementation of a socket.
{
    Connection* connection = new Connection(this);
    connection->setSocketDescriptor(socketDescriptor);     /* void QAbstractSocket::setSocketDescriptor(qintptr )

                                                              creates a new socket.*/
    emit newConnection(connection);
}
