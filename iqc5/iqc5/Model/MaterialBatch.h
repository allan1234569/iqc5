#ifndef MATERIALBATCH_H
#define MATERIALBATCH_H
#include <QString>

class MaterialBatch
{
public:
    MaterialBatch();
    QString MaterialBatchId;
    QString MaterialId;
    QString Unit;
    QString package;
    QString RegisterNo;
    QString BatchNo;
    QString ValidDate;
    QString StartDate;
    QString CreateTime;
    int Status;
};

#endif // MATERIALBATCH_H
