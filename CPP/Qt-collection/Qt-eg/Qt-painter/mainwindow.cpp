#include "mainwindow.h"
#include "ui_mainwindow.h"

class paintedWidget:public QWidget
{
    Q_OBJECT
public:
    paintedWidget(QWidget* parent):QWidget(parent)
    {
        resize(800,600);
        setWindowTitle("Paint Demo");
    }

protected:
    void paintEvent(QPaintEvent* event)
    {
        QPainter painter;
        painter.drawLine(80,100,650,500);
        painter.setPen(Qt::red);
        painter.drawRect(10,10,100,400);
        painter.setPen(QPen(Qt::green,5));
        painter.setBrush(Qt::blue);
        painter.drawEllipse(50,150,400,200);
    }
};
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
