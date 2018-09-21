#ifndef REAGENTBATCH_H
#define REAGENTBATCH_H
#include <QString>

class ReagentBatch
{
public:
    ReagentBatch();

    QString ReagentBatchId;
    QString ReagentId;
    QString Unit;
    QString package;
    QString RegisterNo;
    QString BatchNo;
    QString ValidDate;
    QString StartDate;
    QString CreateTime;
    int Status;
};

#endif // REAGENTBATCH_H
