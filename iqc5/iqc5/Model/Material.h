#ifndef MATERIAL_H
#define MATERIAL_H
#include <QString>
#include <QVector>
#include "TestType.h"

class Material
{
public:
    Material();

    QString MaterialId;
    QString MaterialName;
    QString ManufacturerId;
    QString CountryId;
    QString Origin;
    QString Unit;
    QString RegisterNo;
    QString package;
    QString BatchNo;
    QString ValidDate;
    QString StartDate;
    QString CreateTime;
    int Status;

    QString ManufacturerName;
    QString CountryName;

    QVector<TestType> types;

    QString MaterialBatchId;

};

#endif // MATERIAL_H
