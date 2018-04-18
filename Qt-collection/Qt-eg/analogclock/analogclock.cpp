#include "analogclock.h"
#include "ui_analogclock.h"

#include <QTimer>
#include <QTime>
#include <QPainter>

analogClock::analogClock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::analogClock)
{
    ui->setupUi(this);

    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(1000);

    setWindowTitle(tr("Analog Clock"));
    resize(200,200);
}

analogClock::~analogClock()
{
    delete ui;
}

void analogClock::paintEvent(QPaintEvent* )
{
    static const QPoint hourHand[3] = {QPoint(7,8), QPoint(-7,8), QPoint(0,-60)};

    static const QPoint minuteHand[3] = {QPoint(7,8), QPoint(-7,8), QPoint(0,-80)};

    static const QPoint secondHand[2] = {QPoint(0,0),QPoint(0,-90)};

    QColor hourColor(127,0,127);
    QColor minuteColor(0,127,127,191);

    int side = qMin(width(),height());
    QTime time = QTime::currentTime();

    ui->label->setText(time.toString());

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2,height() / 2);
    /*avoid painting out side the widget*/
    painter.scale(side / 200.0,side / 200.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);

    painter.save();
    painter.rotate(30.0*((time.hour() + time.minute()/60.0)));
    painter.drawConvexPolygon(hourHand,3);
    painter.restore();

    painter.setPen(hourColor);

    for(int i=0; i < 12; i++)
    {
        painter.drawLine(88,0,96,0);
        painter.rotate(30.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.setPen(Qt::gray);
    for(int i=0;i<60;i++)
    {
        painter.drawLine(92,0,96,0);
        painter.rotate(6.0);
    }
    painter.restore();

    painter.save();
    painter.rotate(6.0*(time.minute() + time.second()/60.0));
    painter.drawConvexPolygon(minuteHand,3);
    painter.restore();

    painter.save();
    painter.setPen(Qt::black);
    painter.rotate(6.0*time.second());
    painter.drawLine(secondHand[0],secondHand[1]);
    painter.restore();
}
