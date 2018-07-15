#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    spinbox = new QSpinBox(this);
    spinbox->setGeometry(QRect(50,50,100,25));


    spinbox->setRange(0,100); /*range of the spinbox*/
    spinbox->setValue(50); /*init_value*/
    spinbox->setSuffix(" dollor"); /*suffix*/
    spinbox->setPrefix("$: "); /*prefix*/
}

Widget::~Widget()
{
    delete ui;
}
