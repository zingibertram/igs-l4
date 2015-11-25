#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "common/surface.h"
#include "common/surfacecalculation.h"
#include "common/surfacefunction.h"

class Benchmark
{
    Surface surface;
    SurfaceCalculation *calculator;

    int width;
    int height;

    void calculate();

    void setParams1();
    void setParams2();
    void setParams3();

public:
    Benchmark();

    void test();
};

#endif // BENCHMARK_H
