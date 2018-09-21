#ifndef DATASHEETSERVICE_H
#define DATASHEETSERVICE_H

#include "DataSheet.h"
#include <QVector>

class DataSheetService
{
public:
    DataSheetService();

    QVector<DataSheet> GetDetail(QString projectId);

    QVector<DataSheet> GetDetail(QString projectId, QString startDate, QString endDate);
};

#endif // DATASHEETSERVICE_H
