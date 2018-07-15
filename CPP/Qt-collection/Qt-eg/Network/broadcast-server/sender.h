#ifndef SENDER_H
#define SENDER_H

#include <QtWidgets>
#include <QTimer>
#include <QtNetwork/QUdpSocket>

class Sender : public QWidget
{
    Q_OBJECT

public:
    explicit Sender(QWidget *parent = 0);
    ~Sender();

private slots:
    void startBroadcasting();
    void broadcastDatagram();

private:
    QLabel*      statusLabel = nullptr;
    QPushButton* startButton = nullptr;
    QUdpSocket*  udpSocket   = nullptr;
    QTimer       timer;
    int          messageNo   = 1;
};

#endif // SENDER_H
