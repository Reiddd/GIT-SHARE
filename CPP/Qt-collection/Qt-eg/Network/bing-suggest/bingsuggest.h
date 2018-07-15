#ifndef BINGSUGGEST_H
#define BINGSUGGEST_H

#include <QtWidgets>
#include <QtCore>
#include <QtNetwork/QNetworkAccessManager>

class BingSuggest : public QObject
{
    Q_OBJECT
public:
    explicit BingSuggest(QLineEdit *parent = 0);
    ~BingSuggest();

    bool eventFilter(QObject* object, QEvent* event) override;
    void showCompletion(const QVector<QString>& choices);

public slots:
    void doneCompletion();
    void preventSuggest();
    void autoSuggest();
    void handleNetworkData(QNetworkReply* networkReply);

private:
    QLineEdit*            editor = nullptr;
    QTreeWidget*          popup  = nullptr;
    QTimer                timer;
    QNetworkAccessManager networkManager;
};

#endif // BINGSUGGEST_H
