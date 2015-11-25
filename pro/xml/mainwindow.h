#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common/surface.h"
#include "common/surfacefunction.h"

#include <QMainWindow>
#include <QSpinBox>
#include <QMap>
#include <QList>
#include <QColor>
#include <QPalette>
#include <QMessageBox>
#include <QRadioButton>
#include <QImage>
#include <QStringList>

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

    void textureChanged(QString tex);
    void setConnection();
    void setComboBoxFuncItems();
    void setSlidersRange();
    void paramsChanged();
    void changeChecked(QPushButton* pb, bool need = true);
    int calcSliderTitleWidth(QStringList titles);

private slots:
    void reset();

    void actionAboutTriggered();
    void expandAll();
    void collapseAll();

    void on_comboBox_SurfaceFunctions_currentIndexChanged(int index);

    void shadingChanged(bool isflat);

    void on_checkBox_Textured_clicked(bool checked);
    void on_pushButton_ChooseTexture_clicked();

    void on_slider_UMax_valueChanged(int value);
    void on_slider_VMax_valueChanged(int value);
    void on_slider_dU_valueChanged(int value);
    void on_slider_dV_valueChanged(int value);
    void on_slider_U_Param_valueChanged(int value);
    void on_slider_V_Param_valueChanged(int value);

    void on_X_Rotate_Changed(int value);
    void on_Y_Rotate_Changed(int value);
    void on_Z_Rotate_Changed(int value);

    void on_slider_Absent_valueChanged(int value);
    void on_slider_Diffusion_valueChanged(int value);
    void on_slider_Specular_valueChanged(int value);
    void on_slider_Power_valueChanged(int value);
    void on_slider_Alpha_valueChanged(int value);

    void illuminantCoords_Changed();

    void exteriorColor_Changed(QColor color);
    void interiorColor_Changed(QColor color);
    void dotColor_Changed(QColor color);
    void absentColor_Changed(QColor color);
};

#endif // MAINWINDOW_H
