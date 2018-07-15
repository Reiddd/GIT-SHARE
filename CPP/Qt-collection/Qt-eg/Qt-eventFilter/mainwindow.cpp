#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    /*set a texteditor to the center*/
    textEditor = new QTextEdit;
    setCentralWidget(textEditor);

    /*1. set an eventFilter to editor
         object_pointer -> installEventFilter(this)

      2. if more than one eventFilter are installed on an object, the last installed is the first executed.*/
    textEditor->installEventFilter(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


/*overload QMainWindows::eventFilter(QObject* , QEvent* )*/
bool MainWindow::eventFilter(QObject* obj,QEvent* event) //contains if-else to filter out event not on obj.
{
    if(obj==textEditor)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            qDebug()<<"ate key press: "<<keyEvent->text();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return QMainWindow::eventFilter(obj,event);  //always link other conditions to function before overload.
    }
}
