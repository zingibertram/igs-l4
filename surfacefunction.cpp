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
    // полувывернута
    border = new SurfaceBorder(0, 0, 360, 180, false);
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
    // вывернут
    border = new SurfaceBorder(0, 0, 720, 360);
}

Matrix Trefoil::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = snd * cos(u) * cos(v) + fst * cos(u) * (1.5 + sin(1.5 * u) / 2);
    double y = snd * sin(u) * cos(v) + fst * sin(u) * (1.5 + sin(1.5 * u) / 2);
    double z = snd * sin(v) + 2 * fst / 3 * cos(1.5 * u);

    return Matrix(Point3D(x, y, z));
}

Seashell::Seashell() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 1440, 360, false);
}

Matrix Seashell::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = u * cos(u) * (cos(v) + 1);
    double y = u * sin(u) * (cos(v) + 1);
    double z = u * sin(v) - pow((u + 3) / 8.0 * (180 * radianScal), 2) - 20;

    return Matrix(Point3D(snd * x, snd * y, snd * z));
}

KleinBottle::KleinBottle() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix KleinBottle::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (snd + cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (snd + cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = sin(u / 2.0) * sin(v) + cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(fst * x, fst * y, fst * z));
}
