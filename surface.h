#ifndef SURFACE_H
#define SURFACE_H

#include "point3d.h"
#include "vector.h"

#include <QColor>

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
    int lstParam;

    QColor exterior;
    QColor interior;
    QColor absent;
    QColor dot;

    bool isFlat;
    bool isSort;

    Shading type;

    Point3D illuminant;

    double ka;
    double kd;
    double ks;
    int n;
    double alpha;

    bool isTextured;

    QString textureFile;

    Vector observer;

    Surface();
};

#endif // SURFACE_H
