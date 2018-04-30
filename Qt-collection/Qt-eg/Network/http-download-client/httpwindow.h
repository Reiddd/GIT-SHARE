#ifndef HTTPWINDOW_H
#define HTTPWINDOW_H

#include <QtWidgets>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QSslError>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkReply>
#include <QUrl>

class ProgressDialog: public QProgressDialog{
    Q_OBJECT
public:
    explicit ProgressDialog(const QUrl& url, QWidget* parent = nullptr);

public slots:
    void networkReplyProgress(qint64 bytesRead, qint64 totalBytes);
};


class HttpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HttpWindow(QWidget *parent = 0);
    ~HttpWindow();

    void startRequest(const QUrl& requestedUrl);

private slots:
    void downloadFiles();
    void cancelDownload();
    void httpFinished();
    void httpReadyRead();
    void enableDownloadButton();
    void slotAuthenticationRequired(QNetworkReply* , QAuthenticator* authenticator);
#ifndef QT_NO_SSL
    void sslErrors(QNetworkReply* , const QList<QSslError>& errors);
#endif

private:
    QFile* openFileForWrite(const QString& fileName);

    QLabel*               statusLabel;
    QLineEdit*            urlLineEdit;
    QPushButton*          downloadButton;
    QCheckBox*            launchCheckBox;
    QLineEdit*            defaultFileLineEdit;
    QLineEdit*            downloadDirectoryLineEdit;

    QUrl                  url;
    QNetworkAccessManager qnam;
    QNetworkReply*        reply = nullptr;
    QFile*                file  = nullptr;

    bool                  httpRequestAborted;
};

#endif // HTTPWINDOW_H
