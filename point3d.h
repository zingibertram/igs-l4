#ifndef POINT3D_H
#define POINT3D_H

#include "triangle.h"

#include <QList>
#include <QPointF>
#include <QColor>

class Point3D
{
private:
    double coorX; // ���������������
    double coorY; // ���������� �
    double coorZ; // 3D ������������
public:
    Vector normal;
    QColor color;

    Point3D(); // �����������, ��������� ����� � ������ ���������
    Point3D(double tx, double ty, double tz); // �����������, ��������� ����� � ���������������� ������������
    Point3D(QList<double> coor);
    double x(); // ���������
    double y(); // ���������������
    double z(); // ����������
    QList<double> coordinates();
    double maxCoor();
    void setX(double tx); // ����
    void setY(double ty); // ���������������
    void setZ(double tz); // ����������
    void setPoint3D(double tx, double ty, double tz); // ���� �������� ���� ���������
    void setPoint3D(QList<double> coor);
    Point3D operator *(double d); // ��������� ��������� ����� �� ��������������� �����
    Point3D operator *=(double d);
    bool operator ==(Point3D t);
    void print();
    double to(Point3D t);
    QPointF toQPoint();
};

#endif // POINT3D_H
