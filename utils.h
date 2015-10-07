#ifndef UTILS_H
#define UTILS_H

#include "triangle.h"
#include "point3d.h"
#include "surface.h"

typedef QList<Triangle> Polygons;
typedef QMap<VertexIndex, Point3D> Vertices;
typedef QMap<VertexIndex, QPoint> Texels;

namespace U
{
    QColor colorInterpolation(QColor max, QColor min, double kmax, double kmin);
    QColor calcColor(Surface *surface, Vector *observer, Vector *light, Vector n, bool isColor, QColor tex = QColor(), bool isTextured = false);
    QColor calcColorImpl(Surface *surface, Vector observer, Vector light, Vector n, QColor c);
}

#endif // UTILS_H
