#ifndef DATASHEET_H
#define DATASHEET_H

#include <QString>

class DataSheet
{
public:
    DataSheet();

public:
    QString englishName;        //中文简称
    QString chineseName;        //英文简称
    QString categoryName;       //专业
    QString subCategoryName;    //亚专业
    QString densityId;          //浓度水平
    QString testNum;            //检测次数
    QString materialName;       //质控品名称
    QString materialBatchNo;    //质控品批号
    QString reagentName;        //试剂名称
    QString reagentBatchNo;     //试剂批号
    QString methodName;         //方法
    QString deviceName;         //仪器
    QString resultValue;        //结果
    QString testTime;           //检测时间


};

#endif // DATASHEET_H
