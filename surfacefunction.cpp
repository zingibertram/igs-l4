#include "surfacefunction.h"

#include <math.h>

SurfaceBorder::SurfaceBorder()
{
    minU = 0;
    maxU = 360;
    minV = 0;
    maxV = 360;
    isCycle = true;
}

SurfaceBorder::SurfaceBorder(int iu, int iv, int xu, int xv, bool cycle)
{
    minU = iu;
    maxU = xu;
    minV = iv;
    maxV = xv;
    isCycle = cycle;
}

SurfaceFunction::SurfaceFunction()
{
}

void SurfaceFunction::setParams(double f, double s)
{
    fst = f;
    snd = s;
}

SurfaceBorder* SurfaceFunction::surfaceBorder()
{
    return border;
}

Sphere::Sphere() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, -90, 360, 90);
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

Torus::Torus() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
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

Hourglass::Hourglass() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
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

Trefoil::Trefoil() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 720, 360);
}

Matrix Trefoil::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = cos(u) * cos(v) + 3 * cos(u) * (1.5 + sin(0.75 * u));
    double y = sin(u) * cos(v) + 3 * sin(u) * (1.5 + sin(0.75 * u));
    double z = sin(v) + 2 * cos(1.5 * u);

    return Matrix(Point3D(x * fst, y * fst, z * fst));
}
