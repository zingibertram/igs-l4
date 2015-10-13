#include "surfacefunction.h"

#include <math.h>

SurfaceFunction::SurfaceFunction()
{
}

void SurfaceFunction::setParams(double f, double s)
{
    fst = f;
    snd = s;
}

Matrix Sphere::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = fst * sin(u) * cos(v);
    double y = fst * sin(u) * sin(v);
    double z = fst * cos(u);

    return Matrix(Point3D(x, y, z));
}

Matrix Torus::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u)) * cos(v);
    double y = (fst + snd * cos(u)) * sin(v);
    double z = snd * sin(u);

    return Matrix(Point3D(x, y, z));
}

Matrix Hourglass::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (snd + (fst + snd * cos(u)) * cos(v)) * sin(u);
    double y = (snd + (fst + snd * cos(u)) * sin(v)) * sin(u);
    double z = snd * sin(u) + fst * sin(u);

    return Matrix(Point3D(x, y, z));
}
