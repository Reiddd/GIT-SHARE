#include "graphmodifier.h"

#include <QtDataVisualization/qcategory3daxis.h>
#include <QtDataVisualization/qvalue3daxis.h>
#include <QtDataVisualization/qbardataproxy.h>
#include <QtDataVisualization/q3dscene.h>
#include <QtDataVisualization/q3dcamera.h>
#include <QtDataVisualization/qbar3dseries.h>
#include <QtDataVisualization/q3dtheme.h>

#include <QtCore/QTime>
#include <QtWidgets/QComboBox>
#include <QtCore/qmath.h>

using namespace QtDataVisualization;

const QString celsiusString = QString(QChar(0xB0)) + "C";

GraphModifier::GraphModifier(Q3DBars* bargraph):
    m_graph(bargraph),
    m_xRotation(0.0f),
    m_yRotation(0.0f),
    m_fontSize(30),
    m_segments(4),
    m_subSegments(3),
    m_minval(-20.0f),
    m_maxval(20.0f),
    m_temperatureAxis(new QValue3DAxis),
    m_yearAxis(new QCategory3DAxis),
    m_monthAxis(new QCategory3DAxis),
    m_primarySeries(new QBar3DSeries),
    m_secondarySeries(new QBar3DSeries),
    m_barMesh(QAbstract3DSeries::MeshBevelBar),
    m_smooth(false)
{
    m_graph->SetShadowQuality(QAbstract3DGraph::ShadowQualitySoftMedium);
    m_graph->activeTheme()->setBackgroundEnabled(false);
    m_graph->activeTheme()->setFont(QFont("Times New Roman,m_fontSize"));
    m_graph->activeTheme()->setLabelBackgroundEnabled(true);
    m_graph->setMultiSeriesUniform(true);

    m_months<<"January"<<"February"<<"March"<<"April"<<"May"<<"June"<<"July"<<"August"<<"September"<<"October"<<"November"<<"December";
    m_years<<"2006"<<"2007"<<"2008"<<"2009"<<"2010"<<"2011"<<"2012"<<"2013";

    m_temperatureAxis->SetTitle("Average temperature");
    m_temperatureAxis->setSegmentCount(m_segments);
    m_temperatureAxis->setSubSegmentCount(m_subSegments);
    m_temperatureAxis->setRange(m_minval,m_maxval);
    m_temperatureAxis->setLabelFormat(QString(QStringLiteral("%.1f") + celsiusString));
    m_temperatureAxis->setLabelAutoRotation(30.0f);
    m_temperatureAxis->setTitleVisible(true);

    m_yearAxis->setTitle("Year");
    m_yearAxis->SetLabelAutoRotation(30.0f);
    m_yearAxis->SetTitleVisible(true);
    m_monthAxis->setTitle("Month");
    m_monthAxis->setLabelAutoRotation(30.0f);
    m_monthAxis->setTitleVisible(true);

    m_graph->setValueAxis(m_temperatureAxis);
    m_graph->setRowAxis(m_yearAxis);
    m_graph->setColumnAxis(m_monthAxis);

    m_primarySeries->SetItemLabelFormat(QStringLiteral("Oulu - @colLabel @rowLabel: @valueLabel"));
    m_primarySeries->setMesh(QAbstract3DSeries::MeshBevelBar);
    m_primarySeries->setMeshSmooth(false);

    m_secondarySeries->setItemLabelFormat(QStringLiteral("Helsinki - @colLabel @rowLabel: @valueLabel"));
    m_secondarySeries->setMesh(QAbstract3DSeries::MeshBevelBar);
    m_secondarySeries->setMeshSmooth(false);
    m_secondarySeries->setVisible(false);

    m_graph->addSeries(m_primarySeries);
    m_graph->addSeries(m_secondarySeries);

    changePresetCamera();

    resetTemperatureData();

    Q3DCamera* camera = m_graph->scene()->activeCamera();
    m_defaultAngleX = camera->xRotation();
    m_defaultAngleY = camera->yRotation();
    m_defaultZoom = camera->zoomLevel();
    m_defaultTarget = camera->target();

    m_animationCameraX.setTargetObject(camera);
    m_animationCameraY.setTargetObject(camera);
    m_animationCameraZoom.setTargetObject(camera);
    m_animationCameraTarget.setTargetObject(camera);

    m_animationCameraX.setPropertyName("xRotation");
    m_animationCameraY.setPropertyName("yRotation");
    m_animationCameraZoom.setPropertyName("zoomLevel");
    m_animationCameraTarget.setPropertyName("target");

    int duration = 1700;
    m_animationCameraX.setDuration(duration);
    m_animationCameraY.setDuration(duration);
    m_animationCameraZoom.setDuration(duration);
    m_animationCameraTarget.setDuration(duration);

    qreal zoomOutFraction = 0.3;
    m_animationCameraX.setKeyValueAt(zoomOutFraction,QVariant::fromValue(0.0f));
    m_animationCameraY.setKeyValueAt(zoomOutFraction,QVariant::fromValue(90.f));
    m_animationCameraZoom.setKeyValueAt(zoomOutFraction,QVariant::fromValue(50.0f));
    m_animationCameraTarget.setKeyValueAt(zoomOutFraction,QVariant::fromValue(QVector3D(0.0f,0.0f,0.0f)));
}

GraphModifier::~GraphModifier()
{
    delete m_graph;
}

void GraphModifier::resetTemperatureData()
{
    static const float tempOulu[8][12] = {
        {-6.7f, -11.7f, -9.7f, 3.3f, 9.2f, 14.0f, 16.3f, 17.8f, 10.2f, 2.1f, -2.6f, -0.3f},    // 2006
        {-6.8f, -13.3f, 0.2f, 1.5f, 7.9f, 13.4f, 16.1f, 15.5f, 8.2f, 5.4f, -2.6f, -0.8f},      // 2007
        {-4.2f, -4.0f, -4.6f, 1.9f, 7.3f, 12.5f, 15.0f, 12.8f, 7.6f, 5.1f, -0.9f, -1.3f},      // 2008
        {-7.8f, -8.8f, -4.2f, 0.7f, 9.3f, 13.2f, 15.8f, 15.5f, 11.2f, 0.6f, 0.7f, -8.4f},      // 2009
        {-14.4f, -12.1f, -7.0f, 2.3f, 11.0f, 12.6f, 18.8f, 13.8f, 9.4f, 3.9f, -5.6f, -13.0f},  // 2010
        {-9.0f, -15.2f, -3.8f, 2.6f, 8.3f, 15.9f, 18.6f, 14.9f, 11.1f, 5.3f, 1.8f, -0.2f},     // 2011
        {-8.7f, -11.3f, -2.3f, 0.4f, 7.5f, 12.2f, 16.4f, 14.1f, 9.2f, 3.1f, 0.3f, -12.1f},     // 2012
        {-7.9f, -5.3f, -9.1f, 0.8f, 11.6f, 16.6f, 15.9f, 15.5f, 11.2f, 4.0f, 0.1f, -1.9f}      // 2013
    };

    static const float tempHelsinki[8][12] = {
        {-3.7f, -7.8f, -5.4f, 3.4f, 10.7f, 15.4f, 18.6f, 18.7f, 14.3f, 8.5f, 2.9f, 4.1f},      // 2006
        {-1.2f, -7.5f, 3.1f, 5.5f, 10.3f, 15.9f, 17.4f, 17.9f, 11.2f, 7.3f, 1.1f, 0.5f},       // 2007
        {-0.6f, 1.2f, 0.2f, 6.3f, 10.2f, 13.8f, 18.1f, 15.1f, 10.1f, 9.4f, 2.5f, 0.4f},        // 2008
        {-2.9f, -3.5f, -0.9f, 4.7f, 10.9f, 14.0f, 17.4f, 16.8f, 13.2f, 4.1f, 2.6f, -2.3f},     // 2009
        {-10.2f, -8.0f, -1.9f, 6.6f, 11.3f, 14.5f, 21.0f, 18.8f, 12.6f, 6.1f, -0.5f, -7.3f},   // 2010
        {-4.4f, -9.1f, -2.0f, 5.5f, 9.9f, 15.6f, 20.8f, 17.8f, 13.4f, 8.9f, 3.6f, 1.5f},       // 2011
        {-3.5f, -3.2f, -0.7f, 4.0f, 11.1f, 13.4f, 17.3f, 15.8f, 13.1f, 6.4f, 4.1f, -5.1f},     // 2012
        {-4.8f, -1.8f, -5.0f, 2.9f, 12.8f, 17.2f, 18.0f, 17.1f, 12.5f, 7.5f, 4.5f, 2.3f}       // 2013
    };

    QBarDataArray* dataSet = new QBarDataArray;
    QBarDataArray* dataSet2 = new QBarDataArray;
    QBarDataRow* dataRow;
    QBarDataRow* dataRow2;

    dataSet->reserve(m_years.size());
    for(int year = 0;year<m_years.size();year++)
    {
        dataRow = new QBarDataRow(m_months.size());
        dataRow2 = new QBarDataRow(m_months.size());
        for(int month = 0;month<m_months.size();month++)
        {
            (*dataRow)[month].setValue(tempOulu[year][month]);
            (*dataRow2)[month].setValue(tempHelsinki[year][month]);
        }
        dataSet->append(dataRow);
        dataSet2->append(dataRow2);
    }
    m_primarySeries->dataProxy()->resetArray(dataSet,m_years,m_months);
    m_secondarySeries->dataProxy()->resetArray(dataSet2,m_years,m_months);
}

void GraphModifier::changeRange(int range)
{
    if(range>=m_years.count())
        m_yearAxis->setRange(0,m_years.count()-1);
    else
        m_yearAxis->setRange(range,range);
}

void GraphModifier::changeStyle(int style)
{
    QComboBox* comboBox = qobject_cast<QComboBox*>(sender());
    if(comboBox)
    {
        m_barMesh = QAbstract3DSeries::Mesh(comboBox->itemData(style).toInt());
        m_primarySeries->setMesh(m_barMesh);
        m_secondarySeries->setMesh(m_barMesh);
    }
}
