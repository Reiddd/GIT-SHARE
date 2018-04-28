#include "blockingclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlockingClient w;
    w.show();

    return a.exec();
}
