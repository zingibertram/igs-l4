#include "colorbox.h"
#include "ui_colorbox.h"

ColorBox::ColorBox(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::ColorBox)
{
    ui->setupUi(this);
}

ColorBox::~ColorBox()
{
    delete ui;
}

void ColorBox::on_slider_valueChanged(int value)
{
    int r = ui->slider_R->value();
    int g = ui->slider_G->value();
    int b = ui->slider_B->value();

    QColor color(r, g, b);
    emit colorChanged(color);
}
