#include "ManufacturerService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QUuid>
#include <QRegularExpression>

ManufacturerService::ManufacturerService()
{
}

Manufacturer ManufacturerService::GetById(QString ManufacturerId)
{

    Manufacturer manufacturer;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select ManufacturerId,ManufacturerName from manufacturer where manufacturer.ManufacturerId = :ManufacturerId order by ManufacturerId desc ");
        query.bindValue(":ManufacturerId", ManufacturerId);
        query.exec();

        while(query.next())
        {
            manufacturer.ManufacturerId=query.value(0).toString();
            manufacturer.ManufacturerName=query.value(1).toString();

            return manufacturer;
        }
    }
    return manufacturer;
}

QVector<Manufacturer> ManufacturerService::GetManufacturers(QString name)
{
    QVector<Manufacturer> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select ManufacturerId,ManufacturerName from manufacturer "
                                          " where ManufacturerName like :ManufacturerName "
                                          " order by ManufacturerName "));
        query.bindValue(":ManufacturerName", QString("%%1%").arg(name));
        query.exec();
        while(query.next())
        {
            Manufacturer manufacturer;
            manufacturer.ManufacturerId=query.value(0).toString();
            manufacturer.ManufacturerName= query.value(1).toString();

            list.append(manufacturer);
        }
    }
    return list;
}

QString ManufacturerService::Insert(Manufacturer manufacturer)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into manufacturer (ManufacturerId,ManufacturerName,Status) values (:ManufacturerId,:ManufacturerName,:Status)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":ManufacturerId", guid);
        query.bindValue(":ManufacturerName", manufacturer.ManufacturerName);
        query.bindValue(":Status", "1");
        query.exec();

        manufacturer.ManufacturerId = guid;
        return guid;
    }
    return "";

}

void ManufacturerService::Update(Manufacturer manufacturer)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update manufacturer set ManufacturerName =:ManufacturerName where ManufacturerId=:ManufacturerId");

        query.bindValue(":ManufacturerName", manufacturer.ManufacturerName);
        query.bindValue(":ManufacturerId", manufacturer.ManufacturerId);
        query.exec();
    }
}

void ManufacturerService::DeleteById(QString ManufacturerId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from manufacturer where ManufacturerId =:ManufacturerId");
        query.bindValue(":ManufacturerId", ManufacturerId);
        query.exec();
    }
}

QVector<Country> ManufacturerService::GetCountries()
{
    QVector<Country> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select CountryId,CountryName from Country "
                                          " order by CountryName "));
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
Country ManufacturerService::GetCountryByName(QString name)
{
    Country c;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select CountryId,CountryName from Country where CountryName like :name  ");
        query.bindValue(":name",  "%" + name + "%");
        query.exec();

        while(query.next())
        {
            c.CountryId=query.value(0).toString();
            c.CountryName=query.value(1).toString();

            return c;
        }
    }
    return c;
}
