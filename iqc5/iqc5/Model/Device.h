#ifndef DEVICE_H
#define DEVICE_H
#include <QString>

class Device
{
public:
    Device();

    QString DeviceId;
    QString DeviceName;
    QString ModelId;
    QString ModelName;
    QString BrandId;
    QString BrandName;
    QString code;
    QString sn;
    QString steelseal;
    QString assetscode;
    QString installdate;
    QString installplace;
    QString stopdate;
    QString memo;
    QString CreateTime;
    int Status;

//    Device &operator =(Device &other);

};

#endif // DEVICE_H
