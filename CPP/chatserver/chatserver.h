#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QMap>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtSql/QSqlDatabase>
#include <QMutex>

class ChatServer : public QObject
{
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent = nullptr);                                         /* 1. create a network session if necessary
                                                                                                                    2. prepare the database for use
                                                                                                                    3. connect signals to slots                     */

signals:
    void userLogInSignal(QString& nickname);
    void userLogOutSignal(QString& nickname);
    void newMessageSignal(QString& message);

private slots:
    void sessionOpened();                                                                           /* 1. initialize the tcp server
                                                                                                                    2. redirect the connection to this->newConnection */
    void newConnection();                                                                           /* 1. update the hostSocketMap, delete the old socket
                                                                                                                    2. use mutex when munipulating hostSocketMap
                                                                                                                    3. redirect the readyRead to this->readyRead           */
    void socketReadyRead();                                                                        /* 1. redirect to this->handle**() according to ReceivedDataType */
    void userLogIn(QString& nickname);
    void userLogOut(QString& nickname);
    void newMessage(QString& message);

private:
    bool prepareDatabase();                                                                         /* 1. check whether there is a driver for MySQL
                                                                                                                    2. create users table if there isn't one            */
    void handleUserLogIn(QTcpSocket* socket);
    void handleUserLogOut(QTcpSocket* socket);
    void handleNewMessage(QTcpSocket* socket);
    void handleCreateAccount(QTcpSocket* socket);
    void handleChangePassword(QTcpSocket* socket);

    enum ReceivedDataType{ RUserLogIn     = 1, RUserLogOut  = 2,
                                          RNewMessage = 3, RCreateAccount = 4,
                                          RChangePassword = 5, RReconnection = 6,
                                          RNullType = 0 };
    enum SentDataType{ SUserLogIn = 101, SUserLogOut = 102,
                                    SServerError = 103, SDatabaseError = 104,
                                   SNewMessage = 105, SUserNonExist = 106,
                                    SWrongPassword = 107, SSuccess = 108 };

    QTcpServer* server = nullptr;
    QSqlDatabase db;
    QMap<QString, QTcpSocket*> hostSocketMap;
    QMap<QString, QString> hostNicknameMap;
    QMutex mutex;
};

#endif // CHATSERVER_H
