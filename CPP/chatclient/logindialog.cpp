#include "logindialog.h"
#include <QtNetwork/QNetworkInterface>
#include <QMessageBox>

LogInDialog::LogInDialog(QWidget* parent)
    : QDialog(parent)
{
/* ------- gui ------- */

    setupUi(this);

    okButton->setEnabled(true);
    okButton->setDefault(true);
    usernameEdit->setPlaceholderText(QStringLiteral("xxx"));
    passwordEdit->setPlaceholderText(QStringLiteral("********"));

    connect(okButton, &QPushButton::clicked, this, &LogInDialog::validator);
    connect(cancelButton, &QPushButton::clicked, this, &LogInDialog::close);
    connect(this, &LogInDialog::successfullyLoggedIn, &LogInDialog::close);

/* ------- socket ------- */

    socket = new QTcpSocket;
    connect(socket, &QTcpSocket::readyRead, this, &LogInDialog::socketReadyRead);

    for(QHostAddress& host : QNetworkInterface::allAddresses())
        if(!host.isLoopback()){
            bindOnHost = host;
            break;
        }

    if(!socket->bind(bindOnHost, 10000)){
        informationLabel->setText("connection error: local host error");
        okButton->setEnabled(false);
    }

    bool flag = false;
    for(int i=0; i<5; i++){
        socket->connectToHost(QHostAddress("101.132.110.96"), 10000);
        if(socket->waitForConnected(50000)){
            flag = true;
            break;
        }
    }
    if(!flag){
        informationLabel->setText("connection error: can't connect to the server");
        okButton->setEnabled(false);
    }

    informationLabel->setText("successfully connected to the server :)");
}

LogInDialog::~LogInDialog()
{

}


void LogInDialog::validator()
{
    okButton->setEnabled(false);
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();

    if(username.isEmpty() || password.isEmpty()){
        informationLabel->setText(QStringLiteral("invalid input: username and password can't be empty !"));
        return;
    }

    if(username.size() > 30 || password.size() > 30){
        informationLabel->setText(QStringLiteral("invalid input: username and password's max length is 30 !"));
        return;
    }

    static char invalidChar[] = {' ', '-', '+', '(', ')', '&', '$', '#', '^', '\'', '"', '!', ':', ';', '{', '}', '[', ']', '\\', '|'};
    for(char c : invalidChar){
        if(username.contains(QChar(c))){
            informationLabel->setText(tr("invalid username: contain invalid character %1").arg(c));
            return;
        }
        if(password.contains(QChar(c))){
            informationLabel->setText(tr("invalid password: contain invalid character %1").arg(c));
            return;
        }
    }

    QString text = QString::number(LogInDialog::SUserLogIn) + QString("\n") + username + QString("\n") + password;
    socket->write(text.toStdString().c_str());
}


void LogInDialog::socketReadyRead()
{
    if(state == LogInDialog::LogInState){
        int type = LogInDialog::RNullType;
        type = socket->readLine(10000).toInt();

        switch(type){
        case LogInDialog::RServerError : informationLabel->setText("server error: please try again later."); break;
        case LogInDialog::RDatabaseError : informationLabel->setText("database error: please reboot the server."); break;
        case LogInDialog::RWrongPassword : informationLabel->setText("wrong password"); break;
        case LogInDialog::RSuccess : emit successfullyLoggedIn(usernameEdit->text().trimmed(), bindOnHost.toString()); break;
        case LogInDialog::RUserNonExist :
        {informationLabel->setText(" ");
            QMessageBox::StandardButton button = QMessageBox::warning(this, tr("No such user"), tr("Create a new user using this name?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if(button == QMessageBox::Yes){
                state = LogInDialog::CreateUserState;
                QString text = QString::number(LogInDialog::SCreateAccount) + QString("\n") + usernameEdit->text().trimmed() + QString("\n") + passwordEdit->text().trimmed();
                socket->write(text.toStdString().c_str());
            }
            break;
        }
        default : break;
        }
    }
    else if(state == LogInDialog::CreateUserState){
        int type = LogInDialog::RNullType;
        type = socket->readLine(10000).toInt();
        switch(type){
        case LogInDialog::RServerError : informationLabel->setText("Create user error, server no respond."); break;
        case LogInDialog::RDatabaseError : informationLabel->setText("Create user error, database no respond."); break;
        case LogInDialog::RSuccess : emit successfullyLoggedIn(usernameEdit->text().trimmed(), bindOnHost.toString()); break;
        default: break;
        }
        if(type != LogInDialog::RNullType)
            state = LogInDialog::LogInState;
    }

    okButton->setEnabled(true);
}
