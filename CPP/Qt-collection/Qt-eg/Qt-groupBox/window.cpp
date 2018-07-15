#include "window.h"
#include "ui_window.h"

#include <QLayout>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>
#include <QMenu>

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    QGridLayout* grid = new QGridLayout;
    grid->addWidget(createFirstExclusiveGroup(),0,0);
    grid->addWidget(createSecondExclusiveGroup(),1,0);
    grid->addWidget(createNonExclusiveGroup(),0,1);
    grid->addWidget(createPushButtonGroup(),1,1);

    setLayout(grid);

    setWindowTitle(tr("Group Boxes"));
    resize(480,320);
}

Window::~Window()
{
    delete ui;
}

QGroupBox* Window::createFirstExclusiveGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("Exclusive Radio Buttons"));

    QRadioButton* radio1 = new QRadioButton(tr("&Radio button 1"));
    QRadioButton* radio2 = new QRadioButton(tr("&Radio button 2"));
    QRadioButton* radio3 = new QRadioButton(tr("&Radio button 3"));

    radio1->setChecked(true);

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

QGroupBox* Window::createSecondExclusiveGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("E&xclusive Radio Buttons"));
    groupBox->setCheckable(true);
    groupBox->setChecked(true);

    QRadioButton* radio1 = new QRadioButton(tr("Rad&io button 1"));
    QRadioButton* radio2 = new QRadioButton(tr("Radi&o button 2"));
    QRadioButton* radio3 = new QRadioButton(tr("Radio &button 3"));
    radio1->setChecked(true);

    QCheckBox* checkBox = new QCheckBox(tr("Ind&ependent checkbox"));
    checkBox->setChecked(true);

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addWidget(checkBox);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

QGroupBox* Window::createNonExclusiveGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("Non-Exclusive Checkboxes"));
    groupBox->setFlat(true);

    QCheckBox* checkBox1 = new QCheckBox(tr("&Checkbox"));
    QCheckBox* checkBox2 = new QCheckBox(tr("C&heckbox 2"));
    checkBox2->setChecked(true);
    QCheckBox* tristateBox = new QCheckBox(tr("tri-&state button"));
    tristateBox->setTristate(true);

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(checkBox1);
    vbox->addWidget(checkBox2);
    vbox->addWidget(tristateBox);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

QGroupBox* Window::createPushButtonGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("&Push Buttons"));
    groupBox->setCheckable(true);
    groupBox->setChecked(true);

    QPushButton* pushButton = new QPushButton(tr("&Normal Button"));
    QPushButton* toggleButton = new QPushButton(tr("&Toggle Button"));
    toggleButton->setCheckable(true);
    toggleButton->setChecked(true);

    QPushButton* flatButton = new QPushButton(tr("&Flat Button"));
    flatButton->setFlat(true);

    QPushButton* popupButton = new QPushButton(tr("Pop&up Button"));

    QMenu* menu = new QMenu(this);
    menu->addAction("&First Item");
    menu->addAction(tr("&Second Item"));
    menu->addAction(tr("&Third Item"));
    menu->addAction(tr("F&ourth Item"));

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(pushButton);
    vbox->addWidget(toggleButton);
    vbox->addWidget(flatButton);
    vbox->addWidget(popupButton);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}
