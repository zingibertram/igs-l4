#include "colorbox.h"
#include "ui_colorbox.h"

#include <QFont>
#include <QFontMetrics>

ColorBox::ColorBox(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::ColorBox)
{
    ui->setupUi(this);

    QFont f = font();
    QFontMetrics fm(f);

    int w = fm.width(QString("W"));

    ui->label_R->setMinimumWidth(w);
    ui->label_R->setMaximumWidth(w);
    ui->label_G->setMinimumWidth(w);
    ui->label_G->setMaximumWidth(w);
    ui->label_B->setMinimumWidth(w);
    ui->label_B->setMaximumWidth(w);

    w = fm.width(QString("255")) + 4;

    ui->widget_Color->setMinimumWidth(w);
    ui->widget_Color->setMaximumWidth(w);

    setColor(0, 0, 0);
}

ColorBox::~ColorBox()
{
    delete ui;
}

void ColorBox::setColor(int r, int g, int b)
{
    disconnect(ui->slider_R, SIGNAL(valueChanged(int)), this, SLOT(on_slider_valueChanged(int)));
    disconnect(ui->slider_G, SIGNAL(valueChanged(int)), this, SLOT(on_slider_valueChanged(int)));
    disconnect(ui->slider_B, SIGNAL(valueChanged(int)), this, SLOT(on_slider_valueChanged(int)));

    ui->slider_R->setValue(r);
    ui->slider_G->setValue(g);
    ui->slider_B->setValue(b);

    connect(ui->slider_R, SIGNAL(valueChanged(int)), this, SLOT(on_slider_valueChanged(int)));
    connect(ui->slider_G, SIGNAL(valueChanged(int)), this, SLOT(on_slider_valueChanged(int)));
    connect(ui->slider_B, SIGNAL(valueChanged(int)), this, SLOT(on_slider_valueChanged(int)));

    on_slider_valueChanged(0);
}

QColor ColorBox::color()
{
    int r = ui->slider_R->value();
    int g = ui->slider_G->value();
    int b = ui->slider_B->value();

    return QColor(r, g, b);
}

void ColorBox::on_slider_valueChanged(int /* value */)
{
    QColor c = color();
    QString cs = QColor(255 - c.red(), 255 - c.green(), 255 - c.blue()).name();

    ui->widget_Color->setStyleSheet(QString("QWidget#widget_Color{border: 1px solid #8f8f91; background: %1;}").arg(c.name()));
    ui->label_R_Value->setStyleSheet(QString("QLabel#label_R_Value{color: %1;}").arg(cs));
    ui->label_G_Value->setStyleSheet(QString("QLabel#label_G_Value{color: %1;}").arg(cs));
    ui->label_B_Value->setStyleSheet(QString("QLabel#label_B_Value{color: %1;}").arg(cs));

    emit colorChanged(c);
}
