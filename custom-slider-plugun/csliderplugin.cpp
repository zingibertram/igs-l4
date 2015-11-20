#include "csliderplugin.h"
#include "cslider.h"

CSliderPlugin::CSliderPlugin(QObject *parent)
    : QObject(parent)
    , initialized(false)
{

}

void CSliderPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool CSliderPlugin::isInitialized() const
{
    return initialized;
}

QWidget *CSliderPlugin::createWidget(QWidget *parent)
{
    return new CSlider(parent);
}

QString CSliderPlugin::name() const
{
    return "CSlider";
}

QString CSliderPlugin::group() const
{
    return "Display Widgets [Examples]";
}

QIcon CSliderPlugin::icon() const
{
    return QIcon(":/cslider.png");
}

QString CSliderPlugin::toolTip() const
{
    return "Custom slider";
}

QString CSliderPlugin::whatsThis() const
{
    return "Slider with titel, min, max & value labels";
}

bool CSliderPlugin::isContainer() const
{
    return false;
}

QString CSliderPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"CSlider\" name=\"slider\">\n"
           "  <property name=\"title\">\n"
           "   <string>T</string>\n"
           "  </property>\n"
           "  <property name=\"minimum\">\n"
           "   <number>0</number>\n"
           "  </property>\n"
           "  <property name=\"maximum\">\n"
           "   <number>100</number>\n"
           "  </property>\n"
           "  <property name=\"value\">\n"
           "   <number>10</number>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString CSliderPlugin::includeFile() const
{
    return "cslider.h";
}

