#ifndef UNITSERVICE_H
#define UNITSERVICE_H

#include "Unit.h"

class UnitService
{
public:
    UnitService();

    Unit GetById(QString UnitId);
    QVector<Unit> GetByParentId(QString ParentId);
    QVector<Unit> GetUnits(QString name);
    void Insert(Unit unit);
    void Update(Unit unit);
    void DeleteById(QString UnitId);
};

#endif // UNITSERVICE_H
