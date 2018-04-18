/********************************************************************************
** Form generated from reading UI file 'analogclock.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALOGCLOCK_H
#define UI_ANALOGCLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_analogClock
{
public:
    QLabel *label;

    void setupUi(QWidget *analogClock)
    {
        if (analogClock->objectName().isEmpty())
            analogClock->setObjectName(QStringLiteral("analogClock"));
        analogClock->resize(200, 200);
        analogClock->setMinimumSize(QSize(200, 200));
        analogClock->setMaximumSize(QSize(200, 200));
        label = new QLabel(analogClock);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(55, 120, 121, 41));
        QFont font;
        font.setPointSize(14);
        font.setItalic(true);
        label->setFont(font);

        retranslateUi(analogClock);

        QMetaObject::connectSlotsByName(analogClock);
    } // setupUi

    void retranslateUi(QWidget *analogClock)
    {
        analogClock->setWindowTitle(QApplication::translate("analogClock", "analogClock", 0));
        label->setText(QApplication::translate("analogClock", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class analogClock: public Ui_analogClock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALOGCLOCK_H
