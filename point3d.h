#ifndef POINT3D_H
#define POINT3D_H

#include "triangle.h"

#include <QList>
#include <QPointF>
#include <QColor>

class Point3D
{
private:
    double coorX; // соответствующие
    double coorY; // координаты в
    double coorZ; // 3D пространстве
public:
    Vector normal;
    QColor color;

    Point3D(); // конструктор, создающий точку в начале координат
    Point3D(double tx, double ty, double tz); // конструктор, создающий точку с соответствующими координатами
    Point3D(QList<double> coor);
    double x(); // получение
    double y(); // соответствующей
    double z(); // координаты
    QList<double> coordinates();
    double maxCoor();
    void setX(double tx); // ввод
    void setY(double ty); // соответствующей
    void setZ(double tz); // координаты
    void setPoint3D(double tx, double ty, double tz); // ввод значений всех координат
    void setPoint3D(QList<double> coor);
    Point3D operator *(double d); // умножение координат точки на соответствующее число
    Point3D operator *=(double d);
    bool operator ==(Point3D t);
    void print();
    double to(Point3D t);
    QPointF toQPoint();
};

#endif // POINT3D_H
