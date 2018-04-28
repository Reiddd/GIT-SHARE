#ifndef RECEIVER_H
#define RECEIVER_H

#include <QWidget>
#include <QtWidgets>
#include <QtNetwork/QUdpSocket>

class Receiver : public QWidget
{
    Q_OBJECT

public:
    explicit Receiver(QWidget *parent = 0);
    ~Receiver();

private slots:
    void processPendingDatagrams();

private:
    QLabel*     statusLabel = nullptr;
    QUdpSocket* udpSocket   = nullptr;
};

#endif // RECEIVER_H
