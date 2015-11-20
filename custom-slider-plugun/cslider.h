#ifndef CSLIDER_H
#define CSLIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include <QtCore/QString>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT CSlider : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

public:
    explicit CSlider(QWidget *parent = 0);
//    ~CSlider();

signals:
    void valueChanged(int v);
    void minimumChanged(int v);
    void maximumChanged(int v);
    void titleChanged(QString s);

private slots:
    void on_slider_valueChanged(int v);

private:
    QHBoxLayout *layout;
    QLabel *label_Title;
    QLabel *label_Min;
    QSlider *slider;
    QLabel *label_Max;
    QLabel *label_Value;

    void setupUi();

    void setValue(int v);
    int value();
    void setMinimum(int v);
    int minimum();
    void setMaximum(int v);
    int maximum();
    void setTitle(QString s);
    QString title();
};

#endif // CSLIDER_H
