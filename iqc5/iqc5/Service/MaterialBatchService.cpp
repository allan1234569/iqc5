#include "MaterialBatchService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QUuid>
#include <QRegularExpression>
#include <QDateTime>

MaterialBatchService::MaterialBatchService()
{

}

MaterialBatch MaterialBatchService::GetById(QString MaterialBatchId)
{

    MaterialBatch material;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select MaterialBatchId,MaterialId,Unit,package,RegisterNo,BatchNo,ValidDate,StartDate from materialBatch where MaterialBatchId = :MaterialBatchId order by MaterialBatchId desc ");
        query.bindValue(":MaterialBatchId", MaterialBatchId);
        query.exec();

        while(query.next())
        {
            material.MaterialBatchId=query.value(0).toString();
            material.MaterialId=query.value(1).toString();
            material.Unit=query.value(2).toString();
            material.package=query.value(3).toString();
            material.RegisterNo=query.value(4).toString();
            material.BatchNo=query.value(5).toString();
            material.ValidDate=query.value(6).toString();
            material.StartDate=query.value(7).toString();

            return material;
        }
    }
    return material;
}

QVector<MaterialBatch> MaterialBatchService::GetMaterialBatchs(QString MaterialId, QString name)
{
    QVector<MaterialBatch> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select MaterialBatchId,materialBatch.MaterialId,Unit,package,RegisterNo,materialBatch.BatchNo,ValidDate,a.StartDate from materialBatch "
                      "left join (select project_Detail.MaterialId,batchno,min(testTime) startDate from result "
                      "inner join project_Detail on  result.project_DetailId=project_Detail.project_DetailId "
                      "inner join materialbatch on project_Detail.materialbatchId=materialbatch.materialbatchId "
                      "group by  project_Detail.MaterialId,batchno) a "
                      "on MaterialBatch.batchno=a.batchno and MaterialBatch.MaterialId=a.MaterialId "
                      "where materialBatch.MaterialId = :MaterialId and materialBatch.BatchNo like :BatchNo order by MaterialBatch.CreateTime ");
        query.bindValue(":MaterialId", MaterialId);
        query.bindValue(":BatchNo", QString("%%1%").arg(name));
        query.exec();
        while(query.next())
        {
            MaterialBatch material;
            material.MaterialBatchId=query.value(0).toString();
            material.MaterialId=query.value(1).toString();
            material.Unit=query.value(2).toString();
            material.package=query.value(3).toString();
            material.RegisterNo=query.value(4).toString();
            material.BatchNo=query.value(5).toString();
            material.ValidDate=query.value(6).toString();
            material.StartDate=query.value(7).toString();
            list.append(material);
        }
    }
    return list;
}

QVector<MaterialBatch> MaterialBatchService::GetMaterialBatchs()
{
    QVector<MaterialBatch> list;
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    QSqlQuery query;
    if(db.open())
        query.exec(QString("SELECT BatchNo FROM MaterialBatch"));

    while(query.next())
    {
        MaterialBatch material;
        material.BatchNo=query.value(0).toString();
        list.append(material);
    }
    return list;
}

QString MaterialBatchService::Insert(MaterialBatch material)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into materialBatch (MaterialBatchId,MaterialId,Unit,package,RegisterNo,BatchNo,ValidDate,StartDate,CreateTime,Status) values (:MaterialBatchId,:MaterialId,:Unit,:package,:RegisterNo,:BatchNo,:ValidDate,:StartDate,:CreateTime,:Status)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":MaterialBatchId", guid);
        query.bindValue(":MaterialId", material.MaterialId);
        query.bindValue(":Unit", material.Unit);
        query.bindValue(":package", material.package);
        query.bindValue(":RegisterNo", material.RegisterNo);
        query.bindValue(":BatchNo", material.BatchNo);
        query.bindValue(":ValidDate", material.ValidDate);
        query.bindValue(":StartDate", material.StartDate);
        query.bindValue(":CreateTime", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":Status", "1");
        query.exec();

        return guid;
    }
    return "";
}

void MaterialBatchService::Update(MaterialBatch material)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update materialBatch set MaterialId =:MaterialId,Unit=:Unit,package=:package,RegisterNo=:RegisterNo,BatchNo=:BatchNo,ValidDate=:ValidDate,StartDate=:StartDate where MaterialBatchId=:MaterialBatchId");

        query.bindValue(":MaterialId", material.MaterialId);
        query.bindValue(":Unit", material.Unit);
        query.bindValue(":package", material.package);
        query.bindValue(":RegisterNo", material.RegisterNo);
        query.bindValue(":BatchNo", material.BatchNo);
        query.bindValue(":ValidDate", material.ValidDate);
        query.bindValue(":StartDate", material.StartDate);
        query.bindValue(":MaterialBatchId", material.MaterialBatchId);
        query.exec();

    }
}

void MaterialBatchService::DeleteById(QString MaterialBatchId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from materialBatch where MaterialBatchId =:MaterialBatchId");
        query.bindValue(":MaterialBatchId", MaterialBatchId);
        query.exec();
    }
}

