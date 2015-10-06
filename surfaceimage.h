#ifndef SURFACEIMAGE_H
#define SURFACEIMAGE_H

#include "matrix.h"
#include "point3d.h"
#include "surface.h"
#include "triangle.h"
#include "utils.h"
#include "drawing.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QVector>
#include <QMap>
#include <QPair>
#include <QPaintEvent>
#include <QPen>
#include <QImage>
#include <QRgb>

#include <math.h>

class SurfaceImage : public QGraphicsView
{
    Q_OBJECT

public:
    explicit SurfaceImage(QWidget *parent = 0);
    void setSurface(Surface sur);
    void loadTexture();

private:
    static const double radianScal = 3.14159265 / 180.0;
    static const double eps = 0.00001;

    // параметрическое уравнение
    Surface surface;
    Vector observer;
    Vector light;
    double matbuf[16];
    Matrix rotate;
    QPointF center;
    Polygons polygons;
    Vertices vertices;
    Texels texels;
    double **zBuffer;
    bool nots;
    QImage bmp;
    QColor lineColor;
    QImage textureImg;

    Matrix funcSurface(double u, double v);
    void buildRotateMatrix();
    Vector getPlaneMatrix(Point3D *A, Point3D *B, Point3D *C);
    void setPoints();
    void setPolygons();
    void paintEvent(QPaintEvent *event);
    void drawFrame(QPainter* pai);
    void drawAxis(QPainter *p);
    Matrix rotMatrix(int i, int j, int angle);
    void setZBuffer();
    void delZBuffer();
    void sortVertex(int idx);
    void setVerticesNormal();
    void setVerticesColor();
    void setPolygonsCharacters(bool isColor);
    void draw();
    FlatDrawing* getDrawing();
    void setPixel(QColor current, int i, int j);
};

#endif // SURFACEIMAGE_H
