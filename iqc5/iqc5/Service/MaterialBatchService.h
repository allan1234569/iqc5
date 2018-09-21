#ifndef MATERIALBATCHSERVICE_H
#define MATERIALBATCHSERVICE_H
#include "MaterialBatch.h"

class MaterialBatchService
{
public:
    MaterialBatchService();

    MaterialBatch GetById(QString MaterialBatchId);
    QVector<MaterialBatch> GetMaterialBatchs(QString MaterialId, QString name);
    QVector<MaterialBatch> GetMaterialBatchs();//add by heyi

    QString Insert(MaterialBatch material);
    void Update(MaterialBatch material);
    void DeleteById(QString MaterialBatchId);
};

#endif // MATERIALBATCHSERVICE_H
