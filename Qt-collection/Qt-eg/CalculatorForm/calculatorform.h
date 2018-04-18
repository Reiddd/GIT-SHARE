#ifndef CALCULATORFORM_H
#define CALCULATORFORM_H

#include "ui_calculatorform.h"  /*linked to class name*/

#include <QWidget>

namespace Ui {
class CalculatorForm;
}

class CalculatorForm : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorForm(QWidget *parent = 0);

private:
    Ui::CalculatorForm ui;  /*not pointer*/

private slots:
    void on_inputSpinBox1_valueChanged(int value); /*auto connection : void on_<widget_name>_<signal_name>(signal)*/

    void on_inputSpinBox2_valueChanged(int value);
};

#endif // CALCULATORFORM_H
