#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGroupBox>

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private:
    Ui::Window *ui;

    QGroupBox* createFirstExclusiveGroup();
    QGroupBox* createSecondExclusiveGroup();
    QGroupBox* createNonExclusiveGroup();
    QGroupBox* createPushButtonGroup();
};

#endif // WINDOW_H
