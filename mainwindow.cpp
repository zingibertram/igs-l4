#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "surfacefunction.h"

#include <QFileDialog>
#include <QScrollBar>
#include <QDebug>

#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textureChanged(":/texture/resources/tex1.jpg");
    setConnection();
    setComboBoxFuncItems();
    reset();

    ui->graphicsView_Surface->setSurface(&surface);
    ui->radioButton_WireframeShading->click();
}

void MainWindow::reset()
{
    isSetFirstState = true;

    surface.xRotate = 0;
    surface.yRotate = 0;
    surface.zRotate = 0;

    surface.xOld = 0;
    surface.yOld = 0;
    surface.zOld = 0;

    surface.isTextured = false;
    surface.isPointsChanged = true;

    ui->slider_X_Rotate->setValue(90);
    ui->slider_Y_Rotate->setValue(60);
    ui->slider_Z_Rotate->setValue(30);

    ui->slider_U_Max->setValue(180);
    ui->slider_V_Max->setValue(180);

    ui->slider_U_Interval->setValue(20);
    ui->slider_V_Interval->setValue(20);

    ui->slider_U_Param->setValue(140);
    ui->slider_V_Param->setValue(70);

    ui->slider_R_Ext->setValue(255);
    ui->slider_G_Int->setValue(255);
    ui->slider_R_Abs->setValue(255);
    ui->slider_G_Abs->setValue(255);
    ui->slider_B_Abs->setValue(255);
    ui->slider_R_Dot->setValue(255);
    ui->slider_G_Dot->setValue(255);
    ui->slider_B_Dot->setValue(255);

    ui->slider_X_Illuminant->setValue(0);
    ui->slider_Y_Illuminant->setValue(0);
    ui->slider_Z_Illuminant->setValue(100);

    ui->slider_Absent->setValue(2);
    ui->slider_Diffusion->setValue(10);
    ui->slider_Specular->setValue(8);
    ui->slider_Power->setValue(25);
    ui->slider_Alpha->setValue(10);

    ui->comboBox_SurfaceFunctions->setCurrentIndex(2);

    isSetFirstState = false;

    paramsChanged(true);
}

void MainWindow::setConnection()
{
    this->connect(ui->action_About, SIGNAL(triggered()), this, SLOT(actionAboutTriggered()));
    this->connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));
    this->connect(ui->action_Reset, SIGNAL(triggered()), this, SLOT(reset()));

    this->connect(ui->radioButton_WireframeShading, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));
    this->connect(ui->radioButton_FongShding, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));
    this->connect(ui->radioButton_HuroShading, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));
    this->connect(ui->radioButton_SortFlatShading, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));

    this->connect(ui->slider_X_Rotate, SIGNAL(valueChanged(int)), this, SLOT(on_slider_XRotate_valueChanged(int)));
    this->connect(ui->slider_Y_Rotate, SIGNAL(valueChanged(int)), this, SLOT(on_slider_YRotate_valueChanged(int)));
    this->connect(ui->slider_Z_Rotate, SIGNAL(valueChanged(int)), this, SLOT(on_slider_ZRotate_valueChanged(int)));

    this->connect(ui->slider_R_Ext, SIGNAL(valueChanged(int)), this, SLOT(exteriorColor_Changed()));
    this->connect(ui->slider_G_Ext, SIGNAL(valueChanged(int)), this, SLOT(exteriorColor_Changed()));
    this->connect(ui->slider_B_Ext, SIGNAL(valueChanged(int)), this, SLOT(exteriorColor_Changed()));

    this->connect(ui->slider_R_Int, SIGNAL(valueChanged(int)), this, SLOT(interiorColor_Changed()));
    this->connect(ui->slider_G_Int, SIGNAL(valueChanged(int)), this, SLOT(interiorColor_Changed()));
    this->connect(ui->slider_B_Int, SIGNAL(valueChanged(int)), this, SLOT(interiorColor_Changed()));

    this->connect(ui->slider_R_Dot, SIGNAL(valueChanged(int)), this, SLOT(dotColor_Changed()));
    this->connect(ui->slider_G_Dot, SIGNAL(valueChanged(int)), this, SLOT(dotColor_Changed()));
    this->connect(ui->slider_B_Dot, SIGNAL(valueChanged(int)), this, SLOT(dotColor_Changed()));

    this->connect(ui->slider_R_Abs, SIGNAL(valueChanged(int)), this, SLOT(absentColor_Changed()));
    this->connect(ui->slider_G_Abs, SIGNAL(valueChanged(int)), this, SLOT(absentColor_Changed()));
    this->connect(ui->slider_B_Abs, SIGNAL(valueChanged(int)), this, SLOT(absentColor_Changed()));

    this->connect(ui->slider_U_Max, SIGNAL(valueChanged(int)), this, SLOT(on_slider_UMax_valueChanged(int)));
    this->connect(ui->slider_V_Max, SIGNAL(valueChanged(int)), this, SLOT(on_slider_VMax_valueChanged(int)));

    this->connect(ui->slider_U_Interval, SIGNAL(valueChanged(int)), this, SLOT(on_slider_dU_valueChanged(int)));
    this->connect(ui->slider_V_Interval, SIGNAL(valueChanged(int)), this, SLOT(on_slider_dV_valueChanged(int)));

    this->connect(ui->slider_U_Param, SIGNAL(valueChanged(int)), this, SLOT(on_slider_U_Param_valueChanged(int)));
    this->connect(ui->slider_V_Param, SIGNAL(valueChanged(int)), this, SLOT(on_slider_V_Param_valueChanged(int)));

    this->connect(ui->slider_X_Illuminant, SIGNAL(valueChanged(int)), this, SLOT(illuminantCoords_Changed()));
    this->connect(ui->slider_Y_Illuminant, SIGNAL(valueChanged(int)), this, SLOT(illuminantCoords_Changed()));
    this->connect(ui->slider_Z_Illuminant, SIGNAL(valueChanged(int)), this, SLOT(illuminantCoords_Changed()));

    this->connect(ui->slider_Absent, SIGNAL(valueChanged(int)), this, SLOT(on_slider_Absent_valueChanged(int)));
    this->connect(ui->slider_Diffusion, SIGNAL(valueChanged(int)), this, SLOT(on_slider_Diffusion_valueChanged(int)));
    this->connect(ui->slider_Specular, SIGNAL(valueChanged(int)), this, SLOT(on_slider_Specular_valueChanged(int)));
    this->connect(ui->slider_Power, SIGNAL(valueChanged(int)), this, SLOT(on_slider_Power_valueChanged(int)));

    connect(ui->comboBox_SurfaceFunctions, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_SurfaceFunctions_currentIndexChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentColor(QWidget *panel, QColor current, QColor *surfaceSide)
{
    QString panelName = panel->objectName();
    *surfaceSide = current;
    panel->setStyleSheet(QString("QWidget#%2{border: 1px solid #8f8f91;background:%1;}").arg(current.name(), panelName));
    this->paramsChanged();
}

void MainWindow::exteriorColor_Changed()
{
    int r = ui->slider_R_Ext->value();
    int g = ui->slider_G_Ext->value();
    int b = ui->slider_B_Ext->value();
    this->setValueLabel(ui->value_R_Ext, r, 3, "");
    this->setValueLabel(ui->value_G_Ext, g, 3, "");
    this->setValueLabel(ui->value_B_Ext, b, 3, "");
    QColor current(r, g, b);
    this->setCurrentColor(ui->widget_ExteriorColor, current, &(surface.exterior));
}

void MainWindow::interiorColor_Changed()
{
    int r = ui->slider_R_Int->value();
    int g = ui->slider_G_Int->value();
    int b = ui->slider_B_Int->value();
    this->setValueLabel(ui->value_R_Int, r, 3, "");
    this->setValueLabel(ui->value_G_Int, g, 3, "");
    this->setValueLabel(ui->value_B_Int, b, 3, "");
    QColor current(r, g, b);
    this->setCurrentColor(ui->widget_InteriorColor, current, &(surface.interior));
}

void MainWindow::dotColor_Changed()
{
    int r = ui->slider_R_Dot->value();
    int g = ui->slider_G_Dot->value();
    int b = ui->slider_B_Dot->value();
    this->setValueLabel(ui->value_R_Dot, r, 3, "");
    this->setValueLabel(ui->value_G_Dot, g, 3, "");
    this->setValueLabel(ui->value_B_Dot, b, 3, "");
    QColor current(r, g, b);
    this->setCurrentColor(ui->widget_IlluminantDottedColor, current, &(surface.dot));
}

void MainWindow::absentColor_Changed()
{
    int r = ui->slider_R_Abs->value();
    int g = ui->slider_G_Abs->value();
    int b = ui->slider_B_Abs->value();
    this->setValueLabel(ui->value_R_Abs, r, 3, "");
    this->setValueLabel(ui->value_G_Abs, g, 3, "");
    this->setValueLabel(ui->value_B_Abs, b, 3, "");
    QColor current(r, g, b);
    this->setCurrentColor(ui->widget_IlluminantAbsentColor, current, &(surface.absent));
}

void MainWindow::actionAboutTriggered()
{
    QString message = QString::fromLocal8Bit("О программе");
    QString title = QString::fromLocal8Bit("Лабораторная работа №4 по\nИнтерактивным графическим системам.\n\"Прозрачность и текстура\"\nВыполнил: ст. гр. МО-426 Ахтямов А.А.\nПроверил: проф. каф. ВМиК Верхотуров М.А.");
    QMessageBox aboutBox(QMessageBox::Information, message, title, QMessageBox::Ok, this);
    aboutBox.exec();
}

void MainWindow::paramsChanged(bool isCalc)
{
    if (!isSetFirstState)
    {
        surface.isPointsChanged = isCalc;
        ui->graphicsView_Surface->hide();
        ui->graphicsView_Surface->show();
    }
}

void MainWindow::shadingChanged(bool isflat)
{
    this->setValueLabel();
    ui->checkBox_Textured->setEnabled(true);
    ui->groupBox_ExteriorColor->setEnabled(true);
    ui->groupBox_InterioColor->setEnabled(true);
    QRadioButton *sndr = (QRadioButton*)this->sender();
    if (sndr == ui->radioButton_WireframeShading)
    {
        surface.type = FRAME;
        ui->checkBox_Textured->setChecked(false);
        ui->checkBox_Textured->setEnabled(false);
    }
    /*if (sndr == ui->radioButton_FlatShading)
    {
        surface.type = FLAT;
    }*/
    if (sndr == ui->radioButton_FongShding)
    {
        surface.type = FONG;
    }
    if (sndr == ui->radioButton_HuroShading)
    {
        surface.type = HURO;
    }
    if (sndr == ui->radioButton_SortFlatShading)
    {
        surface.type = FLAT;
    }
    this->paramsChanged(true);
}

void MainWindow::setValueLabel(QLabel *l, double val, int len, QString dec)
{
    QString s;
    int gap = len - s.setNum(val).length();
    for (int i = 0; i < gap; ++i)
    {
        dec += " ";
    }
    if (l)
    {
        dec += s.setNum(val);
        if (dec[0] == '(')
        {
            dec += ")";
        }
        l->setText(dec);
    }
    surface.xOld = surface.xRotate;
    surface.yOld = surface.yRotate;
    surface.zOld = surface.zRotate;
}

void MainWindow::on_slider_XRotate_valueChanged(int value)
{
    this->setValueLabel(ui->value_X_Rotate, value, 4, "(");
    surface.xRotate = value;
    this->paramsChanged(true);
}

void MainWindow::on_slider_YRotate_valueChanged(int value)
{
    this->setValueLabel(ui->value_Y_Rotate, value, 4, "(");
    surface.yRotate = value;
    this->paramsChanged(true);
}

void MainWindow::on_slider_ZRotate_valueChanged(int value)
{
    this->setValueLabel(ui->value_Z_Rotate, value, 4, "(");
    surface.zRotate = value;
    this->paramsChanged(true);
}

void MainWindow::on_slider_UMax_valueChanged(int value)
{
    this->setValueLabel(ui->value_U_Max, value, 3, "(");
    surface.maxU = value;
    surface.func->surfaceBorder()->dU = value;
    this->paramsChanged(true);
}

void MainWindow::on_slider_VMax_valueChanged(int value)
{
    this->setValueLabel(ui->value_V_Max, value, 3, "(");
    surface.maxV = value;
    surface.func->surfaceBorder()->dV = value;
    this->paramsChanged(true);
}

void MainWindow::on_slider_dU_valueChanged(int value)
{
    this->setValueLabel(ui->value_U_Interval, value, 3, "(");
    surface.dU = value;
    this->paramsChanged(true);
}

void MainWindow::on_slider_dV_valueChanged(int value)
{
    this->setValueLabel(ui->value_V_Interval, value, 3, "(");
    surface.dV = value;
    this->paramsChanged(true);
}

void MainWindow::on_slider_U_Param_valueChanged(int value)
{
    this->setValueLabel(ui->value_U_Param, value, 3, "(");
    surface.func->setParams(value, ui->slider_V_Param->value());
    this->paramsChanged(true);
}

void MainWindow::on_slider_V_Param_valueChanged(int value)
{
    this->setValueLabel(ui->value_V_Param, value, 3, "(");
    surface.func->setParams(ui->slider_U_Param->value(), value);
    this->paramsChanged(true);
}

void MainWindow::illuminantCoords_Changed()
{
    double x = ui->slider_X_Illuminant->value();
    double y = ui->slider_Y_Illuminant->value();
    double z = ui->slider_Z_Illuminant->value();

    this->setValueLabel(ui->value_X_Coord, x, 4, "(");
    this->setValueLabel(ui->value_Y_Coord, y, 4, "(");
    this->setValueLabel(ui->value_Z_Coord, z, 4, "(");

    Vector l(x, y, z);
    l.unit();
    surface.light = l;

    this->paramsChanged();
}

void MainWindow::on_slider_Absent_valueChanged(int value)
{
    surface.ka = value / 10.0;
    this->setValueLabel(ui->value_Absent, surface.ka, 3, "(");
    this->paramsChanged();
}

void MainWindow::on_slider_Diffusion_valueChanged(int value)
{
    surface.kd = value / 10.0;
    this->setValueLabel(ui->value_Diffusion, surface.kd, 3, "(");
    this->paramsChanged();
}

void MainWindow::on_slider_Specular_valueChanged(int value)
{
    surface.ks = value / 10.0;
    this->setValueLabel(ui->value_Specular, surface.ks, 3, "(");
    this->paramsChanged();
}

void MainWindow::on_slider_Power_valueChanged(int value)
{
    this->setValueLabel(ui->value_Power, value, 3, "(");
    surface.n = value;
    this->paramsChanged();
}

void MainWindow::on_slider_Alpha_valueChanged(int value)
{
    surface.alpha = value / 10.0;
    this->setValueLabel(ui->value_Alpha, surface.alpha, 3, "(");
    this->paramsChanged();
}

void MainWindow::on_pushButton_ChooseTexture_clicked()
{
    QString title = QString::fromLocal8Bit("Выберете файл изображения для текстур");
    QString tex = QFileDialog::getOpenFileName(this, title, QString(), QString("All files (*.*);; JPEG (*.jpg *.jpeg);; Bitmap (*.bmp);; PNG (*.png)"));
    if (tex == "")
    {
        this->textureChanged(tex);
    }
}

void MainWindow::on_checkBox_Textured_clicked(bool checked)
{
    if (ui->radioButton_WireframeShading->isChecked())
    {
        surface.isTextured = false;
        return;
    }

    ui->groupBox_ExteriorColor->setEnabled(!checked);
    ui->groupBox_InterioColor->setEnabled(!checked);
    surface.isTextured = checked;
    this->setValueLabel();
    this->paramsChanged(true);
}

void MainWindow::textureChanged(QString tex)
{
    surface.textureImg.load(tex);
    paramsChanged(true);
}

void MainWindow::setComboBoxFuncItems()
{
    functions["Sphere"] = new Sphere();
    functions["Torus"] = new Torus();
    functions["Hourglass"] = new Hourglass();
    functions["Trefoil"] = new Trefoil();
    functions["Seashell"] = new Seashell();
    functions["KleinBottle"] = new KleinBottle();

    ui->comboBox_SurfaceFunctions->addItem("Sphere", "Sphere");
    ui->comboBox_SurfaceFunctions->addItem("Torus", "Torus");
    ui->comboBox_SurfaceFunctions->addItem("Hourglass", "Hourglass");
    ui->comboBox_SurfaceFunctions->addItem("Trefoil", "Trefoil");
    ui->comboBox_SurfaceFunctions->addItem("Seashell", "Seashell");
    ui->comboBox_SurfaceFunctions->addItem("KleinBottle", "KleinBottle");
}

void MainWindow::on_comboBox_SurfaceFunctions_currentIndexChanged(int index)
{
    QVariant var = ui->comboBox_SurfaceFunctions->itemData(index);
    QString key = var.toString();
    surface.func = functions[key];
    surface.func->setParams(ui->slider_U_Param->value(), ui->slider_V_Param->value());

    ui->slider_U_Max->setMinimum(surface.func->surfaceBorder()->minU + 1);
    ui->slider_U_Max->setMaximum(surface.func->surfaceBorder()->maxU);
    ui->slider_V_Max->setMinimum(surface.func->surfaceBorder()->minV + 1);
    ui->slider_V_Max->setMaximum(surface.func->surfaceBorder()->maxV);

    surface.func->surfaceBorder()->dU = ui->slider_U_Max->value();
    surface.func->surfaceBorder()->dV = ui->slider_V_Max->value();

    paramsChanged(true);
}
