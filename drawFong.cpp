#include "drawing.h"

FongDrawing::FongDrawing(QImage *texture, Surface *s, Vector *obs, Vector *sun, double **buffer, QImage *img, int w, int h)
    :FlatDrawing(texture, s, obs, sun, buffer, img, w, h)
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
        if (textureImg->valid(texPoint))
        {
            texColor = QColor(textureImg->pixel(texPoint));
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
                current = U::calcColor(surface, observer, light, norm, false, texColor, true);
            }
            else
            {
                if (norm.z > 0)
                {
                    current = surface->exterior;
                }
                else
                {
                    current = surface->interior;
                }
                current = U::calcColor(surface, observer, light, norm, false);
            }

            setPixel(current, xp, yp);
            zBuffer[xp][yp] = sz;
        }
    }
}
