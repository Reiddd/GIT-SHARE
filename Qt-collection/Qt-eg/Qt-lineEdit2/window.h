#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLineEdit>

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
    void echoChanged(int);
    void validatorChanged(int);
    void alignmentChanged(int);
    void inputMaskChanged(int);
    void accessChanged(int);

private:
    Ui::Window *ui;

    QLineEdit* echoLineEdit;
    QLineEdit* validatorLineEdit;
    QLineEdit* alignmentLineEdit;
    QLineEdit* inputMaskLineEdit;
    QLineEdit* accessLineEdit;
};

#endif // WINDOW_H
