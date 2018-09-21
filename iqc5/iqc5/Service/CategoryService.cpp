#include "CategoryService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>

CategoryService::CategoryService()
{
}

QVector<Category> CategoryService::GetCategories()
{
    QVector<Category> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.exec(QObject::tr("select CategoryId,CategoryName from Category where parentId ='' order by CategoryName  "));
        while(query.next())
        {
            Category c;
            c.CategoryId=query.value(0).toString();
            c.CategoryName=query.value(1).toString();
            list.append(c);
        }
    }
    return list;
}

QVector<Category> CategoryService::GetCategories(QString parentId)
{
    QVector<Category> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(QObject::tr("select CategoryId,CategoryName from Category where parentId =:parentId and parentId <> '' order by CategoryName  "));
        query.bindValue(":parentId", parentId);
        query.exec();
        while(query.next())
        {
            Category c;
            c.CategoryId=query.value(0).toString();
            c.CategoryName=query.value(1).toString();
            list.append(c);
        }
    }
    return list;
}
