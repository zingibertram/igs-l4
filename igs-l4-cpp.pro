#-------------------------------------------------
#
# Project created by QtCreator 2012-09-20T19:16:45
#
#-------------------------------------------------

# files encoding in cp1251

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = igs-l4-widgets
TEMPLATE = app


SOURCES += xml/main.cpp\
        xml/mainwindow.cpp \
    common/point3d.cpp \
    common/matrix.cpp \
    xml/surfaceimage.cpp \
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
    xml/colorbox.cpp \
    xml/cslider.cpp

HEADERS  += xml/mainwindow.h \
    common/point3d.h \
    common/matrix.h \
    xml/surfaceimage.h \
    common/surface.h \
    common/drawing.h \
    common/utils.h \
    common/vector.h \
    common/typedefs.h \
    common/surfacecalculation.h \
    common/tripolygon.h \
    common/surfacefunction.h \
    xml/colorbox.h \
    xml/cslider.h

FORMS    += xml/mainwindow.ui \
    xml/colorbox.ui \
    xml/cslider.ui

RESOURCES += \
    common/resources.qrc \
    common/icon_theme/breeze_classic/actions_16.qrc \
    common/icon_theme/breeze_classic/actions_22.qrc \
    common/icon_theme/breeze_classic/actions_24.qrc \
    common/icon_theme/breeze_classic/actions_32.qrc \
    common/icon_theme/breeze_classic/actions_48.qrc \
    common/icon_theme/breeze_classic/applets_256.qrc \
    common/icon_theme/breeze_classic/apps_16.qrc \
    common/icon_theme/breeze_classic/apps_22.qrc \
    common/icon_theme/breeze_classic/apps_32.qrc \
    common/icon_theme/breeze_classic/apps_48.qrc \
    common/icon_theme/breeze_classic/categories_16.qrc \
    common/icon_theme/breeze_classic/categories_22.qrc \
    common/icon_theme/breeze_classic/categories_32.qrc \
    common/icon_theme/breeze_classic/categories_48.qrc \
    common/icon_theme/breeze_classic/devices_16.qrc \
    common/icon_theme/breeze_classic/devices_22.qrc \
    common/icon_theme/breeze_classic/devices_48.qrc \
    common/icon_theme/breeze_classic/devices_64.qrc \
    common/icon_theme/breeze_classic/emblems_8.qrc \
    common/icon_theme/breeze_classic/emblems_16.qrc \
    common/icon_theme/breeze_classic/emblems_22.qrc \
    common/icon_theme/breeze_classic/emotes_22.qrc \
    common/icon_theme/breeze_classic/mimetypes_16.qrc \
    common/icon_theme/breeze_classic/mimetypes_22.qrc \
    common/icon_theme/breeze_classic/mimetypes_32.qrc \
    common/icon_theme/breeze_classic/mimetypes_64.qrc \
    common/icon_theme/breeze_classic/places_16.qrc \
    common/icon_theme/breeze_classic/places_22.qrc \
    common/icon_theme/breeze_classic/places_32.qrc \
    common/icon_theme/breeze_classic/places_64.qrc \
    common/icon_theme/breeze_classic/status_16.qrc \
    common/icon_theme/breeze_classic/status_22.qrc \
    common/icon_theme/breeze_classic/status_24.qrc \
    common/icon_theme/breeze_classic/status_64.qrc

RC_FILE += common/winico.rc
