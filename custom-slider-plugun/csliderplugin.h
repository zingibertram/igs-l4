#ifndef CSLIDERPLUGIN_H
#define CSLIDERPLUGIN_H

#include <QtCore/QObject>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class CSliderPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    //Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "analogclock.json")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit CSliderPlugin(QObject *parent = 0);

    bool isContainer() const Q_DECL_OVERRIDE;
    bool isInitialized() const Q_DECL_OVERRIDE;
    QIcon icon() const Q_DECL_OVERRIDE;
    QString domXml() const Q_DECL_OVERRIDE;
    QString group() const Q_DECL_OVERRIDE;
    QString includeFile() const Q_DECL_OVERRIDE;
    QString name() const Q_DECL_OVERRIDE;
    QString toolTip() const Q_DECL_OVERRIDE;
    QString whatsThis() const Q_DECL_OVERRIDE;
    QWidget *createWidget(QWidget *parent) Q_DECL_OVERRIDE;
    void initialize(QDesignerFormEditorInterface *core) Q_DECL_OVERRIDE;

private:
    bool initialized;
};

#endif // CSLIDERPLUGIN_H
