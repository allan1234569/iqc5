#include "asql.h"
#include "common.h"

#include <QSqlError>
#include <QUuid>
#include <QDateTime>
#include <QRegularExpression>

ASql::ASql()
{

}



void ASql::init()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(g_sHostName);
    db.setPort(g_nHostPort);
    db.setDatabaseName("main");
    db.setUserName("heyi");
    db.setPassword("heyi1990");
}

bool ASql::open()
{
    if (!db.open())
    {
        init();
        if (!db.open())
        {
            switch (db.lastError().type()) {
            case QSqlError::ConnectionError:
                f_log("连接数据库失败");
                break;
            default:
                break;
            }

            return false;
        }
        else
        {
            return true;
        }
    }

    return true;
}

void ASql::close()
{
    QSqlDatabase ld_db = QSqlDatabase(db);
    ld_db.close();
}

int ASql::sendResult(QString as_sampleNo, QString as_itemCode, QString as_result, QString as_instr, QString as_labNo, QString as_resultDateTime) const
{
    QSqlDatabase ld_db = QSqlDatabase(db);
    QUuid uuid;
    QString ls_uid;
    QString ls_dataTime;

    QString ls_testTypeId;
    QString ls_deviceId;
    QString ls_projectId;
    QString ls_projectDetailId;

    QString sqlStr;

    ld_db.transaction();

    QSqlQuery query;
    query.prepare("SELECT TestTypeId, TestTypeCode FROM TestType WHERE TestTypeCode = :TestTypeCode");
    query.bindValue(":TestTypeCode",as_itemCode);
    if (!query.exec())
    {
        f_log("SQL执行失败，错误：%s", query.lastError().text().toStdString().data());
        ld_db.rollback();
        return 1;
    }

    if (!query.next())  //???没法确保证只有一条记录
    {
        ls_uid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"),"");
        ls_testTypeId = ls_uid;
        query.clear();
        sqlStr = "INSERT INTO TestType(TestTypeId,CategoryId,TestTypeCode,TestTypeName,IfDefault,AddTime,Status) VALUES(:TestTypeId,:CategoryId,:TestTypeCode,:TestTypeName,:IfDefault,:AddTime,:Status)";
        query.prepare(sqlStr);
        query.bindValue(":TestTypeId",ls_testTypeId);
        query.bindValue(":CategoryId","");
        query.bindValue(":TestTypeCode",as_itemCode);
        query.bindValue(":TestTypeName",as_itemCode);
        query.bindValue(":IfDefault",0);
        ls_dataTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        query.bindValue(":AddTime",ls_dataTime);
        query.bindValue(":Status",0);
        if (!query.exec())
        {
            f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
            ld_db.rollback();
            return 1;
        }

    }
    else
    {
        ls_testTypeId = query.value("TestTypeId").toString();
        qDebug() << ls_testTypeId;
    }


    query.clear();
    sqlStr = "SELECT DeviceId, DeviceName, LabNo FROM Device WHERE DeviceName = :DeviceName AND LabNo = :LabNo";
    query.prepare(sqlStr);
    query.bindValue(":DeviceName",as_instr);
    query.bindValue(":LabNo",as_labNo.toInt());

    qDebug() <<sqlStr << as_instr << as_labNo;

    if (!query.exec())
    {
        f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
        ld_db.rollback();
        return 1;
    }

    if (!query.next())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("错误"));
        msgBox.setText(QObject::tr("服务器未找到此仪器的信息,程序即将退出\n请录入仪器信息后重新配置启动程序"));
        msgBox.exec();
        f_log("仪器信息配置错误，程序退出");
        return 2;
    }
    else
    {
        ls_deviceId = query.value("DeviceId").toString();
    }

    query.clear();
    query.prepare("SELECT ProjectId, ProjectName,CustomName,TestTypeId,DeviceId FROM Project WHERE ProjectName = :ProjectName and TestTypeId = :TestTypeId and DeviceId = :DeviceId");
    query.bindValue(":ProjectName",as_sampleNo);
    //            query.bindValue(":CustomName",pro->CustomName);
    query.bindValue(":TestTypeId",ls_testTypeId);
    query.bindValue(":DeviceId",ls_deviceId);
    if (!query.exec())
    {
        f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
        ld_db.rollback();
        return 1;
    }

    if (!query.next())
    {
        ls_uid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"),"");
        ls_projectId = ls_uid;
        query.clear();
        sqlStr = "INSERT INTO Project(ProjectId,ProjectName,EnglishName,CustomName,TestTypeId,DeviceId,DensityConut,PerDayBatch,DispIdx,CreateTime) VALUES(:ProjectId,:ProjectName,:EnglishName,:CustomName,:TestTypeId,:DeviceId,:DensityConut,:PerDayBatch,:DispIdx,:CreateTime)";
        query.prepare(sqlStr);
        query.bindValue(":ProjectId",ls_projectId);
        query.bindValue(":ProjectName",as_sampleNo);    //样本号作为项目名
        query.bindValue(":EnglishName","");
        query.bindValue(":CustomName",as_itemCode);     //用质控项目代号来代替
        query.bindValue(":TestTypeId",ls_testTypeId);
        query.bindValue(":DeviceId",ls_deviceId);
        query.bindValue(":DensityConut",1);           //默认一个浓度,不知道如何区分浓度
        query.bindValue(":PerDayBatch",1);
        query.bindValue(":DispIdx",1);
        ls_dataTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        query.bindValue(":CreateTime",ls_dataTime);
        if (!query.exec())
        {
            f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
            ld_db.rollback();
            return 1;
        }
    }
    else
    {
        ls_projectId = query.value("ProjectId").toString();
    }


    query.clear();
    sqlStr = "SELECT Project_DetailId,ProjectId,DensityId,Useflag FROM Project_Detail WHERE ProjectId = :ProjectId AND DensityId = :DensityId AND Useflag = :Useflag";
    query.prepare(sqlStr);
    query.bindValue(":ProjectId",ls_projectId);
    query.bindValue(":DensityId",1);            //浓度水平，因为只有一个浓度水平，自然是1了
    query.bindValue(":Useflag",1);              //表示使用中
    if (!query.exec())
    {
        f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
        ld_db.rollback();
        return 1;
    }

    if (!query.next())
    {
        ls_uid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"),"");
        ls_projectDetailId = ls_uid;

        query.clear();
        sqlStr = "INSERT INTO Project_Detail(Project_DetailId,ProjectId,DensityId,Useflag) VALUES(:Project_DetailId,:ProjectId,:DensityId,:Useflag)";
        query.prepare(sqlStr);
        query.bindValue(":Project_DetailId",ls_projectDetailId);
        query.bindValue(":ProjectId",ls_projectId);
        query.bindValue(":DensityId",1);
        query.bindValue(":Useflag",1);
        if (!query.exec())
        {
            f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
            ld_db.rollback();
            return 1;
        }
    }
    else
    {
        ls_projectDetailId = query.value("Project_DetailId").toString();
    }

    ///Result
    query.clear();
    sqlStr = "SELECT * FROM Result WHERE ProjectId = :ProjectId AND TestTime = :TestTime ";
    query.prepare(sqlStr);
    query.bindValue(":ProjectId",ls_projectId);
    query.bindValue(":Project_DetailId",ls_projectDetailId);
    query.bindValue(":TestTime",as_resultDateTime);
    if (!query.exec())
    {
        f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
        ld_db.rollback();
        return 1;
    }

    if (!query.next())
    {
        ls_uid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"),"");

        query.clear();
        sqlStr = "INSERT INTO Result(ResultId,ProjectId,DensityId,Project_DetailId,ResultNum,TestTime,Value,CreateTime,CreateUser,IfInput,InputBatchId) VALUES(:ResultId,:ProjectId,:DensityId,:Project_DetailId,:ResultNum,:TestTime,:Value,:CreateTime,:CreateUser,:IfInput,:InputBatchId)";
        query.prepare(sqlStr);

        query.bindValue(":ResultId",ls_uid);
        query.bindValue(":ProjectId",ls_projectId);
        query.bindValue(":DensityId",1);        //浓度默认1
        query.bindValue(":Project_DetailId",ls_projectDetailId);
        query.bindValue(":ResultNum",1);
        query.bindValue(":TestTime",as_resultDateTime);
        query.bindValue(":Value",as_result);
        query.bindValue(":CreateTime","");
        query.bindValue(":CreateUser","");
        query.bindValue(":IfInput",0);
        query.bindValue(":InputBatchId","");
        if (!query.exec())
        {
            f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
            ld_db.rollback();
            return 1;
        }
    }
    else
    {
        query.clear();
        sqlStr = "SELECT Max(ResultNum) AS ResultNum FROM Result WHERE ProjectId = :ProjectId AND　ProjectDetailId = :ProjectDetailId AND TestTime = :TestTime";
        query.prepare(sqlStr);
        query.bindValue(":ProjectId",ls_projectId);
        query.bindValue(":ProjectDetailId",ls_projectDetailId);
        query.bindValue(":TestTime",as_resultDateTime);
        if (!query.exec())
        {
            f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
            ld_db.rollback();
            return 1;
        }

        QString maxNum;

        if(query.next())
        {
             maxNum = query.value("ResultNum").toString();
             maxNum += 1;

             ls_uid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
             query.clear();
             sqlStr = "INSERT INTO Result(ResultId,ProjectId,DensityId,Project_DetailId,ResultNum,TestTime,Value,CreateTime,CreateUser,IfInput,InputBatchId) VALUES(:ResultId,:ProjectId,:DensityId,:Project_DetailId,:ResultNum,:TestTime,:Value,:CreateTime,:CreateUser,:IfInput,:InputBatchId)";
             query.prepare(sqlStr);

             query.bindValue(":ResultId",ls_uid);
             query.bindValue(":ProjectId",ls_projectId);
             query.bindValue(":DensityId",1);
             query.bindValue(":Project_DetailId",ls_projectDetailId);
             query.bindValue(":ResultNum",maxNum);
             query.bindValue(":TestTime",as_resultDateTime);
             query.bindValue(":Value",as_result);
             query.bindValue(":CreateTime","");
             query.bindValue(":CreateUser","");
             query.bindValue(":IfInput","");
             query.bindValue(":InputBatchId","");
             if (!query.exec())
             {
                 f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
                 ld_db.rollback();
                 return 1;
             }
        }
    }

    ld_db.commit();

    return 0;
}

QStringList ASql::getItems()
{
    QStringList list;
    QSqlDatabase ldb_db = QSqlDatabase(db);
    QSqlQuery query;
    if (!query.exec("SELECT TestTypeCode FROM TestType ORDER BY TestTypeCode ASC"))
    {

    }
    else
    {
        while(query.next())
        {
            list.append(query.value("TestTypeCode").toString());
        }

    }

    return list;

}

void ASql::handleError(const QString errorString)
{
    f_log("SQL查询错误，错误语句：%s", errorString.toStdString().data());
}
