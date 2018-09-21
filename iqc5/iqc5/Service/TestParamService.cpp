#include "TestParamService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QUuid>
#include <QRegularExpression>

TestParamService::TestParamService()
{
}

TestParam TestParamService::GetById(QString TestParamId)
{

    TestParam testParam;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(" select TestParam.TestParamId,TestParam.TestTypeId,TestParam.StandardId,CV,Bias,TEa,Unit,TestType.CategoryId,Category.ParentId SubjectId, "
                      " TestType.TestTypeName,StandardName from TestParam "
                      " inner join TestType on  TestParam.TestTypeId=TestType.TestTypeId "
                      " inner join Standard on  TestParam.StandardId=Standard.StandardId "
                      " inner join Category on  TestType.CategoryId=Category.CategoryId "
                      " where TestParam.TestParamId = :TestParamId ");
        query.bindValue(":TestParamId", TestParamId);
        query.exec();

        while(query.next())
        {
            testParam.TestParamId=query.value(0).toString();
            testParam.TestTypeId=query.value(1).toString();
            testParam.StandardId=query.value(2).toString();
            testParam.CV=query.value(3).toDouble();
            testParam.Bias=query.value(4).toDouble();
            testParam.TEa=query.value(5).toDouble();
            testParam.unit=query.value(6).toString();
            testParam.CategoryId=query.value(7).toString();
            testParam.SubjectId=query.value(8).toString();
            testParam.TestTypeName=query.value(9).toString();
            testParam.StandardName=query.value(10).toString();

            return testParam;
        }
    }
    return testParam;
}

TestParam TestParamService::GetByTestTypeAndStandard(QString testTypeId, QString standardId)
{

    TestParam testParam;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select TestParam.TestParamId,TestParam.TestTypeId,TestParam.StandardId,CV,Bias,TEa,Unit,TestType.CategoryId,Category.ParentId SubjectId, "
                      " TestType.TestTypeName,StandardName from TestParam "
                      " inner join TestType on  TestParam.TestTypeId=TestType.TestTypeId "
                      " inner join Standard on  TestParam.StandardId=Standard.StandardId "
                      " inner join Category on  TestType.CategoryId=Category.CategoryId "
                      " where TestParam.TestTypeId = :TestTypeId  and TestParam.StandardId = :StandardId ");
        query.bindValue(":TestTypeId", testTypeId);
        query.bindValue(":StandardId", standardId);
        query.exec();

        while(query.next())
        {
            testParam.TestParamId=query.value(0).toString();
            testParam.TestTypeId=query.value(1).toString();
            testParam.StandardId=query.value(2).toString();
            testParam.CV=query.value(3).toDouble();
            testParam.Bias=query.value(4).toDouble();
            testParam.TEa=query.value(5).toDouble();
            testParam.unit=query.value(6).toString();
            testParam.CategoryId=query.value(7).toString();
            testParam.SubjectId=query.value(8).toString();
            testParam.TestTypeName=query.value(9).toString();
            testParam.StandardName=query.value(10).toString();


            return testParam;
        }
    }
    return testParam;
}

QVector<TestParam> TestParamService::GetAll(QString categoryId, QString name, QString standId)
{
    QVector<TestParam> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select TestParam.TestParamId,TestParam.TestTypeId,TestParam.StandardId,CV,Bias,TEa,Unit,TestType.CategoryId,Category.ParentId SubjectId, "
                      " TestType.TestTypeName,StandardName from TestParam "
                      " inner join TestType on  TestParam.TestTypeId=TestType.TestTypeId "
                      " inner join Standard on  TestParam.StandardId=Standard.StandardId "
                      " inner join Category on  TestType.CategoryId=Category.CategoryId "
                      " where category.CategoryId=:categoryId and TestType.TestTypeName like :name and Standard.StandardId=:standId "
                      " order by TestParam.TestParamId ");
        query.bindValue(":categoryId", categoryId);
        query.bindValue(":name", QString("%%1%").arg(name));
        query.bindValue(":standId", standId);
        query.exec();
        while(query.next())
        {
            TestParam testParam;
            testParam.TestParamId=query.value(0).toString();
            testParam.TestTypeId=query.value(1).toString();
            testParam.StandardId=query.value(2).toString();
            testParam.CV=query.value(3).toDouble();
            testParam.Bias=query.value(4).toDouble();
            testParam.TEa=query.value(5).toDouble();
            testParam.unit=query.value(6).toString();
            testParam.CategoryId=query.value(7).toString();
            testParam.SubjectId=query.value(8).toString();
            testParam.TestTypeName=query.value(9).toString();
            testParam.StandardName=query.value(10).toString();

            list.append(testParam);
        }
    }
    return list;
}

QVector<TestParam> TestParamService::GetAll()
{
    QVector<TestParam> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select TestParam.TestParamId,TestParam.TestTypeId,TestParam.StandardId,CV,Bias,TEa,Unit,TestType.CategoryId,Category.ParentId SubjectId, "
                      " TestType.TestTypeName,StandardName from TestParam "
                      " inner join TestType on  TestParam.TestTypeId=TestType.TestTypeId "
                      " inner join Standard on  TestParam.StandardId=Standard.StandardId "
                      " inner join Category on  TestType.CategoryId=Category.CategoryId "
                      " order by TestParam.TestParamId ");
        query.exec();
        while(query.next())
        {
            TestParam testParam;
            testParam.TestParamId=query.value(0).toString();
            testParam.TestTypeId=query.value(1).toString();
            testParam.StandardId=query.value(2).toString();
            testParam.CV=query.value(3).toDouble();
            testParam.Bias=query.value(4).toDouble();
            testParam.TEa=query.value(5).toDouble();
            testParam.unit=query.value(6).toString();
            testParam.CategoryId=query.value(7).toString();
            testParam.SubjectId=query.value(8).toString();
            testParam.TestTypeName=query.value(9).toString();
            testParam.StandardName=query.value(10).toString();

            list.append(testParam);
        }
    }
    return list;
}

QVector<Standard> TestParamService::GetStandard(QString testTypeId)
{
    QVector<Standard> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select distinct Standard.StandardId,Standard.StandardName from TestParam "
                      " inner join Standard on TestParam.StandardId=Standard.StandardId "
                      " where testTypeId = :testTypeId "
                      " order by Standard.StandardId ");
        query.bindValue(":testTypeId", testTypeId);
        query.exec();

        while(query.next())
        {
            Standard standard;
            standard.StandardId=query.value(0).toString();
            standard.StandardName=query.value(1).toString();

            list.append(standard);
        }
    }
    return list;
}

QVector<Standard> TestParamService::GetAllStandard()
{
    QVector<Standard> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select Standard.StandardId,Standard.StandardName from Standard "
                      "order by Standard.StandardId ");
        query.exec();

        while(query.next())
        {
            Standard standard;
            standard.StandardId=query.value(0).toString();
            standard.StandardName=query.value(1).toString();

            list.append(standard);
        }
    }
    return list;
}


void TestParamService::Insert(TestParam testParam)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into TestParam (TestParamId,TestTypeId,StandardId,CV,Bias,TEa,unit) values (:TestParamId,:TestTypeId,:StandardId,:CV,:Bias,:TEa,:unit)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":TestParamId", guid);
        query.bindValue(":TestTypeId", testParam.TestTypeId);
        query.bindValue(":StandardId", testParam.StandardId);
        query.bindValue(":CV", testParam.CV);
        query.bindValue(":Bias", testParam.Bias);
        query.bindValue(":TEa", testParam.TEa);
        query.bindValue(":unit", testParam.unit);
        query.exec();

        testParam.TestParamId = guid;

    }
}

void TestParamService::Update(TestParam testParam)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update TestParam set TestTypeId=:TestTypeId,StandardId=:StandardId,CV=:CV,Bias=:Bias,TEa=:TEa,unit=:unit where TestParamId=:TestParamId");

        query.bindValue(":TestTypeId", testParam.TestTypeId);
        query.bindValue(":StandardId", testParam.StandardId);
        query.bindValue(":CV", testParam.CV);
        query.bindValue(":Bias", testParam.Bias);
        query.bindValue(":TEa", testParam.TEa);
        query.bindValue(":unit", testParam.unit);
        query.bindValue(":TestParamId", testParam.TestParamId);
        query.exec();

    }
}

void TestParamService::DeleteById(QString TestParamId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from TestParam where TestParamId =:TestParamId");
        query.bindValue(":TestParamId", TestParamId);
        query.exec();
    }
}

