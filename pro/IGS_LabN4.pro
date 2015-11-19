#-------------------------------------------------
#
# Project created by QtCreator 2012-09-20T19:16:45
#
#-------------------------------------------------

# files encoding in cp1251

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IGS_LabN4
TEMPLATE = app


SOURCES += xml/main.cpp\
        xml/mainwindow.cpp \
    common/point3d.cpp \
    common/matrix.cpp \
    xml/surfaceimage.cpp \
    common/triangle.cpp \
    common/drawing.cpp \
    common/utils.cpp \
    common/drawFlat.cpp \
    common/drawHuro.cpp \
    common/drawFong.cpp \
    common/vector.cpp \
    common/surface.cpp \
    common/surfacecalculation.cpp \
    common/tripolygon.cpp \
    common/surfacefunction.cpp

HEADERS  += xml/mainwindow.h \
    common/point3d.h \
    common/matrix.h \
    xml/surfaceimage.h \
    common/surface.h \
    common/triangle.h \
    common/drawing.h \
    common/utils.h \
    common/vector.h \
    common/typedefs.h \
    common/surfacecalculation.h \
    common/tripolygon.h \
    common/surfacefunction.h

FORMS    += xml/mainwindow.ui

RESOURCES += \
    common/resources.qrc

RC_FILE += common/winico.rc
