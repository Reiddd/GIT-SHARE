#include <QLineEdit>
#include <QVBoxLayout>

#include "dialog.h"
#include "wigglewidget.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    WiggleWidget* wiggleWidget = new WiggleWidget;
    QLineEdit* lineEdit = new QLineEdit;

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(wiggleWidget);
    layout->addWidget(lineEdit);

    connect(lineEdit,&QLineEdit::textChanged,wiggleWidget,&WiggleWidget::setText);
    lineEdit->setText(tr("Hello World"));

    setWindowTitle(tr("Wiggly"));
    resize(360,145);
}

Dialog::~Dialog()
{

}
