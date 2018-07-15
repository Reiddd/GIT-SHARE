#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene;

    /*QGraphicsScene::addEllipse(qint32 x, qint32 y, qint32 width, qint32 height)*/
    scene->addEllipse(50,50,100,120);
    scene->addEllipse(50,50,120,100);

    view = new QGraphicsView(scene);

    this->setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}
