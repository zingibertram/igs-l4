#include "vector.h"

#include <QDebug>

#include <math.h>

Vector::Vector(double vx, double vy, double vz)
{
    x = vx;
    y = vy;
    z_ = vz;
}

Vector::Vector()
{
    x = 0.0;
    y = 0.0;
    z_ = 0.0;
}

double Vector::z()
{
    return z_;
}

void Vector::unit()
{
    double s = len();
    if (s > 0.000001)
    {
        x /= s;
        y /= s;
        z_ /= s;
    }
}

double Vector::len()
{
    return sqrt(x * x + y * y + z_ * z_);
}

double Vector::operator *(Vector a)
{
    return x * a.x + y * a.y + z_ * a.z_;
}

Vector Vector::operator +(Vector a)
{
    return Vector(x + a.x, y + a.y, z_ + a.z_);
}

Vector Vector::operator -(Vector a)
{
    return Vector(x - a.x, y - a.y, z_ - a.z_);
}

Vector Vector::operator +=(Vector a)
{
    x += a.x;
    y += a.y;
    z_ += a.z_;
    return *this;
}

Vector Vector::operator *(double k)
{
    return Vector(x * k, y * k, z_ * k);
}

void Vector::print()
{
    qDebug() << x << y << z_;
}

double Vector::operator ^(Vector a)
{
    if (this->len() < 0.000001 || a.len() < 0.000001)
    {
        return 0;
    }
    return ((*this) * a) / (this->len() * a.len());
}
