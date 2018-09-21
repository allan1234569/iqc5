#ifndef PROJECTSERVICE_H
#define PROJECTSERVICE_H
#include "Project.h"

class ProjectService
{
public:
    ProjectService();

    Project GetById(QString ProjectId);
    QVector<Project> SearchProject(QString SubjectId,QString CategoryId,QString keyword,QString MaterialName,QString ReagentName,QString MethodName,QString DeviceName);
    QVector<Project> SearchProject(QString SubjectId,QString CategoryId,QString keyword,QString DeviceName);
    QString Insert(Project project);
    QString InsertDetail(ProjectDetail detail);
    QString UpdateDetail(ProjectDetail detail);
    QString InsertResult(Result result);
    void UpdateResult(Result result);
    bool DeleteResult(QString ResultId);
    Result GetResultById(QString ResultId);
    QVector<Result> GetResult(QString ProjectId,QString date,int num,int level);
    QVector<Result> GetResult(QString ProjectId,int level, bool showAll);
    QVector<Result> GetResult(QString ProjectId, int level, QString startTime, QString endTime, bool showAll);
    QVector<Result> GetResult(QString ProjectId, QString startTime, QString endTime, int level, int n = -1);

    QVector<Result> GetResultByProject(QString ProjectId, int level);
    QStringList GetResultIdFromComputatonResult(QString ProjectId);
    ProjectDetail GetDetail(QString ProjectDetailId);
    QVector<ProjectDetail> SearchDetail(QString projectId, int level, QString material, QString materialBatch, QString reagent, QString reagentBatch);
    QVector<ProjectDetail> GetDetail(QString ProjectId,int level);
    void UpdateDetailAndResult(Result result);
    void UpdateDetailAndResultBatch(QVector<QVector<Result> > results);
    void UpdateModel(Project project);
    void DeleteById(QString ProjectId);
    void Import(QString strFilePath, bool needDelete, bool needCaculate);

    void SetDefaultRule(QString testTypeId, QVector<QString> rules);
    QVector<QString> GetRules(QString testTypeId);
    QVector<QString> GetAllRules();

    QVector<Project> GetSumProjectByType(QString testTypeId);
    void InsertComputation(QString ProjectId, QString batchId, int level, QString startTime, QString endTime);
    void InsertComputation(QString ProjectId, QString batchId, int level, QString startTime, int n);
    void InsertComputation(QVector<Result> results, QString startTime, QString endTime);
    void UpdateComputationDate(QString projectId, int level, QString startTime, QString endTime);
    int GetCount(QString ProjectId, int level ,QString startTime, QString endTime);
    double getAvg(QString ProjectId,int level);
    double getSd(QString ProjectId,int level);
    int getN(QString ProjectId,int level);
    double getMax(QString ProjectId, int level);
    double getMin(QString ProjectId, int level);
    QString getStartTime(QString ProjectId,int level);
    QString getEndTime(QString ProjectId,int level);
    QVector<QString> GetProjectsDay(QString categotyId);
    QVector<Project> GetProjectByCategoryId(QString categoryId);
    QVector<Project> GetProjectByCategoryAndDay(QString categoryId, QString date);
    int GetLevelByCategoryId(QString categoryId);
};

#endif // PROJECTSERVICE_H
