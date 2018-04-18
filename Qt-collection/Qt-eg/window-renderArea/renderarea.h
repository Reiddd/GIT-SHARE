#ifndef RENDERAREA
#define RENDERAREA

#include <QWidget>
#include <QSize>
#include <QPen>
#include <QPixmap>

class RenderArea:public QWidget
{
    Q_OBJECT
public:
    enum Shape{Line, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc, Chord, Pie, Path, Text, Pixmap};

    RenderArea(QWidget* parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void setShape(Shape shape);
    void setPen(const QPen& pen);
    void setBrush(const QBrush& brush);
    void setAntialiased(bool antialiased);
    void setTransformed(bool transformed);

protected:
    void paintEvent(QPaintEvent* event);

private:
    Shape shape;
    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;
};

#endif // RENDERAREA
