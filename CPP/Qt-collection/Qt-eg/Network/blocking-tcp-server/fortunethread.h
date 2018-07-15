#ifndef FORTUNETHREAD_H
#define FORTUNETHREAD_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>

class FortuneThread : public QThread
{
    Q_OBJECT
public:
    explicit FortuneThread(QObject *parent = 0);
    ~FortuneThread();

    void requestNewFortune(const QString& hostName, quint16 port);
    void run() override;

signals:
    void newFortune(const QString& );
    void error(int , const QString& );

private:
    QString        hostName;
    quint16        port;
    QMutex         mutex;
    QWaitCondition cond;
    bool           quit;
};

#endif // FORTUNETHREAD_H
