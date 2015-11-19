#include "drawing.h"

#include <QList>
#include <QPoint>

void FlatDrawing::setTexels(QList<QPoint> *texels, TriPolygon *polygon)
{
    if (surface->isTextured)
    {
        texA = &texels->operator [](polygon->a);
        texB = &texels->operator [](polygon->b);
        texC = &texels->operator [](polygon->c);
    }
}

void FlatDrawing::setVertices(QList<Point3D>* vertices, TriPolygon* polygon)
{
    A = &vertices->operator [](polygon->a);
    B = &vertices->operator [](polygon->b);
    C = &vertices->operator [](polygon->c);
}

void FlatDrawing::setPixel(QColor current, int i, int j)
{
    QColor bufCol(bmp->pixel(i, j));
    double one_Minus_Alpha = 1.0 - surface->alpha;
    int r = surface->alpha * (double)current.red() + one_Minus_Alpha * (double)bufCol.red();
    int g = surface->alpha * (double)current.green() + one_Minus_Alpha * (double)bufCol.green();
    int b = surface->alpha * (double)current.blue() + one_Minus_Alpha * (double)bufCol.blue();
    bmp->setPixel(i, j, QColor(std::min(255, r), std::min(255, g), std::min(255, b)).rgb());
}

