#ifndef SURFACEIMAGE_H
#define SURFACEIMAGE_H

#include "matrix.h"
#include "point3d.h"
#include "surface.h"
#include "triangle.h"

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

typedef QList<Triangle> Polygons;
typedef QMap<VertexIndex, Point3D> Vertices;
typedef QMap<VertexIndex, QPoint> Texels;

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
//    void drawFlat(QPainter* pai);
    void drawFrame(QPainter* pai);
    void drawAxis(QPainter *p);
    Matrix rotMatrix(int i, int j, int angle);
    QColor calcColor(Vector n, bool isColor, QColor tex = QColor(), bool isTextured = false);
    void setZBuffer();
    void delZBuffer();
    void sortVertex(int idx);
    void setVerticesNormal();
    void setVerticesColor();
    QColor colorInterpolation(QColor max, QColor min, double kmax, double kmin);
    void setPolygonsCharacters(bool isColor);
    void drawFlat();
    void drawHuro();
    void drawFong();
    void setPixel(QColor current, int i, int j);
};

#endif // SURFACEIMAGE_H
