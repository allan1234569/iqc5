#ifndef RESULT_H
#define RESULT_H
#include <QString>
#include "ProjectDetail.h"

class Result
{
public:
    Result();

    QString ResultId;

    QString ProjectId;

    //QString ProjectDetailId;

    int ResultNum;

    //浓度
    int level;

    //测量值
    double value;

    //创建时间
    QString CreateTime;

    //检测时间
    QString TestTime;

    //是否在控
    bool isValid;

    //失控原因
    QString refuseReason;

    //备注
    QString Memo;

    //Z分数
    double z_value;

    //缓存 计算保留用
    double X;

    //缓存 计算保留用
    double Y;


    ProjectDetail detail;
};

#endif // RESULT_H
