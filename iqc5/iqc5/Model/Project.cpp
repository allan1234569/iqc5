#include "Project.h"
#include "IRule.h"
#include "RuleManager.h"
#include <math.h>
#include <QDebug>
#include <QStringList>
#include "ProjectService.h"

Project::Project()
{
    ProjectId = "";
    level = 0;
    PerDayBatch=0;
    DispIdx=0;

    CV=0;
    Bias=0;
    TEa=0;
}

void Project::Init()
{
}

//得到某一浓度测试结果
//QVector<Result> Project::GetResultByLevel(int level, bool showAll)
//{
//    QVector<Result> list;
//    for(int i=0;i<results.count();i++)
//    {
//        if(results[i].level == level)
//        {
//            if(showAll || results[i].value>0)
//            {
//                list.append(results[i]);
//            }
//        }
//    }
//    return list;
//}


//得到某一日期的测试结果
QVector<Result> Project::GetResultByDate(QString date)
{
    QVector<Result> list;
    for(int i=0;i<results.count();i++)
    {
        if(results[i].level == 1 && results[i].CreateTime <= date)
        {
            list.append(results[i]);
        }
    }
    return list;
}

int Project::GetN(QVector<Result> data, QString beginDate, QString endDate)
{
    int count = 0;
    if(data.count() == 0)
    {
        return 0;
    }
    else
    {
        for(int i=0; i<data.count(); i++)
        {
            bool b = data[i].value>0;
            if(beginDate != "")
            {
                b = b && data[i].TestTime >= beginDate;
            }
            if(endDate != "")
            {
                b = b && data[i].TestTime <= endDate;
            }
            if(b)
            {
                count++;
            }
        }
        return count;
    }
}
//得到测试结果的平均值
double Project::GetAverage(QVector<Result> data, QString beginDate, QString endDate)
{
    int count = 0;
    if(data.count() == 0)
    {
        return 0;
    }
    else
    {
        double sum = 0;
        for(int i=0; i<data.count(); i++)
        {
            bool b = data[i].value>0;
            if(beginDate != "")
            {
                b = b && data[i].TestTime >= beginDate;
            }
            if(endDate != "")
            {
                b = b && data[i].TestTime <= endDate;
            }
            if(b)
            {
                sum += data[i].value;
                count++;
            }
        }
        double s =  sum/count;
        return s;
    }
}
double Project::GetAverage(QVector<Result> data, QString beginDate, int n)
{
    int count = 0;
    if(data.count() == 0)
    {
        return 0;
    }
    else
    {
        double sum = 0;
        for(int i=0; i<data.count(); i++)
        {
            if(i<n)
            {
                bool b = data[i].value>0;
                if(beginDate != "")
                {
                    b = b && data[i].TestTime >= beginDate;
                }
                if(b)
                {
                    sum += data[i].value;
                    count++;
                }
            }
        }
        double s =  sum/count;
        return s;
    }
}
double Project::GetAverage(QString projectId, int level)
{
    ProjectService s;
    double avg = s.getAvg(projectId, level);
    return avg;
}

//得到测试结果的方差
double Project::GetStandardDeviation(QVector<Result> data, QString beginDate, QString endDate)
{
    int count = 0;
    if(data.count() == 0)
    {
        return 0;
    }
    else
    {
        double avg = GetAverage(data,beginDate,endDate);
        double sum = 0;
        for(int i=0; i<data.count(); i++)
        {
            bool b = data[i].value>0;
            if(beginDate != "")
            {
                b = b && data[i].TestTime >= beginDate;
            }
            if(endDate != "")
            {
                b = b && data[i].TestTime <= endDate;
            }
            if(b)
            {
                sum += (data[i].value -avg)*(data[i].value -avg);
                count++;
            }
        }
        double s = sqrt(sum/count);
        return s;
    }
}

//得到测试结果的方差
double Project::GetStandardDeviation(QVector<Result> data, QString beginDate, int n)
{
    int count = 0;
    if(data.count() == 0)
    {
        return 0;
    }
    else
    {
        double avg = GetAverage(data,beginDate,n);
        double sum = 0;
        for(int i=0; i<data.count(); i++)
        {
            if(i<n)
            {
                bool b = data[i].value>0;
                if(beginDate != "")
                {
                    b = b && data[i].TestTime >= beginDate;
                }
                if(b)
                {
                    sum += (data[i].value -avg)*(data[i].value -avg);
                    count++;
                }
            }
        }
        double s = sqrt(sum/count);
        return s;
    }
}

double Project::GetStandardDeviation(QString projectId, int level)
{
    ProjectService s;
    double sd = s.getSd(projectId, level);
    return sd;
}

//得到实际CV
double Project::GetRealCV(QVector<Result> data, QString beginDate, QString endDate)
{
    double s = GetStandardDeviation(data,beginDate,endDate);
    double avg = GetAverage(data,beginDate,endDate);
    if(avg != 0)
    {
        return s / avg *100;
    }
    else
    {
        return 0;
    }
}

//得到Sec
double Project::GetSec(QVector<Result> data, QString beginDate, QString endDate)
{
    double cv = GetStandardDeviation(data,beginDate,endDate) * 100;
    double Sec = (this->TEa - fabs(this->Bias)) / cv - 1.65;

    return Sec;

}

//得到6sigma
double Project::Get6sigma(QVector<Result> data, QString beginDate, QString endDate)
{
    double cv = GetRealCV(data,beginDate,endDate);
    if(cv != 0)
    {
        return (this->TEa-0)/cv;
    }
    else
    {
        return 0;
    }
}

//得到失控概率
double Project::GetPed(QVector<QVector<Result> > &data, QString rules, int level)
{
    QVector<double> means;
    QVector<double> sds;

    for(int i = 0; i < data.count(); i++)
    {
        means.push_back(0.0);
        sds.push_back(0.0);
    }

    CaculateByRule(data, rules, means, sds, QStringList());

    int count=0;
    for(int i=0;i<data[level].count();i++)
    {
        if(data[level][i].isValid == false)
        {
            count++;
        }
    }
    return (double)count/(double)data[level].count() * 100;
}

//得到测试结果的最大值
double Project::GetMax(QVector<Result> data)
{
    int count = data.count();
    if(count == 0)
    {
        return 0;
    }
    else
    {
        double max = data[0].value;

        for(int i = 1; i < data.count(); i++)
        {
            if(data[i].value > max)
            {
                max =data[i].value;
            }
        }
        return max;
    }
}

//得到测试结果的最小值
double Project::GetMin(QVector<Result> data)
{
    int count = data.count();
    if(count == 0)
    {
        return 0;
    }
    else
    {
        double min = data[0].value;
        for(int i=1; i<data.count(); i++)
        {
            if(data[i].value < min && data[i].value>0)
            {
                min =data[i].value;
            }
        }
        return min;
    }
}

//得到测试结果的最大Z值
double Project::GetMaxZ(QVector<Result> data)
{
    int count = data.count();
    if(count == 0)
    {
        return 0;
    }
    else
    {
        double max = data[0].z_value;
        for(int i=1; i<data.count(); i++)
        {
            if(data[i].z_value > max)
            {
                max =data[i].z_value;
            }
        }
        return max;
    }
}

//得到测试结果的最小Z值
double Project::GetMinZ(QVector<Result> data)
{
    int count = data.count();
    if(count == 0)
    {
        return 0;
    }
    else
    {
        double min = data[0].z_value;
        for(int i=1; i<data.count(); i++)
        {
            if(data[i].z_value < min && data[i].value>0)
            {
                min =data[i].z_value;
            }
        }
        return min;
    }
}

//得到测试结果的最大时间
QString Project::GetMaxDate(QVector<Result> data)
{
    int count = data.count();
    if(count == 0)
    {
        return "";
    }
    else
    {
        QString max = data[0].CreateTime;
        for(int i=1; i<data.count(); i++)
        {
           if(QString::compare(data[i].CreateTime, max) > 0 && data[i].value>0)
            {
                max =data[i].CreateTime;
            }
        }
        return max;
    }
}

//得到测试结果的最小时间
QString Project::GetMinDate(QVector<Result> data)
{
    int count = data.count();
    if(count == 0)
    {
        return "";
    }
    else
    {
        QString min = data[0].CreateTime;
        for(int i=1; i<data.count(); i++)
        {
            if(QString::compare(data[i].CreateTime, min) < 0 && data[i].value>0)
            {
                min =data[i].CreateTime;
            }
        }
        return min;
    }
}

////根据规则计算在控或者失控
//void Project::CaculateByRule(QVector<Result> *data, QString ruleName, double avg, double sd)
//{
//    int n = 1;
//    QStringList rulenames2 = ruleName.split(",n=");
//    if(rulenames2.count() ==2)
//    {
//        ruleName = rulenames2.at(0);
//        n = rulenames2.at(1).toInt();
//    }

//    if(avg==0)
//    {
//        avg = GetAverage(*data, "", "");
//    }
//    if(sd==0)
//    {
//        sd = GetStandardDeviation(*data, "", "");
//    }
//    QVector<double> d;
//    for(int i=0; i<(*data).count(); i++)
//    {
//        d.append((*data)[i].value);
//    }
//    QStringList rules = ruleName.split("|");
//    for(int i=0;i<rules.count();i++)
//    {
//        QString rulename = rules.at(i);
//        if(rulename.length()>0)
//        {
//            IRule *rule = RuleManager::GetRule(rulename, avg, sd, d);
//            for(int i=0; i<(*data).count(); i++)
//            {
//                bool valid =  rule->IsValid(i);
//                if(!valid)
//                {
//                    (*data)[i].isValid =false;
//                    (*data)[i].refuseReason = (*data)[i].refuseReason + ruleName.replace("|","+") + QString(", n=%1").arg(n) + QObject::tr("规则违背  ");
//                }
//            }
//        }
//    }
//}

void Project::CaculateByRule(QVector<QVector<Result> > &allData, QString ruleName, QVector<double> &means, QVector<double> &sds, QStringList filterResultIds)
{

    int n = 1;
    QStringList rulenames2 = ruleName.split(",n=");
    if(rulenames2.count() ==2)
    {
        ruleName = rulenames2.at(0);
        n = rulenames2.at(1).toInt();
    }

    QStringList rules = ruleName.split("|");

    Project p;
    p.CaculateZ(allData,means,sds);

    for(int level = 0; level < allData.count(); level++)    //分别对每个浓度的数据进行分析、判断
    {
        if(means[level] == 0)
        {
            means[level] = GetAverage(allData[level],"","");
        }

        if (sds[level] == 0)
        {
            sds[level] = GetStandardDeviation(allData[level],"","");
        }

        QVector<QVector<double> > d;
        for(int l = 0; l < allData.count(); l++)
        {
            QVector<double> dd;
            for(int i=0; i<allData[l].count(); i++)
            {
                dd.append(allData[l][i].value);
            }
            d.push_back(dd);
        }


        for(int j = 0; j < allData[level].count(); j++)
        {
            bool lb_isVaild = true;
            if(!allData[level][j].isValid)
            {
                lb_isVaild = false;
            }
            for(int i = 0; i < rules.size(); i++)
            {
                if (!lb_isVaild)    //如果已经失控了，不再分析
                {
                    break;
                }
                QString subrulename = rules[i];
                IRule *rule = RuleManager::GetRule(subrulename, means, sds, allData);
                if(rule == NULL)    //没有得到规则，不能再往下进行
                {
                    continue;
                }

                bool valid =  rule->IsValid(level,j);
                if(!valid)
                {
                    if (!filterResultIds.contains(allData[level][j].ResultId))  // 初始化时用到的结果不视为违规
                    {
                        allData[level][j].isValid =false;
                        allData[level][j].refuseReason = subrulename + QString(", n=%1").arg(n) + QObject::tr("规则违背  ");
                    }
                    else
                    {
                        if(!allData[level][j].isValid)
                        {
                            allData[level][j].isValid = true;
                            allData[level][j].refuseReason = "";
                        }
                    }
                }
            }
        }
    }
}

//得到Z分数
void Project::CaculateZ(QVector<Result> *data, double avg, double sd)
{
    if(avg == 0)
    {
        avg = GetAverage(*data, "", "");
    }

    if(sd == 0)
    {
        sd = GetStandardDeviation(*data, "", "");
    }
    for(int i=0; i<(*data).count(); i++)
    {
         (*data)[i].z_value = ((*data)[i].value-avg) / sd;
    }
}

void Project::CaculateZ(QVector< QVector<Result> > &allData, QVector<double> &means, QVector<double> &sds)
{
    for(int i = 0; i < allData.count(); i++)
    {
        if(means[i] == 0)
        {
            means[i] = GetAverage(allData[i], "", "");
        }

        if(sds[i] == 0)
        {
            sds[i] = GetStandardDeviation(allData[i], "", "");
        }
        for(int j = 0; j < allData[i].count(); j++)
        {
             allData[i][j].z_value = (allData[i][j].value - means[i]) / sds[i];
        }
    }
}

bool Contain(QVector<Result> list, Result r)
{
    for(int i=0;i<list.count();i++)
    {
        if(QString::compare(list[i].TestTime,r.TestTime)==0 && list[i].ResultNum ==r.ResultNum)
        {
            return true;
        }
    }
    return false;
}

void Insert(QVector<Result> *list, Result r)
{
    int i=0;
    for(i=0;i<(*list).count();i++)
    {
        if(QString::compare((*list)[i].TestTime,r.TestTime)>0 ||
                (QString::compare((*list)[i].TestTime,r.TestTime)==0 && (*list)[i].ResultNum>r.ResultNum) )
        {
            (*list).insert(i, r);
            return;
        }
    }
    (*list).insert(i, r);
}
QVector< QVector<Result> > Project::ReSort(QVector< QVector<Result> > allData)
{
    QVector<Result> timeList;
    for(int i=0;i<allData.count();i++)
    {
        QVector<Result> data = allData[i];
        for(int j=0;j<data.count();j++)
        {
            if(!Contain(timeList, data[j]))
            {
                data[j].level = 0;
                data[j].value = 0;
                data[j].z_value = 0;
                data[j].isValid = true;
                data[j].refuseReason = "";
                Insert(&timeList, data[j]);
            }

        }
    }
    //qSort(timeList.begin(),timeList.end(),qLess<QString>());

    for(int j=0;j<allData.count();j++)
    {
        for(int i=0;i<timeList.count();i++)
        {
            if(!Contain(allData[j],timeList[i]))
            {
                Insert(&allData[j],timeList[i]);
            }
        }
    }


    return allData;
}

//生成平均值是average,方差是standard的随机数据
double gaussrand(double average, double StandardDeviation)
{

    static double V1, V2, S;
    static int phase = 0;
    double X;

    if ( phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;

            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);

        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);

    phase = 1 - phase;


    return X*StandardDeviation + average;
}


//生成随机数据
void Project::GenerateData(double average, double standard, int number)
{
    //生成随机数据
    results.clear();
    for(int i=0; i<number; i++)
    {
        double rand = gaussrand(average, standard);
        Result r;
        r.level = 1;
        r.value = rand;
        results.append(r);
    }
}

double Project::GetDayZ(int level, QString date)
{
    ProjectService service;
    this->results = service.GetResultByProject(this->ProjectId, level);
    double avg = service.getAvg(this->ProjectId, level);
    double sd = service.getSd(this->ProjectId, level);
    //QVector<Result> rs = this->GetResultByDate(date);
    QVector<Result> rs = service.GetResult(this->ProjectId, date, 1, level);
    if(rs.count()>0)
    {
        double val = rs[0].value;

        double z = (val - avg)/sd;
        return z;
    }
    return 0;
}
