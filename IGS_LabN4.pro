#-------------------------------------------------
#
# Project created by QtCreator 2012-09-20T19:16:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IGS_LabN4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    point3d.cpp \
    matrix.cpp \
    surfaceimage.cpp \
    triangle.cpp \
    drawing.cpp \
    utils.cpp \
    drawFlat.cpp \
    drawHuro.cpp \
    drawFong.cpp \
    vector.cpp \
    surface.cpp \
    surfacecalculation.cpp \
    tripolygon.cpp \
    surfacefunction.cpp \
    Debug/debug/moc_mainwindow.cpp \
    Debug/debug/moc_surfaceimage.cpp \
    Debug/debug/qrc_resources.cpp
HEADERS  += mainwindow.h \
    point3d.h \
    matrix.h \
    surfaceimage.h \
    surface.h \
    triangle.h \
    drawing.h \
    utils.h \
    vector.h \
    typedefs.h \
    surfacecalculation.h \
    tripolygon.h \
    surfacefunction.h \
    Debug/ui_mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

RC_FILE += winico.rc

DISTFILES += \
    other/TMVertexGenerator.cs


























