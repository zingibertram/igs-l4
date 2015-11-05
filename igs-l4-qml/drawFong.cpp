#include "drawing.h"

FongDrawing::FongDrawing(Surface *s, double **buffer, QImage *img, int w, int h)
    :FlatDrawing(s, buffer, img, w, h)
{
}

void FongDrawing::setA()
{
    FlatDrawing::setA();
    veca = C->normal;
}

void FongDrawing::setInterpolatedA(double k)
{
    FlatDrawing::setInterpolatedA(k);
    veca = C->normal * (1 - k) + A->normal * k;
}

void FongDrawing::setBCInterpolatedB(double k)
{
    FlatDrawing::setBCInterpolatedB(k);
    vecb = C->normal * (1 - k) + B->normal * k;
}

void FongDrawing::setB()
{
    FlatDrawing::setB();
    vecb = B->normal;
}

void FongDrawing::setABInterpolatedB(double k)
{
    FlatDrawing::setABInterpolatedB(k);
    vecb = B->normal * (1 - k) + A->normal * k;
}

void FongDrawing::swapAB()
{
    FlatDrawing::swapAB();
    Vector buf = veca;
    veca = vecb;
    vecb = buf;
}

void FongDrawing::calculatePixel(int xp, int yp, double sz, double k, QColor c, Vector n)
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

    if (- 1 < xp && xp < width && - 1 < yp && yp < height)
    {
        if (sz - zBuffer[xp][yp] > 0.999)
        {
            Vector norm;
            QColor current;

            norm = veca + (vecb - veca) * k;
            if (surface->isTextured)
            {
                current = U::calcColor(surface, norm, false, texColor, true);
            }
            else
            {
                current = U::calcColor(surface, norm, false);
            }

            setPixel(current, xp, yp);
            zBuffer[xp][yp] = sz;
        }
    }
}
