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

    bool isCycle;

    SurfaceBorder();
    SurfaceBorder(int iu, int iv, int xu, int xv, bool cycle = true);
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

#endif // SURFACEFUNCTION_H
