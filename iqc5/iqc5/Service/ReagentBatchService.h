#ifndef REAGENTBATCHSERVICE_H
#define REAGENTBATCHSERVICE_H

#include "ReagentBatch.h"

class ReagentBatchService
{
public:
    ReagentBatchService();

    ReagentBatch GetById(QString ReagentBatchId);
    QVector<ReagentBatch> GetReagentBatchs(QString ReagentId, QString name);

    QString Insert(ReagentBatch reagent);
    void Update(ReagentBatch reagent);
    void DeleteById(QString ReagentBatchId);
};

#endif // REAGENTBATCHSERVICE_H
