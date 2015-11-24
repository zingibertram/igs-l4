#include "mainwindow.h"
#include "common/surfacefunction.h"
#include "common/utils.h"
#include "common/vector.h"
#include "common/point3d.h"
#include "common/tripolygon.h"

#include <QFileDialog>
#include <QScrollBar>
#include <QPen>
#include <QImage>
#include <QPainter>
#include <QDebug>

#include <math.h>

MainWindow::MainWindow() :
    QObject()
{
    functions["Sphere"] = new Sphere();
    functions["Torus"] = new Torus();
    functions["Hourglass"] = new Hourglass();
    functions["Trefoil"] = new Trefoil();
    functions["Seashell"] = new Seashell();
    functions["KleinBottle"] = new KleinBottle();
    functions["ConicalSpiralModCliffordTorus"] = new ConicalSpiralModCliffordTorus();
    functions["SpiralModCliffordTorus"] = new SpiralModCliffordTorus();
    functions["CliffordTorus"] = new CliffordTorus();
    functions["HyperbolicHelicoid"] = new HyperbolicHelicoid();
    functions["Catenoid"] = new Catenoid();
    functions["Helicoid"] = new Helicoid();
    functions["Surface1"] = new Surface1();
    functions["Hyperboloid2Sheets"] = new Hyperboloid2Sheets();
    functions["Hyperboloid1Sheet"] = new Hyperboloid1Sheet();
    functions["ConicalSpiral"] = new ConicalSpiral();
    functions["Spiral"] = new Spiral();
    functions["Surface2"] = new Surface2();
    functions["CrossCup"] = new CrossCup();
    functions["AstroidalEllipsoid"] = new AstroidalEllipsoid();
    functions["EightSurface"] = new EightSurface();
    functions["Surface3"] = new Surface3();
    functions["Surface4"] = new Surface4();

    surface.textureImg.load(":/textures/resources/tex1.jpg");
    surface.func = functions["Sphere"];

    surfCalc = new SurfaceCalculation(&surface);

    _canCalculate = false;
}

MainWindow::~MainWindow()
{
}

void MainWindow::paramsChanged()
{
    if (!_canCalculate)
    {
        return;
    }

    calculate();
}

QStringList MainWindow::getSurfaceFunctions()
{
    QStringList res;
    QList<QString> keys = functions.keys();
    for (int i = 0; i < keys.count(); ++i)
    {
        res.append(keys[i]);
    }
    return res;
}

void MainWindow::setPaintViewWidth(int value)
{
    width = value;
    paramsChanged();
}

void MainWindow::setPaintViewHeight(int value)
{
    height = value;
    paramsChanged();
}

int MainWindow::getRangeMinU()
{
    return surface.func
            ? surface.func->surfaceBorder()->minU
            : 0;
}

int MainWindow::getRangeMaxU()
{
    return surface.func
            ? surface.func->surfaceBorder()->maxU
            : 360;
}

int MainWindow::getRangeMinV()
{
    return surface.func
            ? surface.func->surfaceBorder()->minV
            : 0;
}

int MainWindow::getRangeMaxV()
{
    return surface.func
            ? surface.func->surfaceBorder()->maxV
            : 360;
}


void MainWindow::setSurfaceFunction(const QString &s)
{
    if (functions.contains(s))
    {
        SurfaceFunction* f = functions[s];
        if (surface.func)
        {
            f->surfaceBorder()->dU = surface.func->surfaceBorder()->dU;
            f->surfaceBorder()->dV = surface.func->surfaceBorder()->dV;
            f->setParams(surface.func->getFst(), surface.func->getSnd());
        }
        surface.func = f;
        paramsChanged();
        emit rangeChanged();
    }
}

void MainWindow::setSurfaceShading(Sh sh)
{
    surface.type = (Shading)sh;
    paramsChanged();
}

void MainWindow::setTextured(bool t)
{
    surface.isTextured = t;
    paramsChanged();
}

void MainWindow::setTexturePath(const QString &s)
{
    // не загружается текстура в png
    QString path(s); // s == file:///*
    path.remove(0, 8);

    surface.textureImg.load(path);
    paramsChanged();
}

void MainWindow::setMaxU(int value)
{
    if (!surface.func)
    {
        return;
    }

    surface.func->surfaceBorder()->dU = value;
    surface.maxU = value;
    paramsChanged();
}

void MainWindow::setMaxV(int value)
{
    if (!surface.func)
    {
        return;
    }

    surface.func->surfaceBorder()->dV = value;
    surface.maxV = value;
    paramsChanged();
}

void MainWindow::setDU(int value)
{
    surface.dU = value;
    paramsChanged();
}

void MainWindow::setDV(int value)
{
    surface.dV = value;
    paramsChanged();
}

void MainWindow::setParam_R(int value)
{
    if (!surface.func)
    {
        return;
    }

    surface.func->setFirstParam(value);
    paramsChanged();
}

void MainWindow::setParam_r(int value)
{
    if (!surface.func)
    {
        return;
    }

    surface.func->setSecondParam(value);
    paramsChanged();
}

void MainWindow::setRotX(int value)
{
    setOldRotate();
    surface.xRotate = value;
    paramsChanged();
    setOldRotate();
}

void MainWindow::setRotY(int value)
{
    setOldRotate();
    surface.yRotate = value;
    paramsChanged();
    setOldRotate();
}

void MainWindow::setRotZ(int value)
{
    setOldRotate();
    surface.zRotate = value;
    paramsChanged();
    setOldRotate();
}

void MainWindow::setLight_ka(double value)
{
    surface.ka = value;
    paramsChanged();
}

void MainWindow::setLight_kd(double value)
{
    surface.kd = value;
    paramsChanged();
}

void MainWindow::setLight_ks(double value)
{
    surface.ks = value;
    paramsChanged();
}

void MainWindow::setLight_n(int value)
{
    surface.n = value;
    paramsChanged();
}

void MainWindow::setLight_alpha(double value)
{
    surface.alpha = value;
    paramsChanged();
}

void MainWindow::setLightX(int value)
{
    surface.light.setX(value);
    paramsChanged();
}

void MainWindow::setLightY(int value)
{
    surface.light.setY(value);
    paramsChanged();
}

void MainWindow::setLightZ(int value)
{
    surface.light.setZ(value);
    paramsChanged();
}


void MainWindow::setDottedColor(const QString &s)
{
    surface.dot = QColor(s);
    paramsChanged();
}

void MainWindow::setAbsentedColor(const QString &s)
{
    surface.absent = QColor(s);
    paramsChanged();
}

void MainWindow::setExteriorColor(const QString &s)
{
    surface.exterior = QColor(s);
    paramsChanged();
}

void MainWindow::setInteriorColor(const QString &s)
{
    surface.interior = QColor(s);
    paramsChanged();
}

void MainWindow::setOldRotate()
{
    surface.xOld = surface.xRotate;
    surface.yOld = surface.yRotate;
    surface.zOld = surface.zRotate;
}

void MainWindow::calculate()
{
    if (!width || !height || width > 9999 || height > 9999 || !surface.func)
    {
        return;
    }

    QImage bmp(width, height, QImage::Format_ARGB32);

    surfCalc->setSize(width, height);
    surfCalc->calculateSurface();

    if (surface.type == FRAME)
    {
        getFrameData();
        emit frameDrawingDataChanged();
    }
    else
    {
        surfCalc->calculateColors(&bmp);

        getColorData(&bmp);
        emit colorDrawingDataChanged();
    }

}

void MainWindow::getFrameData()
{
    _frameDrawingData.clear();

    QList<Point3D>* vertices = surfCalc->vertices_();
    QList<TriPolygon>* polygons = surfCalc->polygons_();
    if (!vertices || vertices->count() == 0 || !polygons || polygons->count() == 0)
    {
        return;
    }
    QPointF center(width / 2.0, height / 2.0);

    // polygons->count() * 2 * 3 - количество элементов
    for (int i = 0; i < polygons->count(); ++i)
    {
        TriPolygon polygon = polygons->operator [](i);
        QPointF vertex[3];
        vertex[0] = vertices->operator [](polygon.a).toQPoint() + center;
        vertex[1] = vertices->operator [](polygon.b).toQPoint() + center;
        vertex[2] = vertices->operator [](polygon.c).toQPoint() + center;

        _frameDrawingData.append(vertex[0].x());
        _frameDrawingData.append(vertex[0].y());
        _frameDrawingData.append(vertex[1].x());
        _frameDrawingData.append(vertex[1].y());
        _frameDrawingData.append(vertex[2].x());
        _frameDrawingData.append(vertex[2].y());
    }
}

void MainWindow::getColorData(QImage* bmp)
{
    _colorDrawingData.clear();

    // width * height - количество элементов
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            QRgb c = bmp->pixel(i, j);
//            if (!c)
//            {
//                unsigned int m = 0;
//                c = m - 1;
//            }
            QColor color(c);
            _colorDrawingData.append(color.red());
            _colorDrawingData.append(color.green());
            _colorDrawingData.append(color.blue());
            _colorDrawingData.append(color.alpha());
        }
    }
}

//void MainWindow::drawFrame(QPainter *pai)
//{
//    QPointF center(width / 2.0, height / 2.0);

//    pai->setPen(QPen(Qt::white));

//    QList<Point3D>* vertices = surfCalc->vertices_();
//    QList<TriPolygon>* polygons = surfCalc->polygons_();
//    if (!vertices || vertices->count() == 0 || !polygons || polygons->count() == 0)
//    {
//        return;
//    }

//    for (int i = 0; i < polygons->count(); ++i)
//    {
//        TriPolygon polygon = polygons->operator [](i);
//        QPointF vertex[3];
//        vertex[0] = vertices->operator [](polygon.a).toQPoint() + center;
//        vertex[1] = vertices->operator [](polygon.b).toQPoint() + center;
//        vertex[2] = vertices->operator [](polygon.c).toQPoint() + center;
//        pai->drawLine(vertex[0], vertex[1]);
//        pai->drawLine(vertex[2], vertex[1]);
//        pai->drawLine(vertex[0], vertex[2]);
//    }

////    for (int i = 0; i < vertices->count(); ++i)
////    {
////        QPointF t = vertices->operator [](i).toQPoint() + center;
////        QString st;
////        pai->drawText(t, st.number(i));
////    }

////    for (int i = 0; i < vertices->count(); ++i)
////    {
////        QPointF t = vertices->operator [](i).toQPoint() + center;
////        QString st;
////        pai->drawEllipse(t, 4, 4);
////    }
//}
