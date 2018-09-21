#include "MethodService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QUuid>
#include <QRegularExpression>

MethodService::MethodService()
{
}

Method MethodService::GetById(QString MethodId)
{

    Method method;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select Method.MethodId,Method.MethodName,TestType.CategoryId,Category.CategoryName CategoryName,subject.CategoryId SubjectId,subject.CategoryName SubjectName from Method "
                      " left join TestType_Method on Method.MethodId=TestType_Method.MethodId "
                      " left join TestType on TestType.TestTypeId=TestType_Method.TestTypeId "
                      " left join Category on TestType.CategoryId=Category.CategoryId "
                      " left join category subject on category.ParentId=subject.CategoryId "
                      " where Method.MethodId = :MethodId ");
        query.bindValue(":MethodId", MethodId);
        query.exec();

        while(query.next())
        {
            method.MethodId=query.value(0).toString();
            method.MethodName=query.value(1).toString();
            method.CategoryId=query.value(2).toString();
            method.CategoryName=query.value(3).toString();
            method.SubjectId=query.value(4).toString();
            method.SubjectName=query.value(5).toString();


            return method;
        }
    }
    return method;
}


QVector<Method> MethodService::GetByCategoryId(QString categoryId)
{
    QVector<Method> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(" select Method.MethodId,Method.MethodName, TestType.CategoryId,Category.CategoryName CategoryName  from Method "
                      " inner join TestType_Method on Method.MethodId=TestType_Method.MethodId "
                      " inner join TestType on TestType.TestTypeId=TestType_Method.TestTypeId "
                      " inner join Category on TestType.CategoryId=Category.CategoryId "
                      " where TestType.CategoryId = :categoryId "
                      " order by Method.MethodId desc ");
        query.bindValue(":categoryId", categoryId);
        query.exec();

        while(query.next())
        {
            Method method;
            method.MethodId=query.value(0).toString();
            method.MethodName=query.value(1).toString();

            list.append(method);
        }
    }
    return list;
}

QVector<Method> MethodService::GetByTestTypeId(QString testTypeId)
{
    QVector<Method> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(" select Method.MethodId,Method.MethodName, TestType.CategoryId,Category.CategoryName CategoryName  from Method "
                      " inner join TestType_Method on Method.MethodId=TestType_Method.MethodId "
                      " inner join TestType on TestType.TestTypeId=TestType_Method.TestTypeId "
                      " inner join Category on TestType.CategoryId=Category.CategoryId "
                      " where TestType.testTypeId = :testTypeId "
                      " order by Method.MethodId desc ");
        query.bindValue(":testTypeId", testTypeId);
        query.exec();

        while(query.next())
        {
            Method method;
            method.MethodId=query.value(0).toString();
            method.MethodName=query.value(1).toString();

            list.append(method);
        }
    }
    return list;
}

QVector<Method> MethodService::GetMethods(QString subjectId,QString categoryId, QString name,int if_user_first)
{
    QVector<Method> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        QString sql = " select Method.MethodId,Method.MethodName, TestType.CategoryId,Category.CategoryName CategoryName,subject.CategoryName SubjectName  from Method "
                      " left join TestType_Method on Method.MethodId=TestType_Method.MethodId "
                      " left join TestType on TestType.TestTypeId=TestType_Method.TestTypeId "
                      " left join Category on TestType.CategoryId=Category.CategoryId "
                      " left join category subject on category.ParentId=subject.CategoryId "
                      " where Method.MethodName like :name "
                      " and ifnull(subject.CategoryId,'') like :subjectId "
                      " and ifnull(TestType.CategoryId,'') like :categoryId "
                      " order by subject.CategoryName,Category.CategoryName,Method.MethodName ";

        if(if_user_first)
        {
            sql = sql.replace("order by", "order by Method.ifDefault, ");
        }
        query.prepare(sql);

        query.bindValue(":subjectId",  QString("%%1%").arg(subjectId));
        query.bindValue(":categoryId",  QString("%%1%").arg(categoryId));
        query.bindValue(":name", QString("%%1%").arg(name));
        query.exec();

        while(query.next())
        {
            Method method;
            method.MethodId=query.value(0).toString();
            method.MethodName=query.value(1).toString();
            method.CategoryName=query.value(3).toString();
            method.SubjectName=query.value(4).toString();


            list.append(method);
        }
    }
    return list;
}

QVector<Method> MethodService::GetMethods()
{
    QVector<Method> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select Method.MethodId,Method.MethodName from Method "
                      " order by Method.MethodId desc ");
        query.exec();

        while(query.next())
        {
            Method method;
            method.MethodId=query.value(0).toString();
            method.MethodName=query.value(1).toString();

            list.append(method);
        }
    }
    return list;
}

void MethodService::Insert(Method method)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into Method (MethodId,MethodName) values (:MethodId,:MethodName)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":MethodId", guid);
        query.bindValue(":MethodName", method.MethodName);
        query.exec();

    }
}

void MethodService::Update(Method method)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update Method set MethodName=:MethodName where MethodId=:MethodId");
        query.bindValue(":MethodName", method.MethodName);
        query.bindValue(":MethodId", method.MethodId);
        query.exec();
    }
}

void MethodService::DeleteById(QString MethodId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from Method where MethodId =:MethodId");
        query.bindValue(":MethodId", MethodId);
        query.exec();
    }
}


void MethodService::UpdateTestType(Method method)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from TestType_Method where MethodId = :MethodId");
        query.bindValue(":MethodId", method.MethodId);
        query.exec();

        TestType t;
        query.prepare("insert into TestType_Method (MethodId,TestTypeId) values (:MethodId,:TestTypeId)");

        QVariantList MethodIdList;
        QVariantList TestTypeIdList;

        for(int i=0; i<method.types.count();i++)
        {
            t = method.types[i];

            MethodIdList<<method.MethodId;
            TestTypeIdList<<t.TestTypeId;

        }
        query.addBindValue(MethodIdList);
        query.addBindValue(TestTypeIdList);

        query.execBatch();
    }
}

