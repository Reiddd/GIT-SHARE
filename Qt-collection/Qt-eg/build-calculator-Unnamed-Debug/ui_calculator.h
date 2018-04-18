/********************************************************************************
** Form generated from reading UI file 'calculator.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATOR_H
#define UI_CALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Calculator
{
public:
    QPushButton *numButton1;
    QPushButton *numButton2;
    QPushButton *numButton3;
    QPushButton *numButton4;
    QPushButton *numButton5;
    QPushButton *numButton6;
    QPushButton *numButton7;
    QPushButton *numButton8;
    QPushButton *numButton9;
    QPushButton *numButton0;
    QLabel *textedit;
    QWidget *widget;
    QLabel *result;
    QPushButton *plusButton;
    QPushButton *minusButton;
    QPushButton *timeButton;
    QPushButton *divideButton;
    QPushButton *ACButton;
    QPushButton *DELButton;
    QPushButton *leftPButton;
    QPushButton *rightPButton;
    QPushButton *dotButton;

    void setupUi(QWidget *Calculator)
    {
        if (Calculator->objectName().isEmpty())
            Calculator->setObjectName(QStringLiteral("Calculator"));
        Calculator->resize(481, 460);
        numButton1 = new QPushButton(Calculator);
        numButton1->setObjectName(QStringLiteral("numButton1"));
        numButton1->setGeometry(QRect(20, 220, 80, 40));
        numButton2 = new QPushButton(Calculator);
        numButton2->setObjectName(QStringLiteral("numButton2"));
        numButton2->setGeometry(QRect(120, 220, 80, 40));
        numButton3 = new QPushButton(Calculator);
        numButton3->setObjectName(QStringLiteral("numButton3"));
        numButton3->setGeometry(QRect(220, 220, 80, 40));
        numButton4 = new QPushButton(Calculator);
        numButton4->setObjectName(QStringLiteral("numButton4"));
        numButton4->setGeometry(QRect(20, 280, 80, 40));
        numButton5 = new QPushButton(Calculator);
        numButton5->setObjectName(QStringLiteral("numButton5"));
        numButton5->setGeometry(QRect(120, 280, 80, 40));
        numButton6 = new QPushButton(Calculator);
        numButton6->setObjectName(QStringLiteral("numButton6"));
        numButton6->setGeometry(QRect(220, 280, 80, 40));
        numButton7 = new QPushButton(Calculator);
        numButton7->setObjectName(QStringLiteral("numButton7"));
        numButton7->setGeometry(QRect(20, 340, 80, 40));
        numButton8 = new QPushButton(Calculator);
        numButton8->setObjectName(QStringLiteral("numButton8"));
        numButton8->setGeometry(QRect(120, 340, 80, 40));
        numButton9 = new QPushButton(Calculator);
        numButton9->setObjectName(QStringLiteral("numButton9"));
        numButton9->setGeometry(QRect(220, 340, 80, 40));
        numButton0 = new QPushButton(Calculator);
        numButton0->setObjectName(QStringLiteral("numButton0"));
        numButton0->setGeometry(QRect(120, 400, 80, 40));
        textedit = new QLabel(Calculator);
        textedit->setObjectName(QStringLiteral("textedit"));
        textedit->setEnabled(true);
        textedit->setGeometry(QRect(30, 40, 341, 61));
        QFont font;
        font.setPointSize(16);
        font.setItalic(true);
        textedit->setFont(font);
        widget = new QWidget(Calculator);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 20, 441, 131));
        widget->setAutoFillBackground(false);
        widget->setStyleSheet(QStringLiteral("background:rgb(255, 255, 255)"));
        result = new QLabel(widget);
        result->setObjectName(QStringLiteral("result"));
        result->setGeometry(QRect(266, 96, 171, 31));
        plusButton = new QPushButton(Calculator);
        plusButton->setObjectName(QStringLiteral("plusButton"));
        plusButton->setGeometry(QRect(340, 390, 50, 50));
        minusButton = new QPushButton(Calculator);
        minusButton->setObjectName(QStringLiteral("minusButton"));
        minusButton->setGeometry(QRect(400, 390, 50, 50));
        timeButton = new QPushButton(Calculator);
        timeButton->setObjectName(QStringLiteral("timeButton"));
        timeButton->setGeometry(QRect(340, 330, 50, 50));
        divideButton = new QPushButton(Calculator);
        divideButton->setObjectName(QStringLiteral("divideButton"));
        divideButton->setGeometry(QRect(400, 330, 50, 50));
        ACButton = new QPushButton(Calculator);
        ACButton->setObjectName(QStringLiteral("ACButton"));
        ACButton->setGeometry(QRect(340, 170, 50, 50));
        DELButton = new QPushButton(Calculator);
        DELButton->setObjectName(QStringLiteral("DELButton"));
        DELButton->setGeometry(QRect(400, 170, 50, 50));
        leftPButton = new QPushButton(Calculator);
        leftPButton->setObjectName(QStringLiteral("leftPButton"));
        leftPButton->setGeometry(QRect(20, 400, 35, 40));
        rightPButton = new QPushButton(Calculator);
        rightPButton->setObjectName(QStringLiteral("rightPButton"));
        rightPButton->setGeometry(QRect(65, 400, 35, 40));
        dotButton = new QPushButton(Calculator);
        dotButton->setObjectName(QStringLiteral("dotButton"));
        dotButton->setGeometry(QRect(220, 400, 35, 40));
        numButton1->raise();
        numButton2->raise();
        numButton3->raise();
        numButton4->raise();
        numButton5->raise();
        numButton6->raise();
        numButton7->raise();
        numButton8->raise();
        numButton9->raise();
        numButton0->raise();
        widget->raise();
        plusButton->raise();
        minusButton->raise();
        timeButton->raise();
        divideButton->raise();
        textedit->raise();
        ACButton->raise();
        DELButton->raise();
        leftPButton->raise();
        rightPButton->raise();
        dotButton->raise();

        retranslateUi(Calculator);

        QMetaObject::connectSlotsByName(Calculator);
    } // setupUi

    void retranslateUi(QWidget *Calculator)
    {
        Calculator->setWindowTitle(QApplication::translate("Calculator", "Calculator", 0));
        numButton1->setText(QApplication::translate("Calculator", "1", 0));
        numButton1->setShortcut(QApplication::translate("Calculator", "1", 0));
        numButton2->setText(QApplication::translate("Calculator", "2", 0));
        numButton2->setShortcut(QApplication::translate("Calculator", "2", 0));
        numButton3->setText(QApplication::translate("Calculator", "3", 0));
        numButton3->setShortcut(QApplication::translate("Calculator", "3", 0));
        numButton4->setText(QApplication::translate("Calculator", "4", 0));
        numButton4->setShortcut(QApplication::translate("Calculator", "4", 0));
        numButton5->setText(QApplication::translate("Calculator", "5", 0));
        numButton5->setShortcut(QApplication::translate("Calculator", "5", 0));
        numButton6->setText(QApplication::translate("Calculator", "6", 0));
        numButton6->setShortcut(QApplication::translate("Calculator", "6", 0));
        numButton7->setText(QApplication::translate("Calculator", "7", 0));
        numButton7->setShortcut(QApplication::translate("Calculator", "7", 0));
        numButton8->setText(QApplication::translate("Calculator", "8", 0));
        numButton8->setShortcut(QApplication::translate("Calculator", "8", 0));
        numButton9->setText(QApplication::translate("Calculator", "9", 0));
        numButton9->setShortcut(QApplication::translate("Calculator", "9", 0));
        numButton0->setText(QApplication::translate("Calculator", "0", 0));
        numButton0->setShortcut(QApplication::translate("Calculator", "0", 0));
        textedit->setText(QString());
        result->setText(QString());
        plusButton->setText(QApplication::translate("Calculator", "+", 0));
        plusButton->setShortcut(QApplication::translate("Calculator", "+", 0));
        minusButton->setText(QApplication::translate("Calculator", "-", 0));
        minusButton->setShortcut(QApplication::translate("Calculator", "-", 0));
        timeButton->setText(QApplication::translate("Calculator", "x", 0));
        timeButton->setShortcut(QApplication::translate("Calculator", "*", 0));
        divideButton->setText(QApplication::translate("Calculator", "/", 0));
        divideButton->setShortcut(QApplication::translate("Calculator", "/", 0));
        ACButton->setText(QApplication::translate("Calculator", "AC", 0));
        ACButton->setShortcut(QApplication::translate("Calculator", "Del", 0));
        DELButton->setText(QApplication::translate("Calculator", "DEL", 0));
        DELButton->setShortcut(QApplication::translate("Calculator", "Backspace", 0));
        leftPButton->setText(QApplication::translate("Calculator", "(", 0));
        leftPButton->setShortcut(QApplication::translate("Calculator", "(", 0));
        rightPButton->setText(QApplication::translate("Calculator", ")", 0));
        rightPButton->setShortcut(QApplication::translate("Calculator", ")", 0));
        dotButton->setText(QApplication::translate("Calculator", ".", 0));
        dotButton->setShortcut(QApplication::translate("Calculator", ".", 0));
    } // retranslateUi

};

namespace Ui {
    class Calculator: public Ui_Calculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_H
