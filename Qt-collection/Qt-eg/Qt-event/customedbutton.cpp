#include "customedbutton.h"
#include <QDebug>  //include it here so no need in .h file.
#include <QMouseEvent>


customedButton::customedButton(QWidget* parent):QPushButton(parent)  //init with QPushButton(parent), body down there is what you want to add.
{
    connect(this,&customedButton::clicked,this,&customedButton::buttonClicked);  //connect in class has no need for 'QObject::'
}


void customedButton::buttonClicked()  //specify return-type in implementation file.
{
    qDebug()<<"button clicked";  //qDebug() not qDebug
}


/*1. QPushButton::mousePressEvent(QEvent*) triggers QPushButton::clicked(),
     and if QPushButton::clicked() is connected to other functions, they are triggered too.

  2. if you want to do something before event triggers other functions, overload it.*/
void customedButton::mousePressEvent(QMouseEvent* event)  //no 'virtual' declaration outside the class
{
    if(event->button() == Qt::LeftButton) //Qt::LeftButton is pre-defined
    {
        qDebug()<<"left";
    }
    else
    {
        QPushButton::mousePressEvent(event);/*in a overload function,
                                              always think about condition that overload has no use,
                                              that's where we need to call the original function.*/
    }
}
