#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
private:
    double x;
    double y;
    double z;

public:
    Vector(double vx, double vy, double vz);
    Vector();

    void unit();
    double len();
    double operator *(Vector a);
    Vector operator +(Vector a);
    Vector operator -(Vector a);
    Vector operator +=(Vector a);
    Vector operator *(double k);
    void print();
    double operator ^(Vector a);
};

#endif // VECTOR_H
