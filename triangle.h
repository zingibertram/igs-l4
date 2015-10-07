#ifndef PLAIN_H
#define PLAIN_H

#include "point3d.h"
#include "vector.h"

#include <QPair>
#include <QColor>

int min(int a, int b);
void debugColor(QColor c, QString s);

typedef QPair<int, int> VertexIndex;

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
bool operator <(Triangle t1, Triangle t2);

#endif // PLAIN_H
