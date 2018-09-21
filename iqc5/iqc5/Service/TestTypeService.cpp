#include "TestTypeService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QUuid>
#include <QRegularExpression>

TestTypeService::TestTypeService()
{
}

TestType TestTypeService::GetById(QString TestTypeId)
{

    TestType testType;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(" select TestType.TestTypeId,TestTypeCode,TestTypeName,TestType.CategoryId,Category.CategoryName CategoryName,Category.parentId SubjectId  from TestType "
                      " inner join Category on TestType.CategoryId=Category.CategoryId "
                      " where TestType.TestTypeId = :TestTypeId ");
        query.bindValue(":TestTypeId", TestTypeId);
        query.exec();

        while(query.next())
        {
            testType.TestTypeId=query.value(0).toString();
            testType.TestTypeCode=query.value(1).toString();
            testType.TestTypeName = query.value(2).toString();
            testType.CategoryId = query.value(3).toString();
            testType.CategoryName = query.value(4).toString();
            testType.SubjectId = query.value(5).toString();

            return testType;
        }
    }
    return testType;
}


QVector<TestType> TestTypeService::GetByCategoryId(QString categoryId)
{
    QVector<TestType> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(" select TestType.TestTypeId,TestTypeCode,TestTypeName, TestType.CategoryId,Category.CategoryName CategoryName,Category.parentId SubjectId from TestType "
                      " inner join Category on TestType.CategoryId=Category.CategoryId "
                      " where TestType.CategoryId = :categoryId "
                      " order by TestType.TestTypeId desc");
        query.bindValue(":categoryId", categoryId);
        query.exec();

        while(query.next())
        {
            TestType testType;
            testType.TestTypeId=query.value(0).toString();
            testType.TestTypeCode=query.value(1).toString();
            testType.TestTypeName = query.value(2).toString();
            testType.CategoryId = query.value(3).toString();
            testType.CategoryName = query.value(4).toString();
            testType.SubjectId = query.value(5).toString();

            list.append(testType);
        }
    }
    return list;
}

QVector<TestType> TestTypeService::GetByCategoryIdAndMaterialId(QString categoryId, QString materialId)
{
    QVector<TestType> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select TestType.TestTypeId,TestTypeCode,TestTypeName, TestType.CategoryId,Category.CategoryName CategoryName,Category.parentId SubjectId from TestType "
                      " inner join Category on TestType.CategoryId=Category.CategoryId "
                      " inner join TestType_Material on TestType.TestTypeId=TestType_Material.TestTypeid "
                      " where TestType.CategoryId = :categoryId and TestType_Material.MaterialId = :materialId "
                      " order by TestType.TestTypeId desc ");
        query.bindValue(":categoryId", categoryId);
        query.bindValue(":materialId", materialId);
        query.exec();

        while(query.next())
        {
            TestType testType;
            testType.TestTypeId=query.value(0).toString();
            testType.TestTypeCode=query.value(1).toString();
            testType.TestTypeName = query.value(2).toString();
            testType.CategoryId = query.value(3).toString();
            testType.CategoryName = query.value(4).toString();
            testType.SubjectId = query.value(5).toString();


            list.append(testType);
        }
    }
    return list;
}


QVector<TestType> TestTypeService::GetTestTypes(QString subjectId, QString categoryId, QString name)
{
    QVector<TestType> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select TestType.TestTypeId,TestTypeCode, TestTypeName, TestType.CategoryId,Category.CategoryName CategoryName,subject.CategoryId SubjectId,subject.CategoryName SubjectName  from TestType "
                      " inner join Category on TestType.CategoryId=Category.CategoryId "
                      " inner join Category subject on category.ParentId=subject.CategoryId "
                      " where (TestType.TestTypeName like :name or TestType.TestTypeCode like :name) "
                      " and ifnull(subject.CategoryId,'') like :subjectId "
                      " and ifnull(TestType.CategoryId,'') like :categoryId "
                      " order by TestType.TestTypeId desc ");
        query.bindValue(":subjectId",  QString("%%1%").arg(subjectId));
        query.bindValue(":categoryId",  QString("%%1%").arg(categoryId));
        query.bindValue(":name", QString("%%1%").arg(name));
        query.exec();

        while(query.next())
        {
            TestType testType;
            testType.TestTypeId=query.value(0).toString();
            testType.TestTypeCode=query.value(1).toString();
            testType.TestTypeName = query.value(2).toString();
            testType.CategoryId = query.value(3).toString();
            testType.CategoryName = query.value(4).toString();
            testType.SubjectId = query.value(5).toString();
            testType.SubjectName = query.value(6).toString();


            list.append(testType);
        }
    }
    return list;
}

QVector<TestType> TestTypeService::GetTestTypes()
{
    QVector<TestType> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.exec("SELECT TestTypeName FROM TestType");

        while(query.next())
        {
            TestType testType;
            testType.TestTypeName=query.value(0).toString();
            list.append(testType);
        }
    }
    return list;
}


QVector<TestType> TestTypeService::GetTestTypesBy3Name(QString name)
{
    QVector<TestType> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select TestType.TestTypeId,TestTypeCode, TestTypeName, TestType.CategoryId,Category.CategoryName CategoryName,subject.CategoryId SubjectId,subject.CategoryName SubjectName  from TestType "
                      " inner join Category on TestType.CategoryId=Category.CategoryId "
                      " inner join Category subject on category.ParentId=subject.CategoryId "
                      " where (TestType.TestTypeName like :name or TestType.TestTypeCode like :name) "
                      " order by TestType.TestTypeCode desc ");
        query.bindValue(":name", name);
        query.exec();

        while(query.next())
        {
            TestType testType;
            testType.TestTypeId=query.value(0).toString();
            testType.TestTypeCode=query.value(1).toString();
            testType.TestTypeName = query.value(2).toString();
            testType.CategoryId = query.value(3).toString();
            testType.CategoryName = query.value(4).toString();
            testType.SubjectId = query.value(5).toString();
            testType.SubjectName = query.value(6).toString();


            list.append(testType);
        }
    }
    return list;
}

QStringList TestTypeService::SearchTestTypesByName(QString name)
{

    QStringList list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");

    db.setDatabaseName("mytest.db");

    if(db.open())
    {
        QSqlQuery query;

        query.prepare("select Project.CustomName from Project where Project.CustomName like :CustomName");
        query.bindValue(":CustomName","%"+name+"%");
        query.exec();
        while(query.next())
        {
            list.append(query.value(0).toString());
        }
    }

    return list;
}


QVector<TestType> TestTypeService::GetTestTypesWithMaterialChecked(QString materialId)
{
    QVector<TestType> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select TestType.TestTypeId,TestTypeCode, TestTypeName, TestType.CategoryId,Category.CategoryName CategoryName,subject.CategoryId SubjectId,subject.CategoryName SubjectName "
                      " ,(ifnull(materialId,0)<>0) checked "
                      " from TestType "
                      " inner join Category on TestType.CategoryId=Category.CategoryId "
                      " inner join Category subject on category.ParentId=subject.CategoryId "
                      " left join testtype_material on testtype_material.TestTypeId=TestType.TestTypeId  "
                      " and testtype_material.materialId=:materialId"
                      " order by SubjectName,CategoryName,TestType.TestTypeName ");
        query.bindValue(":materialId",  QString("%1").arg(materialId));
        query.exec();

        while(query.next())
        {
            TestType testType;
            testType.TestTypeId=query.value(0).toString();
            testType.TestTypeCode=query.value(1).toString();
            testType.TestTypeName = query.value(2).toString();
            testType.CategoryId = query.value(3).toString();
            testType.CategoryName = query.value(4).toString();
            testType.SubjectId = query.value(5).toString();
            testType.SubjectName = query.value(6).toString();
            testType.flag = query.value(7).toInt();

            list.append(testType);
        }
    }
    return list;
}


QVector<TestType> TestTypeService::GetTestTypesWithReagentChecked(QString reagentId, QString testTypeName)
{
    QVector<TestType> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select TestType.TestTypeId,TestTypeCode, TestTypeName, TestType.CategoryId,Category.CategoryName CategoryName,subject.CategoryId SubjectId,subject.CategoryName SubjectName "
                      " ,(ifnull(reagentId,0)<>0) checked "
                      " from TestType "
                      " inner join Category on TestType.CategoryId=Category.CategoryId "
                      " inner join Category subject on category.ParentId=subject.CategoryId "
                      " left join testtype_reagent on testtype_reagent.TestTypeId=TestType.TestTypeId  "
                      " and testtype_reagent.reagentId=:reagentId"
                      " where TestTypeName like :TestTypeName "
                      " order by subject.CategoryName,Category.CategoryName, TestType.TestTypeName ");
        query.bindValue(":reagentId",  QString("%1").arg(reagentId));
        query.bindValue(":TestTypeName",  QString("%%1%").arg(testTypeName));
        query.exec();

        while(query.next())
        {
            TestType testType;
            testType.TestTypeId=query.value(0).toString();
            testType.TestTypeCode=query.value(1).toString();
            testType.TestTypeName = query.value(2).toString();
            testType.CategoryId = query.value(3).toString();
            testType.CategoryName = query.value(4).toString();
            testType.SubjectId = query.value(5).toString();
            testType.SubjectName = query.value(6).toString();
            testType.flag = query.value(7).toInt();


            list.append(testType);
        }
    }
    return list;
}
QVector<TestType> TestTypeService::GetTestTypesWithMethodChecked(QString methodId)
{
    QVector<TestType> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select TestType.TestTypeId,TestTypeCode, TestTypeName, TestType.CategoryId,Category.CategoryName CategoryName,subject.CategoryId SubjectId,subject.CategoryName SubjectName "
                      " ,(ifnull(methodId,0)<>0) checked "
                      " from TestType "
                      " inner join Category on TestType.CategoryId=Category.CategoryId "
                      " inner join Category subject on category.ParentId=subject.CategoryId "
                      " left join testtype_method on testtype_method.TestTypeId=TestType.TestTypeId  "
                      " and testtype_method.methodId=:methodId"
                      " order by SubjectName,CategoryName,TestType.TestTypeName ");
        query.bindValue(":methodId",  QString("%1").arg(methodId));
        query.exec();

        while(query.next())
        {
            TestType testType;
            testType.TestTypeId=query.value(0).toString();
            testType.TestTypeCode=query.value(1).toString();
            testType.TestTypeName = query.value(2).toString();
            testType.CategoryId = query.value(3).toString();
            testType.CategoryName = query.value(4).toString();
            testType.SubjectId = query.value(5).toString();
            testType.SubjectName = query.value(6).toString();
            testType.flag = query.value(7).toInt();


            list.append(testType);
        }
    }
    return list;
}

void TestTypeService::Insert(TestType testType)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into TestType (TestTypeId,CategoryId,TestTypeCode,TestTypeName,AddTime,Status) values (:TestTypeId,:CategoryId,:TestTypeCode,:TestTypeName,:AddTime,:Status)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":TestTypeId", guid);
        query.bindValue(":CategoryId", testType.CategoryId);
        query.bindValue(":TestTypeCode", testType.TestTypeCode);
        query.bindValue(":TestTypeName", testType.TestTypeName);
        query.bindValue(":AddTime", testType.AddTime);
        query.bindValue(":Status", testType.Status);
        query.exec();

        testType.TestTypeId = guid;

    }
}

void TestTypeService::Update(TestType testType)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update TestType set CategoryId=:CategoryId,TestTypeCode=:TestTypeCode,TestTypeName=:TestTypeName,AddTime=:AddTime,Status=:Status where TestTypeId=:TestTypeId");

        query.bindValue(":CategoryId", testType.CategoryId);
        query.bindValue(":TestTypeCode", testType.TestTypeCode);
        query.bindValue(":TestTypeName", testType.TestTypeName);
        query.bindValue(":AddTime", testType.AddTime);
        query.bindValue(":Status", testType.Status);
        query.bindValue(":TestTypeId", testType.TestTypeId);
        query.exec();

    }
}

void TestTypeService::DeleteById(QString TestTypeId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from TestType where TestTypeId =:TestTypeId");
        query.bindValue(":TestTypeId", TestTypeId);
        query.exec();
    }
}

