#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QPixmap>
#include <QBitmap>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(800,1300);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent* event)
{

    /*create a QPainter object with QWidget pointer pointing to widget*/
    QPainter painter(this);


    /*create a QPixmap object with a path
      create a QBitmap object with a path*/
    QPixmap pixmap("/home/reid/Pictures/Wallpapers/19s_by_wlop-dbsw09i.jpg");
    QBitmap bitmap("/home/reid/Pictures/Wallpapers/19s_by_wlop-dbsw09i.jpg");

    /*QPainter.drawPixmap(x_axis,y_axis,h_len,v_len,[QPixmap | QBitmap object])*/
    painter.drawPixmap(0,0,800,500,pixmap);
    painter.drawPixmap(0,500,800,500,bitmap);
}
