#include "MaterialService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QUuid>
#include <QRegularExpression>
#include <QDateTime>

MaterialService::MaterialService()
{

}

Material MaterialService::GetById(QString MaterialId)
{

    Material material;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select MaterialId,MaterialName,ManufacturerId,CountryId,Origin,CreateTime from material where material.MaterialId = :MaterialId order by MaterialId desc ");
        query.bindValue(":MaterialId", MaterialId);
        query.exec();

        while(query.next())
        {
            material.MaterialId=query.value(0).toString();
            material.MaterialName=query.value(1).toString();
            material.ManufacturerId=query.value(2).toString();
            material.CountryId=query.value(3).toString();
            material.Origin=query.value(4).toString();
            material.CreateTime=query.value(5).toString();


            return material;
        }
    }
    return material;
}

QVector<Material> MaterialService::GetMaterials(QString subjectId, QString categoryId, QString name, QString ManufacturerName, QString countryName, int if_user_first)
{
    QVector<Material> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        QString sql = QObject::tr(" select distinct material.MaterialId,MaterialName,material.ManufacturerId,material.CountryId,Origin, "
                                  " material.CreateTime,ManufacturerName,CountryName from material "
                                  " left join TestType_Material on Material.MaterialId=TestType_Material.MaterialId "
                                  " left join TestType on TestType.TestTypeId=TestType_Material.TestTypeId "
                                  " left join category on TestType.CategoryId=category.CategoryId "
                                  " left join category subject on category.ParentId=subject.CategoryId "
                                  " inner join Country on Country.CountryId=material.CountryId "
                                  " inner join Manufacturer on Material.ManufacturerId=Manufacturer.ManufacturerId "
                                  " where material.MaterialName like :name "
                                  " and Manufacturer.ManufacturerName like :ManufacturerName "
                                  " and Country.countryName like :countryName "
                                  " and ifnull(subject.CategoryId,'') like :subjectId "
                                  " and ifnull(TestType.CategoryId,'') like :categoryId "
                                  " order by ManufacturerName,MaterialName ");

        if(if_user_first) //下拉框
        {
            sql = sql.replace("order by", "order by material.ifDefault, ");
        }
        if(!if_user_first)
        {
            sql = sql.replace("where ", "where material.ifDefault <> 1 and ");
        }
        query.prepare(sql);

        query.bindValue(":subjectId",  QString("%%1%").arg(subjectId));
        query.bindValue(":categoryId",  QString("%%1%").arg(categoryId));
        query.bindValue(":name", QString("%%1%").arg(name));
        query.bindValue(":ManufacturerName", QString("%%1%").arg(ManufacturerName));
        query.bindValue(":countryName", QString("%%1%").arg(countryName));
        query.exec();
        while(query.next())
        {
            Material material;
            material.MaterialId=query.value(0).toString();
            material.MaterialName=query.value(1).toString();
            material.ManufacturerId=query.value(2).toString();
            material.CountryId=query.value(3).toString();
            material.Origin=query.value(4).toString();
            material.CreateTime=query.value(5).toString();
            material.ManufacturerName=query.value(6).toString();
            material.CountryName=query.value(7).toString();
            list.append(material);
        }
    }
    return list;
}
QVector<Material> MaterialService::GetMaterials(QString subjectId, QString categoryId, QString name, QString ManufacturerName, QString countryName, QString BatchNo, QString RegisterNo,int if_user_first)
{
    QVector<Material> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        QString sql = QObject::tr(" select distinct material.MaterialId,MaterialName,material.ManufacturerId,material.CountryId,Origin,Unit,RegisterNo,package, "
                                  " MaterialBatch.ValidDate,material.CreateTime,ManufacturerName,CountryName,MaterialBatchId,MaterialBatch.BatchNo,a.startDate from material "
                                  " left join TestType_Material on Material.MaterialId=TestType_Material.MaterialId "
                                  " left join TestType on TestType.TestTypeId=TestType_Material.TestTypeId "
                                  " left join category on TestType.CategoryId=category.CategoryId "
                                  " left join category subject on category.ParentId=subject.CategoryId "
                                  " inner join Country on Country.CountryId=material.CountryId "
                                  " inner join Manufacturer on Material.ManufacturerId=Manufacturer.ManufacturerId "
                                  " left join MaterialBatch on Material.MaterialId=MaterialBatch.MaterialId "

                                  "left join (select project_Detail.MaterialId,batchno,min(testTime) startDate from result "
                                               "inner join project_Detail on  result.project_DetailId=project_Detail.project_DetailId "
                                               "inner join materialbatch on project_Detail.materialbatchId=materialbatch.materialbatchId "
                                               "group by  project_Detail.MaterialId,batchno) a "
                                               "on MaterialBatch.batchno=a.batchno and MaterialBatch.MaterialId=a.MaterialId "


                                  " where material.MaterialName like :name "
                                  " and Manufacturer.ManufacturerName like :ManufacturerName "
                                  " and Country.countryName like :countryName "
                                  " and ifnull(subject.CategoryId,'') like :subjectId "
                                  " and ifnull(TestType.CategoryId,'') like :categoryId "
                                  " and ifnull(MaterialBatch.BatchNo,'') like :BatchNo "
                                  " and ifnull(RegisterNo,'') like :RegisterNo "
                                  " order by ManufacturerName,MaterialName ");

        if(if_user_first) //下拉框
        {
            sql = sql.replace("order by", "order by material.ifDefault, ");
        }
        if(!if_user_first)
        {
            sql = sql.replace("where ", "where material.ifDefault <> 1 and ");
        }
        query.prepare(sql);

        query.bindValue(":subjectId",  QString("%%1%").arg(subjectId));
        query.bindValue(":categoryId",  QString("%%1%").arg(categoryId));
        query.bindValue(":name", QString("%%1%").arg(name));
        query.bindValue(":ManufacturerName", QString("%%1%").arg(ManufacturerName));
        query.bindValue(":countryName", QString("%%1%").arg(countryName));
        query.bindValue(":BatchNo", QString("%%1%").arg(BatchNo));
        query.bindValue(":RegisterNo", QString("%%1%").arg(RegisterNo));
        query.exec();
        while(query.next())
        {
            Material material;
            material.MaterialId=query.value(0).toString();
            material.MaterialName=query.value(1).toString();
            material.ManufacturerId=query.value(2).toString();
            material.CountryId=query.value(3).toString();
            material.Origin=query.value(4).toString();
            material.Unit=query.value(5).toString();
            material.RegisterNo=query.value(6).toString();
            material.package=query.value(7).toString();
            material.ValidDate=query.value(8).toString();
            material.CreateTime=query.value(9).toString();
            material.ManufacturerName=query.value(10).toString();
            material.CountryName=query.value(11).toString();
            material.MaterialBatchId=query.value(12).toString();
            material.BatchNo=query.value(13).toString();
            material.StartDate=query.value(14).toString();

            list.append(material);
        }
    }
    return list;
}

QVector<Material> MaterialService::GetMaterials()
{
    QVector<Material> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.exec(QObject::tr("select distinct material.MaterialId,MaterialName,material.ManufacturerId,material.CountryId,Origin,  "
                               " CreateTime from material "
                               " inner join Country on Country.CountryId=material.CountryId "
                               " inner join Manufacturer on Material.ManufacturerId=Manufacturer.ManufacturerId "
                               " order by material.MaterialId desc"));
        while(query.next())
        {
            Material material;
            material.MaterialId=query.value(0).toString();
            material.MaterialName=query.value(1).toString();
            material.ManufacturerId=query.value(2).toString();
            material.CountryId=query.value(3).toString();
            material.Origin=query.value(4).toString();
            material.CreateTime=query.value(5).toString();
            material.ManufacturerName=query.value(6).toString();
            material.CountryName=query.value(7).toString();
            list.append(material);
        }
    }
    return list;
}

QVector<Material> MaterialService::GetMaterialsByCategoryId(QString categoryId)
{
    QVector<Material> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select distinct material.MaterialId,MaterialName,material.ManufacturerId,material.CountryId,Origin, "
                               " CreateTime from material "
                               " inner join TestType_Material on Material.MaterialId=TestType_Material.MaterialId "
                               " inner join TestType on TestType.TestTypeId=TestType_Material.TestTypeId "
                               " inner join category on TestType.CategoryId=category.CategoryId "
                               " inner join category subject on category.ParentId=subject.CategoryId "
                               " inner join Country on Country.CountryId=material.CountryId "
                               " inner join Manufacturer on Material.ManufacturerId=Manufacturer.ManufacturerId "
                               " where TestType.CategoryId=:categoryId "
                               " order by material.MaterialId desc "));
        query.bindValue(":categoryId", categoryId);
        query.exec();
        while(query.next())
        {
            Material material;
            material.MaterialId=query.value(0).toString();
            material.MaterialName=query.value(1).toString();
            material.ManufacturerId=query.value(2).toString();
            material.CountryId=query.value(3).toString();
            material.Origin=query.value(4).toString();
            material.CreateTime=query.value(5).toString();
            material.ManufacturerName=query.value(6).toString();
            material.CountryName=query.value(7).toString();
            list.append(material);
        }
    }
    return list;
}

QVector<Material> MaterialService::GetMaterialsByTestTypeId(QString testTypeId)
{
    QVector<Material> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select distinct material.MaterialId,MaterialName,material.ManufacturerId,material.CountryId,Origin,"
                               " CreateTime from material "
                               " inner join TestType_Material on Material.MaterialId=TestType_Material.MaterialId "
                               " inner join TestType on TestType.TestTypeId=TestType_Material.TestTypeId "
                               " inner join category on TestType.CategoryId=category.CategoryId "
                               " inner join category subject on category.ParentId=subject.CategoryId "
                               " inner join Country on Country.CountryId=material.CountryId "
                               " inner join Manufacturer on Material.ManufacturerId=Manufacturer.ManufacturerId "
                               " where TestType.TestTypeId=:testTypeId "
                               " order by material.MaterialId desc "));
        query.bindValue(":testTypeId", testTypeId);
        query.exec();
        while(query.next())
        {
            Material material;
            material.MaterialId=query.value(0).toString();
            material.MaterialName=query.value(1).toString();
            material.ManufacturerId=query.value(2).toString();
            material.CountryId=query.value(3).toString();
            material.Origin=query.value(4).toString();
            material.CreateTime=query.value(5).toString();
            material.ManufacturerName=query.value(6).toString();
            material.CountryName=query.value(7).toString();
            list.append(material);
        }
    }
    return list;
}

QVector<Material> MaterialService::GetMaterialsByManufacturerId(QString ManufacturerId)
{

    QVector<Material> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select material.MaterialId,material.MaterialName,material.ManufacturerId,material.CountryId,Origin,material.CreateTime,material.Status,ManufacturerName,CountryName "
                                  "from material "
                                  "inner join Manufacturer on material.ManufacturerId=Manufacturer.ManufacturerId "
                                  "inner join Country on material.CountryId=Country.CountryId "
                                  "where material.ManufacturerId = :ManufacturerId order by ManufacturerName desc"));
        query.bindValue(":ManufacturerId", ManufacturerId);
        query.exec();

        while(query.next())
        {
            Material material;
            material.MaterialId=query.value(0).toString();
            material.MaterialName=query.value(1).toString();
            material.ManufacturerId=query.value(2).toString();
            material.CountryId=query.value(3).toString();
            material.Origin=query.value(4).toString();
            material.CreateTime=query.value(5).toString();
            material.ManufacturerName=query.value(6).toString();
            material.CountryName=query.value(7).toString();
            list.append(material);
        }
    }
    return list;
}

QString MaterialService::Insert(Material material)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into material (MaterialId,MaterialName,ManufacturerId,CountryId,Origin,CreateTime,Status,IfDefault) values (:MaterialId,:MaterialName,:ManufacturerId,:CountryId,:Origin,:CreateTime,:Status,0)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":MaterialId", guid);
        query.bindValue(":MaterialName", material.MaterialName);
        query.bindValue(":ManufacturerId", material.ManufacturerId);
        query.bindValue(":CountryId", material.CountryId);
        query.bindValue(":Origin", material.Origin);

        query.bindValue(":CreateTime", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":Status", "1");
        query.exec();

        return guid;
    }
    return "";
}

void MaterialService::Update(Material material)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update material set MaterialName =:MaterialName,ManufacturerId=:ManufacturerId,CountryId=:CountryId,Origin=:Origin,CreateTime=:CreateTime,Status=:Status where MaterialId=:MaterialId");

        query.bindValue(":MaterialName", material.MaterialName);
        query.bindValue(":ManufacturerId", material.ManufacturerId);
        query.bindValue(":CountryId", material.CountryId);
        query.bindValue(":Origin", material.Origin);
        query.bindValue(":CreateTime", material.CreateTime);
        query.bindValue(":Status", material.Status);
        query.bindValue(":MaterialId", material.MaterialId);
        query.exec();
    }
}

void MaterialService::DeleteById(QString MaterialId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from material where MaterialId =:MaterialId");
        query.bindValue(":MaterialId", MaterialId);
        query.exec();
    }
}

void MaterialService::UpdateTestType(Material material)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from TestType_Material where MaterialId = :MaterialId");
        query.bindValue(":MaterialId", material.MaterialId);
        query.exec();

        TestType t;
        query.prepare("insert into TestType_Material (MaterialId,TestTypeId) values (:MaterialId,:TestTypeId)");

        QVariantList MaterialIdList;
        QVariantList TestTypeIdList;

        for(int i=0; i<material.types.count();i++)
        {
            t = material.types[i];

            MaterialIdList<<material.MaterialId;
            TestTypeIdList<<t.TestTypeId;

        }
        query.addBindValue(MaterialIdList);
        query.addBindValue(TestTypeIdList);

        query.execBatch();
    }
}
