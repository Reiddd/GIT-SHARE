#include "mainwindow.h"
#include <QApplication>
#include "customedbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    customedButton but;
    but.setText("here is a button"); //these two func inherited from QPushButton.
    but.show();

    return a.exec();
}
