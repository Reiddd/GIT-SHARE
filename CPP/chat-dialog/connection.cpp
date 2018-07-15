#include "connection.h"
#include <QTimerEvent>

static const int TransferTimeout = 30 * 1000;
static const int PongTimeout     = 60 * 1000;  // wait others to pong back for PongTimeout millseconds before abort the connection
static const int PingInterval    =  5 * 1000;  // for pingTimer
static const int SeparatorToken  = ' ';        // separate the DataType and message. e.g, "Ping 1 p"

Connection::Connection(QObject* parent)
    : QTcpSocket(parent),
      greetingMessage           (tr("undefined")),
      username                  (tr("unknown")),
      state                     (Connection::WaitingForGreeting),
      currentDataType           (Connection::Undefined),
      numBytesForCurrentDataType(-1),
      transferTimerId           (0),
      isGreetingMessageSent     (false)
{
    pingTimer.setInterval(PingInterval);

    connect(this      , SIGNAL(readyRead()),           // QTcpSocket::readyRead()
            this      , SLOT(processReadyRead()));

    connect(this      , SIGNAL(disconnected()),        // QTcpSocket::disconnected()
            &pingTimer, SLOT(stop()));

    connect(&pingTimer, SIGNAL(timeout()),
            this      , SLOT(sendPing()));

    connect(this      , SIGNAL(connected()),           // QTcpSocket::connected()
            this      , SLOT(sendGreetingMessage()));
}


QString Connection::name() const
{
    return username;
}


void Connection::setGreetingMessage(const QString& message)
{
    greetingMessage = message;
}


bool Connection::sendMessage(const QString& message)
{
    if(message.isEmpty())
        return false;

    QByteArray msg  = message.toUtf8();                                         // QByteArray QString::toUtf8();
    QByteArray data = "MESSAGE " + QByteArray::number(msg.size()) + ' ' + msg;

    return write(data) == data.size();                                          // qint64 QIODevice::write(const QByteArray& )
}


void Connection::timerEvent(QTimerEvent* timerEvent)
{
    if(timerEvent->timerId() == transferTimerId){     // int QTimerEvent::timerId()
        abort();
        killTimer(transferTimerId);                   // void QObject::killTimer(int id)
        transferTimerId = 0;
    }
}


void Connection::processReadyRead()
{
    if(state == Connection::WaitingForGreeting){
        if(!readProtocolHeader())
            return;
        if(currentDataType != Connection::Greeting){
            abort();
            return;
        }
        state = Connection::ReadingGreeting;
    }

    if(state == Connection::ReadingGreeting){
        if(!hasEnoughData())
            return;

        buffer = read(numBytesForCurrentDataType);
        if(buffer.size() != numBytesForCurrentDataType){
            abort();
            return;
        }

        /* QHostAddress QTcpSocket::peerAddress()
           quint16      QTcpSocket::peerPort()     */
        username                   = QString(buffer) + '@' + peerAddress().toString() + ':' + QString::number(peerPort());
        currentDataType            = Connection::Undefined;
        numBytesForCurrentDataType = 0;
        buffer.clear();

        if(!isValid()){                                                                                                     // bool QAbstractSocket::isValid() return true if the socket is valid and ready for use.
            abort();
            return;
        }

        if(!isGreetingMessageSent)
            sendGreetingMessage();

        pingTimer.start();
        pongTime.start();
        state = Connection::ReadyForUse;
        emit readyForUse();
    }

    do{
        if(currentDataType == Connection::Undefined){
            if(!readProtocolHeader())
                return;
        }

        if(!hasEnoughData())
            return;
        processData();
    }while(bytesAvailable()>0);
}


void Connection::sendPing()
{
    if(pongTime.elapsed() > PongTimeout){  // int QTime::elapsed() returns the number of millseconds since last start of restart
        abort();
        return;
    }

    write("PING 1 p");
}


void Connection::sendGreetingMessage()
{
    QByteArray greeting = greetingMessage.toUtf8();
    QByteArray data     = "GREETING " + QByteArray::number(greeting.size()) + ' ' + greeting;
    if(write(data) == data.size())
        isGreetingMessageSent = true;
}


int Connection::readDataIntoBuffer(int maxSize)
{
    if(maxSize > MaxBufferSize)
        return 0;

    int numBytesBeforeRead = buffer.size();
    if(numBytesBeforeRead == MaxBufferSize){
        abort();
        return 0;
    }

    while(bytesAvailable() > 0 && buffer.size() < maxSize){
        buffer.append(read(1));
        if(buffer.endsWith(SeparatorToken))
            break;
    }
    return buffer.size() - numBytesBeforeRead;
}


int Connection::dataLengthForCurrentDataType()
{
    if(bytesAvailable() <= 0 || readDataIntoBuffer() <= 0 || !buffer.endsWith(SeparatorToken))
        return 0;

    buffer.chop(1);                                                                             // void QByteArray::chop(int n) removes n bytes from the end, if n > size, remove all bytes
    int number = buffer.toInt();
    buffer.clear();
    return number;
}


bool Connection::readProtocolHeader()
{
    if(transferTimerId){
        killTimer(transferTimerId);
        transferTimerId = 0;
    }

    if(readDataIntoBuffer() <= 0){
        transferTimerId = startTimer(TransferTimeout);
        return false;
    }

    if     (buffer == "PING")     currentDataType = Connection::Ping;
    else if(buffer == "PONG")     currentDataType = Connection::Pong;
    else if(buffer == "MESSAGE")  currentDataType = Connection::PlainText;
    else if(buffer == "GREETING") currentDataType = Connection::Greeting;
    else{
        currentDataType = Connection::Undefined;
        abort();
        return false;
    }

    buffer.clear();
    numBytesForCurrentDataType = dataLengthForCurrentDataType();
    return true;
}


bool Connection::hasEnoughData()
{
    if(transferTimerId){
        QObject::killTimer(transferTimerId);
        transferTimerId = 0;
    }

    if(numBytesForCurrentDataType <= 0)
        numBytesForCurrentDataType = dataLengthForCurrentDataType();

    if(bytesAvailable() < numBytesForCurrentDataType || numBytesForCurrentDataType <= 0){
        transferTimerId = startTimer(TransferTimeout);
        return false;
    }

    return true;
}


void Connection::processData()
{
    buffer = read(numBytesForCurrentDataType);
    if(buffer.size() != numBytesForCurrentDataType){
        abort();
        return;
    }

    switch(currentDataType){
    case Connection::PlainText :
        emit newMessage(username, QString::fromUtf8(buffer));   // QString QString::fromUtf8(const QByteArray& )
        break;
    case Connection::Ping :
        write("PONG 1 P");
        break;
    case Connection::Pong :
        pongTime.restart();                                     // int     QTime::restart() sets time to current time and returns the number of millseconds since last start.
        break;
    default:
        break;
    }

    currentDataType = Connection::Undefined;
    numBytesForCurrentDataType = 0;
    buffer.clear();
}
