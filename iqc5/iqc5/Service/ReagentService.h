#ifndef REAGENTSERVICE_H
#define REAGENTSERVICE_H
#include "Reagent.h"

class ReagentService
{
public:
    ReagentService();

    Reagent GetById(QString ReagentId);
    QVector<Reagent> GetReagents();
    QVector<Reagent> GetReagents(QString subjectId, QString categoryId, QString name, QString ManufacturerName, QString countryName,int if_user_first);
    QVector<Reagent> GetReagents(QString subjectId, QString categoryId, QString name, QString ManufacturerName, QString countryName, QString BatchNo, QString RegisterNo,int if_user_first);
    QVector<Reagent> GetReagentsByCategoryId(QString categoryId);
    QVector<Reagent> GetReagentsByTestTypeId(QString testTypeId);
    QVector<Reagent> GetReagentsByManufacturerId(QString ManufacturerId);
    QString Insert(Reagent Reagent);
    void Update(Reagent Reagent);
    void DeleteById(QString ReagentId);
    void UpdateTestType(Reagent reagent);
};

#endif // REAGENTSERVICE_H
