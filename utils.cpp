#include "utils.h"
#include "surface.h"

#include <QColor>

QColor U::colorInterpolation(QColor max, QColor min, double kmax, double kmin)
{
    double r = max.red() * kmax + min.red() * kmin;
    if (r > 255)
    {
        r = 255;
    }
    double g = max.green() * kmax + min.green() * kmin;
    if (g > 255)
    {
        g = 255;
    }
    double b = max.blue() * kmax + min.blue() * kmin;
    if (b > 255)
    {
        b = 255;
    }
    return QColor(r, g, b);
}

QColor U::calcColor(Surface *surface, Vector *observer, Vector *light, Vector n, bool isColor, QColor tex, bool isTextured)
{
    QColor c;
    if (n.z > 0)
    {
        c = surface->exterior;
    }
    else
    {
        c = surface->interior;
    }
    if (isColor)
    {
        return c;
    }

    if (isTextured)
    {
        c = tex;
    }
    Vector _light = *light;
    double cosnl = n ^ _light;
    if (n.z * cosnl <= 0)
    {
        cosnl = 0;
    }
    cosnl = surface->kd * fabs(cosnl);

    Vector r;
    double nLength = n.len();
    if (nLength > 0.00001)
    {
        r = n * (2 * (n * _light) * (1.0 / nLength)) - _light;
    }
    Vector _observer = *observer;
    double cosor = _observer ^ r;
    if (cosor < 0)
    {
        cosor = 0;
    }
    cosor = surface->ks * pow(cosor, surface->n);

    int R = min(surface->absent.red(), c.red()) * surface->ka
          + min(surface->dot.red(), c.red()) * cosnl
          + surface->dot.red() * cosor;
    int G = min(surface->absent.green(), c.green()) * surface->ka
          + min(surface->dot.green(), c.green()) * cosnl
          + surface->dot.green() * cosor;
    int B = min(surface->absent.blue(), c.blue()) * surface->ka
          + min(surface->dot.blue(), c.blue()) * cosnl
          + surface->dot.blue() * cosor;

    return QColor(min(R, 255), min(G, 255), min(B, 255));
}
