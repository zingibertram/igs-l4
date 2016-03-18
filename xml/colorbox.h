#ifndef COLORBOX_H
#define COLORBOX_H

#include <QGroupBox>
#include <QColor>
#include <QString>

namespace Ui {
    class ColorBox;
}

class ColorBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit ColorBox(QWidget *parent = 0);
    ~ColorBox();
    void setColor(int r, int g, int b);
    QColor color();

signals:
    void colorChanged(QColor color);

private slots:
    void on_slider_valueChanged(int value);

private:
    Ui::ColorBox *ui;

    QString contrastColor();
};

#endif // COLORBOX_H
