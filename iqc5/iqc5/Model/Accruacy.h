#ifndef ACCRUACY_H
#define ACCRUACY_H

#include <QVector>
#include <QMap>

//#define MEASURE_COUNT   10  // 测量总次数
//#define REPEAT_COUNT    2   //每次重复测量次数
//#define DOF REPEAT_COUNT*MEASURE_COUNT-1    //自由度

/***
 * 正确度的ep15方案参考物质类
 */
class Accruacy_ReferenceMaterial
{
public:
    Accruacy_ReferenceMaterial();
    void Set(QMap<int,double> map);
    /**
     * @brief GetTotalAverage   获取总均值
     * @return
     */
    double GetTotalAverage();

    /**
     * @brief GetSd 获取标准差
     * @return      返回计算得到的标准差
     */
    double GetSd();

    double GetSa();

    int Dof();

    /**
     * @brief GetVI     验证区间
     * @return
     */
    double GetVI();

private:
    QMap<int, double> mData;   //实验数据
    double average;          //实验数据总均值
    double sd;               //标准差

};



typedef QMap< int , QMap<QString,double> > data_Map;
/***
 * 正确度的ep15方案患者样本类
 */
class Accruacy_PatientSample
{
public:
    Accruacy_PatientSample();

    void Set(data_Map map);

    QMap<int, double> GetBi();          //绝对偏移

    QMap<int, double> GetBirel();       //相对偏移

    double GetBiSd();       //得到绝对偏移标准差

    double GetBirelSd();    //得到相对偏移标准差

    double averageBi;               //绝对偏移
    double averageBirel;            //相对偏移

    /// \TODO
    //绝对偏移验证区间

    //相对偏移验证区间

    data_Map mData; //实验数据

    QMap<int, double> mBi;          //每个测量样本两个方法间的绝对偏移量
    QMap<int, double> mBirel;       //每个测量样本两个方法间的相对偏移量
    QMap<int, double> mBiDSqure;    //每个测量样本两个方法间的绝对偏移平方差
    QMap<int, double> mBirelDSqure; //每个测量样本两个方法间的相对偏移平方差

};

#endif // ACCRUACY_H
