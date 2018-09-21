#ifndef MY_PROJECT_H
#define MY_PROJECT_H

#include <QString>
#include "myTestType.h"
#include <QVector>
class MyProject
{
public:
    MyProject();
//    Project &operator =(Project& other);
    void clear();
    bool isEmpty();

public:
    QString sampleId;       //样本编号
    QString testTypeCode;

    double Value;          //值
    QString DataTime;       //日期和时间

    MyTestType testType;

    int subProjectCount;
};

#endif // MY_PROJECT_H
