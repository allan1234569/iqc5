#ifndef LIS_H
#define LIS_H

#include <QSqlDatabase>
#include <QSqlQuery>

#include "LisData.h"
#include "MaterialService.h"
#include "MaterialBatchService.h"
#include "ProjectService.h"
#include "ManufacturerService.h"
#include "UserInput_TestType.h"


class Lis
{
public:
    Lis();
    ~Lis();

    bool importData();

    LisData *data;
private:
    QSqlDatabase db;

};

#endif // LIS_H
