#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "surface.h"
#include "surfacefunction.h"

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Surface surface;
    bool isSetFirstState;
    QImage texture;
    QMap<QString, SurfaceFunction*> functions;

    void setCurrentColor(QWidget *panel, QColor current, QColor *surfaceSide);
    void paramsChanged(bool isCalc = false);
    void textureChanged(QString tex);
    void setConnection();
    void setValueLabel(QLabel *l = 0, double val = 0, int len = 0, QString dec = "");
    void setComboBoxFuncItems();

private slots:
    void actionAboutTriggered();
    void shadingChanged(bool isflat);
    void exteriorColor_Changed();
    void interiorColor_Changed();
    void dotColor_Changed();
    void absentColor_Changed();
    void illuminantCoords_Changed();
    void reset();

    void on_slider_XRotate_valueChanged(int value);
    void on_slider_YRotate_valueChanged(int value);
    void on_slider_ZRotate_valueChanged(int value);
    void on_slider_UMax_valueChanged(int value);
    void on_slider_VMax_valueChanged(int value);
    void on_slider_dU_valueChanged(int value);
    void on_slider_dV_valueChanged(int value);
    void on_slider_U_Param_valueChanged(int value);
    void on_slider_V_Param_valueChanged(int value);

    void on_slider_Absent_valueChanged(int value);
    void on_slider_Diffusion_valueChanged(int value);
    void on_slider_Specular_valueChanged(int value);
    void on_slider_Power_valueChanged(int value);
    void on_slider_Alpha_valueChanged(int value);
    void on_pushButton_ChooseTexture_clicked();
    void on_checkBox_Textured_clicked(bool checked);

    void on_comboBox_SurfaceFunctions_currentIndexChanged(int index);

    void expandAll();
    void collapseAll();
};

#endif // MAINWINDOW_H
