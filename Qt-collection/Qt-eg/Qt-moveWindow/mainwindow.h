#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPushButton* but;

    QPoint last;

protected:
    void mouseMoveEvent(QMouseEvent*);

    void mousePressEvent(QMouseEvent* );

    void mouseReleaseEvent(QMouseEvent* );
};

#endif // MAINWINDOW_H
