#include "surfaceimage.h"
#include "utils.h"
#include "vector.h"
#include "surfacecalculation.h"

#include <QtAlgorithms>
#include <QDebug>

#include <stdio.h>

SurfaceImage::SurfaceImage(QWidget *parent) :
    QGraphicsView(parent)
{
}

void SurfaceImage::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    QPainter painter(this->viewport());
    painter.setRenderHint(QPainter::Antialiasing, true);

    this->drawAxis(&painter);

    surfCalc->calculateSurface();

    this->drawAxis(&painter);

    QImage bmp(this->size(), QImage::Format_ARGB32);
    if (surface->type == FRAME)
    {
        this->drawFrame(&painter);
    }
    else
    {
        surfCalc->calculateColors(&bmp);
        painter.drawImage(0, 0, bmp);
    }
}

void SurfaceImage::drawFrame(QPainter *pai)
{
    QPointF center(this->width() / 2.0, this->height() / 2.0);

//    for (int i = 0; i < polygons.count(); ++i)
//    {
//        Triangle polygon = polygons[i];
//        pai->setPen(QPen(Qt::white));
//        QPointF vertex[3];
//        vertex[0] = vertices[polygon.a].toQPoint() + center;
//        vertex[1] = vertices[polygon.b].toQPoint() + center;
//        vertex[2] = vertices[polygon.c].toQPoint() + center;
//        pai->drawLine(vertex[0], vertex[1]);
//        pai->drawLine(vertex[2], vertex[1]);
//        pai->drawLine(vertex[0], vertex[2]);
//    }
}

void SurfaceImage::drawAxis(QPainter *p)
{
    QPointF center(this->width() / 2.0, this->height() / 2.0);

    p->setPen(QPen(Qt::white, 1));
    QPoint x(this->width() - 20, center.y());
    p->drawLine(QPoint(20, center.y()), x);
    p->drawLine(x, x + QPoint(-12, -8));
    p->drawLine(x, x + QPoint(-12, 8));
    p->drawText(x + QPoint(0, 12), "X");

    QPoint y(center.x(), 20);
    p->drawLine(QPoint(center.x(), this->height() - 20), y);
    p->drawLine(y, y + QPoint(8, 12));
    p->drawLine(y, y + QPoint(-8, 12));
    p->drawText(y + QPoint(12, 8), "Y");
}

void SurfaceImage::setSurface(Surface* sur)
{
    surface = sur;
    surfCalc = new SurfaceCalculation(sur);
}
