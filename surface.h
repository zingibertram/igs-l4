#ifndef SURFACE_H
#define SURFACE_H

#include "vector.h"
#include "surfacefunction.h"

#include <QColor>
#include <QImage>

enum Shading
{
    FLAT, FRAME, FONG, HURO
};

struct Surface
{
    int xRotate;
    int yRotate;
    int zRotate;

    int xOld;
    int yOld;
    int zOld;

    int maxU;
    int maxV;

    int dU;
    int dV;

    int fstParam;
    int sndParam;
    SurfaceFunction* func;

    QColor exterior;
    QColor interior;
    QColor absent;
    QColor dot;

    Shading type;

    double ka;
    double kd;
    double ks;
    int n;
    double alpha;

    bool isTextured;

    QImage textureImg;

    Vector light;
    Vector observer;

    bool isPointsChanged;

    Surface();
};

#endif // SURFACE_H
