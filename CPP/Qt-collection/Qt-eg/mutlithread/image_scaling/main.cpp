#include "images.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Images w;
    w.show();

    return a.exec();
}
