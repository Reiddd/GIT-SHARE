#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*QLineEdit
      for user to enter an path*/
    lineedit = new QLineEdit(this);
    lineedit->setGeometry(QRect(50,50,200,25));
    lineedit->setText("/");

    /*QPushButton
      for user to confirm after enter*/
    button = new QPushButton(this);
    button->setGeometry(QRect(280,50,80,25));
    button->setText("create");

    connect(button,&QPushButton::clicked,this,&MainWindow::createFolder);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createFolder()
{
    /*QDir
      provide folder munipulation*/
    QDir* folder = new QDir;/*default init*/


    bool isexist = folder->exists(lineedit->text());/*QDir::exists(QString)*/
    if(isexist)
    {
        /*QMessageBox::warning(QWidget* ,QString& windowname, QString& content)*/
        QMessageBox::warning(this,tr("create a folder"),tr("folder already exist!"));
    }
    else
    {
        bool isok = folder->mkdir(lineedit->text())/*QDir::mkdir(QString)*/
        if(isok)
        {
            QMessageBox::warning(this,tr("create a folder"),tr("success!"));
        }
        else
        {
            QMessageBox::warning(this,tr("creater a folder"),tr("fail!"));
        }
    }
}
