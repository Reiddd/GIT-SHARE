#include "httpwindow.h"
#include "ui_authenticationdialog.h"

const char defaultUrl[]      = "https://www.qt.io/";
const char defaultFileName[] = "index.html";

ProgressDialog::ProgressDialog(const QUrl& url, QWidget* parent)
    : QProgressDialog(parent)
{
    setWindowTitle(tr("Download Progress"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setLabelText(tr("Download %1.").arg(url.toDisplayString()));
    setMinimum(0);
    setValue(0);
    setMinimumDuration(0);
    setMinimumSize(QSize(400, 75));
}


void ProgressDialog::networkReplyProgress(qint64 bytesRead, qint64 totalBytes)
{
    setMaximum(totalBytes);
    setValue(bytesRead);
}


HttpWindow::HttpWindow(QWidget *parent)
    : QDialog(parent),
      statusLabel              (new QLabel(tr("Please enter the URL of a file you want to download.\n\n"), this)),
      urlLineEdit              (new QLineEdit(defaultUrl)),
      downloadButton           (new QPushButton(tr("Download"))),
      launchCheckBox           (new QCheckBox("Launch file")),
      defaultFileLineEdit      (new QLineEdit(defaultFileName)),
      downloadDirectoryLineEdit(new QLineEdit),
      httpRequestAborted       (false)
{
/* ------- gui ------- */

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("HTTP"));

    QFormLayout* formLayout = new QFormLayout;
    urlLineEdit->setClearButtonEnabled(true);
    formLayout->addRow(tr("&URL:"), urlLineEdit);

    QString downloadDirectory = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    if(downloadDirectory.isEmpty() || !QFileInfo(downloadDirectory).isDir())                     // QFileInfo(QString& ).isDir()
        downloadDirectory = QDir::currentPath();

    downloadDirectoryLineEdit->setText(QDir::toNativeSeparators(downloadDirectory));             // QString QDir::toNativeSeparators(QString)
    formLayout->addRow(tr("&Download directory:"), downloadDirectoryLineEdit);
    formLayout->addRow(tr("Default &file:")      , defaultFileLineEdit);
    launchCheckBox->setChecked(true);
    formLayout->addRow(launchCheckBox);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));

    statusLabel->setWordWrap(true);
    mainLayout->addWidget(statusLabel);

    downloadButton->setDefault(true);

    QPushButton* quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);

    QDialogButtonBox* buttonBox = new QDialogButtonBox;
    buttonBox->addButton(downloadButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton    , QDialogButtonBox::RejectRole);
    mainLayout->addWidget(buttonBox);

    urlLineEdit->setFocus();

/* ------- connection ------- */

    connect(&qnam, &QNetworkAccessManager::authenticationRequired,                                // QNetworkAccessManager::authenticationRequired(QNetworkReply* , QAuthenticator* )
            this , &HttpWindow::slotAuthenticationRequired);

#ifndef QT_NO_SSL
    connect(&qnam, &QNetworkAccessManager::sslErrors,
            this , &HttpWindow::sslErrors);
#endif

    connect(urlLineEdit   , &QLineEdit::textChanged,
            this          , &HttpWindow::enableDownloadButton);

    connect(downloadButton, &QAbstractButton::clicked,
            this          , &HttpWindow::downloadFiles);

    connect(quitButton    , &QAbstractButton::clicked,
            this          , &QWidget::close);
}


HttpWindow::~HttpWindow()
{
}


void HttpWindow::startRequest(const QUrl& requestedUrl)
{
    url                = requestedUrl;
    httpRequestAborted = false;

    reply              = qnam.get(QNetworkRequest(url));

    ProgressDialog* progressDialog = new ProgressDialog(url, this);
    progressDialog->setAttribute(Qt::WA_DeleteOnClose);

/* ------- connection ------- */

    connect(reply         , &QNetworkReply::finished,
            this          , &HttpWindow::httpFinished);

    connect(reply         , &QIODevice::readyRead,
            this          , &HttpWindow::httpReadyRead);

    connect(progressDialog, &QProgressDialog::canceled,
            this          , &HttpWindow::cancelDownload);

    connect(reply         , &QNetworkReply::downloadProgress,           // void QNetworkReply::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
            progressDialog, &ProgressDialog::networkReplyProgress);

    connect(reply         , &QNetworkReply::finished,
            progressDialog, &ProgressDialog::hide);

/* ------- ------- */

    progressDialog->show();

    statusLabel->setText(tr("Downloading %1...").arg(url.toString()));  // QString QUrl::toString()
}


void HttpWindow::downloadFiles()
{
    const QString urlSpec = urlLineEdit->text().trimmed();                                        // QString QString::trimmed() trim whitespaces from the start and the end.
    if(urlSpec.isEmpty())
        return;

    const QUrl newUrl = QUrl::fromUserInput(urlSpec);                                             // QUrl    QUrl::fromUserInput(QString& ) generate QUrl objects from QString objects.
    if(!newUrl.isValid()){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid URL: %1 : %2").arg(urlSpec, newUrl.errorString()));  // whenever QUrl::isValid() returns false, there will be a errorString
        return;
    }

    QString fileName = newUrl.fileName();                                                         /* QString QUrl::fileName()
                                                                                                         if the url is ended with a slash, an empty string is returned.
                                                                                                         else it returns the file name excluding the dorectory path     */
    if(fileName.isEmpty())
        fileName = defaultFileLineEdit->text().trimmed();
    if(fileName.isEmpty())
        fileName = defaultFileName;
    QString downloadDirectory = QDir::cleanPath(downloadDirectoryLineEdit->text().trimmed());     // QString QDir::cleanPath(QString& ) parse and resolve the path, modify it.
    bool    useDirectory      = !downloadDirectory.isEmpty() && QFileInfo(downloadDirectory).isDir();
    if(useDirectory)
        fileName.prepend(downloadDirectory + '/');
    if(QFile::exists(fileName)){
        /* QMessageBox::StandardButton QMessageBox::question(QObject*                    parent,
         *                                                   const QString&              title,
         *                                                   const QString&              text,
         *                                                   QMessageBox::StandardButton buttons       = QMessageBox::Yes | QMessageBox::No,
         *                                                   QMessageBox::StandardButton defaultButton = QMessageBox::No)
         */
        if(QMessageBox::question(this,
                                 tr("Overwrite existing file"),
                                 tr("There already exists a file called %1%2.""Overwrite?").arg(fileName,
                                                                                                useDirectory? QString() : QStringLiteral("in the current directory")),
                                 QMessageBox::Yes | QMessageBox::No,
                                 QMessageBox::No)
           == QMessageBox::No){ return; }
        QFile::remove(fileName);
    }

    file = openFileForWrite(fileName);
    if(!file){ return; }

    downloadButton->setEnabled(false);

    startRequest(newUrl);
}


QFile* HttpWindow::openFileForWrite(const QString& fileName)
{
    QScopedPointer<QFile> file(new QFile(fileName));              // QScopedPointer<T> obj(T* ) makes sure the object will be deleted when the current scope disappear.
    if(!file->open(QIODevice::WriteOnly)){                        // bool QFile::open(QIODevice::OpenMode openMode)
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Unable to save the file %1: %2").arg(QDir::toNativeSeparators(fileName),
                                                                          file->errorString()));
        return nullptr;
    }

    return file.take();                                           // T*   QScopedPointer<T>::take()                    returns the original pointer, the pointer of the QScopedPointer object will be reset to nullptr.
                                                                  // void QScopedPointer<T>::reset(T* other = nullptr) deletes current pointer in the QScopedPointer object, and set the other to its new pointer.
}


void HttpWindow::cancelDownload()
{
    statusLabel->setText(tr("Download canceled"));
    httpRequestAborted = true;
    reply->abort();                                 // void QNetworkReply::abort()
    downloadButton->setEnabled(true);
}


void HttpWindow::httpFinished()
{
    QFileInfo fi;
    if(file){
        fi.setFile(file->fileName());                                                   /* QString QFile::fileName()

                                                                                           QFileInfo::setFile()      */
        file->close();                                                                  // QFile::close()
        delete file;
        file = nullptr;
    }

    if(httpRequestAborted){
        reply->deleteLater();
        reply = nullptr;
        return;
    }

    if(reply->error()){
        QFile::remove(fi.absoluteFilePath());                                           // QString QFileInfo::absoluteFilePath()
        statusLabel->setText(tr("Download failed:\n%1.").arg(reply->errorString()));
        downloadButton->setEnabled(true);
        reply->deleteLater();
        reply = nullptr;
        return;
    }

    /* QVariant QNetworkReply::attribute(QNetworkRequest::Attribute )

       QNetworkRequest::Attribute :
           ( int )       QNetworkRequest::HttpStatusCodeAttribute    -> status clodes like 404, 200, 500.
           ( QByteArray )QNetworkRequest::HttpReasonPhraseAttribute  -> human readable status strings like "not found", "access denied".
           ( QUrl )      QNetworkRequest::RedirectionTargetAttribute -> redirection url.
    */
    const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    reply->deleteLater();
    reply = nullptr;

    if(!redirectionTarget.isNull()){
        const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());             /* QUrl QUrl::resolved(const QUrl& relative) converts relative url to absolute url like :
                                                                                               QUrl baseUrl("http://www.reidblog.cn/");
                                                                                               baseUrl.resolved(QUrl("../blog/"));      -> http://www.reidblog.cn/blog/

                                                                                           QUrl QVariant::toUrl()                                                                  */
        if(QMessageBox::question(this,
                                 tr("Redirect"),
                                 tr("Redirect to %1 ?").arg(redirectedUrl.toString()),
                                 QMessageBox::Yes | QMessageBox::No,
                                 QMessageBox::No)
           == QMessageBox::No){
            QFile::remove(fi.absoluteFilePath());
            downloadButton->setEnabled(true);
            statusLabel->setText(tr("Download failed:\nRedirect rejected."));
            return;
        }
        file = openFileForWrite(fi.absoluteFilePath());
        if(!file){
            downloadButton->setEnabled(true);
            return;
        }
        startRequest(redirectedUrl);
        return;
    }

    statusLabel->setText(tr("Downloaded %1 bytes to %2\nin\n%3").arg(fi.size()).arg(fi.fileName()).arg(QDir::toNativeSeparators(fi.absolutePath())));
    if(launchCheckBox->isChecked())
        QDesktopServices::openUrl(QUrl::fromLocalFile(fi.absoluteFilePath()));            /* bool QDesktopServices::openUrl(const QUrl& )
                                                                                             QUrl QUrl::fromLocalFile(const QString& ) : /someFile -> file:///someFile */
    downloadButton->setEnabled(true);
}


void HttpWindow::httpReadyRead()
{
    if(file)
        file->write(reply->readAll());
}


void HttpWindow::enableDownloadButton()
{
    downloadButton->setEnabled(!urlLineEdit->text().isEmpty());
}


void HttpWindow::slotAuthenticationRequired(QNetworkReply* , QAuthenticator* authenticator)
{
    QDialog authenticationDialog;
    Ui::Dialog ui;
    ui.setupUi(&authenticationDialog);
    authenticationDialog.adjustSize();
    ui.siteDescription->setText(tr("%1 at %2").arg(authenticator->realm(),
                                                   url.host()));
    ui.userEdit->setText(url.userName());
    ui.passwordEdit->setText(url.password());

    if(authenticationDialog.exec() == QDialog::Accepted){
        authenticator->setUser(ui.userEdit->text());
        authenticator->setPassword(ui.passwordEdit->text());
    }
}


#ifndef QT_NO_SSL
void HttpWindow::sslErrors(QNetworkReply* , const QList<QSslError>& errors)
{
    QString errorString;
    foreach(const QSslError& error, errors){
        if(!errorString.isEmpty())
            errorString += '\n';
        errorString += error.errorString();
    }

    if(QMessageBox::warning(this,
                            tr("SSL Errors"),
                            tr("One or more SSL errors has occured:\n%1").arg(errorString),
                            QMessageBox::Ignore | QMessageBox::Abort)
       == QMessageBox::Ignore){
        reply->ignoreSslErrors();
    }
}
#endif
