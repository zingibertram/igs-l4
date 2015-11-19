#include "cslider.h"
#include "ui_cslider.h"

#include <QFont>
#include <QFontMetrics>
#include <QDebug>

CSlider::CSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSlider)
{
    ui->setupUi(this);

    ui->label_Min->setStyleSheet(QString("QLabel#label_Min{color: red;}"));
    ui->label_Max->setStyleSheet(QString("QLabel#label_Max{color: green; border: 1px solid black;}"));

    QFont f = font();
    QFontMetrics fm(f);

    int sliderLabelCharCount = 4;
    int titleCharCount = 3;

    int lw = fm.width(QString("0")) * sliderLabelCharCount;
    int tw = fm.width(QString("W")) * titleCharCount;

    qDebug() << tw << lw;

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

void CSlider::on_slider_valueChanged(int value)
{
    emit valueChanged(value);
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
    emit minimumChanged(v);
}

int CSlider::minimum()
{
    return ui->slider->minimum();
}

void CSlider::setMaximum(int v)
{
    ui->slider->setMaximum(v);
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

