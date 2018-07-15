#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    scene.addLine(0,0,150,150);

    QGraphicsView  view(&scene);
    view.setWindowTitle("Graphics Demo");
    view.resize(500,500);
    view.show();

    return a.exec();
}
