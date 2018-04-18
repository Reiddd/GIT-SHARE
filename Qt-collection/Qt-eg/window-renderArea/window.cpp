#include "window.h"
#include "ui_window.h"

#include <QGridLayout>

const int IdRole = Qt::UserRole;

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    renderArea = new RenderArea(this);

    shapeComboBox = new QComboBox(this);
    shapeComboBox->addItem(tr("Polygon"),RenderArea::Polygon);
    shapeComboBox->addItem(tr("Rectangle"),RenderArea::Rect);
    shapeComboBox->addItem(tr("Rounded Rectangle"),RenderArea::RoundedRect);
    shapeComboBox->addItem(tr("Ellipse"),RenderArea::Ellipse);
    shapeComboBox->addItem(tr("Pie"),RenderArea::Pie);
    shapeComboBox->addItem(tr("Chord"),RenderArea::Chord);
    shapeComboBox->addItem(tr("Path"),RenderArea::Path);
    shapeComboBox->addItem(tr("Line"),RenderArea::Line);
    shapeComboBox->addItem(tr("Polyline"),RenderArea::Polyline);
    shapeComboBox->addItem(tr("Arc"),RenderArea::Arc);
    shapeComboBox->addItem(tr("Points"),RenderArea::Points);
    shapeComboBox->addItem(tr("Text"),RenderArea::Text);
    shapeComboBox->addItem(tr("Pixmap"),RenderArea::Pixmap);

    shapeLabel = new QLabel(tr("&Shape: "),this);
    shapeLabel->setBuddy(shapeComboBox);

    penWidthSpinBox = new QSpinBox(this);
    penWidthSpinBox->setRange(0,20);
    penWidthSpinBox->setSpecialValueText(tr("0(cosmetic pen)"));

    penWidthLabel = new QLabel(tr("Pen &Width: "),this);
    penWidthLabel->setBuddy(penWidthSpinBox);

    penStyleComboBox = new QComboBox(this);
    penStyleComboBox->addItem(tr("Solid"),static_cast<int>(Qt::SolidLine));
    penStyleComboBox->addItem(tr("Dash"),static_cast<int>(Qt::DashLine));
    penStyleComboBox->addItem(tr("Dot"),static_cast<int>(Qt::DotLine));
    penStyleComboBox->addItem(tr("DashDot"),static_cast<int>(Qt::DashDotLine));
    penStyleComboBox->addItem(tr("DahDotDot"),static_cast<int>(Qt::DashDotDotLine));
    penStyleComboBox->addItem(tr("None"),static_cast<int>(Qt::NoPen));

    penStyleLabel = new QLabel(tr("&Pen Style: "),this);
    penStyleLabel->setBuddy(penStyleComboBox);

    penCapComboBox = new QComboBox(this);
    penCapComboBox->addItem(tr("Flat"),Qt::FlatCap);
    penCapComboBox->addItem(tr("Square"),Qt::SquareCap);
    penCapComboBox->addItem(tr("Round"),Qt::RoundCap);

    penCapLabel = new QLabel(tr("Pen &Cap"),this);
    penCapLabel->setBuddy(penCapComboBox);

    penJoinComboBox = new QComboBox(this);
    penJoinComboBox->addItem(tr("Miter"),Qt::MiterJoin);
    penJoinComboBox->addItem(tr("Bevel"),Qt::BevelJoin);
    penJoinComboBox->addItem(tr("Round"),Qt::RoundJoin);

    penJoinLabel = new QLabel(tr("Pen &Join"),this);
    penJoinLabel->setBuddy(penJoinComboBox);

    brushStyleComboBox = new QComboBox(this);
    brushStyleComboBox->addItem(tr("Linear Gradient"),static_cast<int>(Qt::LinearGradientPattern));
    brushStyleComboBox->addItem(tr("Radial Gradient"),static_cast<int>(Qt::RadialGradientPattern));
    brushStyleComboBox->addItem(tr("ConicalGradientPattern"),static_cast<int>(Qt::ConicalGradientPattern));
    brushStyleComboBox->addItem(tr("Solid"),static_cast<int>(Qt::SolidPattern));
    brushStyleComboBox->addItem(tr("Horizontal"),static_cast<int>(Qt::HorPattern));
    brushStyleComboBox->addItem(tr("Vertical"),static_cast<int>(Qt::VerPattern));
    brushStyleComboBox->addItem(tr("Cross"),static_cast<int>(Qt::CrossPattern));
    brushStyleComboBox->addItem(tr("Backward Diagonal"),static_cast<int>(Qt::BDiagPattern));
    brushStyleComboBox->addItem(tr("Forward Diagonal"),static_cast<int>(Qt::FDiagPattern));
    brushStyleComboBox->addItem(tr("Diagonal Cross"),static_cast<int>(Qt::DiagCrossPattern));
    brushStyleComboBox->addItem(tr("Dense 1"),static_cast<int>(Qt::Dense1Pattern));
    brushStyleComboBox->addItem(tr("Dense 2"),static_cast<int>(Qt::Dense2Pattern));
    brushStyleComboBox->addItem(tr("Dense 3"),static_cast<int>(Qt::Dense3Pattern));
    brushStyleComboBox->addItem(tr("Dense 4"),static_cast<int>(Qt::Dense4Pattern));
    brushStyleComboBox->addItem(tr("Dense 5"),static_cast<int>(Qt::Dense5Pattern));
    brushStyleComboBox->addItem(tr("Dense 6"),static_cast<int>(Qt::Dense6Pattern));
    brushStyleComboBox->addItem(tr("Dense 7"),static_cast<int>(Qt::Dense7Pattern));
    brushStyleComboBox->addItem(tr("None"),static_cast<int>(Qt::NoBrush));

    brushStyleLabel = new QLabel(tr("&Brushs: "),this);
    brushStyleLabel->setBuddy(brushStyleComboBox);

    otherOptionsLabel = new QLabel(tr("Options: "),this);
    antialiasingCheckBox = new QCheckBox(tr("&Antialiasing"),this);

    transformationsCheckBox = new QCheckBox(tr("&Transformations"),this);

    connect(shapeComboBox, SIGNAL(activated(int)),this,SLOT(shapeChanged()));
    connect(penWidthSpinBox,SIGNAL(valueChanged(int)),this,SLOT(penChanged()));
    connect(penStyleComboBox,SIGNAL(activated(int)),this,SLOT(penChanged()));
    connect(penCapComboBox,SIGNAL(activated(int)),this,SLOT(penChanged()));
    connect(penJoinComboBox,SIGNAL(activated(int)),this,SLOT(penChanged()));
    connect(brushStyleComboBox,SIGNAL(activated(int)),this,SLOT(brushChanged()));
    connect(antialiasingCheckBox,SIGNAL(toggled(bool)),renderArea,SLOT(setAntialiased(bool)));
    connect(transformationsCheckBox,SIGNAL(toggled(bool)),renderArea,SLOT(setTransformed(bool)));

    mainLayout = new QGridLayout(this);
    mainLayout->setColumnStretch(0,1);
    mainLayout->setColumnStretch(3,1);
    mainLayout->addWidget(renderArea,0,0,1,4);
    mainLayout->addWidget(shapeLabel,2,0,Qt::AlignRight);
    mainLayout->addWidget(shapeComboBox,2,1);
    mainLayout->addWidget(penWidthLabel,3,0,Qt::AlignRight);
    mainLayout->addWidget(penWidthSpinBox,3,1);
    mainLayout->addWidget(penStyleLabel,4,0,Qt::AlignRight);
    mainLayout->addWidget(penStyleComboBox,4,1);
    mainLayout->addWidget(penCapLabel,3,2,Qt::AlignRight);
    mainLayout->addWidget(penCapComboBox,3,3);
    mainLayout->addWidget(penJoinLabel,2,2,Qt::AlignRight);
    mainLayout->addWidget(penJoinComboBox,2,3);
    mainLayout->addWidget(brushStyleLabel,4,2,Qt::AlignRight);
    mainLayout->addWidget(brushStyleComboBox,4,3);
    mainLayout->addWidget(otherOptionsLabel,5,0,Qt::AlignRight);
    mainLayout->addWidget(antialiasingCheckBox,5,1,1,1,Qt::AlignRight);
    mainLayout->addWidget(transformationsCheckBox,5,2,1,2,Qt::AlignRight);
    this->setLayout(mainLayout);

    shapeChanged();
    penChanged();
    brushChanged();
    antialiasingCheckBox->setChecked(true);

    setWindowTitle(tr("Basic Drawing"));

}

Window::~Window()
{
    delete ui;
}

void Window::shapeChanged()
{
    RenderArea::Shape shape = RenderArea::Shape(shapeComboBox->itemData(shapeComboBox->currentIndex(),IdRole).toInt());
    renderArea->setShape(shape);
}

void Window::penChanged()
{
    int width = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(),IdRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penStyleComboBox->currentIndex(),IdRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(),IdRole).toInt());

    renderArea->setPen(QPen(Qt::blue,width,style,cap,join));
}

void Window::brushChanged()
{
    Qt::BrushStyle style = Qt::BrushStyle(brushStyleComboBox->itemData(brushStyleComboBox->currentIndex(),IdRole).toInt());
    if(style == Qt::LinearGradientPattern)
    {
        QLinearGradient linearGradient(0,0,100,100);
        linearGradient.setColorAt(0.0,Qt::white);
        linearGradient.setColorAt(0.2,Qt::green);
        linearGradient.setColorAt(1.0,Qt::black);

        renderArea->setBrush(linearGradient);
    }
    else if(style == Qt::RadialGradientPattern)
    {
        QRadialGradient radialGradient(50,50,50,70,70);
        radialGradient.setColorAt(0.0,Qt::white);
        radialGradient.setColorAt(0.2,Qt::green);
        radialGradient.setColorAt(1.0,Qt::black);

        renderArea->setBrush(radialGradient);
    }
    else if(style == Qt::ConicalGradientPattern)
    {
        QConicalGradient conicalGradient(50,50,150);
        conicalGradient.setColorAt(0.0,Qt::white);
        conicalGradient.setColorAt(0.2,Qt::green);
        conicalGradient.setColorAt(1.0,Qt::black);

        renderArea->setBrush(conicalGradient);
    }
    else
        renderArea->setBrush(QBrush(Qt::green,style));
}
