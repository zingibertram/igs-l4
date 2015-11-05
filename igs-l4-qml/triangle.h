#ifndef PLAIN_H
#define PLAIN_H

#include "point3d.h"
#include "vector.h"
#include "typedefs.h"

#include <QColor>
#include <QList>

struct Triangle
{
    VertexIndex a;
    VertexIndex b;
    VertexIndex c;
    Vector normal;
    QColor color;
    double z;

    Triangle();
};

typedef QList<Triangle> Polygons;

bool operator <(Triangle t1, Triangle t2);

#endif // PLAIN_H
