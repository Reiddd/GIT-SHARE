#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene;

    /*QGraphicsScene::setForegroundBrush(QColor())*/
    scene->setForegroundBrush(QColor(0,255,255,127));

    /*QGraphicsScene::addSimpleText()*/
    scene->addSimpleText("test");

    /*QGraphicsView::QGraphicsView(QGraphicsScene* )*/
    view = new QGraphicsView(scene);
    this->setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}
