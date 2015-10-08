#include "vector.h"

#include <QDebug>

#include <math.h>

Vector::Vector(double vx, double vy, double vz)
{
    x = vx;
    y = vy;
    z = vz;
}

Vector::Vector()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

void Vector::unit()
{
    double s = len();
    if (s > 0.000001)
    {
        x /= s;
        y /= s;
        z /= s;
    }
}

double Vector::len()
{
    return sqrt(x * x + y * y + z * z);
}

double Vector::operator *(Vector a)
{
    return x * a.x + y * a.y + z * a.z;
}

Vector Vector::operator +(Vector a)
{
    return Vector(x + a.x, y + a.y, z + a.z);
}

Vector Vector::operator -(Vector a)
{
    return Vector(x - a.x, y - a.y, z - a.z);
}

Vector Vector::operator +=(Vector a)
{
    x += a.x;
    y += a.y;
    z += a.z;
    return *this;
}

Vector Vector::operator *(double k)
{
    return Vector(x * k, y * k, z * k);
}

void Vector::print()
{
    qDebug() << x << y << z;
}

double Vector::operator ^(Vector a)
{
    if (this->len() < 0.000001 || a.len() < 0.000001)
    {
        return 0;
    }
    return ((*this) * a) / (this->len() * a.len());
}
