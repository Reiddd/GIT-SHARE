#ifndef MANDELBROTWIDGET_H
#define MANDELBROTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include "renderthread.h"

class MandelbrotWidget : public QWidget
{
    Q_OBJECT

private:
    RenderThread thread;
    QPixmap pixmap;
    QPoint pixmapOffset;
    QPoint lastDragPos;
    double centerX;
    double centerY;
    double pixmapScale;
    double curScale;

    void scroll(int deltaX, int deltaY);

public:
    MandelbrotWidget(QWidget *parent = 0);
    ~MandelbrotWidget();

protected:
    void paintEvent   (QPaintEvent*  event) override;
    void resizeEvent  (QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent*    event) override;
    void mousePressEvent  (QMouseEvent* event) override;
    void mouseMoveEvent   (QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
    void updatePixmap(const QImage& image, double scaleFactor);
    void zoom(double zoomFactor);
};

#endif // MANDELBROTWIDGET_H
