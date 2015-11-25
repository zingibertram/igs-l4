#include "surfaceimage.h"
#include "common/surfacecalculation.h"

SurfaceImage::SurfaceImage(QWidget *parent) :
    QGraphicsView(parent)
{
}

// in kubuntu old image didn't removing
void SurfaceImage::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing, true);

    drawAxis(&painter);

    surfCalc->calculateSurface();

    if (surface->type == FRAME)
    {
        drawFrame(&painter);
    }
    else
    {
        QImage bmp(size(), QImage::Format_ARGB32);

        surfCalc->setSize(width(), height());
        surfCalc->calculateColors(&bmp);
        painter.drawImage(0, 0, bmp);
    }
}

void SurfaceImage::drawFrame(QPainter *pai)
{
    QPointF center(width() / 2.0, height() / 2.0);

    pai->setPen(QPen(Qt::red, 1));

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
    int w = width();
    int h = height();
    int cw = w / 2;
    int ch = h / 2;

    p->setPen(QPen(Qt::white, 1));
    p->drawLine(0, ch, w, ch);
    QPolygon pl;
    pl << QPoint(w, ch) << QPoint(w - 10, ch - 5) << QPoint(w - 10, ch + 5);
    QPainterPath pathl;
    pathl.addPolygon(pl);
    p->fillPath(pathl, QBrush(Qt::white));

    p->drawLine(cw, 0, cw, h);
    QPolygon pt;
    pt << QPoint(cw, 0) << QPoint(cw - 5, 10) << QPoint(cw + 5, 10);
    QPainterPath patht;
    patht.addPolygon(pt);
    p->fillPath(patht, QBrush(Qt::white));
}

void SurfaceImage::setSurface(Surface* sur)
{
    surface = sur;
    surfCalc = new SurfaceCalculation(sur);
}
