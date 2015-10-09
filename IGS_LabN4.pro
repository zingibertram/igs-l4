#-------------------------------------------------
#
# Project created by QtCreator 2012-09-20T19:16:45
#
#-------------------------------------------------

QT       += core gui

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
    tripolygon.cpp
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
    tripolygon.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    replace.txt \
    TMVertexGenerator.cs \
    out.txt \
    old.txt

RESOURCES += \
    resources.qrc

RC_FILE += winico.rc


























