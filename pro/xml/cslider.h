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
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

public:
    explicit CSlider(QWidget *parent = 0);
    ~CSlider();

signals:
    void valueChanged(int v);
    void minimumChanged(int v);
    void maximumChanged(int v);
    void titleChanged(QString s);

private slots:
    void on_slider_valueChanged(int v);

private:
    Ui::CSlider *ui;

    void setValue(int v);
    int value();
    void setMinimum(int v);
    int minimum();
    void setMaximum(int v);
    int maximum();
    void setTitle(QString s);
    QString title();
};

#endif // CSLIDER_H
