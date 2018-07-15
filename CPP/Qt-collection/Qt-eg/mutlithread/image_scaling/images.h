#ifndef IMAGES_H
#define IMAGES_H

#include <QtWidgets>
#include <QtConcurrent>

class Images : public QWidget
{
    Q_OBJECT

public:
    explicit Images(QWidget *parent = 0);
    ~Images();

public slots:
    void open();
    void showImage(int num);
    void finished();

private:
    QPushButton*            openButton;
    QPushButton*            cancelButton;
    QPushButton*            pauseButton;
    QVBoxLayout*            mainLayout;
    QList<QLabel*>          labels;
    QGridLayout*            imagesLayout;
    QFutureWatcher<QImage>* imageScaling;
};

#endif // IMAGES_H
