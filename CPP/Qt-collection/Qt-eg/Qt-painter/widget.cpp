#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(800,600);
    setWindowTitle("Paint Demo");
}

Widget::~Widget()
{
    delete ui;
}


/*QPainter.save()
  QPainter.restore()
  QPainter.translate()
  QPainter.setWindow()
  QPainter.setViewport()
  */
void Widget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(10,10,50,100,Qt::red);

    painter.save();

    painter.translate(100,0);
    painter.fillRect(10,10,50,100,Qt::yellow);

    painter.restore();
    painter.save();

    painter.translate(300,0);
    painter.rotate(30);
    painter.fillRect(10,10,50,100,Qt::green);

    painter.restore();
    painter.save();

    painter.translate(400,0);
    painter.scale(2,3);
    painter.fillRect(10,10,50,100,Qt::blue);

    painter.restore();
    painter.save();

    painter.translate(600,0);
    painter.shear(0,1);
    painter.fillRect(10,10,50,100,Qt::cyan);

    painter.restore();
    painter.save();

    /*QPainter.setWindow() set window size, it won't change physical window but change the logical window, or in another word,
      it project physical pixel to logical pixel*/
    painter.setWindow(0,0,400,400);
    painter.translate(200,200);
    painter.fillRect(0,0,100,50,Qt::yellow);

    painter.restore();
    painter.save();

    /*QPainter.setViewport() slice a area out of pyhsical window, other munipulations after are only on the selected area*/
    painter.setViewport(0,300,400,600);
    painter.setWindow(0,0,400,300);
    painter.fillRect(0,0,100,50,Qt::cyan);

    painter.restore();
}
