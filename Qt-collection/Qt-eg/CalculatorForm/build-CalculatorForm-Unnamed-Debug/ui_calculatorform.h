/********************************************************************************
** Form generated from reading UI file 'calculatorform.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATORFORM_H
#define UI_CALCULATORFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalculatorForm
{
public:
    QSpinBox *inputSpinBox1;
    QLabel *label;
    QSpinBox *inputSpinBox2;
    QLabel *label_2;
    QLabel *outputWidget;

    void setupUi(QWidget *CalculatorForm)
    {
        if (CalculatorForm->objectName().isEmpty())
            CalculatorForm->setObjectName(QStringLiteral("CalculatorForm"));
        CalculatorForm->resize(400, 300);
        inputSpinBox1 = new QSpinBox(CalculatorForm);
        inputSpinBox1->setObjectName(QStringLiteral("inputSpinBox1"));
        inputSpinBox1->setGeometry(QRect(20, 100, 81, 31));
        label = new QLabel(CalculatorForm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(120, 100, 67, 17));
        inputSpinBox2 = new QSpinBox(CalculatorForm);
        inputSpinBox2->setObjectName(QStringLiteral("inputSpinBox2"));
        inputSpinBox2->setGeometry(QRect(160, 100, 71, 31));
        label_2 = new QLabel(CalculatorForm);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(260, 100, 67, 17));
        outputWidget = new QLabel(CalculatorForm);
        outputWidget->setObjectName(QStringLiteral("outputWidget"));
        outputWidget->setGeometry(QRect(330, 100, 67, 17));

        retranslateUi(CalculatorForm);

        QMetaObject::connectSlotsByName(CalculatorForm);
    } // setupUi

    void retranslateUi(QWidget *CalculatorForm)
    {
        CalculatorForm->setWindowTitle(QApplication::translate("CalculatorForm", "CalculatorForm", 0));
        inputSpinBox1->setSuffix(QString());
        label->setText(QApplication::translate("CalculatorForm", "+", 0));
        label_2->setText(QApplication::translate("CalculatorForm", "=", 0));
        outputWidget->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CalculatorForm: public Ui_CalculatorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATORFORM_H
