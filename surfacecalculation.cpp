#include "surfacecalculation.h"

#include <QtAlgorithms>

#include <math.h>


SurfaceCalculation::SurfaceCalculation(Surface *sur)
{
    surface = sur;

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
}

void SurfaceCalculation::setSize(int w, int h)
{
    width = w;
    height = h;
}

void SurfaceCalculation::calculateSurface()
{
    if (surface->isPointsChanged)
    {
        vertices.clear();
        texels.clear();
        polygons.clear();

        calculateRotateMatrix();
        calculateVertices();
        calculatePolygons();

        qSort(polygons);
    }
}

void SurfaceCalculation::calculateColors(QImage* bmp)
{
    createZBuffer();

    setPolygonsCharacters(surface->type != FLAT);

    if (surface->type != FLAT)
    {
        setVerticesNormal();
    }
    if (surface->type == HURO)
    {
        setVerticesColor();
    }

    sortPolygonsVertices();

    QPointF center(width / 2.0, height / 2.0);

    FlatDrawing *drawing = getDrawing(bmp);
    for (int i = 0; i < polygons.count(); ++i)
    {
        Point3D A = vertices[polygons[i].a];
        Point3D B = vertices[polygons[i].b];
        Point3D C = vertices[polygons[i].c];

        drawing->setVertices(&vertices, &polygons[i]);

        drawing->setTexels(&texels, &polygons[i]);

        double prevSY = C.y() - 1.0;
        for (double sy = C.y(); sy <= A.y(); sy += 0.5)
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
            for (double sx = xa; sx <= xb; sx += 0.5)
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

    deleteZBuffer();
}

QList<TriPolygon>* SurfaceCalculation::polygons_()
{
    return &polygons;
}

QList<Point3D>* SurfaceCalculation::vertices_()
{
    return &vertices;
}

void SurfaceCalculation::calculateRotateMatrix()
{
    if (surface->xOld != surface->xRotate)
    {
        rotate *= rotateMatrix(1, 2, surface->xRotate - surface->xOld);
        return;
    }
    if (surface->yOld != surface->yRotate)
    {
        rotate *= rotateMatrix(0, 2, 360 - surface->yRotate + surface->yOld);
        return;
    }
    if (surface->zOld != surface->zRotate)
    {
        rotate *= rotateMatrix(0, 1, surface->zRotate - surface->zOld);
        return;
    }
}

Matrix SurfaceCalculation::rotateMatrix(int i, int j, int angle)
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

void SurfaceCalculation::calculateVertices()
{
    SurfaceBorder* b = surface->func->surfaceBorder();
    double mu = b->dU - b->minU;
    double mv = b->dV - b->minV;
    double du = mu / surface->dU;
    double dv = mv / surface->dV;
    double u;
    double v;
    double w = surface->textureImg.width() / mu;
    double h = surface->textureImg.height() / mv;

    for (u = b->minU; u <= mu + 0.000001; u += du)
    {
        for (v = b->minV; v <= mv + 0.000001; v += dv)
        {
            vertices.append((surface->func->getVertex(u, v) * rotate).toPoint3D());
            if (surface->isTextured)
            {
                texels.append(QPoint(w * u, h * v));
            }
        }
    }
    int tr = 90;
    tr++;
}

void SurfaceCalculation::calculatePolygons()
{
    int u = surface->dU + 1;
    int v = surface->dV + 1;

    SurfaceBorder* b = surface->func->surfaceBorder();

    bool isU = b->dU == b->maxU && b->isUCycle;
    bool isV = b->dV == b->maxV && b->isVCycle;

    int mu = isU ? u : u - 1;
    int mv = isV ? v : v - 1;

    for (int i = 0; i < mu; ++i)
    {
        for (int j = 0; j < mv; ++j)
        {
            int j_1 = isV ? (j + 1) % v : j + 1;
            int i_1 = isU ? (i + 1) % u : i + 1;

            int A = i * v + j;
            int B = i_1 * v + j;
            int C = i_1 * v + j_1;
            int D = i * v + j_1;

            TriPolygon fst(C, B, A);
            fst.z = vertices[C].z() + vertices[B].z() + vertices[A].z();

            TriPolygon snd(A, D, C);
            snd.z = vertices[A].z() + vertices[D].z() + vertices[C].z();

            polygons.append(fst);
            polygons.append(snd);
        }
    }
}

void SurfaceCalculation::createZBuffer()
{
    zBuffer = new double* [width];
    for (int i = 0; i < width; ++i)
    {
        zBuffer[i] = new double [height];
        for (int j = 0; j < height; ++j)
        {
            zBuffer[i][j] = -1.0 / 0.0;
        }
    }
}

void SurfaceCalculation::setPolygonsCharacters(bool isColor)
{
    for (int i = 0; i < polygons.count(); ++i)
    {
        Vector normal = calculatePolygonNormal(&vertices[polygons[i].a], &vertices[polygons[i].b], &vertices[polygons[i].c]);
        polygons[i].color = U::calcColor(surface, normal, isColor);
        polygons[i].normal = normal;
    }
}

Vector SurfaceCalculation::calculatePolygonNormal(Point3D *A, Point3D *B, Point3D *C)
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

void SurfaceCalculation::setVerticesNormal()
{
    for (int i = 0; i < polygons.count(); ++i)
    {
        Vector n = polygons[i].normal;
        vertices[polygons[i].a].normal += n;
        vertices[polygons[i].b].normal += n;
        vertices[polygons[i].c].normal += n;
    }

    for (int i = 0; i < vertices.count(); ++i)
    {
        vertices[i].normal.unit();
    }
}

void SurfaceCalculation::setVerticesColor()
{
    for (int i = 0; i < vertices.count(); ++i)
    {
        vertices[i].color = U::calcColor(surface, vertices[i].normal, false);
    }
}

FlatDrawing* SurfaceCalculation::getDrawing(QImage* bmp)
{
    switch (surface->type)
    {
        case FLAT:
            return new FlatDrawing(surface, zBuffer, bmp, width, height);
        case HURO:
            return new HuroDrawing(surface, zBuffer, bmp, width, height);
        case FONG:
            return new FongDrawing(surface, zBuffer, bmp, width, height);
        default:
            throw "Unsupported colorable surface type";
    }
}

void SurfaceCalculation::sortPolygonsVertices()
{
    for (int i = 0; i < polygons.count(); ++i)
    {
        int tmp;
        if (vertices[polygons[i].b].y() > vertices[polygons[i].a].y())
        {
            tmp = polygons[i].a;
            polygons[i].a = polygons[i].b;
            polygons[i].b = tmp;
        }
        if (vertices[polygons[i].c].y() > vertices[polygons[i].a].y())
        {
            tmp = polygons[i].a;
            polygons[i].a = polygons[i].c;
            polygons[i].c = tmp;
        }
        if (vertices[polygons[i].c].y() > vertices[polygons[i].b].y())
        {
            tmp = polygons[i].b;
            polygons[i].b = polygons[i].c;
            polygons[i].c = tmp;
        }
    }
}

void SurfaceCalculation::deleteZBuffer()
{
    for (int i = 0; i < width; ++i)
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
