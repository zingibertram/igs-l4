#ifndef SURFACEIMAGE_H
#define SURFACEIMAGE_H

#include "common/matrix.h"
#include "common/point3d.h"
#include "common/surface.h"
#include "common/triangle.h"
#include "common/utils.h"
#include "common/drawing.h"
#include "common/vector.h"
#include "common/surfacecalculation.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPaintEvent>
#include <QPen>
#include <QRgb>

#include <math.h>

class SurfaceImage : public QGraphicsView
{
    Q_OBJECT

public:
    explicit SurfaceImage(QWidget *parent = 0);
    void setSurface(Surface* sur);

private:
    Surface* surface;
    SurfaceCalculation* surfCalc;

    void paintEvent(QPaintEvent* event);
    void drawFrame(QPainter* pai);
    void drawAxis(QPainter* p);
};

#endif // SURFACEIMAGE_H
