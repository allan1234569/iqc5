#include "parserthread.h"
#include <QFile>
#include <QStringList>
#include <QRegularExpression>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QUuid>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include "myTestType.h"

//extern QSqlDatabase db;

parserThread::parserThread(QObject *parent) :
    QThread(parent)
{
    db.setDatabaseName("mytest.db");
    qDebug() << __LINE__ << db.open();
}

parserThread::parserThread(QObject *parent, QString path) :
    QThread(parent),filePath(path)
{
    getDeviceInfo();
}

void parserThread::getDeviceInfo()
{
    device.DeviceName = settings->value(tr("INSTRUMENT_INFO/DEVICENAME")).toString();
    device.sn = settings->value(tr("INSTRUMENT_INFO/SN")).toString();
    device.installdate = settings->value(tr("INSTRUMENT_INFO/INSTALLDATA")).toString();
    device.installplace = settings->value(tr("INSTRUMENT_INFO/INSTALLPLACE")).toString();
    //TODO:从数据库查询
    QSqlQuery query;
//    query.prepare("select * from Device where DeviceName = :DeviceName and sn = :sn and installdata = :installdata and installplace = :installplace");
//    query.bindValue(":DeviceName",device.DeviceName);
//    query.bindValue(":sn",device.sn);
//    query.bindValue(":installdata",device.installdate);
//    query.bindValue(":installplace",device.installplace);
//    query.exec();
//    if( !query.next() )
//    {
//        query.clear();
//        query.prepare("insert into device (DeviceId,DeviceName,ModelId,code,sn,steelseal,assetscode,installdate,installplace,stopdate,memo,CreateTime,Status) values (:DeviceId,:DeviceName,:ModelId,:code,:sn,:steelseal,:assetscode,:installdate,:installplace,:stopdate,:memo,:CreateTime,:Status)");
//        QUuid quuid;
//        QRegularExpression reg;
//        reg.setPattern("[{|}]");
//        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "").replace(reg, "");
//        query.bindValue(":DeviceId", guid);
//        query.bindValue(":DeviceName", device.DeviceName);
//        query.bindValue(":ModelId", device.ModelId);
//        query.bindValue(":code", device.code);
//        query.bindValue(":sn", device.sn);
//        query.bindValue(":steelseal", device.steelseal);
//        query.bindValue(":assetscode", device.assetscode);
//        query.bindValue(":installdate", device.installdate);
//        query.bindValue(":installplace", device.installplace);
//        query.bindValue(":stopdate", device.stopdate);
//        query.bindValue(":memo", device.memo);
//        query.bindValue(":CreateTime", device.CreateTime);
//        query.bindValue(":Status", "1");
//        query.exec();
//    }
//    else
//    {

//    }
}

QByteArray parserThread::parser(const QString &content)
{
//    QStringList list = split(content,QRegularExpression("<ENQ>"));
    QStringList list = split(content,QRegularExpression("<CR><LF>"));

    QVector<MyProject> proVec;

    foreach (QString str, list) {
        MyProject tempProject;//通用的Project对象
        if( str.contains(QRegularExpression("<STX>\\dR")) )
        {
            QStringList tempList = split(str,QRegularExpression("\\n"));

            foreach (QString line, tempList) {
                if( line.contains(QRegularExpression("<STX>\\dO")) )
                {
                    parserSampleId(tempProject,line);//解析项目编号

                }
                else if( line.contains(QRegularExpression("<STX>\\dR")) )
                {
                    parserFieldValue(tempProject,line);//解析字段值
                    proVec.push_back(tempProject);
                }
            }
        }
    }

    QJsonDocument jsonDocment;

    QJsonArray jsonArray;
    for(int i = 0; i < proVec.size(); i++ )
    {
        MyProject pro = proVec.at(i);
        QJsonObject jsonObject;
        jsonObject.insert("sampleId",pro.sampleId);
        jsonObject.insert("testTypeCode",pro.testTypeCode);
        jsonObject.insert("value",QString::number(pro.Value));
        jsonObject.insert("dataTime",pro.testType.DataTime);
        jsonObject.insert("deviceName",device.DeviceName);
        jsonObject.insert("modelName",device.ModelName);
        jsonObject.insert("brandName",device.BrandName);
        jsonObject.insert("deviceId",device.DeviceId);
        jsonObject.insert("modelId",device.ModelId);
        jsonObject.insert("brandId",device.BrandId);
        jsonArray.insert(i,jsonObject);
    }
    jsonDocment.setArray(jsonArray);
    QByteArray jsonData;
    if( !jsonDocment.isEmpty() )
    {
        jsonData= jsonDocment.toJson();
    }

    return jsonData;
}

void parserThread::parserFieldValue(MyProject &pro, const QString &parsedString)
{
    QString tempStr = parsedString;

    QString exp = "";

    //日期和时间
    exp =  QString::fromLatin1("<CR><ETX>");
    tempStr = tempStr.left(tempStr.indexOf(QRegularExpression(exp)));
    pro.testType.DataTime = tempStr.right(tempStr.length() - tempStr.lastIndexOf("\|") - 1);


    //范围

//    exp = QString::fromLatin1("\\|{3}[A-Z]\\|{4}");
//    tempStr = tempStr.left(tempStr.indexOf(QRegularExpression(exp)));
////    qDebug() << __LINE__ << tempStr;
////    pro.testType.rangeValue = tempStr.right(tempStr.length() - tempStr.lastIndexOf("\|") - 1);

    for( int i = 0; i < 7; i++ )
    {
        tempStr = tempStr.left(tempStr.lastIndexOf("\|"));
    }

    //单位
    tempStr = tempStr.left(tempStr.lastIndexOf("\|"));
    pro.testType.Unit = tempStr.right(tempStr.length() - tempStr.lastIndexOf("\|") - 1);



    //值
    tempStr = tempStr.left(tempStr.lastIndexOf("\|"));
    qDebug() << __LINE__ << tempStr;
    pro.testType.Value = tempStr.right(tempStr.length() - tempStr.lastIndexOf("\|") - 1).toDouble();
    qDebug() << "value: " << pro.testType.Value;

    //项目名称
    exp = QString::fromLatin1("\\^\\d{0,}\\^{2}[A-Z]");
    tempStr = tempStr.left(tempStr.indexOf(QRegularExpression(exp)));
    pro.testType.TestTypeCode = tempStr.right(tempStr.length() - tempStr.lastIndexOf("\^") - 1);
}

void parserThread::parserSampleId(MyProject &pro, const QString &parsedString)
{
    QString tempStr = parsedString;
    QString exp = "";

    //检测项目名称
    exp = QString::fromLatin1("\\^\\d{0,}\\|[A-Z,a-z]\\|{0,}");
    tempStr = tempStr.left(tempStr.indexOf(QRegularExpression(exp)));
    pro.testTypeCode = tempStr.right(tempStr.length() - tempStr.lastIndexOf("\^") - 1);

    //样本号
    exp = QString::fromLatin1("\\|\\d{0,}\\|\\^{3}\\d{0,}\\^");
    tempStr = tempStr.left(tempStr.indexOf(QRegularExpression(exp)));
    pro.sampleId = tempStr.right(tempStr.length() - tempStr.lastIndexOf("\|") - 1);

    //子项目个数
    tempStr = tempStr.left(tempStr.lastIndexOf("\|"));
    pro.subProjectCount = tempStr.right( tempStr.length() - tempStr.lastIndexOf("\|") - 1).toInt();
}

QStringList parserThread::split(const QString &desStr, const QRegularExpression &re, QString::SplitBehavior behavior) const
{
    return desStr.split(re,behavior);
}

void parserThread::getFromJsonData(const QByteArray &jsonData)
{
    qDebug() << __FUNCTION__ << __LINE__ << jsonData;

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
                        project->DeviceId = device.DeviceId;
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
//                        qDebug() << "dataTime: " << dataTime;
                        result->TestTime = dataTime;
                    }
                    ResultVec.push_back(result);
                    ProjectVec.push_back(project);
                    TestTypeVec.push_back(testtype);
                }
            }
        }
    }


    foreach (Result *result, ResultVec) {
       qDebug() << "value: " << result->value;
       qDebug() << "testTime: " << result->TestTime;
    }
    foreach (Project *pro, ProjectVec) {
        qDebug() << "projectName: " << pro->ProjectName;
    }
    foreach (TestType *testtype, TestTypeVec) {
        qDebug() << "testTypeCode: " << testtype->TestTypeCode;
    }
}

void parserThread::CommitToDatabase()
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

            query.clear();
            query.prepare("insert into Project(ProjectId,ProjectName,EnglishName,CustomName,TestTypeId,DeviceId,DensityConut,PerDayBatch,DispIdx,CreateTime) values(:ProjectId,:ProjectName,:EnglishName,:CustomName,:TestTypeId,:DeviceId,:DensityConut,:PerDayBatch,:DispIdx,:CreateTime)");
            query.bindValue(":ProjectId",pro->ProjectId);
            query.bindValue(":ProjectName",pro->ProjectName);
            query.bindValue(":EnglishName","");
            query.bindValue(":CustomName",pro->CustomName);
            query.bindValue(":TestTypeId",pro->testType.TestTypeId);
            query.bindValue(":DeviceId","");
            query.bindValue(":DensityConut","1");
            query.bindValue(":PerDayBatch","");
            query.bindValue(":DispIdx","");
            query.bindValue(":CreateTime","");
            query.exec();

        }//project


        foreach (Result *result, ResultVec) {
            query.clear();
            query.prepare("select * from Result where ProjectId = :ProjectId and TestTime = :TestTime ");
            query.bindValue(":ProjectId",result->ProjectId);
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
                query.bindValue(":DensityId","");
                query.bindValue(":Project_DetailId","");
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
                    query.bindValue(":DensityId","");
                    query.bindValue(":Project_DetailId","");
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
    }//db.open
    else
    {
        QMessageBox::warning(NULL,QString("警告"),QString("数据打开失败。。。"),QMessageBox::Ok);
//        return false;
    }
}

void parserThread::run()
{
    QFile file(filePath);
    if( !file.open(QIODevice::ReadWrite) )
    {
        qDebug() << file.errorString();
        return;
    }

    QString content;
    content.append(file.readAll());
    qDebug() << content;
    file.close();
    QByteArray parserdStr = parser(content);
    getFromJsonData(parserdStr);
    CommitToDatabase();
}
