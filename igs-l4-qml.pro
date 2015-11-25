TEMPLATE = app

QT += qml quick widgets

TARGET = igs-l4-quick

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
# include(deployment.pri)

HEADERS 

RC_FILE=common/winico.rc

RESOURCES += \
    common/resources.qrc \
    qml/qml.qrc

HEADERS += \
    common/drawing.h \
    common/matrix.h \
    common/point3d.h \
    common/surface.h \
    common/surfacecalculation.h \
    common/surfacefunction.h \
    common/triangle.h \
    common/tripolygon.h \
    common/typedefs.h \
    common/utils.h \
    common/vector.h \
    qml/mainwindow.h

SOURCES += \
    common/drawFlat.cpp \
    common/drawFong.cpp \
    common/drawHuro.cpp \
    common/drawing.cpp \
    common/matrix.cpp \
    common/point3d.cpp \
    common/surface.cpp \
    common/surfacecalculation.cpp \
    common/surfacefunction.cpp \
    common/triangle.cpp \
    common/tripolygon.cpp \
    common/utils.cpp \
    common/vector.cpp \
    qml/main.cpp \
    qml/mainwindow.cpp
