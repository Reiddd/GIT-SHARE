/********************************************************************************
** Form generated from reading UI file 'shapedclock.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAPEDCLOCK_H
#define UI_SHAPEDCLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShapedClock
{
public:

    void setupUi(QWidget *ShapedClock)
    {
        if (ShapedClock->objectName().isEmpty())
            ShapedClock->setObjectName(QStringLiteral("ShapedClock"));
        ShapedClock->resize(400, 300);

        retranslateUi(ShapedClock);

        QMetaObject::connectSlotsByName(ShapedClock);
    } // setupUi

    void retranslateUi(QWidget *ShapedClock)
    {
        ShapedClock->setWindowTitle(QApplication::translate("ShapedClock", "ShapedClock", 0));
    } // retranslateUi

};

namespace Ui {
    class ShapedClock: public Ui_ShapedClock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAPEDCLOCK_H
