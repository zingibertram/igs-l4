#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common/surfacefunction.h"

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

    ui->colorBox_Dot->setColor(255, 255, 255);
    ui->colorBox_Absent->setColor(255, 255, 255);
    ui->colorBox_Exterior->setColor(255, 0, 0);
    ui->colorBox_Interior->setColor(0, 255, 0);

    ui->slider_X_Illuminant->setValue(0);
    ui->slider_Y_Illuminant->setValue(0);
    ui->slider_Z_Illuminant->setValue(100);

    ui->slider_Absent->setValue(2);
    ui->slider_Diffusion->setValue(10);
    ui->slider_Specular->setValue(8);
    ui->slider_Power->setValue(25);
    ui->slider_Alpha->setValue(10);

    ui->comboBox_SurfaceFunctions->setCurrentIndex(2);

    changeChecked(ui->pushButton_Expand_ColorSelection, false);
    changeChecked(ui->pushButton_Expand_LightSource, false);
    changeChecked(ui->pushButton_Expand_SurfaceLocation);
    changeChecked(ui->pushButton_Expand_SurfaceMain);

    isSetFirstState = false;

    paramsChanged(true);
}

void MainWindow::setConnection()
{
    this->connect(ui->action_About, SIGNAL(triggered()), this, SLOT(actionAboutTriggered()));
    this->connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));
    this->connect(ui->action_Reset, SIGNAL(triggered()), this, SLOT(reset()));
    this->connect(ui->action_ExpandAll, SIGNAL(triggered()), this, SLOT(expandAll()));
    this->connect(ui->action_CollapseAll, SIGNAL(triggered()), this, SLOT(collapseAll()));

    this->connect(ui->radioButton_WireframeShading, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));
    this->connect(ui->radioButton_FongShding, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));
    this->connect(ui->radioButton_HuroShading, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));
    this->connect(ui->radioButton_SortFlatShading, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));

    this->connect(ui->slider_X_Rotate, SIGNAL(valueChanged(int)), this, SLOT(on_slider_XRotate_valueChanged(int)));
    this->connect(ui->slider_Y_Rotate, SIGNAL(valueChanged(int)), this, SLOT(on_slider_YRotate_valueChanged(int)));
    this->connect(ui->slider_Z_Rotate, SIGNAL(valueChanged(int)), this, SLOT(on_slider_ZRotate_valueChanged(int)));

    this->connect(ui->colorBox_Dot, SIGNAL(colorChanged(QColor)), this, SLOT(dotColor_Changed(QColor)));
    this->connect(ui->colorBox_Absent, SIGNAL(colorChanged(QColor)), this, SLOT(absentColor_Changed(QColor)));
    this->connect(ui->colorBox_Exterior, SIGNAL(colorChanged(QColor)), this, SLOT(exteriorColor_Changed(QColor)));
    this->connect(ui->colorBox_Interior, SIGNAL(colorChanged(QColor)), this, SLOT(interiorColor_Changed(QColor)));

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

void MainWindow::exteriorColor_Changed(QColor color)
{
    surface.exterior = color;
    paramsChanged();
}

void MainWindow::interiorColor_Changed(QColor color)
{
    surface.interior = color;
    paramsChanged();
}

void MainWindow::dotColor_Changed(QColor color)
{
    surface.dot = color;
    paramsChanged();
}

void MainWindow::absentColor_Changed(QColor color)
{
    surface.absent = color;
    paramsChanged();
}

void MainWindow::actionAboutTriggered()
{
    QString message = QString::fromLocal8Bit("� ���������");
    QString title = QString::fromLocal8Bit("������������ ������ �4 ��\n������������� ����������� ��������.\n\"������������ � ��������\"\n��������: ��. ��. ��-426 ������� �.�.\n��������: ����. ���. ���� ���������� �.�.");
    QMessageBox aboutBox(QMessageBox::Information, message, title, QMessageBox::Ok, this);
    aboutBox.exec();
}

void MainWindow::paramsChanged(bool isCalc)
{
    if (!isSetFirstState)
    {
        surface.isPointsChanged = true;
        ui->graphicsView_Surface->hide();
        ui->graphicsView_Surface->show();
    }
}

void MainWindow::shadingChanged(bool isflat)
{
    this->setValueLabel();
    ui->checkBox_Textured->setEnabled(true);
    ui->colorBox_Exterior->setEnabled(true);
    ui->colorBox_Interior->setEnabled(true);
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
    QString title = QString::fromLocal8Bit("�������� ���� ����������� ��� �������");
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

    ui->colorBox_Exterior->setEnabled(!checked);
    ui->colorBox_Interior->setEnabled(!checked);
    surface.isTextured = checked;

    if (checked)
    {
        surface.exterior = surface.interior = QColor(Qt::white);
    }
    else
    {
        surface.exterior = ui->colorBox_Exterior->color();
        surface.interior = ui->colorBox_Interior->color();
    }

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

    QList<QString> keys = functions.keys();
    for (int i = 0; i < keys.count(); ++i)
    {
        ui->comboBox_SurfaceFunctions->addItem(keys[i], keys[i]);
    }
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

void MainWindow::expandAll()
{
    changeChecked(ui->pushButton_Expand_ColorSelection);
    changeChecked(ui->pushButton_Expand_LightSource);
    changeChecked(ui->pushButton_Expand_SurfaceLocation);
    changeChecked(ui->pushButton_Expand_SurfaceMain);
}

void MainWindow::collapseAll()
{
    changeChecked(ui->pushButton_Expand_ColorSelection, false);
    changeChecked(ui->pushButton_Expand_LightSource, false);
    changeChecked(ui->pushButton_Expand_SurfaceLocation, false);
    changeChecked(ui->pushButton_Expand_SurfaceMain, false);
}

void MainWindow::changeChecked(QPushButton* pb, bool need)
{
    if (pb->isChecked() != need)
    {
        pb->click();
    }
}
