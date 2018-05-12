#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QTextTableFormat>
#include "ui_chatdialog.h"
#include "logindialog.h"
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

class ChatDialog : public QDialog, private Ui::ChatDialog
{
    Q_OBJECT

public:
    ChatDialog(QWidget *parent = 0);
    ~ChatDialog();

    LogInDialog* l;

private slots:
    void returnPressed();
    void socketReadyRead();
    void setNicknameAndHost(QString nickname, QString host);
    void dialogClosed();

private:
    void newParticipant(const QString& nickname);
    void participantLeft(const QString& nickname);
    void appendMessage(const QString& from, const QString& message);

    enum SentDataType{ SUserLogIn = 1, SUserLogOut = 2,
                                   SNewMessage = 3, SCreateAccount = 4,
                                   SChangePassword = 5, SReconnection = 6 };
    enum ReceivedDataType{ RUserLogIn = 101, RUserLogOut = 102,
                                          RServerError = 103, RDatabaseError = 104,
                                          RNewMessage = 105, RUserNonExist = 106,
                                          RWrongPassword = 107, RSuccess = 108,
                                          RNullType = 100     };

    QTcpSocket* socket = nullptr;
    QString nickname;
    QHostAddress bindOnHost = QHostAddress::Any;
    QTextTableFormat tableFormat;
};

#endif // CHATDIALOG_H
