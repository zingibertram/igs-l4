#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "surface.h"
#include "surfacefunction.h"

#include <QObject>
#include <QMainWindow>
#include <QSpinBox>
#include <QMap>
#include <QList>
#include <QColor>
#include <QPalette>
#include <QMessageBox>
#include <QRadioButton>
#include <QImage>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList surfaceFunctions READ getSurfaceFunctions)
    Q_PROPERTY(QString surfaceFunction WRITE setSurfaceFunction)
    Q_PROPERTY(Sh surfaceShading WRITE setSurfaceShading)
    Q_PROPERTY(bool textured WRITE setTextured)
    Q_PROPERTY(QString texturePath WRITE setTexturePath)
    Q_PROPERTY(QString dottedColor WRITE setDottedColor)
    Q_PROPERTY(QString absentedColor WRITE setAbsentedColor)
    Q_PROPERTY(QString exteriorColor WRITE setExteriorColor)
    Q_PROPERTY(QString interiorColor WRITE setInteriorColor)

public:
    MainWindow();
    ~MainWindow();

    enum Sh
    {
        FR = FRAME,
        FL = FLAT,
        HU = HURO,
        FO = FONG
    };
    Q_ENUMS(Sh)

private:
    Surface surface;
//    QImage texture;
    QMap<QString, SurfaceFunction*> functions;

    void paramsChanged(bool isCalc = false);

    QStringList getSurfaceFunctions();

    void setSurfaceFunction(const QString &s);
    void setSurfaceShading(const Sh &sh);
    void setTextured(const bool &t);
    void setTexturePath(const QString &s);

    void setDottedColor(const QString &s);
    void setAbsentedColor(const QString &s);
    void setExteriorColor(const QString &s);
    void setInteriorColor(const QString &s);

//    void setCurrentColor(QWidget *panel, QColor current, QColor *surfaceSide);
//    void paramsChanged(bool isCalc = false);
//    void textureChanged(QString tex);
//    void setConnection();
//    void setValueLabel(QLabel *l = 0, double val = 0, int len = 0, QString dec = "");

private slots:
//    void shadingChanged(bool isflat);
//    void illuminantCoords_Changed();

//    void on_slider_XRotate_valueChanged(int value);
//    void on_slider_YRotate_valueChanged(int value);
//    void on_slider_ZRotate_valueChanged(int value);
//    void on_slider_UMax_valueChanged(int value);
//    void on_slider_VMax_valueChanged(int value);
//    void on_slider_dU_valueChanged(int value);
//    void on_slider_dV_valueChanged(int value);
//    void on_slider_U_Param_valueChanged(int value);
//    void on_slider_V_Param_valueChanged(int value);

//    void on_slider_Absent_valueChanged(int value);
//    void on_slider_Diffusion_valueChanged(int value);
//    void on_slider_Specular_valueChanged(int value);
//    void on_slider_Power_valueChanged(int value);
//    void on_slider_Alpha_valueChanged(int value);
//    void on_pushButton_ChooseTexture_clicked();
//    void on_checkBox_Textured_clicked(bool checked);

};

#endif // MAINWINDOW_H
