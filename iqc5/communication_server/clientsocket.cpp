#include "clientsocket.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUuid>
#include <QRegularExpression>
#include <QDateTime>
#include <QMessageBox>

#include <QSqlQuery>
#include <QSqlError>

ClientSocket::ClientSocket(QObject *parent) :
    QTcpSocket(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mytest.db");

    connect(this,SIGNAL(readyRead()),this,SLOT(readClient()));
    connect(this,SIGNAL(disconnected()),this,SLOT(deleteLater()));
}

void ClientSocket::getFromJsonData(const QByteArray &jsonData)
{
//    qDebug() << jsonData;

    QJsonParseError error;
    QJsonDocument jsonDocment = QJsonDocument::fromJson(jsonData,&error);
    if(error.error == QJsonParseError::NoError)
    {
        if(jsonDocment.isArray())
        {
            QJsonArray jsonArray = jsonDocment.array();
            for(int i = 0; i < jsonArray.size(); i++ )
            {
                TestType *testtype = new TestType;
                Device *device = new Device;
                Project *project = new Project;
                Result *result = new Result;

                QJsonValue value = jsonArray.at(i);
                if( value.isObject() )
                {
                    QJsonObject object = value.toObject();
                    if(object.contains("testTypeCode"))
                    {
                        QJsonValue jsonValue = object.take("testTypeCode");
                        QString testtypecode = jsonValue.toString();

                        QUuid quuid;
                        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
                        testtype->TestTypeId = guid;
                        testtype->TestTypeCode = testtypecode;

                        project->testType.TestTypeId = guid;
                        project->testType.TestTypeCode = testtypecode;
                        project->CustomName = testtypecode;
                    }
                    if(object.contains("sampleId"))
                    {
                        QJsonValue jsonValue = object.take("sampleId");
                        QString sampleId = jsonValue.toString();

                        QUuid quuid;
                        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");

                        result->ProjectId = guid;
                        project->ProjectId = guid;
                        project->ProjectName = sampleId;
                    }
                    if(object.contains("value"))
                    {
                        QJsonValue jsonValue = object.take("value");
                        double value = jsonValue.toString().toDouble();
                        result->value = value;
                    }
                    if(object.contains("dataTime"))
                    {
                        QJsonValue jsonValue = object.take("dataTime");
                        QString dataTime = jsonValue.toString();
                        result->TestTime = dataTime;
                    }
                    if(object.contains("deviceName"))
                    {
                        QJsonValue jsonValue = object.take("deviceName");
                        QString deviceName = jsonValue.toString();
                        device->DeviceName = deviceName;

                    }
                    if(object.contains("modelName"))
                    {
                        QJsonValue jsonValue = object.take("modelName");
                        QString modelName = jsonValue.toString();
                        device->ModelName = modelName;
                    }
                    if(object.contains("brandName"))
                    {
                        QJsonValue jsonValue = object.take("brandName");
                        QString brandName = jsonValue.toString();
                        device->BrandName = brandName;
                    }
                    if(object.contains("deviceId"))
                    {
                        QJsonValue jsonValue = object.take("deviceId");
                        QString deviceId = jsonValue.toString();
                        device->DeviceId = deviceId;
                        project->DeviceId = deviceId;
                    }
                    if(object.contains("modelId"))
                    {
                        QJsonValue jsonValue = object.take("modelId");
                        QString modelId = jsonValue.toString();
                        device->ModelId = modelId;
                    }
                    if(object.contains("brandId"))
                    {
                        QJsonValue jsonValue = object.take("brandId");
                        QString brandId = jsonValue.toString();
                        device->BrandId = brandId;
                    }
                    DeviceMap.insert(device->DeviceId,device);
                    qDebug() << device->DeviceId;
                    ResultVec.push_back(result);
                    ProjectVec.push_back(project);
                    TestTypeVec.push_back(testtype);
                }
            }
        }
    }
    else
    {
        qDebug() << error.errorString();
    }


//    foreach (Result *result, ResultVec) {
//       qDebug() << "value: " << result->value;
//       qDebug() << "testTime: " << result->TestTime;
//    }
//    foreach (Project *pro, ProjectVec) {
//        qDebug() << "projectName: " << pro->ProjectName;
//        qDebug() << "projectId: " << pro->ProjectId;

//    }
//    foreach (TestType *testtype, TestTypeVec) {
//        qDebug() << "testTypeCode: " << testtype->TestTypeCode;
//    }

}

void ClientSocket::CommitToDatabase()
{
    if(db.open())
    {
        QSqlQuery query;
        db.transaction();

        QString tempTestTypeId;
        foreach (TestType *testType, TestTypeVec) {
            tempTestTypeId = testType->TestTypeId;
            query.prepare("select * from TestType where TestTypeCode = :TestTypeCode");
            query.bindValue(":TestTypeCode",testType->TestTypeCode);
            query.exec();
            if( !query.next() )
            {
                testType->AddTime = QDateTime::currentDateTimeUtc().toString();
                query.prepare("insert into TestType(TestTypeId,CategoryId,TestTypeCode,TestTypeName,IfDefault,AddTime,Status) values(:TestTypeId,:CategoryId,:TestTypeCode,:TestTypeName,:IfDefault,:AddTime,:Status)");
                query.bindValue(":TestTypeId",testType->TestTypeId);
                query.bindValue(":CategoryId","");
                query.bindValue(":TestTypeCode",testType->TestTypeCode);
                query.bindValue(":TestTypeName","");
                query.bindValue(":IfDefault","");
                query.bindValue(":AddTime",testType->AddTime);
                query.bindValue(":Status","");
                query.exec();
            }
            else
            {
                testType->TestTypeId = query.value("TestTypeId").toString();
            }

            foreach (Project *pro, ProjectVec) {
                if( pro->testType.TestTypeId == tempTestTypeId )
                    pro->testType.TestTypeId = testType->TestTypeId;
            }

        }//testType


        query.clear();
        foreach (Project *pro, ProjectVec) {
            QString tempProjId = pro->ProjectId;

            //设备信息
            query.prepare("select device.DeviceId,DeviceName,Device.ModelId,code,sn,steelseal,assetscode,installdate,installplace,stopdate,memo,Brand.BrandName,Model.ModelName,Brand.BrandId from device as device "
                          " inner join Model on device.ModelId=Model.ModelId "
                          " inner join Brand on Model.BrandId=Brand.BrandId ");
            query.exec();
            bool hasFlag = false;
            while(query.next())
            {
                QString tDeviceName = query.value(1).toString();
                QString tBrandName = query.value(11).toString();
                QString tModelName = query.value(12).toString();




                if( tDeviceName == DeviceMap[pro->DeviceId]->DeviceName &&
                    tBrandName == DeviceMap[pro->DeviceId]->BrandName   &&
                    tModelName == DeviceMap[pro->DeviceId]->ModelName   )
                {
                    DeviceMap[pro->DeviceId]->DeviceId = query.value(0).toString();
                    pro->DeviceId = query.value(0).toString();
                    DeviceMap[pro->DeviceId]->BrandId = query.value(13).toString();
                    DeviceMap[pro->DeviceId]->ModelId = query.value(2).toString();
                    hasFlag = true;
                }
            }

            if(!hasFlag)//数据库里没有，插入
            {
                //Brand
                query.clear();
                query.prepare("select BrandId,BrandName from brand where BrandName = :BrandName");
                query.bindValue(":BrandName",DeviceMap[pro->DeviceId]->BrandName);
                query.exec();
                if(query.size() > 0)
                {
                    while(query.next())
                    {
                        if(query.value(1).toString() == DeviceMap[pro->DeviceId]->BrandName)
                        {
                            DeviceMap[pro->DeviceId]->BrandId = query.value(0).toString();
                        }
                    }
                }
                else
                {
                    query.clear();
                    query.prepare("insert into brand (BrandId,BrandName,Status) values (:BrandId,:BrandName,:Status)");
                    query.bindValue(":BrandId", DeviceMap[pro->DeviceId]->BrandId);
                    query.bindValue(":BrandName", DeviceMap[pro->DeviceId]->BrandName);
                    query.bindValue(":Status", "1");
                    query.exec();
                }

                //Model
                query.clear();
                query.prepare("select ModelId,ModelName from Model where ModelName = :ModelName");
                query.bindValue(":ModelName",DeviceMap[pro->DeviceId]->ModelName);
                query.exec();
                if(query.size() > 0)
                {
                    while(query.next())
                    {
                        if(query.value(1).toString() == DeviceMap[pro->DeviceId]->ModelName)
                        {
                            DeviceMap[pro->DeviceId]->ModelId = query.value(0).toString();
                        }
                    }
                }
                else
                {
                    query.clear();
                    query.prepare("insert into model (ModelId,BrandId,ModelName,Status) values (:ModelId,:BrandId,:ModelName,:Status)");
                    QUuid quuid;
                    QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
                    query.bindValue(":ModelId", DeviceMap[pro->DeviceId]->ModelId);
                    query.bindValue(":BrandId", DeviceMap[pro->DeviceId]->BrandId);
                    query.bindValue(":ModelName", DeviceMap[pro->DeviceId]->ModelName);
                    query.bindValue(":Status", "1");
                    query.exec();
                }

                //Device
                query.clear();
                query.prepare("insert into device (DeviceId,DeviceName,ModelId,code,sn,steelseal,assetscode,installdate,installplace,stopdate,memo,CreateTime,Status) values (:DeviceId,:DeviceName,:ModelId,:code,:sn,:steelseal,:assetscode,:installdate,:installplace,:stopdate,:memo,:CreateTime,:Status)");
                query.bindValue(":DeviceId", DeviceMap[pro->DeviceId]->DeviceId);
                query.bindValue(":DeviceName", DeviceMap[pro->DeviceId]->DeviceName);
                query.bindValue(":ModelId", DeviceMap[pro->DeviceId]->ModelId);
                query.bindValue(":code", "");
                query.bindValue(":sn", "");
                query.bindValue(":steelseal", "");
                query.bindValue(":assetscode", "");
                query.bindValue(":installdate", "");
                query.bindValue(":installplace", "");
                query.bindValue(":stopdate", "");
                query.bindValue(":memo", "");
                query.bindValue(":CreateTime", "");
                query.bindValue(":Status", "1");
                query.exec();
            }

            //Project
            query.clear();
            query.prepare("select ProjectId, ProjectName,CustomName,TestTypeId,DeviceId from Project"
                          " where ProjectName = :ProjectName and TestTypeId = :TestTypeId and DeviceId = :DeviceId");
            query.bindValue(":ProjectName",pro->ProjectName);
//            query.bindValue(":CustomName",pro->CustomName);
            query.bindValue(":TestTypeId",pro->testType.TestTypeId);
            query.bindValue(":DeviceId",pro->DeviceId);
            query.exec();

            ///可能需要要修改,问题：query.size()始终返回-1
            if(query.next())
            {
                foreach (Result *result, ResultVec) {
                    if(result->ProjectId == pro->ProjectId)
                    {
                        pro->ProjectId = query.value(0).toString();
                        result->ProjectId = query.value(0).toString();
                        result->detail.ProjectId = query.value(0).toString();
                    }
                }
            }
            else
            {
                query.clear();
                query.prepare("insert into Project(ProjectId,ProjectName,EnglishName,CustomName,TestTypeId,DeviceId,DensityConut,PerDayBatch,DispIdx,CreateTime) values(:ProjectId,:ProjectName,:EnglishName,:CustomName,:TestTypeId,:DeviceId,:DensityConut,:PerDayBatch,:DispIdx,:CreateTime)");
                query.bindValue(":ProjectId",pro->ProjectId);
                query.bindValue(":ProjectName",pro->ProjectName);
                query.bindValue(":EnglishName","");
                query.bindValue(":CustomName",pro->CustomName);
                query.bindValue(":TestTypeId",pro->testType.TestTypeId);
                query.bindValue(":DeviceId",pro->DeviceId);
                query.bindValue(":DensityConut","1");
                query.bindValue(":PerDayBatch","");
                query.bindValue(":DispIdx","");
                query.bindValue(":CreateTime","");
                query.exec();
            }

            //ProjectDetail
            ProjectDetail projectDetail;
            QUuid uuid;
            QString guid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
            projectDetail.Project_DetailId = guid;
            projectDetail.ProjectId = pro->ProjectId;
            projectDetail.DensityId = 1;
            projectDetail.Useflag = 1;




            qDebug() << "ProjectId: " << projectDetail.ProjectId;
            qDebug() << "DensityId: " << projectDetail.DensityId;
            query.clear();
            query.prepare("select Project_DetailId,ProjectId,DensityId,Useflag from ProjectDetail where ProjectId = :ProjectId and DensityId = :DensityId and Useflag = :Useflag");
            query.bindValue(":ProjectId",projectDetail.ProjectId);
            query.bindValue(":DensityId",QString::number(projectDetail.DensityId));
            query.bindValue(":Useflag",QString::number(projectDetail.Useflag));
            query.exec();
            if(query.next())
            {
                projectDetail.Project_DetailId = query.value(0).toString();
                projectDetail.ProjectId = query.value(1).toString();
                projectDetail.DensityId = query.value(2).toInt();
                foreach (Result *result, ResultVec) {
                   if(result->ProjectId == pro->ProjectId)
                   {
                      result->detail.Project_DetailId = query.value(0).toString();
                      result->detail.ProjectId = query.value(1).toString();
                      result->detail.DensityId = query.value(2).toInt();
                      result->detail.Useflag = query.value(3).toInt();
                   }
                }

            }
            else
            {
                query.clear();
                query.prepare("insert into Project_Detail(Project_DetailId,ProjectId,DensityId,Useflag) values(:Project_DetailId,:ProjectId,:DensityId,:Useflag)");
                query.bindValue(":Project_DetailId",projectDetail.Project_DetailId);
                query.bindValue(":ProjectId",projectDetail.ProjectId);
                query.bindValue(":DensityId",QString::number(projectDetail.DensityId));
                query.bindValue(":Useflag",QString::number(projectDetail.Useflag));
                query.exec();

                foreach (Result *result, ResultVec) {
                   if(result->ProjectId == pro->ProjectId)
                   {
                      result->detail.Project_DetailId = projectDetail.Project_DetailId;
                      result->detail.DensityId = projectDetail.DensityId;
                   }
                }
            }
        }//project


        foreach (Result *result, ResultVec) {
//            QString tempProject = result->ProjectId;
//            query.clear();
//            query.prepare("select * from Project_Detail where ProjectId = :ProjectId");
//            query.bindValue(":ProjectId",result->detail.ProjectId);
//            query.exec();
//            if( !query.next() )
//            {
//                QUuid uuid;
//                QString guid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
//                result->detail.Project_DetailId = guid;
//                query.prepare("insert into Project_Detail(Project_DetailId,ProjectId,DensityId,DensityName,MaterialId,MaterialBatchId,ReagentId,ReagentBatchId,Useflag,MethodId) values(:Project_DetailId,:ProjectId,:DensityId,:DensityName,:MaterialId,:MaterialBatchId,:ReagentId,:ReagentBatchId,:Useflag,:MethodId)");
//                query.bindValue(":Project_DetailId",result->detail.Project_DetailId);
//                query.bindValue(":ProjectId",result->ProjectId);
//                query.bindValue(":DensityId","");
//                query.bindValue(":DensityName","");
//                query.bindValue(":MaterialId",result->detail.MaterialId);
//                query.bindValue(":MaterialBatchId","");
//                query.bindValue(":ReagentId","");
//                query.bindValue(":ReagentBatchId","");
//                query.bindValue(":Useflag","");
//                query.bindValue(":MethodId","");
//                query.exec();
//            }
//            else
//            {
//                result->detail.ProjectId = query.value("ProjectId").toString();
//            }

            query.clear();
            query.prepare("select * from Result where ProjectId = :ProjectId and TestTime = :TestTime ");
            query.bindValue(":ProjectId",result->detail.ProjectId);
            query.bindValue(":Project_DetailId",result->detail.Project_DetailId);
            query.bindValue(":TestTime",result->TestTime);
            query.exec();

            if( !query.next() )
            {
                QUuid uuid;
                QString guid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
                query.prepare("insert into Result(ResultId,ProjectId,DensityId,Project_DetailId,ResultNum,TestTime,Value,CreateTime,CreateUser,IfInput,InputBatchId) values(:ResultId,:ProjectId,:DensityId,:Project_DetailId,:ResultNum,:TestTime,:Value,:CreateTime,:CreateUser,:IfInput,:InputBatchId)");
                result->ResultId = guid;
                query.bindValue(":ResultId",guid);
                query.bindValue(":ProjectId",result->ProjectId);
                query.bindValue(":DensityId",QString::number(result->detail.DensityId));
                query.bindValue(":Project_DetailId",result->detail.Project_DetailId);
                query.bindValue(":ResultNum",1);
                query.bindValue(":TestTime",result->TestTime);
                query.bindValue(":Value",result->value);
                query.bindValue(":CreateTime","");
                query.bindValue(":CreateUser","");
                query.bindValue(":IfInput","");
                query.bindValue(":InputBatchId","");
                query.exec();
            }
            else
            {
                query.clear();
                query.prepare("select Max(ResultNum) as ResultNum from result where ProjectId = :ProjectId and TestTime = :TestTime");
                query.bindValue(":ProjectId",result->ProjectId);
                query.bindValue(":TestTime",result->TestTime);
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
                    query.bindValue(":DensityId",QString::number(result->detail.DensityId));
                    query.bindValue(":Project_DetailId",result->detail.Project_DetailId);
                    query.bindValue(":ResultNum",resultNum);
                    query.bindValue(":TestTime",result->TestTime);
                    query.bindValue(":Value",result->value);
                    query.bindValue(":CreateTime","");
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

        DeviceMap.clear();
        receivedData.clear();
        TestTypeVec.clear();
        ProjectVec.clear();
        ResultVec.clear();
    }//db.open
    else
    {
//        QMessageBox::warning(NULL,QString("警告"),QString("数据打开失败。。。"),QMessageBox::Ok);
    }
}

void ClientSocket::sendMessage(const QByteArray &data)
{
    write(data);
}

void ClientSocket::readClient()
{
    QByteArray data;
    QString tempStr = QString::fromUtf8(readAll());
    data.append(tempStr);

    QByteArray startHead = "#<DataStart ";
    QByteArray endWith = " DataEnd>#";
    if( data.startsWith(startHead) && !data.endsWith(endWith) )
    {
        receivedData.clear();
        data = data.right(data.length() - data.indexOf(startHead) - startHead.length());
        receivedData.append(data);
    }
    else if(data.startsWith(startHead) && data.endsWith(endWith))
    {
        data = data.left(data.indexOf(endWith));
        data.remove(data.indexOf(startHead),startHead.length());
        receivedData.append(data);
        getFromJsonData(receivedData);
        CommitToDatabase();
    }
    else
    {
        receivedData.append(data);
    }
}
