#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QFrame>
#include <QWidget>

namespace Ui {
class TetrixWindow;
}

class QLCDNumber;
class QLabel;
class QPushButton;

class TetrixBoard;

class TetrixWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TetrixWindow(QWidget *parent = 0);
    ~TetrixWindow();

private:
    Ui::TetrixWindow *ui;

    QLabel* createLabel(const QString& text);

    TetrixBoard* board;
    QLabel* nextPieceLabel;
    QLCDNumber* scoreLcd;
    QLCDNumber* levelLcd;
    QLCDNumber* linesLcd;
    QPushButton* startButton;
    QPushButton* quitButton;
    QPushButton* pauseButton;
};

#endif // TETRIXWINDOW_H
