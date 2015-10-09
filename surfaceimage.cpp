#include "surfaceimage.h"
#include "utils.h"
#include "vector.h"

#include <QtAlgorithms>
#include <QDebug>

#include <stdio.h>

SurfaceImage::SurfaceImage(QWidget *parent) :
    QGraphicsView(parent)
{
    matbuf[0] = 1;
    matbuf[1] = 0;
    matbuf[2] = 0;
    matbuf[3] = 0;
    matbuf[4] = 0;
    matbuf[5] = 1;
    matbuf[6] = 0;
    matbuf[7] = 0;
    matbuf[8] = 0;
    matbuf[9] = 0;
    matbuf[10] = 1;
    matbuf[11] = 0;
    matbuf[12] = 0;
    matbuf[13] = 0;
    matbuf[14] = 0;
    matbuf[15] = 1;
    rotate = Matrix(matbuf);

    lineColor = Qt::white;
}

Matrix SurfaceImage::rotMatrix(int i, int j, int angle)
{
    double sina = sin(angle * radianScal);
    double cosa = cos(angle * radianScal);

    Matrix rx(matbuf);
    rx[i][i] = cosa;
    rx[j][j] = cosa;
    rx[i][j] = sina;
    rx[j][i] = -sina;

    return rx;
}

void SurfaceImage::buildRotateMatrix()
{
    if (surface.xOld != surface.xRotate)
    {
        rotate *= this->rotMatrix(1, 2, surface.xRotate - surface.xOld);
        return;
    }
    if (surface.yOld != surface.yRotate)
    {
        rotate *= this->rotMatrix(0, 2, 360 - surface.yRotate + surface.yOld);
        return;
    }
    if (surface.zOld != surface.zRotate)
    {
        rotate *= this->rotMatrix(0, 1, surface.zRotate - surface.zOld);
        return;
    }
}

Vector SurfaceImage::getPlaneMatrix(Point3D *A, Point3D *B, Point3D *C)
{
    double x = (A->y() - B->y())*(A->z() + B->z())
             +(B->y() - C->y())*(B->z() + C->z())
             +(C->y() - A->y())*(C->z() + A->z());
    double y = (A->z() - B->z())*(A->x() + B->x())
             +(B->z() - C->z())*(B->x() + C->x())
             +(C->z() - A->z())*(C->x() + A->x());
    double z = (A->x() - B->x())*(A->y() + B->y())
             +(B->x() - C->x())*(B->y() + C->y())
             +(C->x() - A->x())*(C->y() + A->y());

    Vector plain(x, y, z);
    plain.unit();

    return plain;
}

void SurfaceImage::setPoints()
{
    int i = 0;
    double mu = (double)surface.maxU;
    double mv = (double)surface.maxV;
    double du = mu / surface.dU;
    double dv = mv / surface.dV;
    double u;
    double v;
    int w = (double)surface.textureImg.width();
    int h = (double)surface.textureImg.height();
    for (u = 0.0; u <= mu + 0.000001; u += du)
    {
        int j = 0;
        for (v = 0.0; v <= mv + 0.000001; v += dv)
        {
            VertexIndex vind = VertexIndex(i, j);
            vertices[vind] = (this->funcSurface(u, v) * rotate).toPoint3D();
            if (surface.isTextured)
            {
                texels[vind] = QPoint(w * u / mu, h * v / mv);
            }
            ++j;
        }
        ++i;
    }
}

void SurfaceImage::setPolygons()
{
    polygons.clear();
    for (int i = 0; i < surface.dU; ++i)
    {
        for (int j = 0; j < surface.dV; ++j)
        {
            VertexIndex A, B, C, D;
            int j_1 = j + 1;
            if (j == surface.dV - 1 && surface.maxV == 360)
            {
                j_1 = 0;
            }
            int i_1 = i + 1;
            if (i == surface.dU - 1 && surface.maxU == 360)
            {
                i_1 = 0;
            }
            A = VertexIndex(i, j);
            B = VertexIndex(i_1, j);
            C = VertexIndex(i_1, j_1);
            D = VertexIndex(i, j_1);

            Triangle fst;
            fst.a = C; fst.b = B; fst.c = A;
            fst.z = vertices[C].z() + vertices[B].z() + vertices[A].z();

            Triangle snd;
            snd.a = A; snd.b = D; snd.c = C;
            snd.z = vertices[A].z() + vertices[D].z() + vertices[C].z();

            polygons.append(fst);
            polygons.append(snd);
        }
    }
}

Matrix SurfaceImage::funcSurface(double degu, double degv)
{
    double u = degu * radianScal;
    double v = degv * radianScal;

    double x = (surface.sndParam + (surface.fstParam + surface.sndParam * cos(u)) * cos(v)) * sin(u);
    double y = (surface.sndParam + (surface.fstParam + surface.sndParam * cos(u)) * sin(v)) * sin(u);
    double z = surface.sndParam * sin(u) + surface.fstParam * sin(u);
    return Matrix(Point3D(x, y, z));
}

void SurfaceImage::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    QPainter painter(this->viewport());
    painter.setRenderHint(QPainter::Antialiasing, true);
    this->drawAxis(&painter);
    center = QPointF(this->width() / 2.0, this->height() / 2.0);

    polygons.clear();
    vertices.clear();
    this->setPoints();
    this->setPolygons();
    qSort(polygons);

    this->drawAxis(&painter);

    bmp = QImage(this->size(), QImage::Format_ARGB32);
    if (surface.type == FRAME)
    {
        this->drawFrame(&painter);
    }
    else
    {
        draw();
    }
    painter.drawImage(0, 0, bmp);

    int t = time.elapsed();
    qDebug() << "Calc and draw of (" << surface.type << ") is " << t << " ms";
}

void SurfaceImage::setPolygonsCharacters(bool isColor)
{
    for (int i = 0; i < polygons.count(); ++i)
    {
        Vector normal = this->getPlaneMatrix(&vertices[polygons[i].a], &vertices[polygons[i].b], &vertices[polygons[i].c]);
        polygons[i].color = U::calcColor(&surface, normal, isColor);
        polygons[i].normal = normal;
    }
}

void SurfaceImage::drawFrame(QPainter *pai)
{
    for (int i = 0; i < polygons.count(); ++i)
    {
        Triangle polygon = polygons[i];
        pai->setPen(QPen(lineColor));
        QPointF vertex[3];
        vertex[0] = vertices[polygon.a].toQPoint() + center;
        vertex[1] = vertices[polygon.b].toQPoint() + center;
        vertex[2] = vertices[polygon.c].toQPoint() + center;
        pai->drawLine(vertex[0], vertex[1]);
        pai->drawLine(vertex[2], vertex[1]);
        pai->drawLine(vertex[0], vertex[2]);
    }
}

void SurfaceImage::setZBuffer()
{
    int n = this->width();
    int m = this->height();
    zBuffer = new double* [n];
    for (int i = 0; i < n; ++i)
    {
        zBuffer[i] = new double [m];
        for (int j = 0; j < m; ++j)
        {
            zBuffer[i][j] = -1.0 / 0.0;
        }
    }
}


void SurfaceImage::delZBuffer()
{
    int n = this->width();
    for (int i = 0; i < n; ++i)
    {
        if (zBuffer[i])
        {
            delete zBuffer[i];
        }
    }
    if (zBuffer)
    {
        delete zBuffer;
    }
}

void SurfaceImage::sortVertex(int idx)
{
    VertexIndex tmp;
    if (vertices[polygons[idx].b].y() > vertices[polygons[idx].a].y())
    {
        tmp = polygons[idx].a;
        polygons[idx].a = polygons[idx].b;
        polygons[idx].b = tmp;
    }
    if (vertices[polygons[idx].c].y() > vertices[polygons[idx].a].y())
    {
        tmp = polygons[idx].a;
        polygons[idx].a = polygons[idx].c;
        polygons[idx].c = tmp;
    }
    if (vertices[polygons[idx].c].y() > vertices[polygons[idx].b].y())
    {
        tmp = polygons[idx].b;
        polygons[idx].b = polygons[idx].c;
        polygons[idx].c = tmp;
    }
}

void SurfaceImage::setVerticesNormal()
{
    for (int i = 0; i < polygons.count(); ++i)
    {
        Vector n = polygons[i].normal;
        vertices[polygons[i].a].normal += n;
        vertices[polygons[i].b].normal += n;
        vertices[polygons[i].c].normal += n;
    }

    QList<VertexIndex> keys = vertices.keys();
    for (int k = 0; k < keys.count(); ++k)
    {
        vertices[keys[k]].normal.unit();
    }
}

void SurfaceImage::setVerticesColor()
{
    QList<VertexIndex> keys = vertices.keys();
    for (int k = 0; k < keys.count(); ++k)
    {
        VertexIndex key = keys[k];
        vertices[key].color = U::calcColor(&surface, vertices[key].normal, false);
    }
}

void SurfaceImage::draw()
{
    this->setZBuffer();
    this->setPolygonsCharacters(surface.type != FLAT);

    if (surface.type != FLAT)
    {
        this->setVerticesNormal();
    }
    if (surface.type == HURO)
    {
        this->setVerticesColor();
    }

    FlatDrawing *drawing = getDrawing();
    for (int i = 0; i < polygons.count(); ++i)
    {
        this->sortVertex(i);

        Point3D A = vertices[polygons[i].a];
        Point3D B = vertices[polygons[i].b];
        Point3D C = vertices[polygons[i].c];

        drawing->setVertices(&vertices, &polygons[i]);

        drawing->setTexels(&texels, &polygons[i]);

        double prevSY = C.y() - 1.0;
        for (double sy = C.y(); sy <= A.y(); sy += 0.3)
        {
            if ((int)prevSY == (int)sy)
            {
                continue;
            }
            prevSY = sy;
            double k;
            double xa, xb, za, zb;

            xa = C.x();
            za = C.z();

            drawing->setA();

            if (A.y() - C.y() > eps)
            {
                k = (sy - C.y()) / (A.y() - C.y());
                xa += k * (A.x() - C.x());
                za += k * (A.z() - C.z());

                drawing->setInterpolatedA(k);
            }

            if (sy < B.y())
            {
                k = (sy - C.y()) / (B.y() - C.y());
                xb = C.x() + k * (B.x() - C.x());
                zb = C.z() + k * (B.z() - C.z());

                drawing->setBCInterpolatedB(k);
            }
            else
            {
                xb = B.x();
                zb = B.z();

                drawing->setB();

                if (A.y() - B.y() > eps)
                {
                    k = (sy - B.y()) / (A.y() - B.y());
                    xb += k * (A.x() - B.x());
                    zb += k * (A.z() - B.z());

                    drawing->setABInterpolatedB(k);
                }
            }

            if (xa > xb)
            {
                double tmp;
                tmp = xa; xa = xb; xb = tmp;
                tmp = za; za = zb; zb = tmp;

                drawing->swapAB();
            }
            double prevSX = xa - 1.0;
            for (double sx = xa; sx <= xb; sx += 1.0)
            {

                if ((int)prevSX == (int)sx)
                {
                    continue;
                }
                prevSX = sx;
                double k = (sx - xa) / (xb - xa);
                double sz = za + (zb - za) * k;
                int xp = (int)(sx + center.x());
                int yp = (int)(center.y() - sy);

                drawing->calculatePixel(xp, yp, sz, k, polygons[i].color, polygons[i].normal);
            }
        }
    }
    this->delZBuffer();
}

FlatDrawing* SurfaceImage::getDrawing()
{
    switch (surface.type)
    {
        case FLAT:
            return new FlatDrawing(&surface, zBuffer, &bmp, width(), height());
        case HURO:
            return new HuroDrawing(&surface, zBuffer, &bmp, width(), height());
        case FONG:
            return new FongDrawing(&surface, zBuffer, &bmp, width(), height());
        default:
            throw "Unsupported colorable surface type";
    }
}

void SurfaceImage::drawAxis(QPainter *p)
{
    p->setPen(QPen(lineColor, 1));
    QPoint x(this->width() - 20, this->height() / 2.0);
    p->drawLine(QPoint(20, this->height() / 2.0), x);
    p->drawLine(x, x + QPoint(-12, -8));
    p->drawLine(x, x + QPoint(-12, 8));
    p->drawText(x + QPoint(0, 12), "X");

    QPoint y(this->width() / 2.0, 20);
    p->drawLine(QPoint(this->width() / 2.0, this->height() - 20), y);
    p->drawLine(y, y + QPoint(8, 12));
    p->drawLine(y, y + QPoint(-8, 12));
    p->drawText(y + QPoint(12, 8), "Y");
}

void SurfaceImage::setSurface(Surface sur)
{
    time.start();

    surface = sur;
    if (surface.isTextured)
    {
        surface.exterior = QColor(Qt::white);
        surface.interior = QColor(Qt::white);
    }
    this->buildRotateMatrix();
}
