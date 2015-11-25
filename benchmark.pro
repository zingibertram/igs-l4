# need liab like QColor or QPoint
QT += core gui
#QT -= gui

TARGET = benchmark
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += test/main.cpp \
    common/point3d.cpp \
    common/matrix.cpp \
    common/drawing.cpp \
    common/utils.cpp \
    common/drawFlat.cpp \
    common/drawHuro.cpp \
    common/drawFong.cpp \
    common/vector.cpp \
    common/surface.cpp \
    common/surfacecalculation.cpp \
    common/tripolygon.cpp \
    common/surfacefunction.cpp \
    test/benchmark.cpp

HEADERS  += common/point3d.h \
    common/matrix.h \
    common/surface.h \
    common/drawing.h \
    common/utils.h \
    common/vector.h \
    common/typedefs.h \
    common/surfacecalculation.h \
    common/tripolygon.h \
    common/surfacefunction.h \
    test/benchmark.h

