#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QDataStream>
#include <QtNetwork/QTcpSocket>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QtNetwork/QNetworkSession>

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

private slots:
    void requestNewFortune();
    void readFortune();
    void displayError(QAbstractSocket::SocketError socketError);
    void enableGetFortuneButton();
    void sessionOpened();

private:
    QComboBox*       hostCombo        = nullptr;
    QLineEdit*       portLineEdit     = nullptr;
    QLabel*          statusLabel      = nullptr;
    QPushButton*     getFortuneButton = nullptr;

    QTcpSocket*      tcpSocket        = nullptr;
    QDataStream      in;
    QString          currentFortune;
    QNetworkSession* networkSession   = nullptr;
};

#endif // CLIENT_H
