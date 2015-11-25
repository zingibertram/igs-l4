#ifndef TRIPOLYGON_H
#define TRIPOLYGON_H

#include "vector.h"

#include <QColor>

struct TriPolygon
{
    int a;
    int b;
    int c;

    Vector normal;
    QColor color;
    double z;

    TriPolygon(int i, int j, int k);
};

bool operator <(TriPolygon t1, TriPolygon t2);

#endif // TRIPOLYGON_H
