#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    Ui::Window *ui;

    void fillRuleChanged();
    void fillGradientChanged();
    void penColorChanged();

private:
    void populateWithColors(QComboBox* comboBox);
    QVariant currentItemData(QComboBox* comboBox);

    QList<RenderArea*> renderAreas;

    QLabel* fillRuleLabel;
    QLabel* fillGradientLabel;
    QLabel* fillToLabel;
    QLabel* penColorLabel;
    QLabel* penWidthLabel;
    QLabel* rotationAngleLabel;

    QComboBox* fillRuleComboBox;
    QComboBox* fillColor1ComboBox;
    QComboBox* fillColor2ComboBox;
    QComboBox* penColorComboBox;

    QSpinBox* penWidthSpinBox;
    QSpinBox* rotationAngleSpinBox;
};

#endif // WINDOW_H
