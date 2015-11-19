#include "point3d.h"
#include <math.h>
#include <stdio.h>

Point3D::Point3D()
{
    coorX = 0;
    coorY = 0;
    coorZ = 0;
    normal = Vector();
}

Point3D::Point3D(double tx, double ty, double tz)
{
    coorX = tx;
    coorY = ty;
    coorZ = tz;
    normal = Vector();
}

Point3D::Point3D(QList<double> coor)
{
    this->setPoint3D(coor);
    normal = Vector();
}

double Point3D::x()
{
    return coorX;
}

double Point3D::y()
{
    return coorY;
}

double Point3D::z()
{
    return coorZ;
}

double Point3D::maxCoor()
{
    if (coorX >= coorY && coorX >= coorZ)
    {
        return coorX;
    }
    else
    {
        if (coorY >= coorZ)
        {
            return coorY;
        }
        else
        {
            return coorZ;
        }
    }
}

void Point3D::setX(double tx)
{
    coorX = tx;
}

void Point3D::setY(double ty)
{
    coorY = ty;
}

void Point3D::setZ(double tz)
{
    coorZ = tz;
}

void Point3D::setPoint3D(double tx, double ty, double tz)
{
    coorX = tx;
    coorY = ty;
    coorZ = tz;
}

Point3D Point3D::operator *(double d)
{
    Point3D buf;
    buf.coorX = this->coorX * d;
    buf.coorY = this->coorY * d;
    buf.coorZ = this->coorZ * d;
    return buf;
}

Point3D Point3D::operator *=(double d)
{
    coorX *= d;
    coorY *= d;
    coorZ *= d;
    return *this;
}

bool Point3D::operator ==(Point3D t)
{
    if (this->coorX == t.coorX && this->coorY == t.coorY && this->coorZ == t.coorZ)
    {
        return true;
    }
    return false;
}

void Point3D::print()
{
    printf("\nPoint(%f, %f, %f)\n", coorX, coorY, coorZ);
}

double Point3D::to(Point3D t)
{
    double dx = coorX - t.coorX;
    double dy = coorY - t.coorY;
    double dz = coorZ - t.coorZ;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

void Point3D::setPoint3D(QList<double> coor)
{
    if (coor.count() == 3)
    {
        coorX = coor[0];
        coorY = coor[1];
        coorZ = coor[2];
    }
    else
    {
        coorX = 0;
        coorY = 0;
        coorZ = 0;
    }
}

QList<double> Point3D::coordinates()
{
    QList<double> coor;
    coor << coorX << coorY << coorZ;
    return coor;
}

QPointF Point3D::toQPoint()
{
    return QPointF(coorX, - coorY);
}
