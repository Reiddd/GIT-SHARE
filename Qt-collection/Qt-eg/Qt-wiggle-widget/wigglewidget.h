#ifndef WIGGLEWIDGET
#define WIGGLEWIDGET

#include <QBasicTimer>
#include <QWidget>

class WiggleWidget: public QWidget
{
    Q_OBJECT
public:
    WiggleWidget(QWidget* parent = 0);

public slots:
    void setText(const QString& newText){text = newText;}

protected:
    void paintEvent(QPaintEvent* event) override;
    void timerEvent(QTimerEvent* event) override;

private:
    QBasicTimer timer;
    QString text;
    int step;
};

#endif // WIGGLEWIDGET

