#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QDate>
#include <QVector>
#include "TestType.h"
#include "Material.h"
#include "Reagent.h"
#include "Result.h"
#include "Device.h"
#include "ProjectDetail.h"

typedef struct Calculate_Data{
    double sd;
    double avg;
}Calculate_Data;

class Project
{
public:
    Project();
    //得到某一浓度测试结果
    //QVector<Result> GetResultByLevel(int level, bool showAll);

    QVector<Result> GetResultByDate(QString date);

    int GetN(QVector<Result> data, QString beginDate, QString endDate);

    //得到某一浓度测试结果的平均值
    double GetAverage(QVector<Result> data, QString beginDate, QString endDate);
    double GetAverage(QVector<Result> data, QString beginDate,int n);
    double GetAverage(QString projectId, int level);

    //得到某一浓度测试结果的方差
    double GetStandardDeviation(QVector<Result> data, QString beginDate, QString endDate);
    double GetStandardDeviation(QVector<Result> data, QString beginDate, int n);
    double GetStandardDeviation(QString projectId, int level);

    //得到实际CV
    double GetRealCV(QVector<Result> data, QString beginDate, QString endDate);

    //得到Sec
    double GetSec(QVector<Result> data, QString beginDate, QString endDate);

    //得到6sigma
    double Get6sigma(QVector<Result> data, QString beginDate, QString endDate);

    //得到失控概率
    double GetPed(QVector<QVector<Result> > &data, QString rules, int level);

//    //根据规则计算在控或者失控
//    void CaculateByRule(QVector<Result> *data, QString ruleName, double avg, double sd);

    /**
     * @brief CaculateByRule    根据规则计算在控或者失控
     * @param allData
     * @param ruleName
     * @param cal_data
     * @param mode              标记，只有在当前模式为2，画 Z分图时才使用
     * @param filterResultIds   过滤掉计算用的结果值，不作标记
     */
    void CaculateByRule(QVector<QVector<Result> > &allData, QString ruleName, QVector<double> &means, QVector<double> &variances, QStringList filterResultIds);

    //得到Z分数
    void CaculateZ(QVector<Result> *data, double avg, double sd);
    void CaculateZ(QVector<QVector<Result> > &allData, QVector<double> &means, QVector<double> &sds);

    double GetDayZ(int level, QString date);

    //得到测试结果的最大值
    double GetMax(QVector<Result> data);
    //得到测试结果的最小值
    double GetMin(QVector<Result> data);
    //得到测试结果的最大Z值
    double GetMaxZ(QVector<Result> data);
    //得到测试结果的最小Z值
    double GetMinZ(QVector<Result> data);
    //得到测试结果的最大时间
    QString GetMaxDate(QVector<Result> data);
    //得到测试结果的最小时间
    QString GetMinDate(QVector<Result> data);

    //生成随机数据
    void GenerateData(double average, double standard, int number);

    QVector< QVector<Result> > ReSort(QVector< QVector<Result> > allData);

    //Init
    void Init();

    QString ProjectId;
    QString ProjectName;
    TestType testType;
    QString StandardId;
    int level;
    int PerDayBatch;
    int DispIdx;

    double CV;
    double Bias;
    double TEa;
    QDate CreateTime;

    QVector<Result> results;

    QString defaultRule;


    double avg[];
    double sd[];

    QString EnglishName;
    QString CustomName;
    QString ReagentId;
    QString ReagentName;
    QString CurrentReagentBatch;
    QString MaterialId;
    QString MaterialName;
    QString CurrentMaterialBatch;
    QString MethodId;
    QString MethodName;
    QString DeviceId;
    QString DeviceName;
    QString CreatorId;
    QString CreatorName;

    QString UnitName;
};

#endif // PROJECT_H
