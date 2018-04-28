#include "fortunethread.h"
#include <QtNetwork/QTcpSocket>
#include <QDataStream>

FortuneThread::FortuneThread(QObject *parent) :
    QThread(parent),
    quit(false)
{

}


FortuneThread::~FortuneThread()
{
    mutex.lock();
    quit = true;
    cond.wakeOne();
    mutex.unlock();
    wait();                      // bool QThread::wait(unsigned long timeout = ULONG_MAX)
}


void FortuneThread::requestNewFortune(const QString& hostName, quint16 port)
{
    QMutexLocker locker(&mutex);
    this->hostName = hostName;
    this->port     = port;

    if(!isRunning())                                                           // bool QThread::isRunning(), if the thread of QThread::run() is running, it also returns true.
        start();
    else
        cond.wakeOne();
}


void FortuneThread::run()
{
    mutex.lock();
    QString serverName = this->hostName;
    quint32 serverPort = this->port;
    mutex.unlock();

    while(!quit){
        const int Timeout = 5 * 1000;
        QTcpSocket socket;
        socket.connectToHost(serverName, serverPort);

        if(!socket.waitForConnected(Timeout)){                     // bool QTcpSocket::waitForConnected()
            emit error(socket.error(), socket.errorString());      // QTcpSocket::Error QTcpSocket::error() || QString QTcpSocket::errorString()
            return;
        }

        QDataStream in(&socket);                                   // QDataStream::QDataStream(QTcpSocket* )
        in.setVersion(QDataStream::Qt_5_7);                        // QDataStream::setVersion(QDataStream::Version )
        QString fortune;

        do{
            if(!socket.waitForReadyRead(Timeout)){                 // bool QTcpSocket::waitForReadyRead()
                emit error(socket.error(), socket.errorString());
                return;
            }

            in.startTransaction();                                 // QDataStream::startTransaction()
            in >> fortune;
        } while(!in.commitTransaction());                          // QDataStream::commitTransaction()

        mutex.lock();
        emit newFortune(fortune);
        cond.wait(&mutex);                                         /* QWaitCondition::wait(QMutex* ) requires that the mutex object is locked.
                                                                      so the procedure usually is:
                                                                          mutex.lock();
                                                                          ......
                                                                          waitcondition.wait(mutex);
                                                                          ......
                                                                          mutex.unlock();
                                                                   */
        serverName = hostName;
        serverPort = port;
        mutex.unlock();
    }
}
