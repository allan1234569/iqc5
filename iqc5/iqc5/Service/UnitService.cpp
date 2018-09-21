#include "UnitService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QUuid>
#include <QRegularExpression>

UnitService::UnitService()
{
}

Unit UnitService::GetById(QString UnitId)
{

    Unit unit;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select UnitId,UnitName from unit where unit.UnitId = :UnitId order by UnitId desc ");
        query.bindValue(":UnitId", UnitId);
        query.exec();

        while(query.next())
        {
            unit.UNITID=query.value(0).toString();
            unit.UNITNAME= query.value(1).toString();

            return unit;
        }
    }
    return unit;
}

QVector<Unit> UnitService::GetByParentId(QString ParentId)
{
    QVector<Unit> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select UnitId,UnitName,unit.ParentId,BrandName from unit "
                                          " where unit.ParentId = :ParentId "
                                          " order by UnitName "));
        query.bindValue(":ParentId", ParentId);

        query.exec();
        while(query.next())
        {
            Unit unit;
            unit.UNITID=query.value(0).toString();
            unit.UNITNAME= query.value(1).toString();

            list.append(unit);
        }

    }
    return list;
}

QVector<Unit> UnitService::GetUnits(QString name)
{
    QVector<Unit> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select UnitId,UnitName,unit.ParentId,BrandName from unit "
                                          " where UnitName like :UnitName "
                                          " order by UnitName "));
        query.bindValue(":UnitName", QString("%%1%").arg(name));
        query.exec();
        while(query.next())
        {
            Unit unit;
            unit.UNITID=query.value(0).toString();
            unit.UNITNAME= query.value(1).toString();

            list.append(unit);
        }
    }
    return list;
}

void UnitService::Insert(Unit unit)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into unit (UnitId,ParentId,UnitName,Status) values (:UnitId,:ParentId,:UnitName,:Status)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":UnitId", guid);
        query.bindValue(":ParentId", unit.ParentId);
        query.bindValue(":UnitName", unit.UNITNAME);
        query.bindValue(":UnitId", unit.UNITID);
        query.bindValue(":Status", "1");
        query.exec();

        unit.UNITID = guid;
    }

}

void UnitService::Update(Unit unit)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update unit set ParentId=:ParentId,UnitName =:UnitName where UnitId=:UnitId");

        query.bindValue(":ParentId", unit.ParentId);
        query.bindValue(":UnitName", unit.UNITNAME);
        query.bindValue(":UnitId", unit.UNITID);
        query.exec();
    }
}

void UnitService::DeleteById(QString UnitId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from unit where UnitId =:UnitId");
        query.bindValue(":UnitId", UnitId);
        query.exec();
    }
}
