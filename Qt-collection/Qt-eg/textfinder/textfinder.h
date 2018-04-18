#ifndef TEXTFINDER_H
#define TEXTFINDER_H

#include <QWidget>

#include "ui_textfinder.h"

namespace Ui {
class textFinder;
}

class textFinder : public QWidget
{
    Q_OBJECT

public:
    explicit textFinder(QWidget *parent = 0);

private slots:
    void on_findButton_clicked();

private:
    Ui::textFinder ui;

    void loadTextFile();
};

#endif // TEXTFINDER_H
