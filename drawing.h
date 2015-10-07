#ifndef DRAWING_H
#define DRAWING_H

#include "surface.h"
#include "triangle.h"
#include "point3d.h"
#include "utils.h"

#include <QImage>

class FlatDrawing
{
private:
    QImage *bmp;
    QPoint *texA;
    QPoint *texB;
    QPoint *texC;
protected:
    QImage *textureImg;
    Surface *surface;
    double **zBuffer;

    Point3D *A;
    Point3D *B;
    Point3D *C;

    int texXA;
    int texXB;
    int texYA;
    int texYB;

    int width;
    int height;

    Vector *observer;
    Vector *light;
public:
    FlatDrawing(QImage *, Surface *, Vector *obs, Vector *sun, double **, QImage *, int, int);

    void setTexels(Texels *texels, Triangle *polygon);
    void setVertices(Vertices *vertices, Triangle *polygon);
    void setPixel(QColor current, int i, int j);

    // в порядке использования
    virtual void setA();
    virtual void setInterpolatedA(double k);
    virtual void setBCInterpolatedB(double k);
    virtual void setB();
    virtual void setABInterpolatedB(double k);
    virtual void swapAB();
    virtual void calculatePixel(int xp, int yp, double sz, double k, QColor c, Vector n);
};

class HuroDrawing : public FlatDrawing
{
private:
    QColor cola;
    QColor colb;

public:
    HuroDrawing(QImage *, Surface*, Vector *, Vector *, double **, QImage *, int, int);

    virtual void setA();
    virtual void setInterpolatedA(double k);
    virtual void setBCInterpolatedB(double k);
    virtual void setB();
    virtual void setABInterpolatedB(double k);
    virtual void swapAB();
    virtual void calculatePixel(int xp, int yp, double sz, double k, QColor c, Vector n);
};

class FongDrawing : public FlatDrawing
{
private:
    Vector veca;
    Vector vecb;

public:
    FongDrawing(QImage *, Surface*, Vector *, Vector *, double **, QImage *, int, int);

    virtual void setA();
    virtual void setInterpolatedA(double k);
    virtual void setBCInterpolatedB(double k);
    virtual void setB();
    virtual void setABInterpolatedB(double k);
    virtual void swapAB();
    virtual void calculatePixel(int xp, int yp, double sz, double k, QColor c, Vector n);
};

#endif // DRAWING_H
