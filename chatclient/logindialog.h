#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "ui_logindialog.h"
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

class LogInDialog : public QDialog, private Ui::LogInDialog
{
    Q_OBJECT

public:
    LogInDialog(QWidget* parent = 0);
    ~LogInDialog();

signals:
    void successfullyLoggedIn(QString , QString );

private slots:
    void validator();
    void socketReadyRead();

private:
    enum State{ LogInState, CreateUserState, ChangePasswordState };
    enum SentDataType{ SUserLogIn = 1, SUserLogOut = 2,
                                   SNewMessage = 3, SCreateAccount = 4,
                                   SChangePassword = 5, SReconnection = 6 };
    enum ReceivedDataType{ RUserLogIn = 101, RUserLogOut = 102,
                                          RServerError = 103, RDatabaseError = 104,
                                          RNewMessage = 105, RUserNonExist = 106,
                                          RWrongPassword = 107, RSuccess = 108,
                                          RNullType = 100     };

    QTcpSocket* socket = nullptr;
    LogInDialog::State state = LogInState;
    QHostAddress bindOnHost = QHostAddress::Any;
};

#endif // LOGINDIALOG_H
