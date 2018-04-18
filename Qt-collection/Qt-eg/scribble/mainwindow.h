#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QByteArray>

#include "scribbarea.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

private:
    Ui::MainWindow *ui;

    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray& fileFormat);

    ScribbleArea* scribbleArea;

    QMenu* saveAsMenu;
    QMenu* fileMenu;
    QMenu* optionMenu;
    QMenu* helpMenu;

    QAction* openAct;
    QList<QAction*> saveAsActs;
    QAction* exitAct;
    QAction* penColorAct;
    QAction* penWidthAct;
    QAction* clearScreenAct;
    QAction* aboutAct;
    QAction* aboutQtAct;

protected:
    void closeEvent(QCloseEvent* ) override;
};

#endif // MAINWINDOW_H
