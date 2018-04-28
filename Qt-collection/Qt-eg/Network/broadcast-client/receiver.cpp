#include "receiver.h"

Receiver::Receiver(QWidget *parent)
    : QWidget    (parent),
      statusLabel(new QLabel(tr("Listening for broadcasted messages"))),
      udpSocket  (new QUdpSocket(this))
{
/* ------- gui ------- */
    statusLabel->setWordWrap(true);

    QPushButton* quitButton = new QPushButton(tr("&Quit"));

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Broadcast Receiver"));

/* ------- socket ------- */

    udpSocket->bind(45454, QUdpSocket::ShareAddress);                      /* bool QAbstractSocket::bind(QHostAddress& host, quint16 port, QAbstractSocket::BindMode mode)

                                                                                  QAbstractSocket::ShareAddress     : allow other services binding to the same host and port.
                                                                                  QAbstractSocket::DontShareAddress : don't allow sharing with other services.
                                                                           */

/* ------- signal to slot ------- */

    connect(udpSocket , SIGNAL(readyRead()),
            this      , SLOT(processPendingDatagrams()));

    connect(quitButton, SIGNAL(clicked()),
            this      , SLOT(close()));
}


Receiver::~Receiver()
{

}


void Receiver::processPendingDatagrams()
{
    QByteArray datagram;
    while(udpSocket->hasPendingDatagrams()){                                              // bool        QUdpSocket::hasPendingDatagrams()
        datagram.resize(int(udpSocket->pendingDatagramSize()));                           /* void        QByteArray::resize()

                                                                                             qint64      QUdpSocket::pendingDatagramSize()
                                                                                          */
        udpSocket->readDatagram(datagram.data(), datagram.size());                        /* char*       QByteArray::data()
                                                                                                 like string::c_str()

                                                                                             qint64      QUdpSocket::readDatagram(char* data, qint64 maxSize)
                                                                                          */
        statusLabel->setText(tr("Received datagram: \"%1\"").arg(datagram.constData()));  // const char* QByteArray::constData()
    }
}
