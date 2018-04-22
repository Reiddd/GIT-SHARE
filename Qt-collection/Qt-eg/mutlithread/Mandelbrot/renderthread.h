#ifndef RENDERTHREAD
#define RENDERTHREAD

#include <QThread>
#include <QSize>
#include <QMutex>
#include <QWaitCondition>

class RenderThread: public QThread
{
    Q_OBJECT;
public:
    RenderThread(QObject* parent = 0);
    ~RenderThread();

    void render(double centerX, double centerY, double scaleFactor, QSize resultSize);

signals:
    void renderedImage(const QImage& image, double scaleFactor);

protected:
    void run() override;

private:
    uint rgbFromWaveLength(double wave);

    QMutex         mutex;
    QWaitCondition condition;
    double         centerX;
    double         centerY;
    double         scaleFactor;
    QSize          resultSize;
    bool           restart;
    bool           abort;

    enum{ColormapSize = 512};
    uint colormap[ColormapSize];
};

#endif // RENDERTHREAD

