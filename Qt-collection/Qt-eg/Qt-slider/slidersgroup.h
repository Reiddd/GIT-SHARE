#ifndef SLIDERSGROUP
#define SLIDERSGROUP

#include <QGroupBox>
#include <QSlider>
#include <QDial>
#include <QScrollBar>

class SlidersGroup:public QGroupBox
{
    Q_OBJECT
public:
    SlidersGroup(Qt::Orientation orientation,const QString& title,QWidget* parent = 0);

signals:
    void valueChanged(int value);

public slots:
    void setValue(int value);
    void setMinimum(int value);
    void setMaximum(int value);
    void invertedAppearance(bool invert);
    void invertedKeyBindings(bool invert);

private:
    QSlider* slider;
    QScrollBar* scrollBar;
    QDial* dial;
};

#endif // SLIDERSGROUP

