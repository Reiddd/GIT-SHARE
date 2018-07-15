#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>
#include <QTime>
#include <QTimer>

static const int MaxBufferSize = 1024000;

class Connection : public QTcpSocket
{
    Q_OBJECT

public:
    enum ConnectionState{ WaitingForGreeting, ReadingGreeting, ReadyForUse };

    enum DataType{ PlainText, Ping, Pong, Greeting, Undefined };

    Connection(QObject* parent = nullptr);                                       /* readyRead     -> processReadyRead
                                                                                   connected     -> sendGreetingMessage
                                                                                   disconnected  -> timer.stop
                                                                                   timer.timeout -> sendPing            */

    QString name() const;
    void setGreetingMessage(const QString& message);
    bool sendMessage(const QString& message);                                    /* convert message into QByteArray and send it.
                                                                                   QString::toUtf8() || QTcpSocket::write(QByteArray)
                                                                                   return whether all bytes are sent successfully     */

signals:
    void readyForUse();
    void newMessage(const QString& from, const QString& message);

protected:
    void timerEvent(QTimerEvent* timerEvent) override;

private slots:
    void processReadyRead();                                                     /* make sure the socket is ready for use
                                                                                    if state != ReadyForUse, do the greeting procedure.
                                                                                    readProtocolHeader() -> hasEnoughData() -> processData() */
    void sendGreetingMessage();                                                  // send the greeting message and set isGreetingMessageSent flag to true
    void sendPing();                                                             /* used with a timer, if timeout, abort the connection
                                                                                    QTime.elapsed() || QTcpSocket::abort()              */

private:
    int  readDataIntoBuffer(int maxSize = MaxBufferSize);                        /* if      maxSize       >  MaxBufferSize, buffer doesn't have the size to contain those bytes, return 0.
                                                                                    else if buffer.size() == MaxBufferSize, the buffer is already filled, return 0.
                                                                                    else keep a loop reading one byte of the socket's message into buffer until encounter the SeparatorToken or buffer is filled.
                                                                                    return how much bytes read into buffer.                                                                                       */
    int  dataLengthForCurrentDataType();                                         /* update numBytesForCurrentDataType

                                                                                    e.g. "7 message", it reads 7. */
    bool readProtocolHeader();                                                   /* update currentDataType

                                                                                    e.g. "PLAINTEXT 7 message", it reads "PLAINTEXT".
                                                                                    if      transfer timer exists    , kill it and set transferTimerId = 0.
                                                                                    else if readDataIntoBuffer() <= 0, return false.
                                                                                    set currentDataType according to the message's header.
                                                                                    clear the buffer
                                                                                    the message turns into "7 message", set numBytesForCurrentDataType =  dataLengthForCurrentDataType()
                                                                                    the message turns into "message".*/
    bool hasEnoughData();                                                        /* if there is a transferTimer, kill it and set transferTimerId = 0.
                                                                                    numBytesForCurrentDataType = dataLengthForCurrentDataType()
                                                                                    if      bytesAvailable()           <  numBytesForCurrentDataType, the transfer procedure is interrupted, start a new transferTimer and return false.
                                                                                    else if numBytesForCurrentDataType <= 0                         , there is no byte to read, start a new transferTimer and return false.
                                                                                    else    return true.
                                                                                    return is reading successful.                                                                                                                        */
    void processData();                                                          /* after readProtocolHeader() and dataLengthForCurrentDataType()

                                                                                    if      reading is interrupted, abort
                                                                                    else if DataType == PlainText , emit new message signal
                                                                                    else if DataType == Ping      , Pong back
                                                                                    else if DataType == Pong      , restart the pongTime    */

    QString         greetingMessage;
    QString         username;
    QTimer          pingTimer;                   // ping others with a set interval.
    QTime           pongTime;                    // the number of millseconds since the last time receiving Pong type message.
    QByteArray      buffer;
    ConnectionState state;
    DataType        currentDataType;
    int             numBytesForCurrentDataType;  // e.g. "PlainText 7 message", 7 is numBytesForCurrentDataType.
    int             transferTimerId;             // the id of transferTimer. Timer's id is returned by QAbstractSocket::startTimer(int timeout).
    bool            isGreetingMessageSent;       // a flag represents whether greeting message has been sent.
};

#endif // CONNECTION_H
