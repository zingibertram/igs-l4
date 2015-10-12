#ifndef SURFACEFUNCTION_H
#define SURFACEFUNCTION_H

#include "matrix.h"

class SurfaceFunction
{
protected:
    static const double radianScal = 3.14159265 / 180.0;
    double fst;
    double snd;
public:
    SurfaceFunction();
    void setParams(double f, double s);
    virtual Matrix getVertex(double degu, double degv) = 0;
};

class Sphere : public SurfaceFunction
{
public:
    virtual Matrix getVertex(double degu, double degv);
};

class Torus : public SurfaceFunction
{
public:
    virtual Matrix getVertex(double degu, double degv);
};

class Hourglass : public SurfaceFunction
{
public:
    virtual Matrix getVertex(double degu, double degv);
};

#endif // SURFACEFUNCTION_H
