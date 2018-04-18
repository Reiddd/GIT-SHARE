#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    /*set window's title*/
    setWindowTitle(tr("Main Window"));


    /*set up action object*/
    QAction* openAction = new QAction(tr("&Open..."),this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Opening an exist file"));
    QObject::connect(openAction,&QAction::triggered,this,&MainWindow::open);


    /*add action to menubar*/
    QMenu* file = menuBar()->addMenu(tr("&File"));/*menuBar return (current_menuBar exist)?current_menuBar:new_menuBar
                                                    a mainwindow could only has one menuBar, so menuBar() instead of addMenuBar()*/
    file->addAction(openAction);


    /*add action to toolbar*/
    QToolBar* toolBar = addToolBar(tr("&File"));/*a mainwindow could has multiple toolbars, so addToolBar() instead of toolBar()*/
    toolBar->addAction(openAction);


    statusBar();/*a mainindow could only has one statusbar, so statusBar() instead of addStatusBar()*/
}


void MainWindow::open()
{
    QDialog dialog(this); //specify 'this' to make the dialog share window with parent
    dialog.setWindowTitle(tr("it's a dialog"));
    if(dialog.exec() == QDialog::Accepted)//not show(), or it will jump out and dispear quickly.
    {
        qDebug()<<dialog.result();
    }//if makes sure the dialog is confirmed not canceled.
}


MainWindow::~MainWindow()
{
    delete ui;
}
