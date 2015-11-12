TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    drawFlat.cpp \
    drawFong.cpp \
    drawHuro.cpp \
    drawing.cpp \
    matrix.cpp \
    point3d.cpp \
    surface.cpp \
    surfacecalculation.cpp \
    surfacefunction.cpp \
    surfaceimage.cpp \
    triangle.cpp \
    tripolygon.cpp \
    utils.cpp \
    vector.cpp \
    mainwindow.cpp

RESOURCES += qml.qrc \
    resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
# include(deployment.pri)

HEADERS += \
    drawing.h \
    matrix.h \
    point3d.h \
    surface.h \
    surfacecalculation.h \
    surfacefunction.h \
    surfaceimage.h \
    triangle.h \
    tripolygon.h \
    typedefs.h \
    utils.h \
    vector.h \
    mainwindow.h

RC_FILE=winico.rc
