#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
private:
    double x;
    double y;
    double z_;

public:
    Vector(double vx, double vy, double vz);
    Vector();

    double z();

    void unit();
    double len();
    double operator *(Vector a);
    Vector operator +(Vector a);
    Vector operator -(Vector a);
    Vector operator +=(Vector a);
    Vector operator *(double k);
    void print();
    double operator ^(Vector a);

    void setX(double vx);
    void setY(double vy);
    void setZ(double vz);
};

#endif // VECTOR_H
