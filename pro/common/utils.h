#ifndef UTILS_H
#define UTILS_H

#include "triangle.h"
#include "point3d.h"
#include "surface.h"
#include "typedefs.h"
#include "tripolygon.h"

#include <QColor>

namespace U
{
    void debugColor(QColor c, QString s);

    QColor colorInterpolation(QColor max, QColor min, double kmax, double kmin);

    QColor calcColor(Surface *surface, Vector n, bool isColor, QColor tex = QColor(), bool isTextured = false);
    QColor calcColorImpl(Surface *surface, Vector n, QColor c);
}

#endif // UTILS_H
