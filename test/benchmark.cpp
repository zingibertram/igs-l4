#include "benchmark.h"
#include "common/surfacefunction.h"

#include <QTime>
#include <QDebug>

Benchmark::Benchmark()
{
    calculator = new SurfaceCalculation(&surface);
}

void Benchmark::test()
{
    setParams1();

    QTime timer;
    timer.start();

    calculate();

    int ms = timer.elapsed();

    qDebug() << "Params1" << ms << "milliseconds";
}

void Benchmark::calculate()
{
    QImage bmp(width, height, QImage::Format_ARGB32);

    calculator->calculateSurface();
    calculator->setSize(width, height);
    calculator->calculateColors(&bmp);
}

void Benchmark::setParams1()
{
    width = 400;
    height = 400;

    SurfaceFunction *func = new Helicoid();

    SurfaceBorder *border = func->surfaceBorder();

    Vector l(0, 0, 100);
    l.unit();

    surface.func = func;
    //surface.type = FONG;
    surface.type = HURO;
    surface.isTextured = false;
    border->dU = 360;
    border->dV = 1080;
    surface.dU = 50;
    surface.dV = 50;
    func->setParams(60, 70);
    surface.xOld = surface.xRotate = 0;
    surface.yOld = surface.yRotate = 0;
    surface.zOld = surface.zRotate = 0;
    surface.ka = 0.2;
    surface.kd = 1;
    surface.ks = 0.8;
    surface.n = 25;
    surface.alpha = 1;
    surface.light = l;
    surface.dot = QColor(Qt::white);
    surface.absent = QColor(Qt::white);
    surface.exterior = QColor(255, 0, 0);
    surface.dot = QColor(0, 255, 0);
}

void Benchmark::setParams2()
{

}

void Benchmark::setParams3()
{

}

