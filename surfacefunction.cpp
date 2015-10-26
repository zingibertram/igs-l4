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
    border = new SurfaceBorder(0, 0, 360, 180);
}

Matrix Sphere::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = fst * sin(v) * cos(u);
    double y = fst * sin(v) * sin(u);
    double z = fst * cos(v);

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

    double x = snd * cos(u) * cos(v) + fst * cos(u) * (1.5 + sin(1.5 * u) / 2);
    double y = snd * sin(u) * cos(v) + fst * sin(u) * (1.5 + sin(1.5 * u) / 2);
    double z = snd * sin(v) + 2 * fst / 3 * cos(1.5 * u);

    return Matrix(Point3D(x, y, -z));
}

Seashell::Seashell() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 720, 360, false);
}

Matrix Seashell::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = fst * u * cos(u) * (cos(v) + 1);
    double y = fst * u * sin(u) * (cos(v) + 1);
    double z = fst * pow((u + 3) / 8.0 * (180 * radianScal), 2) - fst * u * sin(v);

    return Matrix(Point3D(x, y, z));
}

KleinBottle::KleinBottle() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360, false);
}

Matrix KleinBottle::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

ConicalSpiralModCliffordTorus::ConicalSpiralModCliffordTorus() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix ConicalSpiralModCliffordTorus::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = fst * cos(10 * radianScal * v + u + v) / (sqrt(2) + cos(v - u));
    double y = fst * sin(10 * radianScal * v + u + v) / (sqrt(2) + cos(v - u));
    double z = fst * sin(v - u) / (sqrt(2) + cos(v - u)) + fst * snd * degv;

    return Matrix(Point3D(x, y, z));
}

SpiralModCliffordTorus::SpiralModCliffordTorus() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360, false);
}

Matrix SpiralModCliffordTorus::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = fst * cos(u + v) / (sqrt(2) + cos(v - u));
    double y = fst * sin(u + v) / (sqrt(2) + cos(v - u));
    double z = fst * sin(v - u) / (sqrt(2) + cos(v - u)) + 30 * v;

    return Matrix(Point3D(x, y, z));
}

CliffordTorus::CliffordTorus() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix CliffordTorus::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = fst * cos(u + v) / (sqrt(2) + cos(v - u));
    double y = fst * sin(u + v) / (sqrt(2) + cos(v - u));
    double z = fst * sin(v - u) / (sqrt(2) + cos(v - u));

    return Matrix(Point3D(x, y, z));
}

HyperbolicHelicoid::HyperbolicHelicoid() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix HyperbolicHelicoid::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

Catenoid::Catenoid() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix Catenoid::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

Helicoid::Helicoid() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix Helicoid::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

Surface1::Surface1() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix Surface1::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

Hyperboloid2Sheets::Hyperboloid2Sheets() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix Hyperboloid2Sheets::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

Hyperboloid1Sheet::Hyperboloid1Sheet() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix Hyperboloid1Sheet::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

ConicalSpiral::ConicalSpiral() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix ConicalSpiral::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

Spiral::Spiral() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix Spiral::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

Surface2::Surface2() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix Surface2::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

CrossCup::CrossCup() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix CrossCup::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

AstroidalEllipsoid::AstroidalEllipsoid() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix AstroidalEllipsoid::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

EightSurface::EightSurface() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix EightSurface::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

Surface3::Surface3() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix Surface3::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}

Surface4::Surface4() :
    SurfaceFunction()
{
    border = new SurfaceBorder(0, 0, 360, 360);
}

Matrix Surface4::getVertex(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * cos(u);
    double y = (fst + snd * cos(u / 2.0) * sin(v) - sin(u / 2.0) * sin(2.0 * v)) * sin(u);
    double z = snd * sin(u / 2.0) * sin(v) + snd * cos(u / 2.0) * sin(2.0 * v);

    return Matrix(Point3D(x, y, z));
}
