#ifndef SURFACEIMAGE_H
#define SURFACEIMAGE_H

#include "matrix.h"
#include "point3d.h"
#include "surface.h"
#include "triangle.h"
#include "utils.h"
#include "drawing.h"
#include "vector.h"
#include "surfacecalculation.h"

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
