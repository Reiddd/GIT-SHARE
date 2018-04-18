/********************************************************************************
** Form generated from reading UI file 'notepad.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEPAD_H
#define UI_NOTEPAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Notepad
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionPrint;
    QAction *actionExit;
    QWidget *centralWidget;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuNew;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Notepad)
    {
        if (Notepad->objectName().isEmpty())
            Notepad->setObjectName(QStringLiteral("Notepad"));
        Notepad->resize(400, 300);
        actionNew = new QAction(Notepad);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionNew->setCheckable(false);
        actionOpen = new QAction(Notepad);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(Notepad);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_as = new QAction(Notepad);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionPrint = new QAction(Notepad);
        actionPrint->setObjectName(QStringLiteral("actionPrint"));
        actionExit = new QAction(Notepad);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(Notepad);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 411, 251));
        Notepad->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Notepad);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        menuNew = new QMenu(menuBar);
        menuNew->setObjectName(QStringLiteral("menuNew"));
        Notepad->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Notepad);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Notepad->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Notepad);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Notepad->setStatusBar(statusBar);

        menuBar->addAction(menuNew->menuAction());
        menuNew->addSeparator();
        menuNew->addAction(actionNew);
        menuNew->addAction(actionOpen);
        menuNew->addAction(actionSave);
        menuNew->addAction(actionSave_as);
        menuNew->addAction(actionExit);

        retranslateUi(Notepad);

        QMetaObject::connectSlotsByName(Notepad);
    } // setupUi

    void retranslateUi(QMainWindow *Notepad)
    {
        Notepad->setWindowTitle(QApplication::translate("Notepad", "Notepad", 0));
        actionNew->setText(QApplication::translate("Notepad", "New", 0));
        actionNew->setShortcut(QApplication::translate("Notepad", "Ctrl+N", 0));
        actionOpen->setText(QApplication::translate("Notepad", "Open", 0));
        actionOpen->setShortcut(QApplication::translate("Notepad", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("Notepad", "Save", 0));
        actionSave->setShortcut(QApplication::translate("Notepad", "Ctrl+S", 0));
        actionSave_as->setText(QApplication::translate("Notepad", "Save as", 0));
        actionSave_as->setShortcut(QApplication::translate("Notepad", "Ctrl+Shift+S", 0));
        actionPrint->setText(QApplication::translate("Notepad", "Print", 0));
        actionExit->setText(QApplication::translate("Notepad", "Exit", 0));
        menuNew->setTitle(QApplication::translate("Notepad", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class Notepad: public Ui_Notepad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEPAD_H
