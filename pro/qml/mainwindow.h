#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common/surface.h"
#include "common/surfacefunction.h"
#include "common/surfacecalculation.h"

#include <QObject>
#include <QMap>
#include <QList>
#include <QString>
#include <QStringList>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList surfaceFunctions READ getSurfaceFunctions)
    Q_PROPERTY(int paintViewWidth WRITE setPaintViewWidth)
    Q_PROPERTY(int paintViewHeight WRITE setPaintViewHeight)
    Q_PROPERTY(int rangeMinU READ getRangeMinU NOTIFY rangeChanged)
    Q_PROPERTY(int rangeMaxU READ getRangeMaxU NOTIFY rangeChanged)
    Q_PROPERTY(int rangeMinV READ getRangeMinV NOTIFY rangeChanged)
    Q_PROPERTY(int rangeMaxV READ getRangeMaxV NOTIFY rangeChanged)

    // main
    Q_PROPERTY(QString surfaceFunction WRITE setSurfaceFunction)

    Q_PROPERTY(Sh surfaceShading WRITE setSurfaceShading)

    Q_PROPERTY(bool textured WRITE setTextured)
    Q_PROPERTY(QString texturePath WRITE setTexturePath)

    // surface params
    Q_PROPERTY(int maxU WRITE setMaxU)
    Q_PROPERTY(int maxV WRITE setMaxV)
    Q_PROPERTY(int dU WRITE setDU)
    Q_PROPERTY(int dV WRITE setDV)
    Q_PROPERTY(int param_R WRITE setParam_R)
    Q_PROPERTY(int param_r WRITE setParam_r)

    Q_PROPERTY(int rotX WRITE setRotX)
    Q_PROPERTY(int rotY WRITE setRotY)
    Q_PROPERTY(int rotZ WRITE setRotZ)

    // illuminant params
    Q_PROPERTY(double light_ka WRITE setLight_ka)
    Q_PROPERTY(double light_kd WRITE setLight_kd)
    Q_PROPERTY(double light_ks WRITE setLight_ks)
    Q_PROPERTY(int light_n WRITE setLight_n)
    Q_PROPERTY(double light_alpha WRITE setLight_alpha)

    Q_PROPERTY(int lightX WRITE setLightX)
    Q_PROPERTY(int lightY WRITE setLightY)
    Q_PROPERTY(int lightZ WRITE setLightZ)

    // color selection
    Q_PROPERTY(QString dottedColor WRITE setDottedColor)

    Q_PROPERTY(QString absentedColor WRITE setAbsentedColor)

    Q_PROPERTY(QString exteriorColor WRITE setExteriorColor)

    Q_PROPERTY(QString interiorColor WRITE setInteriorColor)


    //TODO: заменить на 2 массива
    //массив цветов(bmp) и отрезков
    //Q_PROPERTY(QImage surfaceImage READ surfaceImage WRITE setSurfaceImage NOTIFY surfaceImageChanged)

    Q_PROPERTY(bool canCalculate MEMBER _canCalculate NOTIFY canCalculateChanged)
    Q_PROPERTY(QList<int> frameDrawingData MEMBER _frameDrawingData NOTIFY frameDrawingDataChanged)
    Q_PROPERTY(QList<int> colorDrawingData MEMBER _colorDrawingData NOTIFY colorDrawingDataChanged)

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
    QMap<QString, SurfaceFunction*> functions;
    SurfaceCalculation* surfCalc;
    int width;
    int height;
    bool _canCalculate;
    QList<int> _frameDrawingData;
    QList<int> _colorDrawingData;

    void paramsChanged(bool isCalc = false);

    QStringList getSurfaceFunctions();

    void setSurfaceFunction(const QString &s);

    void setPaintViewWidth(int value);
    void setPaintViewHeight(int value);

    int getRangeMinU();
    int getRangeMaxU();
    int getRangeMinV();
    int getRangeMaxV();

    // main
    void setSurfaceShading(Sh sh);
    void setTextured(bool t);
    void setTexturePath(const QString &s);

    // surface
    void setMaxU(int value);
    void setMaxV(int value);
    void setDU(int value);
    void setDV(int value);
    void setParam_R(int value);
    void setParam_r(int value);

    void setRotX(int value);
    void setRotY(int value);
    void setRotZ(int value);

    // illuminant
    void setLight_ka(double value);
    void setLight_kd(double value);
    void setLight_ks(double value);
    void setLight_n(int value);
    void setLight_alpha(double value);

    void setLightX(int value);
    void setLightY(int value);
    void setLightZ(int value);

    // color selection
    void setDottedColor(const QString &s);

    void setAbsentedColor(const QString &s);

    void setExteriorColor(const QString &s);

    void setInteriorColor(const QString &s);


    void setOldRotate();

    void calculate();
    void getFrameData();
    void getColorData(QImage *bmp);

signals:
    void rangeChanged();
    void canCalculateChanged();
    void frameDrawingDataChanged();
    void colorDrawingDataChanged();

private slots:

};

#endif // MAINWINDOW_H
