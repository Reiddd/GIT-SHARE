#include "images.h"
#include "ui_images.h"

#include <QtAlgorithms>                                            // qDeleteAll()

Images::Images(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(tr("Image loading and scaling example"));
    resize(800, 600);


// QFutureWatcher<QImage>
    imageScaling = new QFutureWatcher<QImage>(this);               // QFutureWatcher<typename>::QFutureWatcher(QObject* parent = nullptr)
    connect(imageScaling, &QFutureWatcher<QImage>::resultReadyAt,  // QFutureWatcher<typename>::resultReadyAt(int index) is a signal.
            this        , &Images::showImage);
    connect(imageScaling, &QFutureWatcher<QImage>::finished,       // QFutureWatcher<typename>::finished() is a signal.
            this        , &Images::finished);


// Button
    openButton = new QPushButton(tr("Open Images"));
    connect(openButton, &QPushButton::clicked,
            this      , &Images::open);


    cancelButton = new QPushButton(tr("Cancel"));
    cancelButton->setEnabled(false);                               // QPushButton::setEnabled(bool) controls whether this button could be clicked.
    connect(cancelButton, &QPushButton::clicked,                   // QFutureWatcher<typename>::cancel() cancels the asynchronous computation.
            imageScaling, &QFutureWatcher<QImage>::cancel);        // add QFutureWatcher<typename>::waitForFinished() for synchronous cancelation.


    pauseButton = new QPushButton(tr("Pause/Resume"));
    pauseButton->setEnabled(false);
    connect(pauseButton , &QPushButton::clicked,                   // QFutureWatcher<typename>::togglePaused() stops the thread if it's working, resumes it if it's stopped.
            imageScaling, &QFutureWatcher<QImage>::togglePaused);


// Layout
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(openButton) ;
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addStretch();                                    // QBoxLayout::addStretch(int stretch = 0) adds a stretchable space into the layout.

    imagesLayout = new QGridLayout();
    mainLayout   = new QVBoxLayout();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(imagesLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);
}


Images::~Images()
{
    imageScaling->cancel();
    imageScaling->waitForFinished();                               // for synchronous conditions.
}


void Images::open()
{
    if(imageScaling->isRunning()){
        imageScaling->cancel();
        imageScaling->waitForFinished();
    }

    /*
       QStringList is QList<QString>
       QFileDialog::getOpenFileNames()
       QStandardPaths::writableLocation()
       QStandardPaths::PicturesLocation || QStandardPaths::DocumentsLocation || QStandardPaths::DownloadLocation */
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Select Images"),
                                                      QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                                                      "*.jpg *.png");

    if(files.isEmpty()) return;

    const int imageSize = 100;

    /*
       qDeleteAll(const container&) equals qDeleteAll(iterator front, iterator back)
       it merely deletes items in the container but doesn't remove them.
       to remove items, call container.clear()
    */
    qDeleteAll(labels);
    labels.clear();

    int dim = qSqrt(qreal(files.count())) + 1;                     // QList.count() || QList.count(value)
    for(int i=0; i<dim; i++)
        for(int j=0; j<dim; j++){
            QLabel* imageLabel = new QLabel;
            imageLabel->setFixedSize(imageSize, imageSize);
            imagesLayout->addWidget(imageLabel, i, j);
            labels.append(imageLabel);
        }

    /*
       std::function<return_type(arg_type, ...)>
    */
    std::function<QImage(const QString&)> scale = [imageSize](const QString& imageFileName){
        QImage image(imageFileName);
        return image.scaled(QSize(imageSize, imageSize), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    };

    /*
       QFuture<T> QtConcurrent::mapped(sequence, function)
       use QFutureIterator || QFuture::const_iterator to iterate through the results.

       in Qt, future could be a series.
    */
    imageScaling->setFuture(QtConcurrent::mapped(files, scale));

    openButton->setEnabled(false);
    cancelButton->setEnabled(true);
    pauseButton->setEnabled(true);
}


void Images::showImage(int num)
{
    labels[num]->setPixmap(QPixmap::fromImage(imageScaling->resultAt(num)));
}


void Images::finished()
{
    openButton->setEnabled(true);
    cancelButton->setEnabled(false);
    pauseButton->setEnabled(false);
}
