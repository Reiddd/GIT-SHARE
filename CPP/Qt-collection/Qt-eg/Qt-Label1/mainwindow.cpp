#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel> //include QLabel class

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //create a QLabel object
    QLabel *label = new QLabel(this);
    //label's text content
    label->setText("Hello World");
    //label's place
    label->setGeometry(QRect(50,50,200,25));/*QRect(arg1,arg2,arg3,arg4)
                                              arg1: x-axis-val
                                              arg2: y-axis-val
                                              arg3: QLabel object's width
                                              arg4: QLabel object's height*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
