#ifndef BLOCKINGCLIENT_H
#define BLOCKINGCLIENT_H

#include <QtWidgets>
#include "fortunethread.h"

class BlockingClient : public QWidget
{
    Q_OBJECT

public:
    explicit BlockingClient(QWidget *parent = 0);
    ~BlockingClient();

private slots:
    void requestNewFortune();
    void showFortune(const QString& fortune);
    void displayError(int socketError, const QString& message);
    void enableGetFortuneButton();

private:
    QLabel*           hostLabel;
    QLabel*           portLabel;
    QLineEdit*        hostLineEdit;
    QLineEdit*        portLineEdit;
    QLabel*           statusLabel;
    QPushButton*      getFortuneButton;
    QPushButton*      quitButton;
    QDialogButtonBox* buttonBox;

    FortuneThread     thread;
    QString           currentFortune;
};

#endif // BLOCKINGCLIENT_H
