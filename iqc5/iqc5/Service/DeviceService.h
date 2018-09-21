#ifndef DEVICESERVICE_H
#define DEVICESERVICE_H
#include "Device.h"

class DeviceService
{
public:
    DeviceService();

    Device GetById(QString deviceId);

    QVector<Device> GetAll(QString brandId, QString modelId, QString deviceName,int if_user_first);

    void Insert(Device device);
    void Update(Device device);
    void DeleteById(QString deviceId);
};

#endif // DEVICESERVICE_H
