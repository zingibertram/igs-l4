#include "triangle.h"

#include <QDebug>

int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

void debugColor(QColor c, QString s)
{
    qDebug() << s << c.red() << ' ' << c.green() << ' ' << c.blue();
}

Triangle::Triangle()
{
    z = 0;
}

bool operator <(Triangle t1, Triangle t2)
{
    return t1.z < t2.z;
}
