#include "utils.h"
#include "surface.h"

#include <QColor>
#include <QDebug>

#include <math.h>
#include <algorithm>

void U::debugColor(QColor c, QString s)
{
    qDebug() << s << c.red() << ' ' << c.green() << ' ' << c.blue();
}

QColor U::colorInterpolation(QColor max, QColor min, double kmax, double kmin)
{
    // ��������
    // QColor::setRgb: RGB parameters out of range
    int r = max.red() * kmax + min.red() * kmin;
    if (r > 255)
    {
        r = 255;
    }
    int g = max.green() * kmax + min.green() * kmin;
    if (g > 255)
    {
        g = 255;
    }
    int b = max.blue() * kmax + min.blue() * kmin;
    if (b > 255)
    {
        b = 255;
    }
//    int a = max.alpha() * kmax + min.alpha() * kmin;
//    if (a > 255)
//    {
//        a = 255;
//    }
    return QColor(r, g, b);
}

QColor U::calcColor(Surface *surface, Vector n, bool isColor, QColor tex, bool isTextured)
{
    QColor c = n.z() > 0 ? surface->exterior  : surface->interior;

    if (isColor)
    {
        return c;
    }

    if (isTextured)
    {
        c = tex;
    }

    return calcColorImpl(surface, n, c);
}

QColor U::calcColorImpl(Surface *surface, Vector n, QColor c)
{
    double cosnl = n ^ surface->light;
    if (n.z() * cosnl <= 0)
    {
        cosnl = 0;
    }
    cosnl = surface->kd * fabs(cosnl);

    Vector r;
    double nLength = n.len();
    if (nLength > 0.00001)
    {
        r = n * (2 * (n * surface->light) * (1.0 / nLength)) - surface->light;
    }

    double cosor = surface->observer ^ r;
    if (cosor < 0)
    {
        cosor = 0;
    }

    cosor = surface->ks * pow(cosor, surface->n);

    int R = std::min(surface->absent.red(), c.red()) * surface->ka
          + std::min(surface->dot.red(), c.red()) * cosnl
          + surface->dot.red() * cosor;
    int G = std::min(surface->absent.green(), c.green()) * surface->ka
          + std::min(surface->dot.green(), c.green()) * cosnl
          + surface->dot.green() * cosor;
    int B = std::min(surface->absent.blue(), c.blue()) * surface->ka
          + std::min(surface->dot.blue(), c.blue()) * cosnl
          + surface->dot.blue() * cosor;
//    qDebug() << std::min(R, 255) << std::min(G, 255) << std::min(B, 255);
    return QColor(std::min(R, 255), std::min(G, 255), std::min(B, 255));
}
