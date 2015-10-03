#include "surfaceimage.h"

#include <QtAlgorithms>

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

    observer.x = 0;
    observer.y = 0;
    observer.z = 1;

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
    Vector plain;
    plain.x = (A->y() - B->y())*(A->z() + B->z())
             +(B->y() - C->y())*(B->z() + C->z())
             +(C->y() - A->y())*(C->z() + A->z());
    plain.y = (A->z() - B->z())*(A->x() + B->x())
             +(B->z() - C->z())*(B->x() + C->x())
             +(C->z() - A->z())*(C->x() + A->x());
    plain.z = (A->x() - B->x())*(A->y() + B->y())
             +(B->x() - C->x())*(B->y() + C->y())
             +(C->x() - A->x())*(C->y() + A->y());
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
    int w = textureImg.width();
    int h = textureImg.height();
    for (u = 0.0; u <= mu + 0.000001; u += du)
    {
        int j = 0;
        for (v = 0.0; v <= mv + 0.000001; v += dv)
        {
            VertexIndex vind = VertexIndex(i, j);
            vertices[vind] = (this->funcSurface(u, v) * rotate).toPoint3D();
            if (surface.isTextured)
            {
                texels[vind] = QPoint((double)w * u / mu, (double)h * v / mv);
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
    else if (surface.type == FLAT)
    {
        this->drawFlat();
    }
    else if (surface.type == HURO)
    {
        this->drawHuro();
    }
    else if (surface.type == FONG)
    {
        drawFong();
    }
    painter.drawImage(0, 0, bmp);
}

QColor SurfaceImage::calcColor(Vector n, bool isColor, QColor tex, bool isTextured)
{
    QColor c;
    if (n.z > 0)
    {
        c = surface.exterior;
    }
    else
    {
        c = surface.interior;
    }
    if (isColor)
    {
        return c;
    }

    if (isTextured)
    {
        c = tex;
    }
    double cosnl = n ^ light;
    if (n.z * cosnl <= 0)
    {
        cosnl = 0;
    }
    cosnl = surface.kd * fabs(cosnl);

    Vector r;
    double nLength = n.len();
    if (nLength > 0.00001)
    {
        r = n * (2 * (n * light) * (1.0 / nLength)) - light;
    }
    double cosor = observer ^ r;
    if (cosor < 0)
    {
        cosor = 0;
    }
    cosor = surface.ks * pow(cosor, surface.n);

    int R = min(surface.absent.red(), c.red()) * surface.ka
          + min(surface.dot.red(), c.red()) * cosnl
          + surface.dot.red() * cosor;
    int G = min(surface.absent.green(), c.green()) * surface.ka
          + min(surface.dot.green(), c.green()) * cosnl
          + surface.dot.green() * cosor;
    int B = min(surface.absent.blue(), c.blue()) * surface.ka
          + min(surface.dot.blue(), c.blue()) * cosnl
          + surface.dot.blue() * cosor;

    return QColor(min(R, 255), min(G, 255), min(B, 255));
}

void SurfaceImage::setPolygonsCharacters(bool isColor)
{
    for (int i = 0; i < polygons.count(); ++i)
    {
        Vector normal = this->getPlaneMatrix(&vertices[polygons[i].a], &vertices[polygons[i].b], &vertices[polygons[i].c]);
        polygons[i].color = this->calcColor(normal, isColor);
        polygons[i].normal = normal;
    }
}

//void SurfaceImage::drawFlat(QPainter *pai)
//{
//    this->setPolygonsCharacters(false);
//    for (int i = 0; i < polygons.count(); ++i)
//    {
//        pai->setPen(QPen(polygons[i].color));
//        pai->setBrush(QBrush(polygons[i].color));
//        QPointF vertex[3];
//        vertex[0] = vertices[polygons[i].a].toQPoint() + center;
//        vertex[1] = vertices[polygons[i].b].toQPoint() + center;
//        vertex[2] = vertices[polygons[i].c].toQPoint() + center;
//        pai->drawPolygon(vertex, 3);
//    }
//}

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
        QColor current;
        if (vertices[key].normal.z > 0)
        {
            current = surface.exterior;
        }
        else
        {
            current = surface.interior;
        }
        vertices[key].color = this->calcColor(vertices[key].normal, false);
    }
}

QColor SurfaceImage::colorInterpolation(QColor max, QColor min, double kmax, double kmin)
{
    double r = max.red() * kmax + min.red() * kmin;
    if (r > 255)
    {
        r = 255;
    }
    double g = max.green() * kmax + min.green() * kmin;
    if (g > 255)
    {
        g = 255;
    }
    double b = max.blue() * kmax + min.blue() * kmin;
    if (b > 255)
    {
        b = 255;
    }
    return QColor(r, g, b);
}

void SurfaceImage::setPixel(QColor current, int i, int j)
{
    QColor bufCol(bmp.pixel(i, j));
    double one_Minus_Alpha = 1.0 - surface.alpha;
    int r = surface.alpha * (double)current.red() + one_Minus_Alpha * (double)bufCol.red();
    int g = surface.alpha * (double)current.green() + one_Minus_Alpha * (double)bufCol.green();
    int b = surface.alpha * (double)current.blue() + one_Minus_Alpha * (double)bufCol.blue();
    bmp.setPixel(i, j, QColor(std::min(255, r), std::min(255, g), std::min(255, b)).rgb());
}

void SurfaceImage::drawFlat()
{
    this->setZBuffer();
    this->setPolygonsCharacters(false);

    for (int i = 0; i < polygons.count(); ++i)
    {
        this->sortVertex(i);
        Point3D A = vertices[polygons[i].a];
        Point3D B = vertices[polygons[i].b];
        Point3D C = vertices[polygons[i].c];

        QPoint texA, texB, texC;
        if (surface.isTextured)
        {
            texA = texels[polygons[i].a];
            texB = texels[polygons[i].b];
            texC = texels[polygons[i].c];
        }
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
            int texXA, texXB, texYA, texYB;

            xa = C.x();
            za = C.z();
            if (surface.isTextured)
            {
                texXA = texC.x();
                texYA = texC.y();
            }

            if (A.y() - C.y() > eps)
            {
                k = (sy - C.y()) / (A.y() - C.y());
                xa += k * (A.x() - C.x());
                za += k * (A.z() - C.z());
                if (surface.isTextured)
                {
                    texXA += k * (double)(texA.x() - texC.x());
                    texYA += k * (double)(texA.y() - texC.y());
                }
            }

            if (sy < B.y())
            {
                k = (sy - C.y()) / (B.y() - C.y());
                xb = C.x() + k * (B.x() - C.x());
                zb = C.z() + k * (B.z() - C.z());

                if (surface.isTextured)
                {
                    texXB = texC.x() + k * (double)(texB.x() - texC.x());
                    texYB = texC.y() + k * (double)(texB.y() - texC.y());
                }
            }
            else
            {
                xb = B.x();
                zb = B.z();
                if (surface.isTextured)
                {
                    texXB = texB.x();
                    texYB = texB.y();
                }

                if (A.y() - B.y() > eps)
                {
                    k = (sy - B.y()) / (A.y() - B.y());
                    xb += k * (A.x() - B.x());
                    zb += k * (A.z() - B.z());
                    if (surface.isTextured)
                    {
                        texXB += k * (double)(texA.x() - texB.x());
                        texYB += k * (double)(texA.y() - texB.y());
                    }
                }
            }

            if (xa > xb)
            {
                double tmp;
                tmp = xa; xa = xb; xb = tmp;
                tmp = za; za = zb; zb = tmp;
                if (surface.isTextured)
                {
                    int tex;
                    tex = texXA; texXA = texXB; texXB = tex;
                    tex = texYA; texYA = texYB; texYB = tex;
                }
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

                QPoint texPoint;
                QColor texColor;
                if (surface.isTextured)
                {
                    texPoint = QPoint(texXA + (double)(texXB - texXA) * k, texYA + (double)(texYB - texYA) * k);
                    if (textureImg.valid(texPoint))
                    {
                        texColor = QColor(textureImg.pixel(texPoint));
                    }
                }

                if (- 1 < xp && xp < this->width() && - 1 < yp && yp < this->height())
                {
                    if (sz - zBuffer[xp][yp] > 0.999)
                    {
                        QColor current;

                        if (surface.isTextured)
                        {
                            current = this->calcColor(polygons[i].normal, false, texColor, true);
                        }
                        else
                        {
                            current = polygons[i].color;
                        }

                        setPixel(current, xp, yp);
                        zBuffer[xp][yp] = sz;
                    }
                }
            }
        }
    }
    this->delZBuffer();
}

void SurfaceImage::drawHuro()
{
    this->setZBuffer();
    this->setPolygonsCharacters(true);

    this->setVerticesNormal();
    this->setVerticesColor();
    for (int i = 0; i < polygons.count(); ++i)
    {
        this->sortVertex(i);
        Point3D A = vertices[polygons[i].a];
        Point3D B = vertices[polygons[i].b];
        Point3D C = vertices[polygons[i].c];

        QPoint texA, texB, texC;
        if (surface.isTextured)
        {
            texA = texels[polygons[i].a];
            texB = texels[polygons[i].b];
            texC = texels[polygons[i].c];
        }
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
            int texXA, texXB, texYA, texYB;

            QColor cola, colb;

            xa = C.x();
            za = C.z();
            if (surface.isTextured)
            {
                texXA = texC.x();
                texYA = texC.y();
            }

            cola = C.color;
            if (A.y() - C.y() > eps)
            {
                k = (sy - C.y()) / (A.y() - C.y());
                xa += k * (A.x() - C.x());
                za += k * (A.z() - C.z());
                if (surface.isTextured)
                {
                    texXA += k * (double)(texA.x() - texC.x());
                    texYA += k * (double)(texA.y() - texC.y());
                }

                cola = this->colorInterpolation(A.color, C.color, k, 1 - k);
            }

            if (sy < B.y())
            {
                k = (sy - C.y()) / (B.y() - C.y());
                xb = C.x() + k * (B.x() - C.x());
                zb = C.z() + k * (B.z() - C.z());

                if (surface.isTextured)
                {
                    texXB = texC.x() + k * (double)(texB.x() - texC.x());
                    texYB = texC.y() + k * (double)(texB.y() - texC.y());
                }

                colb = this->colorInterpolation(B.color, C.color, k, 1 - k);
            }
            else
            {
                xb = B.x();
                zb = B.z();
                if (surface.isTextured)
                {
                    texXB = texB.x();
                    texYB = texB.y();
                }

                colb = B.color;
                if (A.y() - B.y() > eps)
                {
                    k = (sy - B.y()) / (A.y() - B.y());
                    xb += k * (A.x() - B.x());
                    zb += k * (A.z() - B.z());
                    if (surface.isTextured)
                    {
                        texXB += k * (double)(texA.x() - texB.x());
                        texYB += k * (double)(texA.y() - texB.y());
                    }

                    colb = this->colorInterpolation(A.color, B.color, k, 1 - k);
                }
            }

            if (xa > xb)
            {
                double tmp;
                tmp = xa; xa = xb; xb = tmp;
                tmp = za; za = zb; zb = tmp;
                if (surface.isTextured)
                {
                    int tex;
                    tex = texXA; texXA = texXB; texXB = tex;
                    tex = texYA; texYA = texYB; texYB = tex;
                }

                QColor buf = cola;
                cola = colb; colb = buf;
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

                QPoint texPoint;
                QColor texColor;
                if (surface.isTextured)
                {
                    texPoint = QPoint(texXA + (double)(texXB - texXA) * k, texYA + (double)(texYB - texYA) * k);
                    if (textureImg.valid(texPoint))
                    {
                        texColor = QColor(textureImg.pixel(texPoint));
                    }
                }

                if (- 1 < xp && xp < this->width() && - 1 < yp && yp < this->height())
                {
                    if (sz - zBuffer[xp][yp] > 0.999)
                    {
                        QColor current;

                        QColor tmpCol = this->colorInterpolation(colb, cola, k, 1 - k);
                        if (surface.isTextured)
                        {
                            int r = tmpCol.redF() * (double)texColor.red();
                            int g = tmpCol.greenF() * (double)texColor.green();
                            int b = tmpCol.blueF() * (double)texColor.blue();
                            current = QColor(r, g, b);
                        }
                        else
                        {
                            current = tmpCol;
                        }

                        setPixel(current, xp, yp);
                        zBuffer[xp][yp] = sz;
                    }
                }
            }
        }
    }
    this->delZBuffer();
}

void SurfaceImage::drawFong()
{
    this->setZBuffer();
    this->setPolygonsCharacters(true);

    this->setVerticesNormal();
    for (int i = 0; i < polygons.count(); ++i)
    {
        this->sortVertex(i);
        Point3D A = vertices[polygons[i].a];
        Point3D B = vertices[polygons[i].b];
        Point3D C = vertices[polygons[i].c];

        QPoint texA, texB, texC;
        if (surface.isTextured)
        {
            texA = texels[polygons[i].a];
            texB = texels[polygons[i].b];
            texC = texels[polygons[i].c];
        }
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
            int texXA, texXB, texYA, texYB;

            Vector veca, vecb;

            xa = C.x();
            za = C.z();
            if (surface.isTextured)
            {
                texXA = texC.x();
                texYA = texC.y();
            }

            veca = C.normal;
            if (A.y() - C.y() > eps)
            {
                k = (sy - C.y()) / (A.y() - C.y());
                xa += k * (A.x() - C.x());
                za += k * (A.z() - C.z());
                if (surface.isTextured)
                {
                    texXA += k * (double)(texA.x() - texC.x());
                    texYA += k * (double)(texA.y() - texC.y());
                }

                veca = C.normal * (1 - k) + A.normal * k;
            }

            if (sy < B.y())
            {
                k = (sy - C.y()) / (B.y() - C.y());
                xb = C.x() + k * (B.x() - C.x());
                zb = C.z() + k * (B.z() - C.z());

                if (surface.isTextured)
                {
                    texXB = texC.x() + k * (double)(texB.x() - texC.x());
                    texYB = texC.y() + k * (double)(texB.y() - texC.y());
                }

                vecb = C.normal * (1 - k) + B.normal * k;
            }
            else
            {
                xb = B.x();
                zb = B.z();
                if (surface.isTextured)
                {
                    texXB = texB.x();
                    texYB = texB.y();
                }

                vecb = B.normal;
                if (A.y() - B.y() > eps)
                {
                    k = (sy - B.y()) / (A.y() - B.y());
                    xb += k * (A.x() - B.x());
                    zb += k * (A.z() - B.z());
                    if (surface.isTextured)
                    {
                        texXB += k * (double)(texA.x() - texB.x());
                        texYB += k * (double)(texA.y() - texB.y());
                    }

                    vecb = B.normal * (1 - k) + A.normal * k;
                }
            }

            if (xa > xb)
            {
                double tmp;
                tmp = xa; xa = xb; xb = tmp;
                tmp = za; za = zb; zb = tmp;
                if (surface.isTextured)
                {
                    int tex;
                    tex = texXA; texXA = texXB; texXB = tex;
                    tex = texYA; texYA = texYB; texYB = tex;
                }

                Vector buf = veca;
                veca = vecb; vecb = buf;
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

                QPoint texPoint;
                QColor texColor;
                if (surface.isTextured)
                {
                    texPoint = QPoint(texXA + (double)(texXB - texXA) * k, texYA + (double)(texYB - texYA) * k);
                    if (textureImg.valid(texPoint))
                    {
                        texColor = QColor(textureImg.pixel(texPoint));
                    }
                }

                if (- 1 < xp && xp < this->width() && - 1 < yp && yp < this->height())
                {
                    if (sz - zBuffer[xp][yp] > 0.999)
                    {
                        Vector norm;
                        QColor current;

                        norm = veca + (vecb - veca) * k;
                        if (surface.isTextured)
                        {
                            current = this->calcColor(norm, false, texColor, true);
                        }
                        else
                        {
                            if (norm.z > 0)
                            {
                                current = surface.exterior;
                            }
                            else
                            {
                                current = surface.interior;
                            }
                            current = this->calcColor(norm, false);
                        }

                        setPixel(current, xp, yp);
                        zBuffer[xp][yp] = sz;
                    }
                }
            }
        }
    }
    this->delZBuffer();
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
    surface = sur;
    light = Vector(sur.illuminant.x(), sur.illuminant.y(), sur.illuminant.z());
    light.unit();
    if (surface.isTextured)
    {
        surface.exterior = QColor(Qt::white);
        surface.interior = QColor(Qt::white);
    }
    this->buildRotateMatrix();
}

void SurfaceImage::loadTexture()
{
    textureImg.load(surface.textureFile);
}
