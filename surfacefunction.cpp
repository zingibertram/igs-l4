#include "surfacefunction.h"

#include <math.h>

SurfaceFunction::SurfaceFunction()
{
}

QString SurfaceFunction::name()
{
    return _name;
}

void SurfaceFunction::setParams(double f, double s)
{
    fst = f;
    snd = s;
}

Sphere::Sphere()
    :SurfaceFunction()
{
    _name = "Sphere";
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

Torus::Torus()
    :SurfaceFunction()
{
    _name = "Torus";
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

Hourglass::Hourglass()
    :SurfaceFunction()
{
    _name = "Hourglass";
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
