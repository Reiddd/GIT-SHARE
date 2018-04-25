#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationDisplayName(Client::tr("Fortune Client"));
    Client w;
    w.show();

    return a.exec();
}
