#include "surfacecalculation.h"

#include <QtAlgorithms>
#include <QDebug>

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
    vertices.clear();
    texels.clear();
    polygons.clear();

    calculateRotateMatrix();
    calculateVertices();
    calculatePolygons();

    qSort(polygons);
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

        // Good 1100 ms -> 800 ms
        if (!pointInImage(&A) && !pointInImage(&B) && !pointInImage(&C))
        {
            continue;
        }

        drawing->setPolygon(i);

        for (int sy = (int)C.y(); sy <= (int)(A.y() + 0.5); sy++)
        {
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

            for (int sx = (int)xa; sx <= (int)(xb + 0.5); sx++)
            {
                double k = (sx - xa) / (xb - xa);
                double sz = za + (zb - za) * k;
                int xp = (int)(sx + center.x());
                int yp = (int)(center.y() - sy);

                if (xp < 0 || width <= xp || yp < 0 || height <= yp)
                {
                    continue;
                }

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
        surface->xOld = surface->xRotate;
        return;
    }
    if (surface->yOld != surface->yRotate)
    {
        rotate *= rotateMatrix(0, 2, 360 - surface->yRotate + surface->yOld);
        surface->yOld = surface->yRotate;
        return;
    }
    if (surface->zOld != surface->zRotate)
    {
        rotate *= rotateMatrix(0, 1, surface->zRotate - surface->zOld);
        surface->zOld = surface->zRotate;
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
}

void SurfaceCalculation::calculatePolygons()
{
    SurfaceBorder* b = surface->func->surfaceBorder();

    bool isU = b->dU == b->maxU && b->isUCycle;
    bool isV = b->dV == b->maxV && b->isVCycle;

    int u = surface->dU + !isU;
    int v = surface->dV + !isV;

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
    double ax = A->x();
    double ay = A->y();
    double az = A->z();

    double bx = B->x();
    double by = B->y();
    double bz = B->z();

    double cx = C->x();
    double cy = C->y();
    double cz = C->z();

    double x = (ay - by)*(az + bz)+(by - cy)*(bz + cz)+(cy - ay)*(cz + az);
    double y = (az - bz)*(ax + bx)+(bz - cz)*(bx + cx)+(cz - az)*(cx + ax);
    double z = (ax - bx)*(ay + by)+(bx - cx)*(by + cy)+(cx - ax)*(cy + ay);

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
    FlatDrawing* drawing;
    switch (surface->type)
    {
        case FLAT:
            drawing = new FlatDrawing(surface, zBuffer, bmp);
            break;
        case HURO:
            drawing = new HuroDrawing(surface, zBuffer, bmp);
            break;
        case FONG:
            drawing = new FongDrawing(surface, zBuffer, bmp);
            break;
        default:
            throw "Unsupported colorable surface type";
    }

    drawing->setDataArrays(&vertices, &texels, &polygons);
    return drawing;
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

bool SurfaceCalculation::pointInImage(Point3D* p)
{
    int x = p->x() + width / 2;
    int y = height / 2 - p->y();

    return !(x < 0 || width < x || y < 0 || height < y);
}
