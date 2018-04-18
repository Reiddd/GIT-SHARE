#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent> //must include

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    but=new QPushButton(this); /*QPushButton(QWidget*)*/
    but->setText("close"); /*QPushButton::setText("text on button")*/
    connect(but,&QPushButton::clicked,this,&MainWindow::close); /*&QPushButton::clicked | &MainWindow::close
                                                                  '&className::funcName' works,
                                                                  'SIGNAL(funcName()) doesn't work.*/
    setStyleSheet("background:red"); /*QWidget::setStyleSheet(QString styleSheet)
                                       styleSheet : color:red', like this form.*/
    setWindowFlags(Qt::WindowMinMaxButtonsHint); /*only keep max\min icons
                                                   'Qt::WindowCloseButtonHint' only keep the close icon*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    last=event->globalPos(); /*QMouseEvent::globalPos() return a QPoint object*/
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->globalX() - last.x(); /*QMouseEvent::globalX() return current cursor's x_axis*/
    int dy = event->globalY() - last.y(); /*QMouseEvent::globalY() return current cursor's y_axis*/

    move(last.x() + dx, last.y() + dy);  /*QWidget::move(chosen_point_x, chosen_point_y)*/
    last = event->globalPos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    int dx = event->globalX() - last.x();
    int dy = event->globalY() - last.y();
    move(last.x() + dx, last.y() + dy);
}
