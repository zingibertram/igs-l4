#include "mainwindow.h"
#include "surfacefunction.h"
#include "utils.h"
#include "vector.h"

#include <QFileDialog>
#include <QScrollBar>
#include <QDebug>

#include <math.h>

MainWindow::MainWindow() :
    QObject()
{
//    ui->setupUi(this);
//    textureChanged(":/texture/resources/tex1.jpg");
//    setConnection();
//    setComboBoxFuncItems();
//    reset();

//    ui->graphicsView_Surface->setSurface(&surface);
//    ui->radioButton_WireframeShading->click();

    functions["Sphere"] = new Sphere();
    functions["Torus"] = new Torus();
    functions["Hourglass"] = new Hourglass();
    functions["Trefoil"] = new Trefoil();
    functions["Seashell"] = new Seashell();
    functions["KleinBottle"] = new KleinBottle();
    functions["ConicalSpiralModCliffordTorus"] = new ConicalSpiralModCliffordTorus();
    functions["SpiralModCliffordTorus"] = new SpiralModCliffordTorus();
    functions["CliffordTorus"] = new CliffordTorus();
    functions["HyperbolicHelicoid"] = new HyperbolicHelicoid();
    functions["Catenoid"] = new Catenoid();
    functions["Helicoid"] = new Helicoid();
    functions["Surface1"] = new Surface1();
    functions["Hyperboloid2Sheets"] = new Hyperboloid2Sheets();
    functions["Hyperboloid1Sheet"] = new Hyperboloid1Sheet();
    functions["ConicalSpiral"] = new ConicalSpiral();
    functions["Spiral"] = new Spiral();
    functions["Surface2"] = new Surface2();
    functions["CrossCup"] = new CrossCup();
    functions["AstroidalEllipsoid"] = new AstroidalEllipsoid();
    functions["EightSurface"] = new EightSurface();
    functions["Surface3"] = new Surface3();
    functions["Surface4"] = new Surface4();

    surface.textureImg.load(":/textures/resources/tex1.jpg");
}

MainWindow::~MainWindow()
{
}

void MainWindow::paramsChanged(bool isCalc)
{
    surface.isPointsChanged = isCalc;
//    ui->graphicsView_Surface->hide();
//    ui->graphicsView_Surface->show();
    qDebug() << "Params changed";
}

QStringList MainWindow::getSurfaceFunctions()
{
    QStringList res;
    QList<QString> keys = functions.keys();
    for (int i = 0; i < keys.count(); ++i)
    {
        res.append(keys[i]);
    }
    return res;
}

void MainWindow::setPaintViewWidth(int value)
{
    width = value;
    paramsChanged(true);
}

void MainWindow::setPaintViewHeight(int value)
{
    height = value;
    paramsChanged(true);
}

int MainWindow::getRangeMinU()
{
    return surface.func
            ? surface.func->surfaceBorder()->minU
            : 0;
}

int MainWindow::getRangeMaxU()
{
    return surface.func
            ? surface.func->surfaceBorder()->maxU
            : 360;
}

int MainWindow::getRangeMinV()
{
    return surface.func
            ? surface.func->surfaceBorder()->minV
            : 0;
}

int MainWindow::getRangeMaxV()
{
    return surface.func
            ? surface.func->surfaceBorder()->maxV
            : 360;
}


void MainWindow::setSurfaceFunction(const QString &s)
{
    surface.func = functions[s];
    paramsChanged(true);
    emit rangeChanged();
}

void MainWindow::setSurfaceShading(Sh sh)
{
    surface.type = (Shading)sh;
    paramsChanged(true);
}

void MainWindow::setTextured(bool t)
{
    surface.isTextured = t;
    paramsChanged(true);
}

void MainWindow::setTexturePath(const QString &s)
{
    // не загружается текстура в png
    QString path(s); // s == file:///*
    path.remove(0, 8);

    surface.textureImg.load(path);
    paramsChanged(true);
}

void MainWindow::setMaxU(int value)
{
    if (!surface.func)
    {
        return;
    }

    surface.func->surfaceBorder()->maxU = value;
    surface.maxU = value;
    paramsChanged(true);

    qDebug() << "max u changed" << value;
}

void MainWindow::setMaxV(int value)
{
    if (!surface.func)
    {
        return;
    }

    surface.func->surfaceBorder()->maxV = value;
    surface.maxV = value;
    paramsChanged(true);
}

void MainWindow::setDU(int value)
{
    surface.dU = value;
    paramsChanged(true);
}

void MainWindow::setDV(int value)
{
    surface.dV = value;
    paramsChanged(true);
}

void MainWindow::setParam_R(int value)
{
    if (!surface.func)
    {
        return;
    }

    surface.func->setFirstParam(value);
    paramsChanged(true);
}

void MainWindow::setParam_r(int value)
{
    qDebug() << (surface.func == 0);
    if (!surface.func)
    {
        return;
    }

    surface.func->setSecondParam(value);
    paramsChanged(true);
}

void MainWindow::setRotX(int value)
{
    setOldRotate();
    surface.xRotate = value;
    paramsChanged(true);
    setOldRotate();
}

void MainWindow::setRotY(int value)
{
    setOldRotate();
    surface.yRotate = value;
    paramsChanged(true);
    setOldRotate();
}

void MainWindow::setRotZ(int value)
{
    setOldRotate();
    surface.zRotate = value;
    paramsChanged(true);
    setOldRotate();
}

void MainWindow::setLight_ka(double value)
{
    surface.ka = value;
    paramsChanged();
}

void MainWindow::setLight_kd(double value)
{
    surface.kd = value;
    paramsChanged();
}

void MainWindow::setLight_ks(double value)
{
    surface.ks = value;
    paramsChanged();
}

void MainWindow::setLight_n(int value)
{
    surface.n = value;
    paramsChanged();
}

void MainWindow::setLight_alpha(double value)
{
    surface.alpha = value;
    paramsChanged();
}

void MainWindow::setLightX(int value)
{
    surface.light.setX(value);
    paramsChanged();
}

void MainWindow::setLightY(int value)
{
    surface.light.setY(value);
    paramsChanged();
}

void MainWindow::setLightZ(int value)
{
    surface.light.setZ(value);
    paramsChanged();
}


void MainWindow::setDottedColor(const QString &s)
{
    surface.dot = QColor(s);
    paramsChanged();
}

void MainWindow::setAbsentedColor(const QString &s)
{
    surface.absent = QColor(s);
    paramsChanged();
}

void MainWindow::setExteriorColor(const QString &s)
{
    surface.exterior = QColor(s);
    paramsChanged();
}

void MainWindow::setInteriorColor(const QString &s)
{
    surface.interior = QColor(s);
    paramsChanged();
}

void MainWindow::setOldRotate()
{
    surface.xOld = surface.xRotate;
    surface.yOld = surface.yRotate;
    surface.zOld = surface.zRotate;
}

//void MainWindow::setConnection()
//{
//    this->connect(ui->action_About, SIGNAL(triggered()), this, SLOT(actionAboutTriggered()));
//    this->connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));
//    this->connect(ui->action_Reset, SIGNAL(triggered()), this, SLOT(reset()));
//    this->connect(ui->action_ExpandAll, SIGNAL(triggered()), this, SLOT(expandAll()));
//    this->connect(ui->action_CollapseAll, SIGNAL(triggered()), this, SLOT(collapseAll()));

//    this->connect(ui->radioButton_WireframeShading, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));
//    this->connect(ui->radioButton_FongShding, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));
//    this->connect(ui->radioButton_HuroShading, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));
//    this->connect(ui->radioButton_SortFlatShading, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));

//    this->connect(ui->slider_X_Rotate, SIGNAL(valueChanged(int)), this, SLOT(on_slider_XRotate_valueChanged(int)));
//    this->connect(ui->slider_Y_Rotate, SIGNAL(valueChanged(int)), this, SLOT(on_slider_YRotate_valueChanged(int)));
//    this->connect(ui->slider_Z_Rotate, SIGNAL(valueChanged(int)), this, SLOT(on_slider_ZRotate_valueChanged(int)));

//    this->connect(ui->slider_R_Ext, SIGNAL(valueChanged(int)), this, SLOT(exteriorColor_Changed()));
//    this->connect(ui->slider_G_Ext, SIGNAL(valueChanged(int)), this, SLOT(exteriorColor_Changed()));
//    this->connect(ui->slider_B_Ext, SIGNAL(valueChanged(int)), this, SLOT(exteriorColor_Changed()));

//    this->connect(ui->slider_R_Int, SIGNAL(valueChanged(int)), this, SLOT(interiorColor_Changed()));
//    this->connect(ui->slider_G_Int, SIGNAL(valueChanged(int)), this, SLOT(interiorColor_Changed()));
//    this->connect(ui->slider_B_Int, SIGNAL(valueChanged(int)), this, SLOT(interiorColor_Changed()));

//    this->connect(ui->slider_R_Dot, SIGNAL(valueChanged(int)), this, SLOT(dotColor_Changed()));
//    this->connect(ui->slider_G_Dot, SIGNAL(valueChanged(int)), this, SLOT(dotColor_Changed()));
//    this->connect(ui->slider_B_Dot, SIGNAL(valueChanged(int)), this, SLOT(dotColor_Changed()));

//    this->connect(ui->slider_R_Abs, SIGNAL(valueChanged(int)), this, SLOT(absentColor_Changed()));
//    this->connect(ui->slider_G_Abs, SIGNAL(valueChanged(int)), this, SLOT(absentColor_Changed()));
//    this->connect(ui->slider_B_Abs, SIGNAL(valueChanged(int)), this, SLOT(absentColor_Changed()));

//    this->connect(ui->slider_U_Max, SIGNAL(valueChanged(int)), this, SLOT(on_slider_UMax_valueChanged(int)));
//    this->connect(ui->slider_V_Max, SIGNAL(valueChanged(int)), this, SLOT(on_slider_VMax_valueChanged(int)));

//    this->connect(ui->slider_U_Interval, SIGNAL(valueChanged(int)), this, SLOT(on_slider_dU_valueChanged(int)));
//    this->connect(ui->slider_V_Interval, SIGNAL(valueChanged(int)), this, SLOT(on_slider_dV_valueChanged(int)));

//    this->connect(ui->slider_U_Param, SIGNAL(valueChanged(int)), this, SLOT(on_slider_U_Param_valueChanged(int)));
//    this->connect(ui->slider_V_Param, SIGNAL(valueChanged(int)), this, SLOT(on_slider_V_Param_valueChanged(int)));

//    this->connect(ui->slider_X_Illuminant, SIGNAL(valueChanged(int)), this, SLOT(illuminantCoords_Changed()));
//    this->connect(ui->slider_Y_Illuminant, SIGNAL(valueChanged(int)), this, SLOT(illuminantCoords_Changed()));
//    this->connect(ui->slider_Z_Illuminant, SIGNAL(valueChanged(int)), this, SLOT(illuminantCoords_Changed()));

//    this->connect(ui->slider_Absent, SIGNAL(valueChanged(int)), this, SLOT(on_slider_Absent_valueChanged(int)));
//    this->connect(ui->slider_Diffusion, SIGNAL(valueChanged(int)), this, SLOT(on_slider_Diffusion_valueChanged(int)));
//    this->connect(ui->slider_Specular, SIGNAL(valueChanged(int)), this, SLOT(on_slider_Specular_valueChanged(int)));
//    this->connect(ui->slider_Power, SIGNAL(valueChanged(int)), this, SLOT(on_slider_Power_valueChanged(int)));

//    connect(ui->comboBox_SurfaceFunctions, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_SurfaceFunctions_currentIndexChanged(int)));
//}

//void MainWindow::shadingChanged(bool isflat)
//{
//    this->setValueLabel();
//    ui->checkBox_Textured->setEnabled(true);
//    ui->groupBox_ExteriorColor->setEnabled(true);
//    ui->groupBox_InterioColor->setEnabled(true);
//    QRadioButton *sndr = (QRadioButton*)this->sender();
//    if (sndr == ui->radioButton_WireframeShading)
//    {
//        surface.type = FRAME;
//        ui->checkBox_Textured->setChecked(false);
//        ui->checkBox_Textured->setEnabled(false);
//    }
//    /*if (sndr == ui->radioButton_FlatShading)
//    {
//        surface.type = FLAT;
//    }*/
//    if (sndr == ui->radioButton_FongShding)
//    {
//        surface.type = FONG;
//    }
//    if (sndr == ui->radioButton_HuroShading)
//    {
//        surface.type = HURO;
//    }
//    if (sndr == ui->radioButton_SortFlatShading)
//    {
//        surface.type = FLAT;
//    }
//    this->paramsChanged(true);
//}

//void MainWindow::setValueLabel(QLabel *l, double val, int len, QString dec)
//{
//    QString s;
//    int gap = len - s.setNum(val).length();
//    for (int i = 0; i < gap; ++i)
//    {
//        dec += " ";
//    }
//    if (l)
//    {
//        dec += s.setNum(val);
//        if (dec[0] == '(')
//        {
//            dec += ")";
//        }
//        l->setText(dec);
//    }
//    surface.xOld = surface.xRotate;
//    surface.yOld = surface.yRotate;
//    surface.zOld = surface.zRotate;
//}

//void MainWindow::on_slider_XRotate_valueChanged(int value)
//{
//    this->setValueLabel(ui->value_X_Rotate, value, 4, "(");
//    surface.xRotate = value;
//    this->paramsChanged(true);
//}

//void MainWindow::on_slider_YRotate_valueChanged(int value)
//{
//    this->setValueLabel(ui->value_Y_Rotate, value, 4, "(");
//    surface.yRotate = value;
//    this->paramsChanged(true);
//}

//void MainWindow::on_slider_ZRotate_valueChanged(int value)
//{
//    this->setValueLabel(ui->value_Z_Rotate, value, 4, "(");
//    surface.zRotate = value;
//    this->paramsChanged(true);
//}

//void MainWindow::on_slider_UMax_valueChanged(int value)
//{
//    this->setValueLabel(ui->value_U_Max, value, 3, "(");
//    surface.maxU = value;
//    surface.func->surfaceBorder()->dU = value;
//    this->paramsChanged(true);
//}

//void MainWindow::on_slider_VMax_valueChanged(int value)
//{
//    this->setValueLabel(ui->value_V_Max, value, 3, "(");
//    surface.maxV = value;
//    surface.func->surfaceBorder()->dV = value;
//    this->paramsChanged(true);
//}

//void MainWindow::on_slider_dU_valueChanged(int value)
//{
//    this->setValueLabel(ui->value_U_Interval, value, 3, "(");
//    surface.dU = value;
//    this->paramsChanged(true);
//}

//void MainWindow::on_slider_dV_valueChanged(int value)
//{
//    this->setValueLabel(ui->value_V_Interval, value, 3, "(");
//    surface.dV = value;
//    this->paramsChanged(true);
//}

//void MainWindow::on_slider_U_Param_valueChanged(int value)
//{
//    this->setValueLabel(ui->value_U_Param, value, 3, "(");
//    surface.func->setParams(value, ui->slider_V_Param->value());
//    this->paramsChanged(true);
//}

//void MainWindow::on_slider_V_Param_valueChanged(int value)
//{
//    this->setValueLabel(ui->value_V_Param, value, 3, "(");
//    surface.func->setParams(ui->slider_U_Param->value(), value);
//    this->paramsChanged(true);
//}

//void MainWindow::illuminantCoords_Changed()
//{
//    double x = ui->slider_X_Illuminant->value();
//    double y = ui->slider_Y_Illuminant->value();
//    double z = ui->slider_Z_Illuminant->value();

//    this->setValueLabel(ui->value_X_Coord, x, 4, "(");
//    this->setValueLabel(ui->value_Y_Coord, y, 4, "(");
//    this->setValueLabel(ui->value_Z_Coord, z, 4, "(");

//    Vector l(x, y, z);
//    l.unit();
//    surface.light = l;

//    this->paramsChanged();
//}

//void MainWindow::on_slider_Absent_valueChanged(int value)
//{
//    surface.ka = value / 10.0;
//    this->setValueLabel(ui->value_Absent, surface.ka, 3, "(");
//    this->paramsChanged();
//}

//void MainWindow::on_slider_Diffusion_valueChanged(int value)
//{
//    surface.kd = value / 10.0;
//    this->setValueLabel(ui->value_Diffusion, surface.kd, 3, "(");
//    this->paramsChanged();
//}

//void MainWindow::on_slider_Specular_valueChanged(int value)
//{
//    surface.ks = value / 10.0;
//    this->setValueLabel(ui->value_Specular, surface.ks, 3, "(");
//    this->paramsChanged();
//}

//void MainWindow::on_slider_Power_valueChanged(int value)
//{
//    this->setValueLabel(ui->value_Power, value, 3, "(");
//    surface.n = value;
//    this->paramsChanged();
//}

//void MainWindow::on_slider_Alpha_valueChanged(int value)
//{
//    surface.alpha = value / 10.0;
//    this->setValueLabel(ui->value_Alpha, surface.alpha, 3, "(");
//    this->paramsChanged();
//}

//void MainWindow::on_pushButton_ChooseTexture_clicked()
//{
//    QString title = QString::fromLocal8Bit("Выберете файл изображения для текстур");
//    QString tex = QFileDialog::getOpenFileName(this, title, QString(), QString("All files (*.*);; JPEG (*.jpg *.jpeg);; Bitmap (*.bmp);; PNG (*.png)"));
//    if (tex == "")
//    {
//        this->textureChanged(tex);
//    }
//}

//void MainWindow::on_checkBox_Textured_clicked(bool checked)
//{
//    if (ui->radioButton_WireframeShading->isChecked())
//    {
//        surface.isTextured = false;
//        return;
//    }

//    ui->groupBox_ExteriorColor->setEnabled(!checked);
//    ui->groupBox_InterioColor->setEnabled(!checked);
//    surface.isTextured = checked;

//    if (checked)
//    {
//        surface.exterior = surface.interior = QColor(Qt::white);
//    }
//    else
//    {
//        int r = ui->slider_R_Ext->value();
//        int g = ui->slider_G_Ext->value();
//        int b = ui->slider_B_Ext->value();
//        surface.exterior = QColor(r, g, b);

//        r = ui->slider_R_Int->value();
//        g = ui->slider_G_Int->value();
//        b = ui->slider_B_Int->value();
//        surface.interior = QColor(r, g, b);
//    }

//    this->setValueLabel();
//    this->paramsChanged(true);
//}

//void MainWindow::textureChanged(QString tex)
//{
//    surface.textureImg.load(tex);
//    paramsChanged(true);
//}
