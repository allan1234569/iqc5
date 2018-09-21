#ifndef REAGENT_H
#define REAGENT_H
#include <QString>
#include <QVector>
#include "TestType.h"

class Reagent
{
public:
    Reagent();

    QString ReagentId;
    QString ReagentName;
    QString ProjectName;
    QString ManufacturerId;
    QString CountryId;
    QString Unit;
    QString ValidDate;
    QString RegisterNo;
    QString StartDate;
    QString package;
    QString BatchNo;
    QString CreateTime;
    int Status;
    QString ManufacturerName;
    QString CountryName;


    QVector<TestType> types;

    QString ReagentBatchId;

};

#endif // REAGENT_H
