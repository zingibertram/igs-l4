
QT          += widgets uiplugin

CONFIG      += plugin

TEMPLATE    = lib

TARGET = $$qtLibraryTarget($$TARGET)

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

HEADERS += \
    cslider.h \
    csliderplugin.h

SOURCES += \
    cslider.cpp \
    csliderplugin.cpp

RESOURCES += \
    icons.qrc

#DESTDIR = $(QTDIR)/plugins/designer
