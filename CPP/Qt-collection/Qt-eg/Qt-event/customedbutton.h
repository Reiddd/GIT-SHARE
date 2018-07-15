#ifndef CUSTOMEDBUTTON
#define CUSTOMEDBUTTON

#endif // CUSTOMEDBUTTON

#include <QPushButton>

class customedButton:public QPushButton //inherited from QPushButton
{
    Q_OBJECT  //declare it in every QObject

private:
    void buttonClicked();

public:
    customedButton(QWidget* parent=0);

protected:
    void virtual mousePressEvent(QMouseEvent* event); //overload virtual func
};
