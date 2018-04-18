#ifndef GRAPHICSVIEWWIDGET_H
#define GRAPHICSVIEWWIDGET_H

#include <QWidget>

namespace Ui {
class graphicsViewWidget;
}

class graphicsViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit graphicsViewWidget(QWidget *parent = 0);
    ~graphicsViewWidget();

private:
    Ui::graphicsViewWidget *ui;
};

#endif // GRAPHICSVIEWWIDGET_H
