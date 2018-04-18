/********************************************************************************
** Form generated from reading UI file 'tetrixwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TETRIXWINDOW_H
#define UI_TETRIXWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TetrixWindow
{
public:

    void setupUi(QWidget *TetrixWindow)
    {
        if (TetrixWindow->objectName().isEmpty())
            TetrixWindow->setObjectName(QStringLiteral("TetrixWindow"));
        TetrixWindow->resize(400, 300);

        retranslateUi(TetrixWindow);

        QMetaObject::connectSlotsByName(TetrixWindow);
    } // setupUi

    void retranslateUi(QWidget *TetrixWindow)
    {
        TetrixWindow->setWindowTitle(QApplication::translate("TetrixWindow", "TetrixWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class TetrixWindow: public Ui_TetrixWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TETRIXWINDOW_H
