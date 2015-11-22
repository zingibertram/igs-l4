#include "drawing.h"

#include <QColor>

FlatDrawing::FlatDrawing(Surface *s, double **buffer, QImage *img, int w, int h)
{
    surface = s;
    zBuffer = buffer;
    bmp = img;

    width = w;
    height = h;

    if (surface->isTextured)
    {
        surface->exterior = QColor(Qt::white);
        surface->interior = QColor(Qt::white);
    }
}

void FlatDrawing::setA()
{
    if (surface->isTextured)
    {
        texXA = texC->x();
        texYA = texC->y();
    }
}

void FlatDrawing::setInterpolatedA(double k)
{
    if (surface->isTextured)
    {
        texXA += k * (double)(texA->x() - texC->x());
        texYA += k * (double)(texA->y() - texC->y());
    }
}

void FlatDrawing::setBCInterpolatedB(double k)
{
    if (surface->isTextured)
    {
        texXB = texC->x() + k * (double)(texB->x() - texC->x());
        texYB = texC->y() + k * (double)(texB->y() - texC->y());
    }
}

void FlatDrawing::setB()
{
    if (surface->isTextured)
    {
        texXB = texB->x();
        texYB = texB->y();
    }
}

void FlatDrawing::setABInterpolatedB(double k)
{
    if (surface->isTextured)
    {
        texXB += k * (double)(texA->x() - texB->x());
        texYB += k * (double)(texA->y() - texB->y());
    }
}

void FlatDrawing::swapAB()
{
    if (surface->isTextured)
    {
        int tex;
        tex = texXA; texXA = texXB; texXB = tex;
        tex = texYA; texYA = texYB; texYB = tex;
    }
}

void FlatDrawing::calculatePixel(int xp, int yp, double sz, double k, QColor c, Vector n)
{
    QPoint texPoint;
    QColor texColor;
    if (surface->isTextured)
    {
        texPoint = QPoint(texXA + (double)(texXB - texXA) * k, texYA + (double)(texYB - texYA) * k);
        if (surface->textureImg.valid(texPoint))
        {
            texColor = QColor(surface->textureImg.pixel(texPoint));
        }
    }

    //if (- 1 < xp && xp < width && - 1 < yp && yp < height)
    {
        if (sz - zBuffer[xp][yp] > 0.999)
        {
            QColor current;

            if (surface->isTextured)
            {
                current = U::calcColor(surface, n, false, texColor, true);
            }
            else
            {
                current = c;
            }

            setPixel(current, xp, yp);
            zBuffer[xp][yp] = sz;
        }
    }
}
