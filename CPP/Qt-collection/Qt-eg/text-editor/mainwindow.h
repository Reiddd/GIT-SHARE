#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openfile();
    void savefile();

private:
    Ui::MainWindow *ui;
    QTextEdit* textEditor;
};

#endif // MAINWINDOW_H
