#include "DeviceService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QUuid>
#include <QRegularExpression>

DeviceService::DeviceService()
{

}


Device DeviceService::GetById(QString deviceId)
{
    Device device;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select device.DeviceId,DeviceName,Device.ModelId,code,sn,steelseal,assetscode,installdate,installplace,stopdate,memo,Brand.BrandName,Model.ModelName,Brand.BrandId from device "
                      " inner join Model on device.ModelId=Model.ModelId "
                      " inner join Brand on Model.BrandId=Brand.BrandId "
                      " where device.DeviceId = :deviceId order by device.DeviceId desc ");
        query.bindValue(":deviceId", deviceId);
        query.exec();

        while(query.next())
        {
            device.DeviceId=query.value(0).toString();
            device.DeviceName=query.value(1).toString();
            device.ModelId=query.value(2).toString();
            device.code=query.value(3).toString();
            device.sn=query.value(4).toString();
            device.steelseal=query.value(5).toString();
            device.assetscode=query.value(6).toString();
            device.installdate=query.value(7).toString();
            device.installplace=query.value(8).toString();
            device.stopdate=query.value(9).toString();
            device.memo=query.value(10).toString();
            device.BrandName=query.value(11).toString();
            device.ModelName=query.value(12).toString();
            device.BrandId=query.value(13).toString();


            return device;
        }
    }
    return device;
}

QVector<Device> DeviceService::GetAll(QString brandName, QString modelName, QString deviceName,int if_user_first)
{
    QVector<Device> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        QString sql = QObject::tr("select device.DeviceId,DeviceName,Device.ModelId,code,sn,steelseal,assetscode,installdate,installplace,stopdate,memo,Brand.BrandName,Model.ModelName from device"
                                  " inner join Model on device.ModelId=Model.ModelId "
                                  " inner join Brand on Model.BrandId=Brand.BrandId "
                                  " where Brand.brandName like :brandName and Model.modelName like :modelName and deviceName like :deviceName "
                                  " order by BrandName,ModelName,DeviceName ");
        if(if_user_first)
        {
            sql = sql.replace("order by", "order by device.ifDefault, ");
        }
        query.prepare(sql);

        query.bindValue(":brandName", QString("%%1%").arg(brandName));
        query.bindValue(":modelName", QString("%%1%").arg(modelName));
        query.bindValue(":deviceName", QString("%%1%").arg(deviceName));
        query.exec();
        while(query.next())
        {
            Device device;
            device.DeviceId=query.value(0).toString();
            device.DeviceName=query.value(1).toString();
            device.ModelId=query.value(2).toString();
            device.code=query.value(3).toString();
            device.sn=query.value(4).toString();
            device.steelseal=query.value(5).toString();
            device.assetscode=query.value(6).toString();
            device.installdate=query.value(7).toString();
            device.installplace=query.value(8).toString();
            device.stopdate=query.value(9).toString();
            device.memo=query.value(10).toString();
            device.BrandName=query.value(11).toString();
            device.ModelName=query.value(12).toString();
            list.append(device);
        }
    }
    return list;
}


void DeviceService::Insert(Device device)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into device (DeviceId,DeviceName,ModelId,code,sn,steelseal,assetscode,installdate,installplace,stopdate,memo,CreateTime,Status) values (:DeviceId,:DeviceName,:ModelId,:code,:sn,:steelseal,:assetscode,:installdate,:installplace,:stopdate,:memo,:CreateTime,:Status)");
        QUuid quuid;
        QRegularExpression reg;
        reg.setPattern("[{|}]");
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "").replace(reg, "");
        query.bindValue(":DeviceId", guid);
        query.bindValue(":DeviceName", device.DeviceName);
        query.bindValue(":ModelId", device.ModelId);
        query.bindValue(":code", device.code);
        query.bindValue(":sn", device.sn);
        query.bindValue(":steelseal", device.steelseal);
        query.bindValue(":assetscode", device.assetscode);
        query.bindValue(":installdate", device.installdate);
        query.bindValue(":installplace", device.installplace);
        query.bindValue(":stopdate", device.stopdate);
        query.bindValue(":memo", device.memo);
        query.bindValue(":CreateTime", device.CreateTime);
        query.bindValue(":Status", "1");
        query.exec();
    }
}

void DeviceService::Update(Device device)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update device set DeviceName =:DeviceName,ModelId =:ModelId,code=:code,sn=:sn,steelseal=:steelseal,assetscode=:assetscode,installdate=:installdate,installplace=:installplace,stopdate=:stopdate,memo=:memo,Status=:Status,CreateTime=:CreateTime where deviceId=:deviceId");

        query.bindValue(":DeviceName", device.DeviceName);
        query.bindValue(":ModelId", device.ModelId);
        query.bindValue(":code", device.code);
        query.bindValue(":sn", device.sn);
        query.bindValue(":steelseal", device.steelseal);
        query.bindValue(":assetscode", device.assetscode);
        query.bindValue(":installdate", device.installdate);
        query.bindValue(":installplace", device.installplace);
        query.bindValue(":stopdate", device.stopdate);
        query.bindValue(":memo", device.memo);
        query.bindValue(":CreateTime", device.CreateTime);
        query.bindValue(":Status", device.Status);
        query.bindValue(":deviceId", device.DeviceId);
        query.exec();

    }
}

void DeviceService::DeleteById(QString deviceId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from device where deviceId =:deviceId");
        query.bindValue(":deviceId", deviceId);
        query.exec();
    }
}

