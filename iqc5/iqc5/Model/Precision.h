#ifndef PRECISION_H
#define PRECISION_H

#include <QMap>
#include <QVector>
#include <QList>
#include <QString>

class Precision
{
public:
    Precision(){}
    ~Precision(){}

public:
    virtual void CalculateAverage(){}               //计算平均值
    virtual void CalculateStandardDeviation(){}     //计算标准差
//    QMap<int, float> GetAverage(){}
//    QMap<int, float> GetStandardDeviation(){}
};


#define DAYS 20
#define LEVEL_COUNT 2

typedef QMap< int,QMap<QString,double> > indexMap;
typedef QMap< QString, QMap<QString, double> > RCS_Map;
typedef QMap<QString,double> dataMap;


enum Level{
    LEVEL1, //浓度水平1
    LEVEL2,  //浓度水平2
    LEVEL3,
};

class PrecisionEp5
{
public:
    /**
     * @brief Precision 无参构造函数
     */
    PrecisionEp5();

    /**
     * @brief Precision 带参构造函
     * @param run1      运行1的Map
     * @param run2      运行2的Maps
     */
    PrecisionEp5(indexMap &run1, indexMap &run2);

    void init(indexMap &run1, indexMap &run2);

    void Set(indexMap &run1, indexMap &run2);



    /**
     * @brief CalculateAverage  计算平均值
     */
    void CalculateAverage();

    /**
     * @brief GetAverages   获取某一组平均值
     * @param level         浓度水平
     * @return              返回一组平均值的数组
     */
    QMap<int, double> GetAverages(Level level);

    double GetTotalAverage();

    /**
     * @brief CalculateStandardDeviation 计算标准差
     */
    void CalculateStandardDeviation();


    /**
     * @brief GetStandardDeviations 获取某一组标准差
     * @param level                 浓度水平
     * @return                      返回所有一组标准差的数组
     */
    QMap<int, double> GetStandardDeviations(Level level);

    /**
     * @brief result_D_Value    平方差之和
     * @param level             浓度水平
     * @return
     */

    double GetResult_D_Value(Level level);

    /**
     * @brief mean_D_Value  均值平方差之和
     * @return
     */
    double GetMean_D_Value();

    dataMap GetdailyMean();

    /**
     * @brief GetSr     计算标准差   Sd = sqrtf( (level1+level2)/(4*days) )
     * @param level1    水平1的差值和
     * @param level2    水平2的差值和
     * @return          返回精密度的值
     */
    double GetSd();

    /**
     * @brief GetA  得到A值    A=sqrtf( value/(2*days) )
     * @param value 均值平方差
     * @return      返回计算的值
     */

    double GetA();

    /**
     * @brief GetB  得到B值（每日的均值平方差）
     * @return
     */
    double GetB();

    double GetSt();

    /**
     * @brief GetT  总标准差估计自由度
     * @param sr
     * @param a
     * @param b
     * @return
     */
    int GetT();

    /**
     * @brief checkOutliers 离群值检测
     */
    void checkOutliers();

    inline int getR(){ return 4*20-1; }//批内均方差自由度

public:
    static bool fOutliers;          //离群值标志
    QMap< int, QMap<QString,QString> > outliers1;   //离群值数组
    QMap< int, QMap<QString,QString> > outliers2;   //离群值数组

private:
     indexMap run1OriginalDataMap;  //浓度水平1的原始数据数
     indexMap run2OriginalDataMap;  //浓度水平2的原始数据数

     QMap<int, double> average1Map; //浓度水平1时的平均值
     QMap<int, double> average2Map; //浓度水平2时的平均值
     double totalAverage1;          //浓度水平1时的总平均值
     double totalAverage2;          //浓度水平2时的总平均值

     QMap<int, double> sd1Map;      //浓度水平1时的标准差
     QMap<int, double> sd2Map;      //浓度水平2时的标准差
     double totalSd1;               //浓度水平1时的总标准差
     double totalSd2;               //浓度水平2时的总标准差
};

class PrecisionEp15
{
public:
    /**
     * @brief PrecisionEp15 Ep15无参构造函数
     */
    PrecisionEp15();

    void Set(RCS_Map &map, Level level);

    double GetT(Level level);  //自由度

    double GetBatchAverage(RCS_Map &map, QString batchStr);
    double GetTotalAverage(RCS_Map &map);
    double GetSr(Level level);     //批内精密度
    double GetSrr(Level level);    //批间精密度

private:
    int days;
    int counts;
    RCS_Map mData1;
    RCS_Map mData2;
    RCS_Map mData3;

    double GetSd(RCS_Map &map);     //批内标准差
    double GetSdb(Level &level);    //批间标准差
    double GetSb(RCS_Map &map);
};

class PrecisionWestgard
{
public:
    enum LEVEL{
        L1,
        L2,
        L3
    };

public :
    PrecisionWestgard();
    PrecisionWestgard(indexMap map);
    void Set(indexMap map);

    double GetSr(PrecisionWestgard::LEVEL level);         //精密度


private:
    indexMap mData;
    double Sr(QString level);
};

#endif // PRECISION_H
