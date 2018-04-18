#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

#include "ui_calculator.h"

#include <string.h>
#include <unordered_set>
using namespace std;

namespace Ui {
class Calculator;
}

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);

private:
    Ui::Calculator ui;

    string str; //store the expression
    double Result;  //store the result

    unordered_set<string> symbol{"+","-","x","/"};

    void on_numButton1_clicked();
    void on_numButton2_clicked();
    void on_numButton3_clicked();
    void on_numButton4_clicked();
    void on_numButton5_clicked();
    void on_numButton6_clicked();
    void on_numButton7_clicked();
    void on_numButton8_clicked();
    void on_numButton9_clicked();
    void on_numButton0_clicked();
    void on_dotButton_clicked();

    void on_leftPButton_clicked();
    void on_rightPButton_clicked();

    void on_plusButton_clicked();
    void on_minusButton_clicked();
    void on_timeButton_clicked();
    void on_divideButton_clicked();

    void on_ACButton_clicked();
    void on_DELButton_clicked();

    void event_after_clicked(string button);

    //-------
    string parseString(string& button);
    double calString(string str);
    string divideCalString(string str);

};

#endif // CALCULATOR_H
