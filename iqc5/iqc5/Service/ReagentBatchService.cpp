#include "ReagentBatchService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QUuid>
#include <QRegularExpression>
#include <QDateTime>

ReagentBatchService::ReagentBatchService()
{

}

ReagentBatch ReagentBatchService::GetById(QString ReagentBatchId)
{

    ReagentBatch reagent;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select ReagentBatchId,ReagentId,Unit,package,RegisterNo,BatchNo,ValidDate,StartDate from reagentBatch where ReagentBatchId = :ReagentBatchId order by ReagentBatchId desc ");
        query.bindValue(":ReagentBatchId", ReagentBatchId);
        query.exec();

        while(query.next())
        {
            reagent.ReagentBatchId=query.value(0).toString();
            reagent.ReagentId=query.value(1).toString();
            reagent.Unit=query.value(2).toString();
            reagent.package=query.value(3).toString();
            reagent.RegisterNo=query.value(4).toString();
            reagent.BatchNo=query.value(5).toString();
            reagent.ValidDate=query.value(6).toString();
            reagent.StartDate=query.value(7).toString();

            return reagent;
        }
    }
    return reagent;
}

QVector<ReagentBatch> ReagentBatchService::GetReagentBatchs(QString ReagentId, QString name)
{
    QVector<ReagentBatch> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select ReagentBatchId,reagentBatch.ReagentId,Unit,package,RegisterNo,reagentBatch.BatchNo,ValidDate,a.StartDate from reagentBatch "
                      "left join (select project_Detail.ReagentId,batchno,min(testTime) startDate from result "
                      "inner join project_Detail on  result.project_DetailId=project_Detail.project_DetailId "
                      "inner join reagentBatch on project_Detail.ReagentBatchId=reagentBatch.ReagentBatchId "
                      "group by  project_Detail.ReagentId,batchno) a "
                      "on reagentBatch.batchno=a.batchno and reagentBatch.ReagentId=a.ReagentId "
                      "where reagentBatch.ReagentId = :ReagentId and reagentBatch.BatchNo like :BatchNo order by ReagentBatch.CreateTime ");
        query.bindValue(":ReagentId", ReagentId);
        query.bindValue(":BatchNo", QString("%%1%").arg(name));
        query.exec();
        while(query.next())
        {
            ReagentBatch reagent;
            reagent.ReagentBatchId=query.value(0).toString();
            reagent.ReagentId=query.value(1).toString();
            reagent.Unit=query.value(2).toString();
            reagent.package=query.value(3).toString();
            reagent.RegisterNo=query.value(4).toString();
            reagent.BatchNo=query.value(5).toString();
            reagent.ValidDate=query.value(6).toString();
            reagent.StartDate=query.value(7).toString();
            list.append(reagent);
        }
    }
    return list;
}

QString ReagentBatchService::Insert(ReagentBatch reagent)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into reagentBatch (ReagentBatchId,ReagentId,Unit,package,RegisterNo,BatchNo,ValidDate,StartDate,CreateTime,Status) values (:ReagentBatchId,:ReagentId,:Unit,:package,:RegisterNo,:BatchNo,:ValidDate,:StartDate,:CreateTime,:Status)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":ReagentBatchId", guid);
        query.bindValue(":ReagentId", reagent.ReagentId);
        query.bindValue(":Unit", reagent.Unit);
        query.bindValue(":package", reagent.package);
        query.bindValue(":RegisterNo", reagent.RegisterNo);
        query.bindValue(":BatchNo", reagent.BatchNo);
        query.bindValue(":ValidDate", reagent.ValidDate);
        query.bindValue(":StartDate", reagent.StartDate);
        query.bindValue(":CreateTime", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":Status", "1");
        query.exec();

        return guid;
    }
    return "";
}

void ReagentBatchService::Update(ReagentBatch reagent)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update reagentBatch set ReagentId =:ReagentId,Unit=:Unit,package=:package,RegisterNo=:RegisterNo,BatchNo=:BatchNo,ValidDate=:ValidDate,StartDate=:StartDate where ReagentBatchId=:ReagentBatchId");

        query.bindValue(":ReagentId", reagent.ReagentId);
        query.bindValue(":Unit", reagent.Unit);
        query.bindValue(":package", reagent.package);
        query.bindValue(":RegisterNo", reagent.RegisterNo);
        query.bindValue(":BatchNo", reagent.BatchNo);
        query.bindValue(":ValidDate", reagent.ValidDate);
        query.bindValue(":StartDate", reagent.StartDate);
        query.bindValue(":ReagentBatchId", reagent.ReagentBatchId);
        query.exec();

    }
}

void ReagentBatchService::DeleteById(QString ReagentBatchId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from reagentBatch where ReagentBatchId =:ReagentBatchId");
        query.bindValue(":ReagentBatchId", ReagentBatchId);
        query.exec();
    }
}

