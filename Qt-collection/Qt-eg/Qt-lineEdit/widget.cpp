#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    lineEdit = new QLineEdit(this);
    lineEdit->setGeometry(QRect(100,100,200,25)); /*QRect(x_axis, y_axis, h_len, v_len)*/
    lineEdit->setStyleSheet("color:red;");

    lineEdit->setMaxLength(12);
    /*
     * QLineEdit::setEchoMode(QLineEdit::NoEcho) : no access to enter words in
     * QLineEdit::setEchoMode(QLineEdit::Password) : characters will be replaced by '*'
     */
    lineEdit->setText(tr("test"));
}

Widget::~Widget()
{
    delete ui;
    delete lineEdit;
}

