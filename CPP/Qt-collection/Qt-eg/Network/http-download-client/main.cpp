#include "httpwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HttpWindow w;
    const QRect availableSize = QApplication::desktop()->availableGeometry(&w);
    w.resize(availableSize.width()/5, availableSize.height()/5);
    w.move((availableSize.width() - w.width())/2, (availableSize.height() - w.height())/2);
    w.show();

    return a.exec();
}
