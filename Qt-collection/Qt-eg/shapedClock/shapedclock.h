#ifndef SHAPEDCLOCK_H
#define SHAPEDCLOCK_H

#include <QWidget>
#include <QPoint>
#include<QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>

namespace Ui {
class ShapedClock;
}

class ShapedClock : public QWidget
{
    Q_OBJECT

public:
    explicit ShapedClock(QWidget *parent = 0);
    ~ShapedClock();

    QSize sizeHint() const override;

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::ShapedClock *ui;

    QPoint dragPosition;
};

#endif // SHAPEDCLOCK_H
