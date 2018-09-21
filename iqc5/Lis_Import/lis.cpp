#include "lis.h"
#include <QVariant>
#include <QUuid>
#include <QRegularExpression>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

Lis::Lis()
{
    data = new LisData();
//    db = QSqlDatabase::database("qt_sql_default_connection");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mytest.db");
}

Lis::~Lis()
{
    delete data;
}

bool Lis::importData()
{
    qDebug() << "importData";
    if(db.open())
    {
        QSqlQuery query;
        db.transaction();

        QString tempTestTypeId;
        foreach (TestType *testType, data->testTypeVec) {
            tempTestTypeId = testType->TestTypeId;
            query.prepare("select * from TestType where TestTypeName = :TestTypeName and TestTypeCode = :TestTypeCode");
            query.bindValue(":TestTypeName",testType->TestTypeName);
            query.bindValue(":TestTypeCode",testType->TestTypeCode);
            query.exec();
            if( !query.next() )
            {
                QUuid uuid;
                QString guid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
                testType->TestTypeId = guid;
                query.prepare("insert into TestType(TestTypeId,CategoryId,TestTypeCode,TestTypeName,IfDefault,AddTime,Status) values(:TestTypeId,:CategoryId,:TestTypeCode,:TestTypeName,:IfDefault,:AddTime,:Status)");
                query.bindValue(":TestTypeId",testType->TestTypeId);
                query.bindValue(":CategoryId","");
                query.bindValue(":TestTypeCode",testType->TestTypeCode);
                query.bindValue(":TestTypeName",testType->TestTypeName);
                query.bindValue(":IfDefault","");
                query.bindValue(":AddTime",testType->AddTime);
                query.bindValue(":Status","");
                query.exec();
            }
            else
            {
                testType->TestTypeId = query.value("TestTypeId").toString();
            }

            QUuid uid;
            QString proId = uid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");

            foreach (Project *pro, data->projectVec) {
                if( pro->testType.TestTypeId == tempTestTypeId )
                    pro->testType.TestTypeId = testType->TestTypeId;
            }
            foreach (Project *pro, data->projectVec) {
                if(pro->ProjectId == tempTestTypeId)
                {
                    pro->ProjectId = proId;
                }
            }
            foreach (Result *result, data->resultVec) {
                if( result->ProjectId == tempTestTypeId )
                {
                    result->ProjectId = proId;
                    result->detail.ProjectId = proId;
                }
                else
                {
//                    QUuid uuid;
//                    QString guid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
//                    result->ProjectId = guid;
//                    result->detail.ProjectId = guid;
                }
            }

        }//testType


        query.clear();
        foreach (Project *pro, data->projectVec) {
            QString tempProjId = pro->ProjectId;
            query.prepare("select * from Project where TestTypeId = :TestTypeId and ProjectName =:ProjectName and EnglishName=:EnglishName and CustomName=:CustomName");
            query.bindValue(":TestTypeId",pro->testType.TestTypeId);
            query.bindValue(":ProjectName",pro->ProjectName);
            query.bindValue(":EnglishName",pro->EnglishName);
            query.bindValue(":CustomName",pro->CustomName);
            query.exec();
            if( !query.next() )
            {
                query.clear();
//                QUuid uuid;
//                QString guid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
                query.prepare("insert into Project(ProjectId,ProjectName,EnglishName,CustomName,TestTypeId,DeviceId,DensityConut,PerDayBatch,DispIdx,CreateTime) values(:ProjectId,:ProjectName,:EnglishName,:CustomName,:TestTypeId,:DeviceId,:DensityConut,:PerDayBatch,:DispIdx,:CreateTime)");
//                pro->ProjectId = guid;
                query.bindValue(":ProjectId",pro->ProjectId);
                query.bindValue(":ProjectName",pro->ProjectName);
                query.bindValue(":EnglishName",pro->EnglishName);
                query.bindValue(":CustomName",pro->CustomName);
                query.bindValue(":TestTypeId",pro->testType.TestTypeId);
                query.bindValue(":DeviceId","");
                query.bindValue(":DensityConut","1");
                query.bindValue(":PerDayBatch","");
                query.bindValue(":DispIdx","");
                query.bindValue(":CreateTime","");
                query.exec();
//                foreach (Result *result, data->resultVec) {
//                   if( result->ProjectId == tempProjId )
//                   {
//                       result->ProjectId = pro->ProjectId;
//                   }
//                }
            }
            else
            {
                do{
                    QString projectId = query.value("ProjectId").toString();
                    int densitycount = query.value("DensityConut").toInt();
                    densitycount += 1;
                    query.clear();
                    query.prepare("update Project set DensityConut=:DensityConut where ProjectId=:ProjectId");
                    query.bindValue(":ProjectId",projectId);
                    query.bindValue(":DensityConut",densitycount);
                    query.exec();

                    foreach (Result *result, data->resultVec) {
                       if( result->ProjectId == tempProjId )
                       {
                           result->ProjectId = projectId;
                           result->detail.ProjectId = projectId;
                       }
                    }
                }
                while(query.next());
            }
        }//project


        foreach (Result *result, data->resultVec) {

            QString tempProject = result->ProjectId;
            query.clear();
            query.prepare("select * from Project_Detail where ProjectId = :ProjectId");
            query.bindValue(":ProjectId",result->detail.ProjectId);
            query.exec();
            if( !query.next() )
            {
                QUuid uuid;
                QString guid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
                result->detail.Project_DetailId = guid;
                query.prepare("insert into Project_Detail(Project_DetailId,ProjectId,DensityId,DensityName,MaterialId,MaterialBatchId,ReagentId,ReagentBatchId,Useflag,MethodId) values(:Project_DetailId,:ProjectId,:DensityId,:DensityName,:MaterialId,:MaterialBatchId,:ReagentId,:ReagentBatchId,:Useflag,:MethodId)");
                query.bindValue(":Project_DetailId",result->detail.Project_DetailId);
                query.bindValue(":ProjectId",result->ProjectId);
                query.bindValue(":DensityId","");
                query.bindValue(":DensityName","");
                query.bindValue(":MaterialId",result->detail.MaterialId);
                query.bindValue(":MaterialBatchId","");
                query.bindValue(":ReagentId","");
                query.bindValue(":ReagentBatchId","");
                query.bindValue(":Useflag","");
                query.bindValue(":MethodId","");
                query.exec();
            }
            else
            {
                result->detail.ProjectId = query.value("ProjectId").toString();
            }

            query.clear();
            query.prepare("select * from Result where ProjectId = :ProjectId and CreateTime = :CreateTime ");
            query.bindValue(":ProjectId",result->ProjectId);
//            query.bindValue(":Project_DetailId",result->detail.Project_DetailId);
            query.bindValue(":CreateTime",result->CreateTime);
            query.exec();

            if( !query.next() )
            {
                QUuid uuid;
                QString guid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
                query.prepare("insert into Result(ResultId,ProjectId,DensityId,Project_DetailId,ResultNum,TestTime,Value,CreateTime,CreateUser,IfInput,InputBatchId) values(:ResultId,:ProjectId,:DensityId,:Project_DetailId,:ResultNum,:TestTime,:Value,:CreateTime,:CreateUser,:IfInput,:InputBatchId)");
                result->ResultId = guid;
                query.bindValue(":ResultId",guid);
                query.bindValue(":ProjectId",result->ProjectId);
                query.bindValue(":DensityId","");
                query.bindValue(":Project_DetailId","");
                query.bindValue(":ResultNum",1);
                query.bindValue(":TestTime","");
                query.bindValue(":Value",result->value);
                query.bindValue(":CreateTime",result->CreateTime);
                query.bindValue(":CreateUser","");
                query.bindValue(":IfInput","");
                query.bindValue(":InputBatchId","");
                query.exec();
            }
            else
            {
                query.clear();
                query.prepare("select Max(ResultNum) as ResultNum from result where ProjectId = :ProjectId and CreateTime = :CreateTime");
                query.bindValue(":ProjectId",result->ProjectId);
                query.bindValue(":CreateTime",result->CreateTime);
                query.exec();
                if(query.next())
                {
                    int resultNum = query.value("ResultNum").toInt();
                    resultNum += 1;
                    QUuid uuid;
                    QString guid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
                    query.prepare("insert into Result(ResultId,ProjectId,DensityId,Project_DetailId,ResultNum,TestTime,Value,CreateTime,CreateUser,IfInput,InputBatchId) values(:ResultId,:ProjectId,:DensityId,:Project_DetailId,:ResultNum,:TestTime,:Value,:CreateTime,:CreateUser,:IfInput,:InputBatchId)");
                    result->ResultId = guid;
                    query.bindValue(":ResultId",guid);
                    query.bindValue(":ProjectId",result->ProjectId);
                    query.bindValue(":DensityId","");
                    query.bindValue(":Project_DetailId","");
                    query.bindValue(":ResultNum",resultNum);
                    query.bindValue(":TestTime","");
                    query.bindValue(":Value",result->value);
                    query.bindValue(":CreateTime",result->CreateTime);
                    query.bindValue(":CreateUser","");
                    query.bindValue(":IfInput","");
                    query.bindValue(":InputBatchId","");
                    query.exec();
                }
            }
        }//Result
        qDebug() << "importData end!!!";
        db.commit();
        db.close();
        return true;
    }//db.open
    else
    {
        QMessageBox::warning(NULL,QString("警告"),QString("数据打开失败。。。"),QMessageBox::Ok);
        return false;
    }
}
