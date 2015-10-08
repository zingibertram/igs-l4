#include "drawing.h"

HuroDrawing::HuroDrawing(QImage *texture, Surface *s, double **buffer, QImage *img, int w, int h)
    :FlatDrawing(texture, s, buffer, img, w, h)
{
}

void HuroDrawing::setA()
{
    FlatDrawing::setA();
    cola = C->color;
}

void HuroDrawing::setInterpolatedA(double k)
{
    FlatDrawing::setInterpolatedA(k);
    cola = U::colorInterpolation(A->color, C->color, k, 1 - k);
}

void HuroDrawing::setBCInterpolatedB(double k)
{
    FlatDrawing::setBCInterpolatedB(k);
    colb = U::colorInterpolation(B->color, C->color, k, 1 - k);
}

void HuroDrawing::setB()
{
    FlatDrawing::setB();
    colb = B->color;
}

void HuroDrawing::setABInterpolatedB(double k)
{
    FlatDrawing::setABInterpolatedB(k);
    colb = U::colorInterpolation(A->color, B->color, k, 1 - k);
}

void HuroDrawing::swapAB()
{
    FlatDrawing::swapAB();
    QColor buf = cola;
    cola = colb;
    colb = buf;
}

void HuroDrawing::calculatePixel(int xp, int yp, double sz, double k, QColor c, Vector n)
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
            QColor current;

            QColor tmpCol = U::colorInterpolation(colb, cola, k, 1 - k);
            if (surface->isTextured)
            {
                int r = tmpCol.redF() * texColor.redF();
                int g = tmpCol.greenF() * texColor.greenF();
                int b = tmpCol.blueF() * texColor.blueF();
                current = QColor(r, g, b);
            }
            else
            {
                current = tmpCol;
            }

            setPixel(current, xp, yp);
            zBuffer[xp][yp] = sz;
        }
    }
}
