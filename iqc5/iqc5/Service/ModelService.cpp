#include "ModelService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QUuid>
#include <QRegularExpression>

ModelService::ModelService()
{
}

Model ModelService::GetById(QString ModelId)
{

    Model model;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select ModelId,ModelName from model where model.ModelId = :ModelId order by ModelId desc ");
        query.bindValue(":ModelId", ModelId);
        query.exec();

        while(query.next())
        {
            model.ModelId=query.value(0).toString();
            model.ModelName=query.value(1).toString();

            return model;
        }
    }
    return model;
}

QVector<Model> ModelService::GetByBrandId(QString BrandId)
{
    QVector<Model> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select ModelId,ModelName,model.BrandId,BrandName from model "
                                  " inner join Brand on model.BrandId=Brand.BrandId "
                                          " where model.BrandId = :BrandId "
                                          " order by ModelName "));
        query.bindValue(":BrandId", BrandId);

        query.exec();
        while(query.next())
        {
            Model model;
            model.ModelId=query.value(0).toString();
            model.ModelName= query.value(1).toString();
            model.BrandId= query.value(2).toString();
            model.BrandName= query.value(3).toString();

            list.append(model);
        }

    }
    return list;
}

QVector<Model> ModelService::GetModels(QString name)
{
    QVector<Model> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select ModelId,ModelName,model.BrandId,BrandName from model "
                                  " inner join Brand on model.BrandId=Brand.BrandId "
                                          " where ModelName like :ModelName "
                                          " order by ModelName "));
        query.bindValue(":ModelName", QString("%%1%").arg(name));
        query.exec();
        while(query.next())
        {
            Model model;
            model.ModelId=query.value(0).toString();
            model.ModelName= query.value(1).toString();
            model.BrandId=query.value(2).toString();
            model.BrandName= query.value(3).toString();

            list.append(model);
        }
    }
    return list;
}

QString ModelService::Insert(Model model)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into model (ModelId,BrandId,ModelName,Status) values (:ModelId,:BrandId,:ModelName,:Status)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":ModelId", guid);
        query.bindValue(":BrandId", model.BrandId);
        query.bindValue(":ModelName", model.ModelName);
        query.bindValue(":Status", "1");
        query.exec();

        model.ModelId = guid;

        return guid;
    }
    return "";

}

void ModelService::Update(Model model)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update model set BrandId=:BrandId,ModelName =:ModelName where ModelId=:ModelId");

        query.bindValue(":BrandId", model.BrandId);
        query.bindValue(":ModelName", model.ModelName);
        query.bindValue(":ModelId", model.ModelId);
        query.exec();
    }
}

void ModelService::DeleteById(QString ModelId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from model where ModelId =:ModelId");
        query.bindValue(":ModelId", ModelId);
        query.exec();
    }
}

