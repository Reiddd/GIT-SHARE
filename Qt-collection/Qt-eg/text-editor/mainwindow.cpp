#include "mainwindow.h"
#include "ui_mainwindow.h"

/*GUI*/
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QMessageBox>

/*FILE*/
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*openAction*/
    QAction* openAction = new QAction(tr("open..."),this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("open an exist file"));

    connect(openAction,SIGNAL(QAction::triggered()),this,SLOT(openfile()));


    /*saveAction*/
    QAction* saveAction = new QAction(tr("save..."),this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("save the file"));

    connect(saveAction,SIGNAL(QAction::triggered()),this,SLOT(MainWindow::saveFile()));


    /*menuBar*/
    QMenu* fileMenu = menuBar()->addMenu(tr("files"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);


    /*statusBar*/
    statusBar();


    /*textEditor*/
    textEditor = new QTextEdit(this);
    setCentralWidget(textEditor);//set editor to the centre
}

void MainWindow::openfile()
{
    QFileDialog dia(this,tr("open file:"),"/home");
    QString path = dia.getOpenFileName(this,tr("open file:"),"/home",tr("Text Files(*.txt)"));
    if(!path.isEmpty())
    {
        QFile file(path);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            textEditor->setText(in.readAll());
            file.close();
        }
        else
        {
            QMessageBox::warning(this,tr("reading file"),tr("can not open file: \n%1").arg(path));
            return;
        }
    }
    else
    {
        QMessageBox::warning(this,tr("opening file"),tr("you did not select any files"));
    }
}

void MainWindow::savefile()
{

}


MainWindow::~MainWindow()
{
    delete ui;
}
