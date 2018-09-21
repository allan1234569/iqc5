#ifndef MATERIALSERVICE_H
#define MATERIALSERVICE_H
#include "Material.h"

class MaterialService
{
public:
    MaterialService();

    Material GetById(QString MaterialId);
    QVector<Material> GetMaterials();
    QVector<Material> GetMaterials(QString subjectId, QString categoryId, QString name, QString ManufacturerName, QString countryName,int if_user_first);
    QVector<Material> GetMaterials(QString subjectId, QString categoryId, QString name, QString ManufacturerName, QString countryName, QString BatchNo, QString RegisterNo,int if_user_first);
    QVector<Material> GetMaterialsByCategoryId(QString categoryId);
    QVector<Material> GetMaterialsByTestTypeId(QString testTypeId);
    QVector<Material> GetMaterialsByManufacturerId(QString ManufacturerId);
    QString Insert(Material material);
    void Update(Material material);
    void DeleteById(QString MaterialId);
    void UpdateTestType(Material material);

};

#endif // MATERIALSERVICE_H
