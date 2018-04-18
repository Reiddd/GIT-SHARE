#include "mainwindow.h"
#include <QApplication>
#include <QSpinBox>
#include <QSlider>
#include <QLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    /*create a widget*/
    QWidget win;
    win.setWindowTitle("Enter your age");


    /*create a spinbox with value between 0 and 100*/
    QSpinBox* spinBox = new QSpinBox(&win);
    spinBox->setRange(0,100);


    /*create a slider with value between 0 and 100*/
    QSlider* slider = new QSlider(Qt::Horizontal,&win);
    slider->setRange(0,100);


    /*connect two functions
      they both have signal valueChanged and slot setValue.
      QSpinBox::valueChanged has two version : QSpinBox::valueChanged(int)
                                               QSpinBox::valueChanged(const QString&)*/
    QObject::connect(slider,&QSlider::valueChanged,spinBox,&QSpinBox::setValue);
    void (QSpinBox::*alias)(int) = &QSpinBox::valueChanged;/*pointers pointing to class member function needs to add class name before it when declaring,
                                                             but no need for it when using it.
                                                             (return_tyoe)(*function_name) = &func_name;
                                                             (return_type)(class_name::*function_name)(arg_type1,...argn_type) = &func_name*/
    QObject::connect(spinBox,alias,slider,&QSlider::setValue);
    spinBox->setValue(35);


    /*layout: QHBoxLayout (horizontal)
              QVBoxLayout (vertical)
              QGridLayout
              QFormLayout
              QStackedLayout (most tutorials' stack form)
      step:
              1. declare a layout object.
              2. add widgets to layout.
              3. set window to chosen layout(no need for .show() to each object)*/
    QHBoxLayout* hlayout = new QHBoxLayout;//no parentheses
    hlayout->addWidget(spinBox);
    hlayout->addWidget(slider);
    win.setLayout(hlayout);


    win.show();


    return a.exec();
}
