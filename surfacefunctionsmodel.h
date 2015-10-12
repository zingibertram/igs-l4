#ifndef SURFACEFUNCTIONSMODEL_H
#define SURFACEFUNCTIONSMODEL_H

#include "surfacefunction.h"

#include <QAbstractListModel>
#include <QVariant>
#include <QList>

class SurfaceFunctionsModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QList<SurfaceFunction*> functions;
public:
    explicit SurfaceFunctionsModel(QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
};

#endif // SURFACEFUNCTIONSMODEL_H
