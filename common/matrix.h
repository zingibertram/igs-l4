#ifndef MATRIX_H
#define MATRIX_H

#include <QPointF>
#include "point3d.h"

enum MatrixType
{
    VECTOR, TRANSFORMATION_MATRIX, COLUMN, DIGIT
};

class Matrix
{
public:
    Matrix(); // ����������� ��� ���������� ������ ������� �������
    Matrix(double a, double b, double c, double d); // �����������, �������� ������������ �������
    Matrix(Point3D p); // �����������, �������� ������ �������� �����
    Matrix(Point3D p, int w); //
    Matrix(double digit); // �����������, ��������� ������� �� 1 ��������
    Matrix(double *arr); // �����������, ��������� ������� �� ��������� �������
    Matrix operator *(double d); // ��������� ������� �� �����
    Matrix operator *(Matrix m); // ��������� ���� ������
    Matrix operator *=(Matrix m); // ��������� ���� ������ � �������������
    Matrix operator -(Matrix m); // �������� ��������
    Matrix operator +(Matrix m); // ����� ��������
    double operator ^(Matrix m); // ������� ���� ����� ���������
    double* operator [](int i); // ����� ��������� �� ������ ������� ��� ������� ������� � � ���������
    QPointF toQPoint(); // ���������� ��������� �����, ������� � ��������� ���, �� � ������-�������
    double toDigit(); //
    Point3D toPoint3D();
    double vectorLength(); //
    void print();
private:
    bool isVector; // ��� ������� (������ ��� ������� ��������������)
    MatrixType mType;
    double mat[4][4]; // �������� �������
};

#endif // MATRIX_H
