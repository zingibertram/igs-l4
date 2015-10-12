#include "surfacefunctionsmodel.h"

#include <Qt>
#include <QVariant>

SurfaceFunctionsModel::SurfaceFunctionsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    functions.append(new Sphere());
    functions.append(new Torus());
    functions.append(new Hourglass());
}

int SurfaceFunctionsModel::rowCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant SurfaceFunctionsModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (role == Qt::DisplayRole)
    {
        return 1;
    }
    return 1;
}
