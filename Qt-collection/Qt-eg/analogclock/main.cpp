#include "analogclock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    analogClock w;
    w.show();

    return a.exec();
}
