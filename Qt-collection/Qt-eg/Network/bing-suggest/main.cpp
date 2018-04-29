#include "searchbox.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SearchBox w;
    w.show();

    return a.exec();
}
