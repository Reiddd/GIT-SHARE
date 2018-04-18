#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*QGraphicsScene* scene = new QGaphicsScene;*/
    scene = new QGraphicsScene;


    QPen pen;

    /*QPen::setStyle(Qt::PenStyle)
      -------
      QT::PenStyle :
      1. Qt::SolidLine
      2. Qt::DashLine
      3. Qt::DashDotLine
      4. Qt::DahDotDotLine*/
    pen.setStyle(Qt::DashDotLine);


    /*QPen::setWidth(qint32 )
      QPen::setWidthF(qreal )
      -------
      the width is set in pixel*/
    pen.setWidth(2);


    /*QPen::setBrush(const QBrush& )
      -------
      Qt::BrushStyle :
      1. Qt::SolidPattern
      2. Qt::Dense1Pattern
      3. Qt::Dense2Pattern
      4. Qt::Dense3Pattern
      5. Qt::Dense4Pattern
      6. Qt::Dense5Pattern
      7. Qt::Dense6Pattern
      8. Qt::Dense7Pattern
      9. Qt::NoBrush
      10. Qt::HorPattern
      11. Qt::VerPattern
      12. Qt::CrossPattern
      13. Qt::BDiagPattern
      14. Qt::FDiagPattern
      15. Qt::DiagCrossPattern
      16. Qt::LinearGradientPattern
      17. Qt::RadialGradientPattern
      18. Qt::ConicalGradientPattern

      other : Qt::Color
      */
    pen.setBrush(Qt::black);


    /*QPen::setCapStyle(Qt::PenCapStyle)
      -------
      Qt::PenCapStyle :
      1. Qt::FlatCap
      2. Qt::SquareCap
      3. Qt::RoundCap*/
    pen.setCapStyle(Qt::RoundCap);


    /*QPen::setJoinStyle(Qt::PenJoinStyle)
      -------
      Qt::PenJoinStyle :
      1. Qt::BevalJoin
      2. Qt::MiterJoin
      3. Qt::RoundJoin*/
    pen.setJoinStyle(Qt::RoundJoin);

    scene->addLine(30,30,200,30,pen);

    view = new QGraphicsView(scene);

    this->setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}
