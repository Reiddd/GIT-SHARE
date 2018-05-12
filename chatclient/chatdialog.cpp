#include "chatdialog.h"
#include <QTextTable>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QScrollBar>
#include <QtNetwork/QNetworkInterface>

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent),
      socket(new QTcpSocket(this))
{
/* ------- gui ------- */

    setupUi(this);

    lineEdit->setFocusPolicy(Qt::StrongFocus);
    textEdit->setFocusPolicy(Qt::NoFocus);
    textEdit->setReadOnly(true);
    listWidget->setFocusPolicy(Qt::NoFocus);
    tableFormat.setBorder(0);

    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
    connect(exitButton, &QPushButton::clicked, this, &ChatDialog::dialogClosed);
    connect(exitButton, &QPushButton::clicked, this, &ChatDialog::close);

    newParticipant(nickname);

/* ------- socket ------- */

    if(!socket->bind(bindOnHost, 10000)){
        QColor color = textEdit->textColor();
        textEdit->setTextColor(Qt::red);
        textEdit->append("connection error");
        textEdit->setTextColor(color);
        lineEdit->setEnabled(false);
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
        QColor color = textEdit->textColor();
        textEdit->setTextColor(Qt::red);
        textEdit->append("server error");
        textEdit->setTextColor(color);
        lineEdit->setEnabled(false);
    }

/* ------- login ------- */

   l = new LogInDialog(this);
    connect(l, SIGNAL(successfullyLoggedIn(QString,QString)), this, SLOT(setNicknameAndHost(QString, QString)));
}


ChatDialog::~ChatDialog()
{

}


void ChatDialog::setNicknameAndHost(QString username, QString host)
{
    nickname = username;
    bindOnHost = QHostAddress(host);

    show();
}


void ChatDialog::newParticipant(const QString &nickname)
{
    if(nickname.isEmpty())
        return;

    QColor color = textEdit->textColor();
    textEdit->setTextColor(Qt::gray);
    textEdit->append(tr("%1 has joined.").arg(nickname));
    textEdit->setTextColor(color);
    listWidget->addItem(nickname);
}


void ChatDialog::participantLeft(const QString &nickname)
{
    if(nickname.isEmpty())
        return;

    QList<QListWidgetItem*> items = listWidget->findItems(nickname, Qt::MatchExactly);
    if(!items.isEmpty()){
        delete items.at(0);
        QColor color = textEdit->textColor();
        textEdit->setTextColor(Qt::gray);
        textEdit->append(tr("* %! has left").arg(nickname));
        textEdit->setTextColor(color);
    }
}


void ChatDialog::appendMessage(const QString &from, const QString &message)
{
    if(from.isEmpty() || message.isEmpty())
        return;

    QTextCursor cursor(textEdit->textCursor());
    cursor.movePosition(QTextCursor::End);

    QTextTable* table = cursor.insertTable(1, 2, tableFormat);
    table->cellAt(0 ,0).firstCursorPosition().insertText('<' + from + '>');
    table->cellAt(0, 1).firstCursorPosition().insertText(message);

    QScrollBar* bar = textEdit->verticalScrollBar();
    bar->setValue(bar->maximum());
}


void ChatDialog::returnPressed()
{
    QString text = lineEdit->text().trimmed();
    if(text.isEmpty())
        return;

    QString data = QString::number(ChatDialog::SNewMessage) + QString("\n") + nickname + QString("\n") + text;
    socket->write(data.toStdString().c_str());

    lineEdit->setText(tr(""));
}


void ChatDialog::dialogClosed()
{
    QString data = QString::number(SUserLogOut) + QString("\n") + nickname;
    socket->write(data.toStdString().c_str());
}


void ChatDialog::socketReadyRead()
{
    int type = ChatDialog::RNullType;
    type = socket->readLine(10000).toInt();

    switch(type){
    case ChatDialog::RUserLogIn :
    {
        QString user = QString(socket->readLine(10000));
        newParticipant(user);
        break;
    }
    case ChatDialog::RUserLogOut :
    {
        QString user = QString(socket->readLine(10000));
        participantLeft(user);
        break;
    }
    case ChatDialog::RNewMessage :
    {
        QString user = QString(socket->readLine(10000));
        QString message = QString(socket->readLine(10000));
        appendMessage(user, message);
        break;
    }
    case ChatDialog::RServerError:
    case ChatDialog::RDatabaseError:
    {
        QColor color = textEdit->textColor();
        textEdit->setTextColor(Qt::red);
        textEdit->append("connection error");
        textEdit->setTextColor(color);
        break;
    }
    default: break;
    }
}
