#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>

namespace Ui {
class analogClock;
}

class analogClock : public QWidget
{
    Q_OBJECT

public:
    explicit analogClock(QWidget *parent = 0);
    ~analogClock();

private:
    Ui::analogClock *ui;

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // ANALOGCLOCK_H
