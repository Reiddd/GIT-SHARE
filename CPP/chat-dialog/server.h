#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>
#include "connection.h"

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject* parent = nullptr);

signals:
    void newConnection(Connection* connection);

protected:
    void incomingConnection(qintptr socketDescriptor) override;  // called by QTcpServer when new connection is available
};

#endif // SERVER_H
