#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common/surfacefunction.h"

#include <QFileDialog>
#include <QScrollBar>
#include <QStringList>
#include <QFont>
#include <QFontMetrics>
#include <QToolButton>
#include <QIcon>
#include <qdebug.h>

#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->menuBar->setVisible(false);

    textureChanged(":/texture/resources/tex1.jpg");
    setConnection();
    setComboBoxFuncItems();
    setSlidersRange();
    reset();

    ui->graphicsView_Surface->setSurface(&surface);
    ui->radioButton_WireframeShading->click();

    paramsChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setConnection()
{
    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(actionAboutTriggered()));
    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->action_Reset, SIGNAL(triggered()), this, SLOT(reset()));
    connect(ui->action_ExpandAll, SIGNAL(triggered()), this, SLOT(expandAll()));
    connect(ui->action_CollapseAll, SIGNAL(triggered()), this, SLOT(collapseAll()));

    connect(ui->comboBox_SurfaceFunctions, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_SurfaceFunctions_currentIndexChanged(int)));

    connect(ui->radioButton_WireframeShading, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));
    connect(ui->radioButton_FongShding, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));
    connect(ui->radioButton_HuroShading, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));
    connect(ui->radioButton_SortFlatShading, SIGNAL(clicked(bool)), this, SLOT(shadingChanged(bool)));

    connect(ui->slider_U_Max, SIGNAL(valueChanged(int)), this, SLOT(on_slider_UMax_valueChanged(int)));
    connect(ui->slider_V_Max, SIGNAL(valueChanged(int)), this, SLOT(on_slider_VMax_valueChanged(int)));
    connect(ui->slider_U_Interval, SIGNAL(valueChanged(int)), this, SLOT(on_slider_dU_valueChanged(int)));
    connect(ui->slider_V_Interval, SIGNAL(valueChanged(int)), this, SLOT(on_slider_dV_valueChanged(int)));
    connect(ui->slider_U_Param, SIGNAL(valueChanged(int)), this, SLOT(on_slider_U_Param_valueChanged(int)));
    connect(ui->slider_V_Param, SIGNAL(valueChanged(int)), this, SLOT(on_slider_V_Param_valueChanged(int)));

    connect(ui->slider_X_Rotate, SIGNAL(valueChanged(int)), this, SLOT(on_X_Rotate_Changed(int)));
    connect(ui->slider_Y_Rotate, SIGNAL(valueChanged(int)), this, SLOT(on_Y_Rotate_Changed(int)));
    connect(ui->slider_Z_Rotate, SIGNAL(valueChanged(int)), this, SLOT(on_Z_Rotate_Changed(int)));

    connect(ui->slider_Absent, SIGNAL(valueChanged(int)), this, SLOT(on_slider_Absent_valueChanged(int)));
    connect(ui->slider_Diffusion, SIGNAL(valueChanged(int)), this, SLOT(on_slider_Diffusion_valueChanged(int)));
    connect(ui->slider_Specular, SIGNAL(valueChanged(int)), this, SLOT(on_slider_Specular_valueChanged(int)));
    connect(ui->slider_Power, SIGNAL(valueChanged(int)), this, SLOT(on_slider_Power_valueChanged(int)));
    connect(ui->slider_Alpha, SIGNAL(valueChanged(int)), this, SLOT(on_slider_Alpha_valueChanged(int)));

    connect(ui->slider_X_Illuminant, SIGNAL(valueChanged(int)), this, SLOT(illuminantCoords_Changed()));
    connect(ui->slider_Y_Illuminant, SIGNAL(valueChanged(int)), this, SLOT(illuminantCoords_Changed()));
    connect(ui->slider_Z_Illuminant, SIGNAL(valueChanged(int)), this, SLOT(illuminantCoords_Changed()));

    connect(ui->colorBox_Dot, SIGNAL(colorChanged(QColor)), this, SLOT(dotColor_Changed(QColor)));
    connect(ui->colorBox_Absent, SIGNAL(colorChanged(QColor)), this, SLOT(absentColor_Changed(QColor)));
    connect(ui->colorBox_Exterior, SIGNAL(colorChanged(QColor)), this, SLOT(exteriorColor_Changed(QColor)));
    connect(ui->colorBox_Interior, SIGNAL(colorChanged(QColor)), this, SLOT(interiorColor_Changed(QColor)));

    connect(ui->pushButton_Expand_ColorSelection, SIGNAL(clicked(bool)), this, SLOT(on_expandBtn_Clicked(bool)));
    connect(ui->pushButton_Expand_LightSource, SIGNAL(clicked(bool)), this, SLOT(on_expandBtn_Clicked(bool)));
    connect(ui->pushButton_Expand_SurfaceLocation, SIGNAL(clicked(bool)), this, SLOT(on_expandBtn_Clicked(bool)));
    connect(ui->pushButton_Expand_SurfaceMain, SIGNAL(clicked(bool)), this, SLOT(on_expandBtn_Clicked(bool)));

    connect(ui->showMainMenu_act, SIGNAL(triggered(bool)), ui->menuBar, SLOT(setVisible(bool)));
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

void MainWindow::setSlidersRange()
{
    QStringList titles;

    SurfaceBorder* border = surface.func->surfaceBorder();

    ui->slider_U_Max->init("mU", border->minU, border->maxU);
    ui->slider_V_Max->init("mV", border->minV, border->maxV);
    ui->slider_U_Interval->init("dU", 1, 50);
    ui->slider_V_Interval->init("dV", 1, 50);
    ui->slider_U_Param->init("RU", 1, 200);
    ui->slider_V_Param->init("rV", 1, 200);

    titles.clear();
    titles << "mU" << "mV" << "dU" << "dV" << "RU" << "rV";
    int w = calcSliderTitleWidth(titles);
    ui->slider_U_Max->setLabelWidth(w, 1, 4, 4);
    ui->slider_V_Max->setLabelWidth(w, 1, 4, 4);
    ui->slider_U_Interval->setLabelWidth(w, 1, 4, 4);
    ui->slider_V_Interval->setLabelWidth(w, 1, 4, 4);
    ui->slider_U_Param->setLabelWidth(w, 1, 4, 4);
    ui->slider_V_Param->setLabelWidth(w, 1, 4, 4);;

    ui->slider_X_Rotate->init("OX", -180, 180);
    ui->slider_Y_Rotate->init("OY", -180, 180);
    ui->slider_Z_Rotate->init("OZ", -180, 180);

    titles.clear();
    titles << "OX" << "OY" << "OZ";
    w = calcSliderTitleWidth(titles);
    ui->slider_X_Rotate->setLabelWidth(w, 4, 3, 4);
    ui->slider_Y_Rotate->setLabelWidth(w, 4, 3, 4);
    ui->slider_Z_Rotate->setLabelWidth(w, 4, 3, 4);

    ui->slider_Absent->init("ka", 0, 10, 10);
    ui->slider_Diffusion->init("kd", 0, 10, 10);
    ui->slider_Specular->init("ks", 0, 10, 10);
    ui->slider_Power->init("n", 0, 127);
    ui->slider_Alpha->init(QString(QChar(0xb1, 0x03)), 0, 10, 10);

    titles.clear();
    titles << "ka" << "kd" << "ks" << "n" << QString(QChar(0xb1, 0x03));
    w = calcSliderTitleWidth(titles);
    ui->slider_Absent->setLabelWidth(w, 1, 1, 3);
    ui->slider_Diffusion->setLabelWidth(w, 1, 1, 3);
    ui->slider_Specular->setLabelWidth(w, 1, 1, 3);
    ui->slider_Power->setLabelWidth(w, 1, 3, 3);
    ui->slider_Alpha->setLabelWidth(w, 1, 1, 3);

    ui->slider_X_Illuminant->init("X", -500, 500);
    ui->slider_Y_Illuminant->init("Y", -500, 500);
    ui->slider_Z_Illuminant->init("Z", -500, 500);

    titles.clear();
    titles << "X" << "Y" << "Z";
    w = calcSliderTitleWidth(titles);
    ui->slider_X_Illuminant->setLabelWidth(w, 4, 3, 4);
    ui->slider_Y_Illuminant->setLabelWidth(w, 4, 3, 4);
    ui->slider_Z_Illuminant->setLabelWidth(w, 4, 3, 4);
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

    changeChecked(ui->pushButton_Expand_ColorSelection, false);
    changeChecked(ui->pushButton_Expand_LightSource, false);
    changeChecked(ui->pushButton_Expand_SurfaceLocation);
    changeChecked(ui->pushButton_Expand_SurfaceMain);

    ui->comboBox_SurfaceFunctions->setCurrentIndex(14);

    ui->slider_U_Max->setValue(180);
    ui->slider_V_Max->setValue(180);
    ui->slider_U_Interval->setValue(20);
    ui->slider_V_Interval->setValue(20);
    ui->slider_U_Param->setValue(140);
    ui->slider_V_Param->setValue(70);

    ui->slider_X_Rotate->setValue(90);
    ui->slider_Y_Rotate->setValue(60);
    ui->slider_Z_Rotate->setValue(30);

    ui->slider_Absent->setValue(2);
    ui->slider_Diffusion->setValue(10);
    ui->slider_Specular->setValue(8);
    ui->slider_Power->setValue(25);
    ui->slider_Alpha->setValue(10);

    ui->slider_X_Illuminant->setValue(0);
    ui->slider_Y_Illuminant->setValue(0);
    ui->slider_Z_Illuminant->setValue(100);

    ui->colorBox_Dot->setColor(255, 255, 255);
    ui->colorBox_Absent->setColor(255, 255, 255);
    ui->colorBox_Exterior->setColor(255, 0, 0);
    ui->colorBox_Interior->setColor(0, 255, 0);

    isSetFirstState = false;

    paramsChanged();
}

void MainWindow::paramsChanged()
{
    ui->graphicsView_Surface->hide();
    ui->graphicsView_Surface->show();
}

void MainWindow::actionAboutTriggered()
{
    QString message = QString::fromLocal8Bit("О программе");
    QString title = QString::fromLocal8Bit("Лабораторная работа №4 по\nИнтерактивным графическим системам.\n\"Прозрачность и текстура\"\nВыполнил: ст. гр. МО-426 Ахтямов А.А.\nПроверил: проф. каф. ВМиК Верхотуров М.А.");
    QMessageBox aboutBox(QMessageBox::Information, message, title, QMessageBox::Ok, this);
    aboutBox.exec();
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

void MainWindow::changeChecked(QToolButton* pb, bool need)
{
    if (pb->isChecked() != need)
    {
        pb->click();
    }
}

void MainWindow::on_comboBox_SurfaceFunctions_currentIndexChanged(int index)
{
    QVariant var = ui->comboBox_SurfaceFunctions->itemData(index);
    QString key = var.toString();
    surface.func = functions[key];

    ui->slider_U_Max->setMinimum(surface.func->surfaceBorder()->minU + 1);
    ui->slider_U_Max->setMaximum(surface.func->surfaceBorder()->maxU);
    ui->slider_V_Max->setMinimum(surface.func->surfaceBorder()->minV + 1);
    ui->slider_V_Max->setMaximum(surface.func->surfaceBorder()->maxV);

    surface.func->surfaceBorder()->dU = ui->slider_U_Max->value();
    surface.func->surfaceBorder()->dV = ui->slider_V_Max->value();
    surface.func->setParams(ui->slider_U_Param->value(), ui->slider_V_Param->value());

    paramsChanged();
}

void MainWindow::shadingChanged(bool /* isflat */)
{
    QRadioButton *sndr = (QRadioButton*)sender();
    if (sndr == ui->radioButton_WireframeShading)
    {
        surface.type = FRAME;
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
    paramsChanged();
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

    paramsChanged();
}

void MainWindow::on_pushButton_ChooseTexture_clicked()
{
    QString title = QString::fromLocal8Bit("Выберете файл изображения для текстур");
    QString tex = QFileDialog::getOpenFileName(this, title, QString(), QString("All files (*.*);; JPEG (*.jpg *.jpeg);; Bitmap (*.bmp);; PNG (*.png)"));
    if (tex != "")
    {
        textureChanged(tex);
    }
}

void MainWindow::textureChanged(QString tex)
{
    surface.textureImg.load(tex);
    paramsChanged();
}

void MainWindow::on_slider_UMax_valueChanged(int value)
{
    surface.maxU = value;
    surface.func->surfaceBorder()->dU = value;
    paramsChanged();
}

void MainWindow::on_slider_VMax_valueChanged(int value)
{
    surface.maxV = value;
    surface.func->surfaceBorder()->dV = value;
    paramsChanged();
}

void MainWindow::on_slider_dU_valueChanged(int value)
{
    surface.dU = value;
    paramsChanged();
}

void MainWindow::on_slider_dV_valueChanged(int value)
{
    surface.dV = value;
    paramsChanged();
}

void MainWindow::on_slider_U_Param_valueChanged(int value)
{
    surface.func->setParams(value, ui->slider_V_Param->value());
    paramsChanged();
}

void MainWindow::on_slider_V_Param_valueChanged(int value)
{
    surface.func->setParams(ui->slider_U_Param->value(), value);
    paramsChanged();
}

void MainWindow::on_X_Rotate_Changed(int value)
{
    surface.xRotate = value;
    paramsChanged();
}

void MainWindow::on_Y_Rotate_Changed(int value)
{
    surface.yRotate = value;
    paramsChanged();
}

void MainWindow::on_Z_Rotate_Changed(int value)
{
    surface.zRotate = value;
    paramsChanged();
}

void MainWindow::on_slider_Absent_valueChanged(int value)
{
    surface.ka = value / 10.0;
    paramsChanged();
}

void MainWindow::on_slider_Diffusion_valueChanged(int value)
{
    surface.kd = value / 10.0;
    paramsChanged();
}

void MainWindow::on_slider_Specular_valueChanged(int value)
{
    surface.ks = value / 10.0;
    paramsChanged();
}

void MainWindow::on_slider_Power_valueChanged(int value)
{
    surface.n = value;
    paramsChanged();
}

void MainWindow::on_slider_Alpha_valueChanged(int value)
{
    surface.alpha = value / 10.0;
    paramsChanged();
}

void MainWindow::illuminantCoords_Changed()
{
    double x = ui->slider_X_Illuminant->value();
    double y = ui->slider_Y_Illuminant->value();
    double z = ui->slider_Z_Illuminant->value();

    Vector l(x, y, z);
    l.unit();
    surface.light = l;

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

int MainWindow::calcSliderTitleWidth(QStringList titles)
{
    int width = 0;

    QFont f = ui->centralWidget->font();
    QFontMetrics fm(f);

    for (int i = 0; i < titles.count(); ++i)
    {
        int w = fm.width(titles[i]);
        if (w > width)
        {
            width = w;
        }
    }
    return width;
}

void MainWindow::on_expandBtn_Clicked(bool checked)
{
    QToolButton *tbtn = (QToolButton*)sender();
    QIcon icon;
    if (checked)
    {
        icon = QIcon(":/breeze_classic/actions/16/go-up.svg");
    }
    else
    {
        icon = QIcon(":/breeze_classic/actions/16/go-down.svg");
    }
    tbtn->setIcon(icon);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);
    if (event->key() == Qt::Key_Alt)
    {
        ui->showMainMenu_act->trigger();
        // ui->menuBar->setVisible(!ui->menuBar->isVisible());
    }
}
