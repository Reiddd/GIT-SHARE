#include "chatserver.h"
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkSession>
#include <QtNetwork/QNetworkInterface>
#include <QtSql/QSqlQuery>
#include <QMutexLocker>
#include <iterator>

ChatServer::ChatServer(QObject *parent)
    : QObject(parent)
{
/* ------- session ------- */

    QNetworkConfigurationManager manager(this);
    if(manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired){
        QNetworkSession session(manager.defaultConfiguration(), this);
        connect(&session, &QNetworkSession::opened, this, &ChatServer::sessionOpened);
        session.open();
    }
    else
        sessionOpened();

/* ------- prepare the database ------- */

    if(!prepareDatabase())
        return;

/* ------- signals to slots ------- */

    connect(this, &ChatServer::userLogOutSignal, &ChatServer::userLogOut);
    connect(this, &ChatServer::userLogInSignal, &ChatServer::userLogIn);
    connect(this, &ChatServer::newMessageSignal, &ChatServer::newMessage);
}


void ChatServer::sessionOpened()
{
    server = new QTcpServer(this);

    QHostAddress listenOnHost = QHostAddress::Any;
    for(QHostAddress& host : QNetworkInterface::allAddresses())
        if(!host.isLoopback()){
            listenOnHost = host;
            break;
        }

    if(!server->listen(listenOnHost, 10000)){
        fprintf(stderr, "server can't listen on port 10000\n");
        return;
    }
    connect(server, &QTcpServer::newConnection, this, &ChatServer::newConnection);
}


bool ChatServer::prepareDatabase()
{
    if(!QSqlDatabase::drivers().contains("QMYSQL", Qt::CaseInsensitive)){
        fprintf(stderr, "need a driver for MySQL\n");
        return false;
    }

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("Qt_data");
    db.setUserName("root");
    db.setPassword("Hlw03301227");
    if(!db.open()){
        fprintf(stderr, "can't open the specified database\n");
        return false;
    }

    if(!db.tables().contains("users", Qt::CaseInsensitive)){
        QSqlQuery q(db);
        if(!q.exec("create table users(id int primary key, nickname varchar(30), password varchar(30))")){
            fprintf(stderr, "Error when creating the users table\n");
            return false;
        }
    }

    return true;
}


void ChatServer::newConnection()
{
    QTcpSocket* socket = server->nextPendingConnection();

    QString host = socket->peerAddress().toString();
    {
        QMutexLocker locker(&mutex);
        if(hostSocketMap.find(host) != hostSocketMap.end())
            delete hostSocketMap[host];
        hostSocketMap.insert(host, socket);
        connect((hostSocketMap[host]), &QTcpSocket::readyRead, this, &ChatServer::socketReadyRead);
    }
}


void ChatServer::socketReadyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    int dataType = ChatServer::RNullType;
    dataType = socket->readLine(10000).toInt();
    if(dataType == ChatServer::RNullType)
        return;

    switch(dataType){
    case ChatServer::RUserLogIn: handleUserLogIn(socket); break;
    case ChatServer::RUserLogOut: handleUserLogOut(socket); break;
    case ChatServer::RNewMessage: handleNewMessage(socket); break;
    case ChatServer::RCreateAccount: handleCreateAccount(socket); break;
    case ChatServer::RChangePassword: handleChangePassword(socket); break;
    default: break;
    }
}


void ChatServer::handleUserLogIn(QTcpSocket *socket)
{
    QString nickname = QString(socket->readLine(10000));
    QString password = QString(socket->readLine(10000));
    if(nickname.isEmpty() || password.isEmpty())
        return;

    QSqlQuery q(db);
    q.prepare("select * from users where nickname == ?");
    q.addBindValue(nickname);

    if(!q.exec()){
        QString text = QString::number(ChatServer::SDatabaseError);
        socket->write(text.toStdString().c_str());
        return;
    }

    if(!q.next()){
        QString text = QString::number(ChatServer::SUserNonExist);
        socket->write(text.toStdString().c_str());
        return;
    }

    if(q.value("password").toString() != password){
        QString text = QString::number(ChatServer::SWrongPassword);
        socket->write(text.toStdString().c_str());
        return;
    }

    {
        QMutexLocker locker(&mutex);
        hostNicknameMap[socket->peerAddress().toString()] = nickname;
    }

    socket->write(QString::number(ChatServer::SSuccess).toStdString().c_str());
    emit userLogInSignal(nickname);
}


void ChatServer::handleUserLogOut(QTcpSocket *socket)
{
    QMutexLocker locker(&mutex);

    QMap<QString, QTcpSocket*>::iterator it = hostSocketMap.find(socket->peerAddress().toString());
    if(it != hostSocketMap.end()){
        QMap<QString, QString>::iterator i = hostNicknameMap.find(socket->peerAddress().toString());
        QString nickname = *i;
        hostSocketMap.erase(it);
        hostNicknameMap.erase(i);
        emit userLogOutSignal(nickname);
    }
}


void ChatServer::handleNewMessage(QTcpSocket *socket)
{
    QString message = QString(socket->readLine(10000));

    if(!message.isEmpty())
        emit newMessageSignal(message);
}


void ChatServer::handleCreateAccount(QTcpSocket *socket)
{
    QString nickname = socket->readLine(10000);
    QString password = socket->readLine(10000);
    if(nickname.isEmpty() || password.isEmpty())
        return;

    QSqlQuery q(db);
    q.prepare("insert into users(nickname, password) values(?, ?)");
    q.addBindValue(nickname);
    q.addBindValue(password);

    if(!q.exec()){
        QString text = QString::number(ChatServer::SDatabaseError);
        socket->write(text.toStdString().c_str());
        return;
    }

    socket->write(QString::number(ChatServer::SSuccess).toStdString().c_str());
}


void ChatServer::handleChangePassword(QTcpSocket *socket)
{
    QString nickname = socket->readLine(10000);
    QString password = socket->readLine(10000);
    if(nickname.isEmpty() || password.isEmpty())
        return;

    QSqlQuery q(db);
    q.prepare("select * from users where nickname == ?");
    q.addBindValue(nickname);

    if(!q.exec()){
        QString text = QString::number(ChatServer::SDatabaseError);
        socket->write(text.toStdString().c_str());
        return;
    }

    if(!q.next()){
        QString text = QString::number(ChatServer::SUserNonExist);
        socket->write(text.toStdString().c_str());
        return;
    }

    q.prepare("update users set password := ? where nickname == ?");
    q.addBindValue(password);
    q.addBindValue(nickname);
    if(!q.exec()){
        QString text = QString::number(ChatServer::SDatabaseError);
        socket->write(text.toStdString().c_str());
        return;
    }

    socket->write(QString::number(ChatServer::SSuccess).toStdString().c_str());
}


void ChatServer::userLogIn(QString &nickname)
{
    QMutexLocker locker(&mutex);

    QString text = QString::number(ChatServer::SUserLogIn) + QStringLiteral("\n") + nickname;

    for(auto key : hostSocketMap.keys())
        hostSocketMap[key]->write(text.toStdString().c_str());
}


void ChatServer::userLogOut(QString& nickname)
{
    QMutexLocker locker(&mutex);

    QString text = QString::number(ChatServer::SUserLogOut) + QStringLiteral("\n") + nickname;

    for(auto key : hostSocketMap.keys())
        hostSocketMap[key]->write(text.toStdString().c_str());
}


void ChatServer::newMessage(QString& message)
{
    QMutexLocker locker(&mutex);

    QString text = QString::number(ChatServer::SNewMessage) + QStringLiteral("\n") + message;

    for(auto key : hostSocketMap.keys())
        hostSocketMap[key]->write(text.toStdString().c_str());
}
