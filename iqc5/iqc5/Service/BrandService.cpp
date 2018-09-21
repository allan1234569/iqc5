#include "BrandService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QUuid>
#include <QRegularExpression>

BrandService::BrandService()
{
}

Brand BrandService::GetById(QString BrandId)
{

    Brand brand;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select BrandId,BrandName from brand where brand.BrandId = :BrandId order by BrandId desc ");
        query.bindValue(":BrandId", BrandId);
        query.exec();

        while(query.next())
        {
            brand.BrandId=query.value(0).toString();
            brand.BrandName=query.value(1).toString();

            return brand;
        }
    }
    return brand;
}

QVector<Brand> BrandService::GetBrands(QString name)
{
    QVector<Brand> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select BrandId,BrandName from brand "
                                          " where BrandName like :BrandName "
                                          " order by BrandName "));
        query.bindValue(":BrandName", QString("%%1%").arg(name));
        query.exec();
        while(query.next())
        {
            Brand brand;
            brand.BrandId=query.value(0).toString();
            brand.BrandName= query.value(1).toString();

            list.append(brand);
        }
    }
    return list;
}

QString BrandService::Insert(Brand brand)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into brand (BrandId,BrandName,Status) values (:BrandId,:BrandName,:Status)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":BrandId", guid);
        query.bindValue(":BrandName", brand.BrandName);
        query.bindValue(":Status", "1");
        query.exec();

        brand.BrandId = guid;

        return guid;
    }
    return "";
}

void BrandService::Update(Brand brand)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update brand set BrandName =:BrandName where BrandId=:BrandId");

        query.bindValue(":BrandName", brand.BrandName);
        query.bindValue(":BrandId", brand.BrandId);
        query.exec();
    }
}

void BrandService::DeleteById(QString BrandId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from brand where BrandId =:BrandId");
        query.bindValue(":BrandId", BrandId);
        query.exec();
    }
}

