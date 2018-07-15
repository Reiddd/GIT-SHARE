#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* )
{
    QPixmap image("/home/reid/Documents/Qt-collection/Qt-eg/Qt-GraphicsView/Qt-graphicsView-paintEvent/test.jpg");

    QPainter painter(this);
    painter.drawPixmap(20,20,400,700);
}
