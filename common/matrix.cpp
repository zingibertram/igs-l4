#include "matrix.h"
#include <stdio.h>
#include <math.h>
#include <QDebug>

Matrix::Matrix()
{
    mType = TRANSFORMATION_MATRIX;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            mat[i][j] = 0;
        }
    }
}

Matrix::Matrix(double a, double b, double c, double d)
{
    mType = COLUMN;
    mat[0][0] = a;
    mat[1][0] = b;
    mat[2][0] = c;
    mat[3][0] = d;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 1; j < 4; ++j)
        {
            mat[i][j] = 0;
        }
    }
}

Matrix::Matrix(Point3D p)
{
    mType = VECTOR;
    mat[0][0] = p.x();
    mat[0][1] = p.y();
    mat[0][2] = p.z();
    mat[0][3] = 1;
    for (int i = 1; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            mat[i][j] = 0;
        }
    }
}

Matrix::Matrix(Point3D p, int w)
{
    mType = VECTOR;
    mat[0][0] = p.x();
    mat[0][1] = p.y();
    mat[0][2] = p.z();
    mat[0][3] = w;
    for (int i = 1; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            mat[i][j] = 0;
        }
    }
}

Matrix::Matrix(double digit)
{
    mType = DIGIT;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            mat[i][j] = 0;
        }
    }
    mat[0][0] = digit;
}

Matrix::Matrix(double *arr)
{
    mType = TRANSFORMATION_MATRIX;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            mat[i][j] = arr[i*4 + j];
        }
    }
}

Matrix Matrix::operator *(Matrix m)
{
    Matrix mul;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                mul.mat[i][j] += mat[i][k]*m.mat[k][j];
            }
        }
    }
    if (this->mType == TRANSFORMATION_MATRIX && m.mType == TRANSFORMATION_MATRIX)
    {
        mul.mType = TRANSFORMATION_MATRIX;
        return mul;
    }
    if (this->mType == VECTOR && m.mType == TRANSFORMATION_MATRIX)
    {
        mul.mType = VECTOR;
        return mul;
    }
    if (this->mType == VECTOR && m.mType == COLUMN)
    {
        mul.mType = DIGIT;
        return mul;
    }
    return Matrix();
}

Matrix Matrix::operator *=(Matrix m)
{
    Matrix mul;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                mul.mat[i][j] += mat[i][k]*m.mat[k][j];
            }
        }
    }
    *this = mul;
    if (this->mType == TRANSFORMATION_MATRIX && m.mType == TRANSFORMATION_MATRIX)
    {
        mul.mType = TRANSFORMATION_MATRIX;
        return mul;
    }
    if (this->mType == VECTOR && m.mType == TRANSFORMATION_MATRIX)
    {
        mul.mType = VECTOR;
        return mul;
    }
    if (this->mType == VECTOR && m.mType == COLUMN)
    {
        mul.mType = DIGIT;
        return mul;
    }
    return Matrix();
}

Matrix Matrix::operator -(Matrix m)
{
    Matrix mul(Point3D(0, 0, 0));
    for (int i = 0; i < 4 ; ++i)
    {
        mul.mat[0][i] = mat[0][i] - m.mat[0][i];
    }
    if (this->mType == VECTOR && m.mType == VECTOR)
    {
        mul.mType = VECTOR;
        return mul;
    }
    return Matrix(Point3D(0, 0, 0));
}

Matrix Matrix::operator +(Matrix m)
{
    Matrix mul(Point3D(0, 0, 0));
    for (int i = 0; i < 4 ; ++i)
    {
        mul.mat[0][i] = mat[0][i] + m.mat[0][i];
    }
    if (this->mType == VECTOR && m.mType == VECTOR)
    {
        mul.mType = VECTOR;
        return mul;
    }
    return Matrix(Point3D(0, 0, 0));
}

QPointF Matrix::toQPoint()
{
    if (mType == VECTOR)
    {
        if (mat[0][3])
        {
            return QPointF(mat[0][0] / mat[0][3], mat[0][1] / mat[0][3]);
        }
        else
        {
            return QPointF(mat[0][0], mat[0][1]);
        }
    }
    return QPointF(0, 0);
}

double Matrix::toDigit()
{
    if (mType == DIGIT)
    {
        return mat[0][0];
    }
    return 0;
}

void Matrix::print()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            printf("%f ", mat[i][j]);
        }
        qDebug() << mat[i][0] << mat[i][1] << mat[i][2] << mat[i][3];
        printf("\n");
    }
    switch (mType)
    {
    case DIGIT: printf("DIGIT\n"); break;
    case VECTOR: printf("VECTOR\n"); break;
    case COLUMN: printf("COLUMN\n"); break;
    case TRANSFORMATION_MATRIX: printf("TRANSFORMATION_MATRIX\n"); break;
    }

    printf("\n");
}

double* Matrix::operator [](int i)
{
    return mat[i];
}

double Matrix::vectorLength()
{
    if (mType == VECTOR)
    {
        return sqrt(mat[0][0]*mat[0][0] + mat[0][1]*mat[0][1] + mat[0][2]*mat[0][2]);
    }
    return -1;
}

Point3D Matrix::toPoint3D()
{
    if (mat[0][3] == 1)
    {
        return Point3D(mat[0][0], mat[0][1], mat[0][2]);
    }
    return Point3D(0, 0, 0);
}

Matrix Matrix::operator *(double d)
{
    Matrix mul;
    mul.mType = mType;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            mul.mat[i][j] += d*mat[i][j];
        }
    }
    return mul;
}

double Matrix::operator ^(Matrix m)
{
    if (mType == VECTOR && m.mType == VECTOR)
    {
        const double E = 0.001;
        double d1 = vectorLength();
        double d2 = m.vectorLength();
        double scalar = mat[0][0]*m.mat[0][0] + mat[0][1]*m.mat[0][1] + mat[0][2]*m.mat[0][2] + mat[0][3]*m.mat[0][3];
        if (fabs(d1) < E || fabs(d2) < E)
        {
            return 0;
        }
        return scalar / (d1*d2);
    }
    return 2;
}
