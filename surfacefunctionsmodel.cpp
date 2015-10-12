#include "surfacefunctionsmodel.h"

#include <Qt>
#include <QVariant>
#include <QDebug>

SurfaceFunctionsModel::SurfaceFunctionsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    functions.append(new Sphere());
    functions.append(new Torus());
    functions.append(new Hourglass());
}

int SurfaceFunctionsModel::rowCount(const QModelIndex &parent) const
{
    return functions.count();
}

QVariant SurfaceFunctionsModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    qDebug() << row << role << functions.count();
    if (role == Qt::DisplayRole)
    {
        return functions[row]->name();
    }
    return 0;
}

//QVariant SurfaceFunctionsModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    if (role == Qt::DisplayRole)
//    {
//        return 2;
//    }
//    return 2;
//}
