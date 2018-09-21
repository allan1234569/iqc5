#ifndef PROJECTDETAIL_H
#define PROJECTDETAIL_H

#include <QString>

class ProjectDetail
{
public:
    ProjectDetail();

    QString Project_DetailId;
    QString ProjectId;
    int DensityId;
    QString DensityName;
    QString MaterialId;
    QString MaterialName;
    QString MaterialBatchId;
    QString MaterialBatchName;
    QString ReagentId;
    QString ReagentName;
    QString ReagentBatchId;
    QString ReagentBatchName;
    int Useflag;
    QString CreateTime;
    QString CreateUser;
    int Status;
    QString MethodId;
    QString MethodName;
};

#endif // PROJECTDETAIL_H
