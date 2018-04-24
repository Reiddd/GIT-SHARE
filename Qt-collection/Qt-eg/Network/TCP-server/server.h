#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <QLabel>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QNetworkSession>

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private slots:
    void sessionOpened();
    void sendFortune();

private:
    QLabel* statusLabel = nullptr;
    QTcpServer* tcpServer = nullptr;
    QVector<QString> fortunes;
    QNetworkSession* networkSession = nullptr;
};

#endif // SERVER_H
