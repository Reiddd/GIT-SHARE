#include "graphicsviewwidget.h"
#include "ui_graphicsviewwidget.h"

graphicsViewWidget::graphicsViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphicsViewWidget)
{
    ui->setupUi(this);
}

graphicsViewWidget::~graphicsViewWidget()
{
    delete ui;
}
