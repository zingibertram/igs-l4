#ifndef VECTOR_H
#define VECTOR_H

#include <QDebug>

#include <math.h>

struct Vector
{
    double x;
    double y;
    double z;

    Vector(double vx, double vy, double vz)
    {
        x = vx;
        y = vy;
        z = vz;
    }

    Vector()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    void unit()
    {
        double s = len();
        if (s > 0.000001)
        {
            x /= s;
            y /= s;
            z /= s;
        }
    }

    double len()
    {
        return sqrt(x * x + y * y + z * z);
    }

    double operator *(Vector a)
    {
        return x * a.x + y * a.y + z * a.z;
    }

    Vector operator +(Vector a)
    {
        return Vector(x + a.x, y + a.y, z + a.z);
    }

    Vector operator -(Vector a)
    {
        return Vector(x - a.x, y - a.y, z - a.z);
    }

    Vector operator +=(Vector a)
    {
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }

    Vector operator *(double k)
    {
        return Vector(x * k, y * k, z * k);
    }

    void print()
    {
        qDebug() << x << y << z;
    }

    double operator ^(Vector a)
    {
        if (this->len() < 0.000001 || a.len() < 0.000001)
        {
            return 0;
        }
        return ((*this) * a) / (this->len() * a.len());
    }
};

#endif // VECTOR_H
