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
    Q_PROPERTY(QString title MEMBER _title)

public:
    explicit ColorBox(QWidget *parent = 0);
    ~ColorBox();

signals:
    void colorChanged(QColor color);

private slots:
    void on_slider_valueChanged(int value);

private:
    Ui::ColorBox *ui;
    QString _title;
};

#endif // COLORBOX_H
