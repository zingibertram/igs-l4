#include "benchmark.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Benchmark benchmark;

    for (int i = 0; i < 5; ++i)
    {
        benchmark.test();
    }

    return a.exec();
}

