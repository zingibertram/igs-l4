#include "surfaceimage.h"
#include "surfacecalculation.h"

#include <QDebug>
#include <QTime>

#include <stdio.h>

SurfaceImage::SurfaceImage(QWidget *parent) :
    QGraphicsView(parent)
{
}

void SurfaceImage::paintEvent(QPaintEvent *event)
{
    QTime time;
    time.start();

    QGraphicsView::paintEvent(event);

    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing, true);

    drawAxis(&painter);

    surfCalc->calculateSurface();

    drawAxis(&painter);

    QImage bmp(size(), QImage::Format_ARGB32);
    if (surface->type == FRAME)
    {
        drawFrame(&painter);
    }
    else
    {
        surfCalc->setSize(width(), height());
        surfCalc->calculateColors(&bmp);
        painter.drawImage(0, 0, bmp);
    }

    int t = time.elapsed();
    qDebug() << "Draw surface of type (%i)" << surface->type << ") is " << t << "ms";
}

void SurfaceImage::drawFrame(QPainter *pai)
{
    QPointF center(width() / 2.0, height() / 2.0);

    pai->setPen(QPen(Qt::white));

    QList<Point3D>* vertices = surfCalc->vertices_();
    QList<TriPolygon>* polygons = surfCalc->polygons_();
    if (!vertices || vertices->count() == 0 || !polygons || polygons->count() == 0)
    {
        return;
    }

    for (int i = 0; i < polygons->count(); ++i)
    {
        TriPolygon polygon = polygons->operator [](i);
        QPointF vertex[3];
        vertex[0] = vertices->operator [](polygon.a).toQPoint() + center;
        vertex[1] = vertices->operator [](polygon.b).toQPoint() + center;
        vertex[2] = vertices->operator [](polygon.c).toQPoint() + center;
        pai->drawLine(vertex[0], vertex[1]);
        pai->drawLine(vertex[2], vertex[1]);
        pai->drawLine(vertex[0], vertex[2]);
    }
}

void SurfaceImage::drawAxis(QPainter *p)
{
    QPointF center(width() / 2.0, height() / 2.0);

    p->setPen(QPen(Qt::white, 1));
    QPoint x(width() - 20, center.y());
    p->drawLine(QPoint(20, center.y()), x);
    p->drawLine(x, x + QPoint(-12, -8));
    p->drawLine(x, x + QPoint(-12, 8));
    p->drawText(x + QPoint(0, 12), "X");

    QPoint y(center.x(), 20);
    p->drawLine(QPoint(center.x(), height() - 20), y);
    p->drawLine(y, y + QPoint(8, 12));
    p->drawLine(y, y + QPoint(-8, 12));
    p->drawText(y + QPoint(12, 8), "Y");
}

void SurfaceImage::setSurface(Surface* sur)
{
    surface = sur;
    surfCalc = new SurfaceCalculation(sur);
}
