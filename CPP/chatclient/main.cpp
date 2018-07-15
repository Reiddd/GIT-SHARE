#include "chatdialog.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChatDialog c;
    c.l->show();

    return a.exec();
}
