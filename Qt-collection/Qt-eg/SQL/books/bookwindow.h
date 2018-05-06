#ifndef BOOKWINDOW_H
#define BOOKWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include "ui_bookwindow.h"

class BookWindow : public QMainWindow
{
    Q_OBJECT

public:
    BookWindow(QWidget *parent = 0);
    ~BookWindow();

private:
    void showError(const QSqlError& err);

    Ui::BookWindow            ui;
    QSqlRelationalTableModel* model;
    int                       authorIdx;
    int                       genreIdx;
};

#endif // BOOKWINDOW_H
