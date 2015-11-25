#include "drawing.h"
#include "tripolygon.h"

#include <QList>
#include <QPoint>
#include <QColor>

void FlatDrawing::setDataArrays(QList<Point3D>* vs, QList<QPoint>* ts, QList<TriPolygon> *ps)
{
    vertices = vs;
    texels = ts;
    polygons = ps;
}

void FlatDrawing::setPolygon(int idx)
{
    TriPolygon *polygon = &polygons->operator [](idx);

    A = &vertices->operator [](polygon->a);
    B = &vertices->operator [](polygon->b);
    C = &vertices->operator [](polygon->c);

    if (surface->isTextured)
    {
        texA = &texels->operator [](polygon->a);
        texB = &texels->operator [](polygon->b);
        texC = &texels->operator [](polygon->c);
    }
}

QColor FlatDrawing::getTextureColor(double k)
{
    QColor texColor;
    if (surface->isTextured)
    {
        int x = texXA + (double)(texXB - texXA) * k;
        int y = texYA + (double)(texYB - texYA) * k;
        if (surface->textureImg.valid(x, y))
        {
            texColor = QColor(surface->textureImg.pixel(x, y));
        }
    }
    return texColor;
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

