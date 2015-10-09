#ifndef SURFACECALCULATION_H
#define SURFACECALCULATION_H

#include "surface.h"
#include "matrix.h"
#include "point3d.h"
#include "vector.h"
#include "drawing.h"
#include "typedefs.h"
#include "tripolygon.h"

#include <QImage>
#include <QList>
#include <QPoint>

class SurfaceCalculation
{
    static const double radianScal = 3.14159265 / 180.0;
    static const double eps = 0.00001;

    Surface* surface;
    double** zBuffer;

    double matbuf[16];
    Matrix rotate;
    QList<Point3D> vertices;
    QList<QPoint> texels;
    QList<TriPolygon> polygons;

    int width;
    int height;

public:
    SurfaceCalculation(Surface* sur);

    void setSize(int w, int h);
    void calculateSurface();
    void calculateColors(QImage* bmp);
    QList<TriPolygon>* polygons_(); // ��������� ���� ���������, ��� ���������� �������
    QList<Point3D>* vertices_(); // ��������� ���� �����, ��� ���������� �������

private:
    // � ������� �������������
    void calculateRotateMatrix(); // ���������� ������� ��������
    Matrix rotateMatrix(int i, int j, int angle); // ���������� ������� ��������
    Matrix funcSurface(double degu, double degv); // ��������������� ������� ������� �����������
    void calculateVertices(); // ���������� ������ �����������
    void calculatePolygons(); // ���������� ��������� �����������

    void createZBuffer(); // �������� ������ �������
    void setPolygonsCharacters(bool isColor); // ������� ������� � ����� ���������
    Vector calculatePolygonNormal(Point3D *A, Point3D *B, Point3D *C); // ���������� ������ �������� (������ getPlaneMatrix)
    void setVerticesNormal(); // ������� �������� ������
    void setVerticesColor(); // ������� ������ ������
    FlatDrawing* getDrawing(QImage *bmp); // ����������
    void sortPolygonsVertices(); // ���������� ������ ���� ���������, ������ ���� � calculateColors
    void deleteZBuffer(); // �������� ������ �������

};

#endif // SURFACECALCULATION_H
