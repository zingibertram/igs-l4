#include "drawing.h"

#include <QColor>

FlatDrawing::FlatDrawing(Surface *s, double **buffer, QImage *img)
{
    surface = s;
    zBuffer = buffer;
    bmp = img;

    check = 0;

    if (surface->isTextured)
    {
        surface->exterior = QColor(Qt::white);
        surface->interior = QColor(Qt::white);
    }
}

void FlatDrawing::setA()
{
    ++check;
    if (surface->isTextured)
    {
        texXA = texC->x();
        texYA = texC->y();
    }
}

void FlatDrawing::setInterpolatedA(double k)
{
    ++check;
    if (surface->isTextured)
    {
        texXA += k * (double)(texA->x() - texC->x());
        texYA += k * (double)(texA->y() - texC->y());
    }
}

void FlatDrawing::setBCInterpolatedB(double k)
{
    ++check;
    if (surface->isTextured)
    {
        texXB = texC->x() + k * (double)(texB->x() - texC->x());
        texYB = texC->y() + k * (double)(texB->y() - texC->y());
    }
}

void FlatDrawing::setB()
{
    ++check;
    if (surface->isTextured)
    {
        texXB = texB->x();
        texYB = texB->y();
    }
}

void FlatDrawing::setABInterpolatedB(double k)
{
    ++check;
    if (surface->isTextured)
    {
        texXB += k * (double)(texA->x() - texB->x());
        texYB += k * (double)(texA->y() - texB->y());
    }
}

void FlatDrawing::swapAB()
{
    ++check;
    if (surface->isTextured)
    {
        int tex;
        tex = texXA; texXA = texXB; texXB = tex;
        tex = texYA; texYA = texYB; texYB = tex;
    }
}

void FlatDrawing::calculatePixel(int xp, int yp, double sz, double k, QColor c, Vector n)
{
    if (sz - zBuffer[xp][yp] > 0.999)
    {
        QColor current;

        if (surface->isTextured)
        {
            QColor texColor = getTextureColor(k);
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
