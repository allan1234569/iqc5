#include "ReagentService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QUuid>
#include <QRegularExpression>
#include <QDateTime>

ReagentService::ReagentService()
{

}

Reagent ReagentService::GetById(QString ReagentId)
{

    Reagent reagent;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select ReagentId,ReagentName,ProjectName,ManufacturerId,CountryId,CreateTime from Reagent where Reagent.ReagentId = :ReagentId order by ReagentId desc ");
        query.bindValue(":ReagentId", ReagentId);
        query.exec();

        while(query.next())
        {
            reagent.ReagentId=query.value(0).toString();
            reagent.ReagentName=query.value(1).toString();
            reagent.ProjectName=query.value(2).toString();
            reagent.ManufacturerId=query.value(3).toString();
            reagent.CountryId=query.value(4).toString();
            reagent.CreateTime=query.value(5).toString();

            return reagent;
        }
    }
    return reagent;
}

QVector<Reagent> ReagentService::GetReagents(QString subjectId, QString categoryId, QString name, QString ManufacturerName, QString countryName,int if_user_first)
{
    QVector<Reagent> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        QString sql = QObject::tr(" select distinct reagent.ReagentId,ReagentName,ProjectName,reagent.ManufacturerId,reagent.CountryId,CreateTime,"
                                  " CountryName,ManufacturerName from reagent "
                                  " left join TestType_Reagent on reagent.ReagentId=TestType_Reagent.ReagentId "
                                  " left join TestType on TestType.TestTypeId=TestType_Reagent.TestTypeId  "
                                  " left join category on TestType.CategoryId=category.CategoryId "
                                  " left join category subject on category.ParentId=subject.CategoryId "
                                  " inner join Country on Country.CountryId=reagent.CountryId "
                                  " inner join Manufacturer on Reagent.ManufacturerId=Manufacturer.ManufacturerId "
                                  " where reagent.ReagentName like :name "
                                  " and Manufacturer.ManufacturerName like :ManufacturerName "
                                  " and Country.countryName like :countryName "
                                  " and ifnull(subject.CategoryId,'') like :subjectId "
                                  " and ifnull(TestType.CategoryId,'') like :categoryId "
                                  " order by ManufacturerName,ReagentName");

        if(if_user_first) //下拉框
        {
            sql = sql.replace("order by", "order by reagent.ifDefault, ");
        }
        if(!if_user_first)
        {
            sql = sql.replace("where ", "where reagent.ifDefault <> 1 and ");
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
            Reagent reagent;
            reagent.ReagentId=query.value(0).toString();
            reagent.ReagentName=query.value(1).toString();
            reagent.ProjectName=query.value(2).toString();
            reagent.ManufacturerId=query.value(3).toString();
            reagent.CountryId=query.value(4).toString();
            reagent.CreateTime=query.value(5).toString();
            reagent.CountryName=query.value(6).toString();
            reagent.ManufacturerName=query.value(7).toString();
            list.append(reagent);
        }
    }
    return list;
}

QVector<Reagent> ReagentService::GetReagents(QString subjectId, QString categoryId, QString name, QString ManufacturerName, QString countryName, QString BatchNo, QString RegisterNo,int if_user_first)
{
    QVector<Reagent> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        QString sql = QObject::tr("select distinct reagent.ReagentId,ReagentName,ProjectName,reagent.ManufacturerId,reagent.CountryId,Unit,ReagentBatch.ValidDate,RegisterNo,package,reagent.CreateTime,"
                                  " CountryName,ManufacturerName,ReagentBatchId,ReagentBatch.BatchNo,a.startDate from reagent "
                                  " left join TestType_Reagent on reagent.ReagentId=TestType_Reagent.ReagentId "
                                  " left join TestType on TestType.TestTypeId=TestType_Reagent.TestTypeId  "
                                  " left join category on TestType.CategoryId=category.CategoryId "
                                  " left join category subject on category.ParentId=subject.CategoryId "
                                  " left join ReagentBatch on Reagent.ReagentId=ReagentBatch.ReagentId "
                                  " inner join Country on Country.CountryId=reagent.CountryId "
                                  " inner join Manufacturer on Reagent.ManufacturerId=Manufacturer.ManufacturerId "


                                  "left join (select project_Detail.ReagentId,batchno,min(testTime) startDate from result "
                                               "inner join project_Detail on  result.project_DetailId=project_Detail.project_DetailId "
                                               "inner join reagentbatch on project_Detail.ReagentBatchId=reagentbatch.ReagentBatchId "
                                               "group by  project_Detail.ReagentId,batchno) a "
                                               "on ReagentBatch.batchno=a.batchno and ReagentBatch.ReagentId=a.ReagentId "

                                  " where reagent.ReagentName like :name "
                                  " and Manufacturer.ManufacturerName like :ManufacturerName "
                                  " and Country.countryName like :countryName "
                                  " and ifnull(subject.CategoryId,'') like :subjectId "
                                  " and ifnull(TestType.CategoryId,'') like :categoryId "
                                  " and ifnull(ReagentBatch.BatchNo,'') like :BatchNo "
                                  " and ifnull(RegisterNo,'') like :RegisterNo "
                                  " order by ManufacturerName,ReagentName");

        if(if_user_first) //下拉框
        {
            sql = sql.replace("order by", "order by reagent.ifDefault, ");
        }
        if(!if_user_first)
        {
            sql = sql.replace("where ", "where reagent.ifDefault <> 1 and ");
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
            Reagent reagent;
            reagent.ReagentId=query.value(0).toString();
            reagent.ReagentName=query.value(1).toString();
            reagent.ProjectName=query.value(2).toString();
            reagent.ManufacturerId=query.value(3).toString();
            reagent.CountryId=query.value(4).toString();
            reagent.Unit=query.value(5).toString();
            reagent.ValidDate=query.value(6).toString();
            reagent.RegisterNo=query.value(7).toString();
            reagent.package=query.value(8).toString();
            reagent.CreateTime=query.value(9).toString();
            reagent.CountryName=query.value(10).toString();
            reagent.ManufacturerName=query.value(11).toString();
            reagent.ReagentBatchId=query.value(12).toString();
            reagent.BatchNo=query.value(13).toString();
            reagent.StartDate=query.value(14).toString();
            list.append(reagent);
        }
    }
    return list;
}


QVector<Reagent> ReagentService::GetReagents()
{
    QVector<Reagent> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.exec(QObject::tr("select distinct reagent.ReagentId,ReagentName,ProjectName,reagent.ManufacturerId,reagent.CountryId,CreateTime,"
                               " CountryName,ManufacturerName from reagent "
                               " inner join Country on Country.CountryId=reagent.CountryId "
                               " inner join Manufacturer on Reagent.ManufacturerId=Manufacturer.ManufacturerId "
                               " order by reagent.ReagentId desc"));
        while(query.next())
        {
            Reagent reagent;
            reagent.ReagentId=query.value(0).toString();
            reagent.ReagentName=query.value(1).toString();
            reagent.ProjectName=query.value(2).toString();
            reagent.ManufacturerId=query.value(3).toString();
            reagent.CountryId=query.value(4).toString();
            reagent.CreateTime=query.value(5).toString();
            reagent.CountryName=query.value(6).toString();
            reagent.ManufacturerName=query.value(7).toString();
            list.append(reagent);
        }
    }
    return list;
}

QVector<Reagent> ReagentService::GetReagentsByCategoryId(QString categoryId)
{
    QVector<Reagent> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select distinct reagent.ReagentId,ReagentName,ProjectName,reagent.ManufacturerId,reagent.CountryId,CreateTime,"
                               " CountryName,ManufacturerName from reagent "
                               " inner join TestType_Reagent on reagent.ReagentId=TestType_Reagent.ReagentId "
                               " inner join TestType on TestType.TestTypeId=TestType_Reagent.TestTypeId  "
                               " inner join category on TestType.CategoryId=category.CategoryId "
                               " inner join category subject on category.ParentId=subject.CategoryId "
                               " inner join Country on Country.CountryId=reagent.CountryId "
                               " inner join Manufacturer on Reagent.ManufacturerId=Manufacturer.ManufacturerId "
                               " where category.CategoryId=:categoryId "
                               " order by reagent.ReagentId desc"));
        query.bindValue(":categoryId", categoryId);
        query.exec();
        while(query.next())
        {
            Reagent reagent;
            reagent.ReagentId=query.value(0).toString();
            reagent.ReagentName=query.value(1).toString();
            reagent.ProjectName=query.value(2).toString();
            reagent.ManufacturerId=query.value(3).toString();
            reagent.CountryId=query.value(4).toString();
            reagent.CreateTime=query.value(5).toString();
            reagent.CountryName=query.value(6).toString();
            reagent.ManufacturerName=query.value(7).toString();
            list.append(reagent);
        }
    }
    return list;
}

QVector<Reagent> ReagentService::GetReagentsByTestTypeId(QString testTypeId)
{
    QVector<Reagent> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select distinct reagent.ReagentId,ReagentName,ProjectName,reagent.ManufacturerId,reagent.CountryId,CreateTime,"
                               " CountryName,ManufacturerName from reagent "
                               " inner join TestType_Reagent on reagent.ReagentId=TestType_Reagent.ReagentId "
                               " inner join TestType on TestType.TestTypeId=TestType_Reagent.TestTypeId  "
                               " inner join category on TestType.CategoryId=category.CategoryId "
                               " inner join category subject on category.ParentId=subject.CategoryId "
                               " inner join Country on Country.CountryId=reagent.CountryId "
                               " inner join Manufacturer on Reagent.ManufacturerId=Manufacturer.ManufacturerId "
                               " where TestType.TestTypeId=:testTypeId "
                               " order by reagent.ReagentId desc"));
        query.bindValue(":testTypeId", testTypeId);
        query.exec();
        while(query.next())
        {
            Reagent reagent;
            reagent.ReagentId=query.value(0).toString();
            reagent.ReagentName=query.value(1).toString();
            reagent.ProjectName=query.value(2).toString();
            reagent.ManufacturerId=query.value(3).toString();
            reagent.CountryId=query.value(4).toString();
            reagent.CreateTime=query.value(5).toString();
            reagent.CountryName=query.value(6).toString();
            reagent.ManufacturerName=query.value(7).toString();
            list.append(reagent);
        }
    }
    return list;
}


QVector<Reagent> ReagentService::GetReagentsByManufacturerId(QString ManufacturerId)
{

    QVector<Reagent> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select reagent.ReagentId,ReagentName,ProjectName,reagent.ManufacturerId,reagent.CountryId,CreateTime,"
                                  " CountryName,ManufacturerName "
                                  "from reagent "
                                  "inner join Manufacturer on reagent.ManufacturerId=Manufacturer.ManufacturerId "
                                  "inner join Country on reagent.CountryId=Country.CountryId "
                                  "where reagent.ManufacturerId = :ManufacturerId order by ManufacturerName desc"));
        query.bindValue(":ManufacturerId", ManufacturerId);
        query.exec();

        while(query.next())
        {
            Reagent reagent;
            reagent.ReagentId=query.value(0).toString();
            reagent.ReagentName=query.value(1).toString();
            reagent.ProjectName=query.value(2).toString();
            reagent.ManufacturerId=query.value(3).toString();
            reagent.CountryId=query.value(4).toString();
            reagent.CreateTime=query.value(5).toString();
            reagent.CountryName=query.value(6).toString();
            reagent.ManufacturerName=query.value(7).toString();
            list.append(reagent);
        }
    }
    return list;
}

QString ReagentService::Insert(Reagent reagent)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into reagent (ReagentId,ReagentName,ProjectName,ManufacturerId,CountryId,CreateTime,status,IfDefault) values (:ReagentId,:ReagentName,:ProjectName,:ManufacturerId,:CountryId,:CreateTime,:status,0)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":ReagentId", guid);
        query.bindValue(":ReagentName", reagent.ReagentName);
        query.bindValue(":ProjectName", reagent.ProjectName);
        query.bindValue(":ManufacturerId", reagent.ManufacturerId);
        query.bindValue(":CountryId", reagent.CountryId);
        query.bindValue(":CreateTime", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":status", "1");
        query.exec();


        return guid;
    }
    return "";
}

void ReagentService::Update(Reagent reagent)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update reagent set ReagentName =:ReagentName,ProjectName=:ProjectName,ManufacturerId=:ManufacturerId,CountryId=:CountryId where ReagentId=:ReagentId");

        query.bindValue(":ReagentName", reagent.ReagentName);
        query.bindValue(":ProjectName", reagent.ProjectName);
        query.bindValue(":ManufacturerId", reagent.ManufacturerId);
        query.bindValue(":CountryId", reagent.CountryId);
        query.bindValue(":ReagentId", reagent.ReagentId);
        query.exec();

    }
}

void ReagentService::DeleteById(QString ReagentId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from reagent where ReagentId =:ReagentId");
        query.bindValue(":ReagentId", ReagentId);
        query.exec();
    }
}


void ReagentService::UpdateTestType(Reagent reagent)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from TestType_Reagent where ReagentId = :ReagentId");
        query.bindValue(":ReagentId", reagent.ReagentId);
        query.exec();

        TestType t;
        query.prepare("insert into TestType_Reagent (ReagentId,TestTypeId) values (:ReagentId,:TestTypeId)");

        QVariantList ReagentIdList;
        QVariantList TestTypeIdList;

        for(int i=0; i<reagent.types.count();i++)
        {
            t = reagent.types[i];

            ReagentIdList<<reagent.ReagentId;
            TestTypeIdList<<t.TestTypeId;

        }
        query.addBindValue(ReagentIdList);
        query.addBindValue(TestTypeIdList);

        query.execBatch();
    }
}


