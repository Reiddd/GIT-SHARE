/********************************************************************************
** Form generated from reading UI file 'graphicsviewwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICSVIEWWIDGET_H
#define UI_GRAPHICSVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_graphicsViewWidget
{
public:

    void setupUi(QWidget *graphicsViewWidget)
    {
        if (graphicsViewWidget->objectName().isEmpty())
            graphicsViewWidget->setObjectName(QStringLiteral("graphicsViewWidget"));
        graphicsViewWidget->resize(400, 300);

        retranslateUi(graphicsViewWidget);

        QMetaObject::connectSlotsByName(graphicsViewWidget);
    } // setupUi

    void retranslateUi(QWidget *graphicsViewWidget)
    {
        graphicsViewWidget->setWindowTitle(QApplication::translate("graphicsViewWidget", "graphicsViewWidget", 0));
    } // retranslateUi

};

namespace Ui {
    class graphicsViewWidget: public Ui_graphicsViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICSVIEWWIDGET_H
