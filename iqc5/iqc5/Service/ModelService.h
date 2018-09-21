#ifndef MODELSERVICE_H
#define MODELSERVICE_H
#include "Model.h"

class ModelService
{
public:
    ModelService();

    Model GetById(QString ModelId);
    QVector<Model> GetByBrandId(QString BrandId);
    QVector<Model> GetModels(QString name);
    QString Insert(Model model);
    void Update(Model model);
    void DeleteById(QString ModelId);
};

#endif // MODELSERVICE_H
