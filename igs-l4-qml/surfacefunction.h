#ifndef SURFACEFUNCTION_H
#define SURFACEFUNCTION_H

#include "matrix.h"

#include <QString>

struct SurfaceBorder
{
    int minU;
    int minV;
    int maxU;
    int maxV;

    int dU;
    int dV;

    bool isUCycle;
    bool isVCycle;

    SurfaceBorder();
    SurfaceBorder(int iu, int iv, int xu, int xv, bool uCycle = true, bool vCycle = true);
};

class SurfaceFunction
{
protected:
    static const double radianScal = 3.14159265 / 180.0;
    double fst;
    double snd;

    SurfaceBorder* border;

public:
    SurfaceFunction();
    void setParams(double f, double s);
    void setFirstParam(double f);
    void setSecondParam(double s);
    SurfaceBorder* surfaceBorder();
    virtual Matrix getVertex(double degu, double degv) = 0;
};

class Sphere : public SurfaceFunction
{
public:
    Sphere();
    virtual Matrix getVertex(double degu, double degv);
};

class Torus : public SurfaceFunction
{
public:
    Torus();
    virtual Matrix getVertex(double degu, double degv);
};

class Hourglass : public SurfaceFunction
{
public:
    Hourglass();
    virtual Matrix getVertex(double degu, double degv);
};

class Trefoil : public SurfaceFunction
{
public:
    Trefoil();
    virtual Matrix getVertex(double degu, double degv);
};

class Seashell : public SurfaceFunction
{
public:
    Seashell();
    virtual Matrix getVertex(double degu, double degv);
};

class KleinBottle : public SurfaceFunction
{
public:
    KleinBottle();
    virtual Matrix getVertex(double degu, double degv);
};


// Conical spiral modification of cliffordtorus
class ConicalSpiralModCliffordTorus : public SurfaceFunction
{
public:
    ConicalSpiralModCliffordTorus();
    virtual Matrix getVertex(double degu, double degv);
};

// Spiral modification of cliffordtorus
class SpiralModCliffordTorus : public SurfaceFunction
{
public:
    SpiralModCliffordTorus();
    virtual Matrix getVertex(double degu, double degv);
};

// Ñliffordtorus
class CliffordTorus : public SurfaceFunction
{
public:
    CliffordTorus();
    virtual Matrix getVertex(double degu, double degv);
};

// Hyperbolic-Helicoid
class HyperbolicHelicoid : public SurfaceFunction
{
public:
    HyperbolicHelicoid();
    virtual Matrix getVertex(double degu, double degv);
};

// Catenoid
class Catenoid : public SurfaceFunction
{
public:
    Catenoid();
    virtual Matrix getVertex(double degu, double degv);
};

// Helicoid
class Helicoid : public SurfaceFunction
{
public:
    Helicoid();
    virtual Matrix getVertex(double degu, double degv);
};

/*x = a * Math.Cosh(U) * Math.Cos(V);
y = a * Math.Cosh(U) * Math.Sin(V);
z = a * U;*/
class Surface1 : public SurfaceFunction
{
public:
    Surface1();
    virtual Matrix getVertex(double degu, double degv);
};

// Two-sheeted hyperboloid a,b,c = a
class Hyperboloid2Sheets : public SurfaceFunction
{
public:
    Hyperboloid2Sheets();
    virtual Matrix getVertex(double degu, double degv);
};

// One-sheeted hyperboloid a,b,c = a
class Hyperboloid1Sheet : public SurfaceFunction
{
public:
    Hyperboloid1Sheet();
    virtual Matrix getVertex(double degu, double degv);
};

// Conical spiral R = a, r = a/2, p = 40, k = 10
class ConicalSpiral : public SurfaceFunction
{
public:
    ConicalSpiral();
    virtual Matrix getVertex(double degu, double degv);
};

// Spiral R = a, r = a/2, k = 30
class Spiral : public SurfaceFunction
{
public:
    Spiral();
    virtual Matrix getVertex(double degu, double degv);
};

// #####
/*x = a / 2 * (1 + Math.Cos(V)) * Math.Cos(U);
y = a / 2 * (1 + Math.Cos(V)) * Math.Sin(U);
z = -Math.Tanh(U - Math.PI) * a * Math.Sin(V);*/
class Surface2 : public SurfaceFunction
{
public:
    Surface2();
    virtual Matrix getVertex(double degu, double degv);
};

//Cross cup
class CrossCup : public SurfaceFunction
{
public:
    CrossCup();
    virtual Matrix getVertex(double degu, double degv);
};

//Astroidal ellipsoid
class AstroidalEllipsoid : public SurfaceFunction
{
public:
    AstroidalEllipsoid();
    virtual Matrix getVertex(double degu, double degv);
};

// Eight surface
class EightSurface : public SurfaceFunction
{
public:
    EightSurface();
    virtual Matrix getVertex(double degu, double degv);
};

/*x = a * Math.Sin(2 * U) * Math.Pow(Math.Sin(V), 2);
y = a * Math.Sin(U) * Math.Cos(2 * V);
z = a * Math.Cos(U) * Math.Sin(2 * V);*/
class Surface3 : public SurfaceFunction
{
public:
    Surface3();
    virtual Matrix getVertex(double degu, double degv);
};

/*x = (a + a * Math.Cos(V)) * Math.Sin(U);
y = (a + a * Math.Cos(V)) * Math.Cos(U);
z = a * Math.Sin(U);*/
class Surface4 : public SurfaceFunction
{
public:
    Surface4();
    virtual Matrix getVertex(double degu, double degv);
};

#endif // SURFACEFUNCTION_H
