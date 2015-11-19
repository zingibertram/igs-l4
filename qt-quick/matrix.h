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
    Matrix(); // конструктор без параметров создаёт нулевую матрицу
    Matrix(double a, double b, double c, double d); // конструктор, создающи координатный столбец
    Matrix(Point3D p); // конструктор, создающи вектор заданной точки
    Matrix(Point3D p, int w); //
    Matrix(double digit); // конструктор, создающий матрицу из 1 элемента
    Matrix(double *arr); // конструктор, создающий матрицу из заданного массива
    Matrix operator *(double d); // умножение матрицы на число
    Matrix operator *(Matrix m); // умножение двух матриц
    Matrix operator *=(Matrix m); // умножение двух матриц с присваиванием
    Matrix operator -(Matrix m); // разность векторов
    Matrix operator +(Matrix m); // сумма векторов
    double operator ^(Matrix m); // косинус угла между векторами
    double* operator [](int i); // вывод указателя на строку матрицы для прямого доступа к её элементам
    QPointF toQPoint(); // нахождение координат точки, лежащей в плоскости хОу, по её радиус-вектору
    double toDigit(); //
    Point3D toPoint3D();
    double vectorLength(); //
    void print();
private:
    bool isVector; // тип матрицы (вектор или матрица преобразования)
    MatrixType mType;
    double mat[4][4]; // элементы матрицы
};

#endif // MATRIX_H
