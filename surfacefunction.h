#ifndef SURFACEFUNCTION_H
#define SURFACEFUNCTION_H

#include "matrix.h"

#include <QString>

class SurfaceFunction
{
protected:
    static const double radianScal = 3.14159265 / 180.0;
    double fst;
    double snd;
    QString _name;
public:
    SurfaceFunction();
    void setParams(double f, double s);
    QString name();
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

#endif // SURFACEFUNCTION_H
