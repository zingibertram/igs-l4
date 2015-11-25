#ifndef CSLIDER_H
#define CSLIDER_H

#include <QWidget>
#include <QString>

namespace Ui {
    class CSlider;
}

class CSlider : public QWidget
{
    Q_OBJECT

public:
    explicit CSlider(QWidget *parent = 0);
    ~CSlider();

    void setValue(int v);
    int value();
    void setMinimum(int v);
    int minimum();
    void setMaximum(int v);
    int maximum();
    void setTitle(QString s);
    QString title();
    void init(QString t, int min, int max, double d = 0);
    void setLabelWidth(int w, int lmin, int lmax, int lval);

signals:
    void valueChanged(int v);
    void minimumChanged(int v);
    void maximumChanged(int v);
    void titleChanged(QString s);

private slots:
    void on_slider_valueChanged(int v);

private:
    Ui::CSlider *ui;
    double divider;
};

#endif // CSLIDER_H
