#include "cslider.h"
#include "ui_cslider.h"

#include <QFont>
#include <QFontMetrics>

CSlider::CSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSlider)
{
    ui->setupUi(this);

    ui->label_Min->setStyleSheet(QString("QLabel#label_Min{color: red;}"));
    ui->label_Max->setStyleSheet(QString("QLabel#label_Max{color: green;}"));

    QFont f = font();
    QFontMetrics fm(f);

    int sliderLabelCharCount = 4;
    int titleCharCount = 2;

    int lw = fm.width(QString("0")) * sliderLabelCharCount;
    int tw = fm.width(QString("W")) * titleCharCount;

    ui->label_Title->setMinimumWidth(tw);
    ui->label_Title->setMaximumWidth(tw);
    ui->label_Min->setMinimumWidth(lw);
    ui->label_Min->setMaximumWidth(lw);
    ui->label_Value->setMinimumWidth(lw);
    ui->label_Value->setMaximumWidth(lw);
    ui->label_Max->setMinimumWidth(lw);
    ui->label_Max->setMaximumWidth(lw);
}

CSlider::~CSlider()
{
    delete ui;
}

void CSlider::on_slider_valueChanged(int v)
{
    if (divider)
    {
        ui->label_Value->setText(QString::number((double)v / divider));
    }
    else
    {
        ui->label_Value->setNum(v);
    }
    emit valueChanged(v);
}

void CSlider::setValue(int v)
{
    ui->slider->setValue(v);
    emit valueChanged(v);
}

int CSlider::value()
{
    return ui->slider->value();
}

void CSlider::setMinimum(int v)
{
    ui->slider->setMinimum(v);
    ui->label_Min->setNum(v);
    emit minimumChanged(v);
}

int CSlider::minimum()
{
    return ui->slider->minimum();
}

void CSlider::setMaximum(int v)
{
    ui->slider->setMaximum(v);
    ui->label_Max->setNum(v);
    emit maximumChanged(v);
}

int CSlider::maximum()
{
    return ui->slider->maximum();
}

void CSlider::setTitle(QString s)
{
    ui->label_Title->setText(s);
    emit titleChanged(s);
}

QString CSlider::title()
{
    return ui->label_Title->text();
}

void CSlider::init(QString t, int min, int max, double d)
{
    setTitle(t);
    setMinimum(min);
    setMaximum(max);
    divider = d;
}
