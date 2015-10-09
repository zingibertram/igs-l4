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
    QList<TriPolygon>* polygons_(); // получение всех полигонов, для построения каркаса
    QList<Point3D>* vertices_(); // получение всех точек, для построения каркаса

private:
    // в порядке использования
    void calculateRotateMatrix(); // вычисление матрицы поворота
    Matrix rotateMatrix(int i, int j, int angle); // вычисление матрицы поворота
    Matrix funcSurface(double degu, double degv); // параметрическая функция задания поверхности
    void calculateVertices(); // вычисление вершин поверхности
    void calculatePolygons(); // вычисление полигонов поверхности

    void createZBuffer(); // создание буфера глубины
    void setPolygonsCharacters(bool isColor); // задание нормали и цвета полигонов
    Vector calculatePolygonNormal(Point3D *A, Point3D *B, Point3D *C); // вычисление номали полигона (раньше getPlaneMatrix)
    void setVerticesNormal(); // задание нормалей вершин
    void setVerticesColor(); // задание цветов вершин
    FlatDrawing* getDrawing(QImage *bmp); // рисователь
    void sortPolygonsVertices(); // сортировка вершин всех полигонов, должна быть в calculateColors
    void deleteZBuffer(); // удаление буфера глубины

};

#endif // SURFACECALCULATION_H
