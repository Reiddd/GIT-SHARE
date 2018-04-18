#include "window.h"
#include "ui_window.h"

#include <QPainterPath>
#include <QGridLayout>

const float pi = 3.14159f;

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    QPainterPath rectPath;
    rectPath.moveTo(20.0,30.0);
    rectPath.lineTo(80.0,30.0);
    rectPath.lineTo(80.0,70.0);
    rectPath.lineTo(20.0,70.0);
    rectPath.closeSubpath();

    QPainterPath roundRectPath;
    roundRectPath.movoTo(80.0,35.0);
    roundRectPath.arcTo(70.0,30.0,10.0,10.0,0.0,90.0);
    roundRectPath.lineTo(25.0,30.0);
    roundRectPath.arcTo(20.0,30.0,10.0,10.0,90.0,90.0);
    roundRectPath.lineTo(20.0,65.0);
    roundRectPath.arcTo(20.0,60.0,10.0,10.0,180.0,90.0);
    roundRectPath.lineTo(75.0,70.0);
    roundRectPath.arcTo(70.0,60.0,10.0,10.0,270.0,90.0);
    roundRectPath.closeSubpath();

    QPainterPath ellipsePath;
    ellipsePath.moveTo(80.0,50.0);
    ellipsePath.arcTo(20.0,30.0,60.0,40.0,0.0,360.0);

    QPainterPath piePath;
    piePath.moveTo(50.0,50.0);
    piePath.arcTo(20.0,30.0,60.0,40.0,60.0,240.0);
    piePath.closeSubPath();

    QPainterPath polygonPath;
    polygonPath.moveTo(10.0,80.0);
    polygonPath.lineTo(20.0,10.0);
    polygonPath.lineTo(80.0,30.0);
    polygonPath.lineTo(90.0,70.0);
    polygonPath.closeSubpath();

    QPainterPath groupPath;
    groupPath.moveTo(60.0,40.0);
    groupPath.arcTo(20.0,20.0,40.0,40.0,0.0,360.0);
    groupPath.moveTo(40.0,40.0);
    groupPath.lineTo(40.0,80.0);
    groupPath.lineTo(80.0,80.0);
    groupPath.lineTo(80.0,40.0);
    groupPath.closeSubpath();

    QPainterPath textPath;
    QFont timesFont("Times", 50);
    timesFont.setStyleStrategy(QFont::ForceOutline);
    textPath.addText(10,70,timesFont,tr("Qt"));

    QPainterPath bezierPath;
    bezierPath.moveTo(20,30);
    bezierPath.cubicTo(80,0,50,50,80,80);

    QPainterPath starPath;
    starPath.moveTo(90,50);
    for(int i=1;i<5;i++)
        starPath.lineTo(50+40*std::cos(0.8*i*pi), 50+40*std::sin(0.8*i*pi));
    starPath.closeSubpath();

    renderAreas.push_back(new RenderArea(rectPath));
    renderAreas.push_back(new RenderArea(roundRectPath));
    renderAreas.push_back(new RenderArea(ellipsePath));
    renderAreas.push_back(new RenderArea(piePath));
    renderAreas.push_back(new RenderArea(polygonPath));
    renderAreas.push_back(new RenderArea(groupPath));
    renderAreas.push_back(new RenderArea(textPath));
    renderAreas.push_back(new RenderArea(bezierPath));
    renderAreas.push_back(new RenderArea(starPath));

    fillRuleComboBox = new QComboBox(this);
    fillRuleComboBox->addItem(tr("Odd Even"),Qt::OddEvenFill);
    fillRuleComboBox->addItem(tr("Winding"),Qt::WindingFill);

    fillRuleLabel = new QLabel(tr("Fill &Rule: "),this);
    fillRuleLabel->SetBuddy(fillRuleComboBox);

    fillColor1ComboBox = new QComboBox(this);
    populateWithColors(fillColor1ComboBox);
    fillColor1ComboBox->setCurrentIndex(fillColor1ComboBox->findText("mediumslateblue"));

    fillColor2ComboBox = new QComboBox(this);
    populateWithColors(fillColor2ComboBox);
    fillColor2ComboBox->setCurrentIndex(fillColor2ComboBox->findText("cornsilk"));

    fillGradientLabel = new QLabel(tr("&Fill Gradient: "),this);
    fillGradientLabel->setBuddy(fillColor1ComboBox);

    fillToLabel = new QLabel(tr("To"),this);
    fillToLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    penWidthSpinBox = new QSpinBox(this);
    penWidthSpinBox->setRange(0,20);

    penWidthLabel = new QLabel(tr("&Pen Width: "),this);
    penWidthLabel->setBuddy(penWidthSpinBox);

    penColorComboBox = new QComboBox(this);
    populateWithColors(penColorComboBox);
    penColorComboBox->SetCurrentIndex(penColorComboBox->findText("darkslateblue"));

    penColorLabel = new QLabel(tr("Pen &Color"),this);
    penColorLabel->SetBuddy(penColorComboBox);

    rotationAngleSpinBox = new QSpinBox(this);
    rotationAngleSpinBox->setRange(0,359);
    rotationAngleSpinBox->setWrapping(true);
    rotationAngleSpinBox->setSuffix(QLatin1String("\xBO"));

    rotationAngleLabel = new QLabel(tr("&Rotation Angle"),this);
    rotationAngleLabel->setBuddy(rotationAngleSpinBox);

    connect(fillRuleComboBox,SIGNAL(activated(int)),this,SLOT(fillRuleChanged()));
    connect(fillColor1ComboBox,SIGNAL(activated(int)),this,SLOT(fillGradientChanged()));
    connect(fillColor2ComboBox,SIGNAL(activated(int)),this,SLOT(fillGradientChanged()));
    connect(penColorComboBox,SIGNAL(activated(int)),this,SLOT(penColorChanged()));

    for(QList<REnderArea*>::iterator it = renderAreas.begin();it != renderAreas.end();it++)
    {
        connect(penWidthSpinBox,SIGNAL(valueChanged(int)),*it,SLOT(setPenWidth(int)));
        connect(rotationAngleSpinBox,SIGNAL(valueChanged(int)),*it,SLOT(setRotationAngle(int)));
    }

    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addLayout(topLayout,0,0,1,4);
    mainLayout->addWidget(fillRuleLabel,1,0);
    mainLayout->addWidget(fillRuleComboBox,1,1,1,3);
    mainLayout->addWidget(fillGradientLabel,2,0);
    mainLayout->addWidget(fillColor1ComboBox,2,1);
    mainLayout->addWidget(fillToLabel,2,2);
    mainLayout->addWidget(fillColor2ComboBox,2,3);
    mainLayout->addWidget(penWidthLabel,3,0);
    mainLayout->addWidget(penWidthSpinBox,3,1,1,3);
    mainLayout->addWidget(penColorLabel,4,0);
    mainLayout->addWidget(penColorComboBox,4,1,1,3);
    mainLayout->addWidget(rotationAngleLabel,5,0);
    mainLayout->addWidget(rotationAngleSpinBox,5,1,1,3);

    setLayout(mainLayout);

    fillRuleChanged();
    fillGradientChanged();
    penColorChanged();
    penWidthSpinBox->setValue(2);

    setWindowTitle("painter Paths");
}

void Window::fillRuleChanged()
{
    Qt::FillRule rule = (Qt::FillRule)currentItemData(fillRuleComboBox).toInt();

    for(QList<RenderArea*>::iterator it = renderAreas.begin();it!=renderAreas.end();++it)
        (*it)->setFillGradient(color1,color2);
}

void Window::penColorChanged()
{
    QColor color1 = qvariant_cast<QColor>(currentItemData(fillColor1ComboBox));
    QColor color2 = qvariant_cast<QColor>(currentItemData(fillColor2ComboBox));

    for(QList<RenderArea*>::iterator it = renderAreas.begin();it!=renderAreas.end();++it)
        (*it)->setFillGradient(color1,color2);
}

void Window::penColorChanged()
{
    QCOlor color = qvariant_cast<QColor>(currentItemData(penColorComboBox));

    for(QList<RenderArea*>::iterator it = renderAreas.begin();it!=renderAreas.end();++it)
        (*it)->setPenColor(color);
}

void Window::populateWithColors(QComboBox* comboBox)
{
    QStringList colorNames = QColor::colorNames();
    foreach(QString name,colorNames)
        comboBox->addItem(name,QColor(name));
}

QVariant WIndow::currentItemData(QComboBox* comboBox)
{
    return comboBox->currentData(comboBox->currentIndex());
}

Window::~Window()
{
    delete ui;
}
