#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QGridLayout>

#include "renderarea.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private:
    Ui::Window *ui;

    RenderArea* renderArea;

    QLabel* shapeLabel;
    QLabel* penWidthLabel;
    QLabel* penStyleLabel;
    QLabel* penCapLabel;
    QLabel* penJoinLabel;
    QLabel* brushStyleLabel;
    QLabel* otherOptionsLabel;

    QComboBox* shapeComboBox;
    QComboBox* penStyleComboBox;
    QComboBox* penCapComboBox;
    QComboBox* penJoinComboBox;
    QComboBox* brushStyleComboBox;

    QCheckBox* antialiasingCheckBox;
    QCheckBox* transformationsCheckBox;

    QSpinBox* penWidthSpinBox;

    QGridLayout* mainLayout;

private slots:
    void shapeChanged();
    void penChanged();
    void brushChanged();
};

#endif // WINDOW_H
