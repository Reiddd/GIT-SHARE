#include "sender.h"
#include <QtCore>

Sender::Sender(QWidget *parent)
    : QWidget    (parent),
      statusLabel(new QLabel(tr("Ready to broadcast datagrams on port 45454"), this)),
      startButton(new QPushButton(tr("&Start"), this)),
      udpSocket  (new QUdpSocket(this))
{
/* ------- gui ------- */
    statusLabel->setWordWrap(true);

    QPushButton* quitButton = new QPushButton(tr("&Quit"), this);

    QDialogButtonBox* buttonBox = new QDialogButtonBox;
    buttonBox->addButton(startButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton , QDialogButtonBox::RejectRole);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    setWindowTitle(tr("Broadcast Sender"));

/* ------- singal to slot ------- */

    connect(startButton, &QPushButton::clicked,
            this       , &Sender::startBroadcasting);

    connect(quitButton , &QPushButton::clicked,
            this       , &Sender::close);

    connect(&timer     , &QTimer::timeout,
            this       , &Sender::broadcastDatagram);
}


Sender::~Sender()
{

}


void Sender::startBroadcasting()
{
    startButton->setEnabled(false);
    timer.start(1000);
}


void Sender::broadcastDatagram()
{
    statusLabel->setText(tr("Now broadcasting datagram %1").arg(messageNo));
    QByteArray datagram = "Broadcast message " + QByteArray::number(messageNo);  // QByteArray::number()
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);          // qint64 QUdpSocket::writeDatagram(QByteArray& datagram, const QHostAddress& host, quint16 port)
    ++messageNo;
}
