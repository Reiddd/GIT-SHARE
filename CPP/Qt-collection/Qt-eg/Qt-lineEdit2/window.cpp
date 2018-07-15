#include "window.h"
#include "ui_window.h"

#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    QGroupBox* echoGroup = new QGroupBox(tr("Echo"),this);

    QLabel* echoLabel = new QLabel(tr("Mode:"),this);
    QComboBox* echoComboBox = new QComboBox(this);
    echoComboBox->addItem(tr("Normal"));
    echoComboBox->addItem(tr("PassWord"));
    echoComboBox->addItem(tr("PasswordEchoOnEdit"));
    echoComboBox->addItem(tr("No Echo"));

    echoLineEdit = new QLineEdit(this);
    echoLineEdit->setPlaceholderText("Placeholder Text");
    echoLineEdit->setFocus();

    QGroupBox* validatorGroup = new QGroupBox(tr("Validator"),this);

    QLabel* validatorLabel = new QLabel(tr("Type:"),this);
    QComboBox* validatorComboBox = new QComboBox;
    validatorComboBox->addItem(tr("No validator"));
    validatorComboBox->addItem(tr("Integer validator"));
    validatorComboBox->addItem(tr("Double validator"));

    validatorLineEdit = new QLineEdit(this);
    validatorLineEdit->setPlaceholderText("Placeholder Text");

    QGroupBox* alignmentGroup = new QGroupBox(tr("Alignment"),this);

    QLabel* alignmentLabel = new QLabel(tr("Type:"));
    QComboBox* alignmentComboBox = new QComboBox;
    alignmentComboBox->addItem(tr("Left"));
    alignmentComboBox->addItem(tr("Centered"));
    alignmentComboBox->addItem(tr("Right"));

    alignmentLineEdit = new QLineEdit(this);
    alignmentLineEdit->setPlaceholderText("Placeholder Text");

    QGroupBox* inputMaskGroup = new QGroupBox(tr("Input mask"),this);

    QLabel* inputMaskLabel = new QLabel(tr("Type:"),this);
    QComboBox* inputMaskComboBox = new QComboBox(this);
    inputMaskComboBox->addItem(tr("No Mask"));
    inputMaskComboBox->addItem(tr("Phone number"));
    inputMaskComboBox->addItem(tr("ISO date"));
    inputMaskComboBox->addItem(tr("License key"));

    inputMaskLineEdit = new QLineEdit(this);
    inputMaskLineEdit->setPlaceholderText("placeholder Text");

    QGroupBox* accessGroup = new QGroupBox(tr("Access"),this);

    QLabel* accessLabel = new QLabel(tr("Read-only:"),this);
    QComboBox* accessComboBox = new QComboBox(this);
    accessComboBox->addItem(tr("False"));
    accessComboBox->addItem(tr("True"));

    accessLineEdit = new QLineEdit(this);
    accessLineEdit->setPlaceholderText("Placeholder Text");

    connect(echoComboBox,SIGNAL(activated(int)),this,SLOT(echoChanged(int)));
    connect(validatorComboBox,SIGNAL(activated(int)),this,SLOT(validatorChanged(int)));
    connect(alignmentComboBox,SIGNAL(activated(int)),this,SLOT(alignmentChanged(int)));
    connect(inputMaskComboBox,SIGNAL(activated(int)),this,SLOT(inputMaskChangkd(int)));
    connect(accessComboBox,SIGNAL(activated(int)),this,SLOT(accessChanged(int)));

    QGridLayout* echoLayout = new QGridLayout;
    echoLayout->addWidget(echoLabel,0,0);
    echoLayout->addWidget(echoComboBox,0,1);
    echoLayout->addWidget(echoLineEdit,1,0,1,2);
    echoGroup->setLayout(echoLayout);

    QGridLayout* validatorLayout = new QGridLayout;
    validatorLayout->addWidget(validatorLabel,0,0);
    validatorLayout->addWidget(validatorComboBox,0,1);
    validatorLayout->addWidget(validatorLineEdit,1,0,1,2);
    validatorGroup->setLayout(validatorLayout);

    QGridLayout* alignmentLayout = new QGridLayout;
    alignmentLayout->addWidget(alignmentLabel,0,0);
    alignmentLayout->addWidget(alignmentComboBox,0,1);
    alignmentLayout->addWidget(alignmentLineEdit,1,0,1,2);
    alignmentGroup->setLayout(alignmentLayout);

    QGridLayout* inputMaskLayout = new QGridLayout;
    inputMaskLayout->addWidget(inputMaskLabel,0,0);
    inputMaskLayout->addWidget(inputMaskComboBox,0,1);
    inputMaskLayout->addWidget(inputMaskLineEdit,1,0,1,2);
    inputMaskGroup->setLayout(inputMaskLayout);

    QGridLayout* accessLayout = new QGridLayout;
    accessLayout->addWidget(accessLabel,0,0);
    accessLayout->addWidget(accessComboBox,0,1);
    accessLayout->addWidget(accessLineEdit,1,0,1,2);
    accessGroup->setLayout(accessLayout);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(echoGroup,0,0);
    layout->addWidget(validatorGroup,1,0);
    layout->addWidget(alignmentGroup,2,0);
    layout->addWidget(inputMaskGroup,0,1);
    layout->addWidget(accessGroup,1,1);
    setLayout(layout);

    setWindowTitle(tr("Line Edits"));
}

void Window::echoChanged(int index)
{
    switch(index)
    {
    case 0:
        echoLineEdit->setEchoMode(QLineEdit::Normal);break;
    case 1:
        echoLineEdit->setEchoMode(QLineEdit::Password);break;
    case 2:
        echoLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);break;
    case 3:
        echoLineEdit->setEchoMode(QLineEdit::NoEcho);break;
    }
}

void Window::validatorChanged(int index)
{
    switch(index)
    {
    case 0:
        validatorLineEdit->setValidator(0);break;
    case 1:
        validatorLineEdit->setValidator(new QIntValidator(validatorLineEdit));break;
    case 2:
        validatorLineEdit->setValidator(new QDoubleValidator(-999.0,999.0,2,validatorLineEdit));break;
    }

    validatorLineEdit->clear();
}

void Window::alignmentChanged(int index)
{
    switch(index)
    {
    case 0:
        alignmentLineEdit->setAlignment(Qt::AlignLeft);break;
    case 1:
        alignmentLineEdit->setAlignment(Qt::AlignCenter);break;
    case 2:
        alignmentLineEdit->setAlignment(Qt::AlignRight);break;
    }
}

void Window::inputMaskChanged(int index)
{
    switch(index)
    {
    case 0:
        inputMaskLineEdit->setInputMask("");break;
    case 1:
        inputMaskLineEdit->setInputMask("+99 99 99 99 99;_");break;
    case 2:
        inputMaskLineEdit->setInputMask("0000-00-00");
        inputMaskLineEdit->setText("00000000");
        inputMaskLineEdit->setCursorPosition(0);
        break;
    case 3:
        inputMaskLineEdit->setInputMask(">AAAAA-AAAAA-AAAAA-AAAAA-AAAAA;#");break;
    }
}

void Window::accessChanged(int index)
{
    switch(index)
    {
    case 0:
        accessLineEdit->setReadOnly(false);break;
    case 1:
        accessLineEdit->setReadOnly(true);break;
    }
}

Window::~Window()
{
    delete ui;
}
