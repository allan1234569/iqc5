#include "CountryService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QUuid>
#include <QRegularExpression>

CountryService::CountryService()
{
}

Country CountryService::GetById(QString CountryId)
{

    Country country;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select CountryId,CountryName from country where country.CountryId = :CountryId order by CountryId desc ");
        query.bindValue(":CountryId", CountryId);
        query.exec();

        while(query.next())
        {
            country.CountryId=query.value(0).toString();
            country.CountryName=query.value(1).toString();

            return country;
        }
    }
    return country;
}

QVector<Country> CountryService::GetCountrys(QString name)
{
    QVector<Country> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select CountryId,CountryName from country "
                                          " where CountryName like :CountryName "
                                          " order by CountryName "));
        query.bindValue(":CountryName", QString("%%1%").arg(name));
        query.exec();
        while(query.next())
        {
            Country country;
            country.CountryId=query.value(0).toString();
            country.CountryName= query.value(1).toString();

            list.append(country);
        }
    }
    return list;
}

QString CountryService::Insert(Country country)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into country (CountryId,CountryName) values (:CountryId,:CountryName)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":CountryId", guid);
        query.bindValue(":CountryName", country.CountryName);
        query.exec();

        country.CountryId = guid;

        return guid;
    }
    return "";

}

void CountryService::Update(Country country)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update country set CountryName =:CountryName where CountryId=:CountryId");

        query.bindValue(":CountryName", country.CountryName);
        query.bindValue(":CountryId", country.CountryId);
        query.exec();
    }
}

void CountryService::DeleteById(QString CountryId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from country where CountryId =:CountryId");
        query.bindValue(":CountryId", CountryId);
        query.exec();
    }
}

