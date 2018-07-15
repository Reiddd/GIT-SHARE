#include "tetrixwindow.h"
#include <QApplication>
#include <QtWidgets>

#include <stdlib.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TetrixWindow w;
    w.show();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    return a.exec();
}
