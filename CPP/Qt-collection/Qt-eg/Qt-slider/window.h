#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QGroupBox>
#include <QStackedWidget>
#include <QCheckBox>

#include "slidersgroup.h"

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

    void createControls(const QString& title);

    SlidersGroup* horizontalSliders;
    SlidersGroup* verticalSliders;
    QStackedWidget* stackedWidget;

    QGroupBox* controlsGroup;
    QLabel* minimumLabel;
    QLabel* maximumLabel;
    QLabel* valueLabel;
    QCheckBox* invertedAppearance;
    QCheckBox* invertedKeyBindings;
    QSpinBox* minimumSpinBox;
    QSpinBox* maximumSpinBox;
    QSpinBox* valueSpinBox;
    QComboBox* orientationCombo;
};

#endif // WINDOW_H
