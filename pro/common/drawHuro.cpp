#include "drawing.h"

HuroDrawing::HuroDrawing(Surface *s, double **buffer, QImage *img)
    :FlatDrawing(s, buffer, img)
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

void HuroDrawing::calculatePixel(int xp, int yp, double sz, double k, QColor /* c */, Vector /* n */)
{
    if (sz - zBuffer[xp][yp] > 0.999)
    {
        QColor current;

        QColor tmpCol = U::colorInterpolation(colb, cola, k, 1 - k);
        if (surface->isTextured)
        {
            QColor texColor = getTextureColor(k);

            double rtex = texColor.red();
            double gtex = texColor.green();
            double btex = texColor.blue();

            double rc = tmpCol.red() / 255.0;
            double gc = tmpCol.green() / 255.0;
            double bc = tmpCol.blue() / 255.0;

            int r = rc * rtex;
            int g = gc * gtex;
            int b = bc * btex;
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
