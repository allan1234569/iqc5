#ifndef INPUTBATCH_H
#define INPUTBATCH_H
#include <QString>

class InputBatch
{
public:
    InputBatch();

    QString InputBatchId;
    QString UserInputid;
    QString InputBatchNo;
    QString InputTime;
    QString InputUser;
    int DelFlag;
};

#endif // INPUTBATCH_H
