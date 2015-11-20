#include "cslider.h"
#include "ui_cslider.h"

#include <QFont>
#include <QFontMetrics>

CSlider::CSlider(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

//CSlider::~CSlider()
//{
//    delete label_Value;
//    delete label_Max;
//    delete label_Min;
//    delete label_Title;
//    delete slider;
//    delete layout;
//}

void CSlider::setupUi()
{
    if (objectName().isEmpty())
    {
        setObjectName(QStringLiteral("CSlider"));
    }
//    resize(180, 19);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);

    layout = new QHBoxLayout(this);
    layout->setObjectName(QStringLiteral("horizontalLayout"));
    layout->setContentsMargins(0, 0, 0, 0);

    label_Title = new QLabel(this);
    label_Title->setObjectName(QStringLiteral("label_Title"));

    layout->addWidget(label_Title);

    label_Min = new QLabel(this);
    label_Min->setObjectName(QStringLiteral("label_Min"));
    label_Min->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    layout->addWidget(label_Min);

    slider = new QSlider(this);
    slider->setObjectName(QStringLiteral("slider"));
    slider->setOrientation(Qt::Horizontal);

    layout->addWidget(slider);

    label_Max = new QLabel(this);
    label_Max->setObjectName(QStringLiteral("label_Max"));

    layout->addWidget(label_Max);

    label_Value = new QLabel(this);
    label_Value->setObjectName(QStringLiteral("label_Value"));
    label_Value->setAlignment(Qt::AlignCenter);

    layout->addWidget(label_Value);

    setWindowTitle(QApplication::translate("CSlider", "Form", 0));
    label_Title->setText(QApplication::translate("CSlider", "T", 0));
    label_Min->setText(QApplication::translate("CSlider", "0", 0));
    label_Max->setText(QApplication::translate("CSlider", "360", 0));
    label_Value->setText(QApplication::translate("CSlider", "0", 0));

    label_Min->setStyleSheet(QString("QLabel#label_Min{color: red;}"));
    label_Max->setStyleSheet(QString("QLabel#label_Max{color: green; border: 1px solid black;}"));

    QFont f = font();
    QFontMetrics fm(f);

    int sliderLabelCharCount = 4;
    int titleCharCount = 3;

    int lw = fm.width(QString("0")) * sliderLabelCharCount;
    int tw = fm.width(QString("W")) * titleCharCount;

    label_Title->setMinimumWidth(tw);
    label_Title->setMaximumWidth(tw);
    label_Min->setMinimumWidth(lw);
    label_Min->setMaximumWidth(lw);
    label_Value->setMinimumWidth(lw);
    label_Value->setMaximumWidth(lw);
    label_Max->setMinimumWidth(lw);
    label_Max->setMaximumWidth(lw);

    connect(slider, SIGNAL(valueChanged(int)), label_Value, SLOT(setNum(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(on_slider_valueChanged(int)));
}

void CSlider::on_slider_valueChanged(int value)
{
    emit valueChanged(value);
}

void CSlider::setValue(int v)
{
    slider->setValue(v);
    emit valueChanged(v);
}

int CSlider::value()
{
    return slider->value();
}

void CSlider::setMinimum(int v)
{
    slider->setMinimum(v);
    emit minimumChanged(v);
}

int CSlider::minimum()
{
    return slider->minimum();
}

void CSlider::setMaximum(int v)
{
    slider->setMaximum(v);
    emit maximumChanged(v);
}

int CSlider::maximum()
{
    return slider->maximum();
}

void CSlider::setTitle(QString s)
{
    label_Title->setText(s);
    emit titleChanged(s);
}

QString CSlider::title()
{
    return label_Title->text();
}

