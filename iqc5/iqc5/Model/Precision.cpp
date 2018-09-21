#include "Precision.h"
#include <QString>
#include <QDebug>
#include <math.h>

 bool PrecisionEp5::fOutliers = false;

PrecisionEp5::PrecisionEp5()
{
    totalAverage1 = 0;
    totalAverage2 = 0;
    totalSd1 = 0;
    totalSd2 = 0;
    fOutliers = false;
}

PrecisionEp5::PrecisionEp5(indexMap &run1, indexMap &run2)
{

    init(run1,run2);
}

void PrecisionEp5::init(indexMap &run1, indexMap &run2)
{
    run1OriginalDataMap.clear();
    run2OriginalDataMap.clear();
    average1Map.clear();
    average2Map.clear();
    sd1Map.clear();
    sd2Map.clear();

    totalAverage1 = 0;
    totalAverage2 = 0;
    totalSd1 = 0;
    totalSd2 = 0;
    run1OriginalDataMap = run1;
    run2OriginalDataMap = run2;
    CalculateAverage();
    CalculateStandardDeviation();
}

void PrecisionEp5::Set(indexMap &run1, indexMap &run2)
{
    init(run1,run2);
}

void PrecisionEp5::CalculateAverage()
{//假设20组数据齐全的情况下
    double value1;
    double value2;
    double avg;

    //计算平均值，并且将结果放入数组中
    for(int i = 1; i <= 20; i++)
    {
        value1 = run1OriginalDataMap[i]["Result1"];
        value2 = run1OriginalDataMap[i]["Result2"];
        avg = (value1+value2)/2;
        average1Map.insert(i,avg);

        value1 = run2OriginalDataMap[i]["Result1"];
        value2 = run2OriginalDataMap[i]["Result2"];
        avg = (value1+value2)/2;
        average2Map.insert(i,avg);
    }

    double sum1 = 0,sum2 = 0;
    for(int i = 1; i <= 20; i++)
    {
        sum1 += average1Map.value(i);
        sum2 += average2Map.value(i);
    }
    totalAverage1 = sum1/20;
    totalAverage2 = sum2/20;
}

QMap<int, double> PrecisionEp5::GetAverages(Level level)
{
    if(level == LEVEL1)
        return average1Map;
    else if(level == LEVEL2)
        return average2Map;
}

double PrecisionEp5::GetTotalAverage()
{
    double sum11 = 0,sum12 = 0,sum21 = 0,sum22 = 0;

    for(int i = 1; i <= 20; i++)
    {
        sum11 += run1OriginalDataMap[i]["Result1"];
        sum12 += run1OriginalDataMap[i]["Result2"];
        sum21 += run2OriginalDataMap[i]["Result1"];
        sum22 += run2OriginalDataMap[i]["Result2"];
    }
    return (sum11 + sum12 + sum21 + sum22)/(4*DAYS);
}

void PrecisionEp5::CalculateStandardDeviation()
{
    double avg, rep1,rep2;
    double sd;

    for(int i = 1; i <= DAYS; i++)
    {
        if(average1Map.contains(i))
            avg = average1Map.value(i);
        else
            avg = 0;
        if(avg != 0)
        {
            rep1 = run1OriginalDataMap[i].value(QString("Result1"));
            rep2 = run1OriginalDataMap[i].value(QString("Result2"));
            sd = sqrtf(((avg-rep1)*(avg-rep1)+(avg-rep2)*(avg-rep2))/(LEVEL_COUNT-1));
            sd1Map.insert(i,sd);
        }

        if(average2Map.contains(i))
            avg = average2Map.value(i);
        else
            avg = 0;
        if(avg != 0)
        {
            rep1 = run2OriginalDataMap[i].value(QString("Result1"));
            rep2 = run2OriginalDataMap[i].value(QString("Result2"));
            sd = sqrtf(((avg-rep1)*(avg-rep1)+(avg-rep2)*(avg-rep2))/(LEVEL_COUNT-1));
            sd2Map.insert(i,sd);
        }
    }

    //总的标准差
    double sum1 = 0, sum2 = 0;
    for(int i = 1; i <= 20; i++)
    {
        sum1 += sd1Map.value(i);
        sum2 += sd2Map.value(i);
    }

    totalSd1 = sum1/20;
    totalSd2 = sum2/20;
}

QMap<int, double> PrecisionEp5::GetStandardDeviations(Level level)
{
    if(level == LEVEL1)
    {
        return sd1Map;
    }
    else if(level == LEVEL2)
    {
        return sd2Map;
    }
}

double PrecisionEp5::GetResult_D_Value(Level level)
{
    double sum = 0;
    double dv = 0;
    if(level == LEVEL1)
    {
        for(int i = 1; i <= 20; i++)
        {
            dv = run1OriginalDataMap[i]["Result1"]-run1OriginalDataMap[i]["Result2"];
            sum += dv*dv;
        }
    }
    else if(level == LEVEL2)
    {
        for(int i = 1; i <= 20; i++)
        {
            dv = run2OriginalDataMap[i]["Result1"]-run2OriginalDataMap[i]["Result2"];
            sum += dv*dv;
        }
    }

    return sum;
}

double PrecisionEp5::GetMean_D_Value()
{
    double sum = 0;
    double dv = 0;
    for(int i = 1; i <= 20; i++)
    {
        dv = average1Map.value(i)-average2Map.value(i);
        sum += dv*dv;
    }
    return sum;
}

dataMap PrecisionEp5::GetdailyMean()
{

}

double PrecisionEp5::GetSd()
{
    double level1 = GetResult_D_Value(LEVEL1);
    double level2 = GetResult_D_Value(LEVEL2);
    return sqrt( (level1+level2)/(4*20) );
}

double PrecisionEp5::GetA()
{
    double mean = GetMean_D_Value();
    return sqrt( mean/(2*20) );
}

double PrecisionEp5::GetB()
{
    double sd;               //标准差
    double avg = 0;
    double sum = 0;
    double dailyMean[20];    //每日的平均值
    //计算每日平均值
    for(int i = 0; i < 20; i++)
    {
        dailyMean[i] =  (average1Map.value(i+1)+average2Map.value(i+1))/2;
    }

    //计算总的平均值
    for(int i = 0; i < 20; i++)
    {
        sum += dailyMean[i];
    }
    avg = sum/20;

    //计算标准差
    double dv = 0;
    sum = 0;
    for(int i = 0; i < 20; i++)
    {
        dv = avg-dailyMean[i];
        sum += dv*dv;
    }
    sd = sqrt(sum/(20-1));
    return sd;
}

double PrecisionEp5::GetSt()
{
    double a = GetA();
    double b = GetB();
    double sd = GetSd();
    return sqrt((2*b*b + a*a + sd*sd)/2);

}

int PrecisionEp5::GetT()
{
    double ME = 0.0;
    double MR = 0.0;
    double MD = 0.0;

    double Sr = GetSd();
    double A = GetA();
    double B = GetB();
    ME = Sr*Sr;
    MR = 2*A*A;
    MD = 4*B*B;
    double value = 2*ME*ME+MR*MR+(DAYS*MD*MD)/(DAYS-1);
    return qRound((DAYS*(2*ME+MR+MD)*(2*ME+MR+MD))/value);
}

void PrecisionEp5::checkOutliers()
{
    outliers1.clear();
    outliers2.clear();
    double Abs;
    for(int i = 1; i <= 20; i++)
    {
        QMap<QString,QString> tMap;

        Abs = run1OriginalDataMap[i]["Result1"]>totalAverage1?run1OriginalDataMap[i]["Result1"] - totalAverage1:totalAverage1 - run1OriginalDataMap[i]["Result1"];
        if(Abs > 4*totalSd1)
        {
            tMap.insert("Result1","true");
            fOutliers = true;
        }


        Abs = run1OriginalDataMap[i]["Result2"]>totalAverage1?run1OriginalDataMap[i]["Result2"] - totalAverage1:totalAverage1 - run1OriginalDataMap[i]["Result2"];

        if(Abs > 4*totalSd1)
        {
            tMap.insert("Result2","true");
            fOutliers = true;
        }
        outliers1.insert(i,tMap);


        tMap.clear();

        Abs = run2OriginalDataMap[i]["Result1"]>totalAverage2?run2OriginalDataMap[i]["Result1"] - totalAverage2:totalAverage2 - run2OriginalDataMap[i]["Result1"];

        if(Abs > 4*totalSd2)
        {
            tMap.insert("Result1","true");
            fOutliers = true;
        }

        Abs = run2OriginalDataMap[i]["Result2"]>totalAverage2?run2OriginalDataMap[i]["Result2"] - totalAverage2:totalAverage2 - run2OriginalDataMap[i]["Result2"];

        if(Abs > 4*totalSd2)
        {
            tMap.insert("Result2","true");
            fOutliers = true;
        }
        outliers2.insert(i,tMap);
    }
}


PrecisionWestgard::PrecisionWestgard()
{

}

PrecisionWestgard::PrecisionWestgard(indexMap map)
{
    Set(map);
}

void PrecisionWestgard::Set(indexMap map)
{
    mData.clear();
    mData = map;
}

double PrecisionWestgard::GetSr(LEVEL level)
{

    if(level == PrecisionWestgard::L1)
    {
        return Sr("L1");
    }
    else if(level == PrecisionWestgard::L2)
    {
        return Sr("L2");
    }
    else if(level == PrecisionWestgard::L3)
    {
        return Sr("L3");
    }
}

double PrecisionWestgard::Sr(QString level)
{
    double sum = 0;
    for(int i = 0; i < mData.count(); i++)
    {
        sum += mData[i][level];
    }

    double avg = sum/mData.count();
    sum = 0;

    for(int i = 0; i < mData.count(); i++)
    {
        double value = mData[i][level]-avg;
        sum += value*value;
    }
    return ( sqrt( sum / ( mData.count()-1 ) ) )/ avg;
}

PrecisionEp15::PrecisionEp15()
{
}

void PrecisionEp15::Set(RCS_Map &map, Level level)
{
    mData1.clear();
    mData2.clear();
    mData3.clear();

    if(level == LEVEL1)
    {
        mData1 = map;
    }
    else if(level == LEVEL2)
    {
        mData2 = map;
    }
    else if(level == LEVEL3)
    {
        mData3 = map;
    }
}

double PrecisionEp15::GetT(Level level)
{

    int n = 3;  //每批测量次数
    int D = 5;  //测量天（批）数
    double sd = 0, sb = 0;
    if(level == LEVEL1)
    {
        sd = GetSd(mData1);
        sb = GetSb(mData1);
    }
    else if(level == LEVEL2)
    {
        sd = GetSd(mData2);
        sb = GetSb(mData2);
    }
    else if(level == LEVEL3)
    {
        sd = GetSd(mData3);
        sb = GetSb(mData3);
    }

    double value = ((n-1)*sd*sd + sb*sb)*((n-1)*sd*sd + sb*sb) / ((n-1)*sd*sd*sd*sd/D + n*n*sb*sb*sb*sb/(D-1));

    return value;
}

double PrecisionEp15::GetBatchAverage(RCS_Map &map, QString batchStr)
{
    double sum = 0;
    sum = map["x1"][batchStr] + map["x2"][batchStr] + map["x2"][batchStr];
    return sum/3;
}

double PrecisionEp15::GetTotalAverage(RCS_Map &map)
{
    double sum = 0;
    for(int i = 1; i <= 5; i++)
    {
        double value = GetBatchAverage(map,QString("batch%1").arg(i));
        sum += value;
    }
    return sum / 5;
}

double PrecisionEp15::GetSr(Level level)
{
    if(level == LEVEL1)
    {
        return GetSd(mData1)/GetTotalAverage(mData1);
    }
    else if(level == LEVEL2)
    {
        return GetSd(mData2)/GetTotalAverage(mData2);
    }
    else if(level == LEVEL3)
    {
        return GetSd(mData3)/GetTotalAverage(mData3);
    }
}

double PrecisionEp15::GetSrr(Level level)
{
    if(level == LEVEL1)
    {
        return GetSdb(level) / GetTotalAverage(mData1);
    }
    else if(level == LEVEL2)
    {
        return GetSdb(level) / GetTotalAverage(mData2);
    }
    else if(level == LEVEL3)
    {
        return GetSdb(level) / GetTotalAverage(mData3);
    }
}

double PrecisionEp15::GetSd(RCS_Map &map)
{
    double sum = 0;
    for(int i = 1; i <= 5; i++)
    {
        double avg = GetBatchAverage(map,QString("batch%1").arg(i));
        double value1 = map["x1"][QString("batch%1").arg(i)] - avg;
        double value2 = map["x2"][QString("batch%1").arg(i)] - avg;
        double value3 = map["x3"][QString("batch%1").arg(i)] - avg;
        double sd2 = (value1*value1 + value2*value2 + value3*value3) / 2;
        sum += sd2;
    }
    return sqrt(sum/5);
}

double PrecisionEp15::GetSdb(Level &level)
{
    double sb = 0, sd = 0;
    if(level == LEVEL1)
    {
        sb = GetSb(mData1);
        sd = GetSd(mData1);
    }
    else if(level == LEVEL2)
    {
        sb = GetSb(mData2);
        sd = GetSd(mData2);
    }
    else if(level == LEVEL3)
    {
        sb = GetSb(mData3);
        sd = GetSd(mData3);
    }

    return sqrt( ( (2*sb*sb) / 3 ) +sb*sb );
}

double PrecisionEp15::GetSb(RCS_Map &map)
{
    double totalAvg = GetTotalAverage(map);

    double sum = 0;
    for(int i = 1; i <= 5; i++)
    {
        double avg = GetBatchAverage(map,QString("batch%1").arg(i));
        double value = avg -totalAvg;
        sum += value*value;
    }
    return sqrt(sum / 4);//5个批次n-1
}

