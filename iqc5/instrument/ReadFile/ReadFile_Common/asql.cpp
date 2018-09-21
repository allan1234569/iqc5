#include "asql.h"
#include "common.h"

#include <QSqlError>
#include <QUuid>
#include <QDateTime>
#include <QRegularExpression>
#include "common.h"
ASql::ASql()
{

}

void ASql::init()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("mytest.db");
    db.setDatabaseName(g_sSqlPath);

//    db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName(g_sHostName);
//    db.setPort(g_nHostPort);
//    db.setDatabaseName("main");
//    db.setUserName("zhisheng");
//    db.setPassword("zhisheng2016");
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

int ASql::sendResult(QString as_item, QString as_result, int densityId, QString as_instr, QString as_installplace, QString as_resultDateTime, QString as_createDateTime)
{
    QSqlDatabase ld_db = QSqlDatabase(db);
    QUuid uuid;
    QString ls_uid;
    QString ls_dataTime;

    QString ls_testTypeId;
    QString ls_deviceId;
    QString ls_projectId;
    int li_densityCount;
    QString ls_projectDetailId;
    QString ls_resultId;

    QString sqlStr;

    ld_db.transaction();
    ///设备
    QSqlQuery query;
    sqlStr = "SELECT DeviceId, DeviceName, installplace FROM Device WHERE DeviceName = :DeviceName AND installplace = :installplace";
    query.prepare(sqlStr);
    query.bindValue(":DeviceName",as_instr.trimmed());
    query.bindValue(":installplace",as_installplace.trimmed());

    if (!query.exec())
    {
        f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
        ld_db.rollback();
        return 1;
    }

    if (!query.next())
    {
        ld_db.rollback();
        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("错误"));
        msgBox.setText(QObject::tr("服务器未注册此仪器的信息或解码程序仪器信息配置不正确\n请录入仪器信息后重新配置启动程序"));
        msgBox.exec();
        f_log("仪器信息配置错误，程序退出");

        return 2;
    }
    else
    {
        ls_deviceId = query.value("DeviceId").toString();
    }

    ///检测项目
    query.clear();
    query.prepare("SELECT TestTypeId, TestTypeCode FROM TestType WHERE TestTypeCode = :TestTypeCode");
    query.bindValue(":TestTypeCode",as_item);
    if (!query.exec())
    {
        f_log("SQL执行失败，错误：%s", query.lastError().text().toStdString().data());
        ld_db.rollback();
        return 1;
    }

    if (!query.next())
    {
        f_log("查询失败,没有找到项目类型%s",as_item.toStdString().data());
        ld_db.rollback();
        return 1;
//        ls_uid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"),"");
//        ls_testTypeId = ls_uid;
//        query.clear();
//        sqlStr = "INSERT INTO TestType(TestTypeId,CategoryId,TestTypeCode,TestTypeName,IfDefault,AddTime,Status) VALUES(:TestTypeId,:CategoryId,:TestTypeCode,:TestTypeName,:IfDefault,:AddTime,:Status)";
//        query.prepare(sqlStr);
//        query.bindValue(":TestTypeId",ls_testTypeId);
//        query.bindValue(":CategoryId","");
//        query.bindValue(":TestTypeCode",as_item);
//        query.bindValue(":TestTypeName",as_item);
//        query.bindValue(":IfDefault",0);
//        ls_dataTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//        query.bindValue(":AddTime",ls_dataTime);
//        query.bindValue(":Status",0);
//        if (!query.exec())
//        {
//            f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
//            ld_db.rollback();
//            return 1;
//        }

    }
    else
    {
        ls_testTypeId = query.value("TestTypeId").toString();
    }

    ///工程项目
    query.clear();
    query.prepare("SELECT ProjectId,CustomName,TestTypeId,DeviceId,DensityCount FROM Project WHERE CustomName = :CustomName and TestTypeId = :TestTypeId and DeviceId = :DeviceId");
    query.bindValue(":CustomName",as_item);
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

        f_log("没有找到匹配的项目%s，可能未配置该仪器下的项目",as_item.toStdString().data());
        ld_db.rollback();
        return 1;

//        ls_uid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"),"");
//        ls_projectId = ls_uid;
//        query.clear();
//        sqlStr = "INSERT INTO Project(ProjectId,ProjectName,EnglishName,CustomName,TestTypeId,DeviceId,DensityCount,PerDayBatch,DispIdx,CreateTime) VALUES(:ProjectId,:ProjectName,:EnglishName,:CustomName,:TestTypeId,:DeviceId,:DensityConut,:PerDayBatch,:DispIdx,:CreateTime)";
//        query.prepare(sqlStr);
//        query.bindValue(":ProjectId",ls_projectId);
//        query.bindValue(":ProjectName",as_CustomProjectName);    //样本号作为项目名
//        query.bindValue(":EnglishName","");
//        query.bindValue(":CustomName",as_CustomProjectName);     //用质控项目代号来代替
//        query.bindValue(":TestTypeId",ls_testTypeId);
//        query.bindValue(":DeviceId",ls_deviceId);
//        query.bindValue(":DensityCount",densityId);
//        query.bindValue(":PerDayBatch",1);
//        query.bindValue(":DispIdx",1);
//        ls_dataTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//        query.bindValue(":CreateTime",ls_dataTime);
//        if (!query.exec())
//        {
//            f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
//            ld_db.rollback();
//            return 1;
//        }

    }
    else
    {
        ls_projectId = query.value("ProjectId").toString();
        li_densityCount = query.value("DensityCount").toInt();
        li_densityCount = qMax(li_densityCount,densityId);

        query.clear();
        sqlStr = "UPDATE Project SET DensityCount = :DensityId WHERE ProjectId = :ProjectId";
        query.prepare(sqlStr);
        query.bindValue(":DensityId",li_densityCount);
        query.bindValue(":ProjectId",ls_projectId);
        if (!query.exec())
        {
            f_log("SQL语句执行失败，错误：%s(错误语句:%s)", query.lastError().text().toStdString().data(),sqlStr.toStdString().data());
            ld_db.rollback();
            return 1;
        }
    }

    ///项目明细
    query.clear();
    sqlStr = "SELECT Project_DetailId,ProjectId,DensityId,Useflag FROM Project_Detail WHERE ProjectId = :ProjectId AND DensityId = :DensityId AND Useflag = :Useflag";
    query.prepare(sqlStr);
    query.bindValue(":ProjectId",ls_projectId);
    query.bindValue(":DensityId",densityId);
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
        query.bindValue(":DensityId",densityId);
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

    ///结果
    query.clear();
    sqlStr = "SELECT * FROM Result WHERE ProjectId = :ProjectId AND Project_DetailId = :Project_DetailId AND DensityId = :DensityId AND TestTime = :TestTime ";
    query.prepare(sqlStr);
    query.bindValue(":ProjectId",ls_projectId);
    query.bindValue(":Project_DetailId",ls_projectDetailId);
    query.bindValue(":DensityId",densityId);
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
        query.bindValue(":DensityId",densityId);
        query.bindValue(":Project_DetailId",ls_projectDetailId);
        query.bindValue(":ResultNum",1);
        query.bindValue(":TestTime",as_resultDateTime);
        query.bindValue(":Value",as_result);
        query.bindValue(":CreateTime",as_createDateTime);
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
        sqlStr = "SELECT MAX(ResultNum) AS ResultNum FROM Result WHERE ProjectId = :ProjectId And Project_DetailId = :Project_DetailId And TestTime = :TestTime";
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

        int maxNum;

        if(query.next())
        {
             maxNum = query.value("ResultNum").toInt();
             maxNum += 1;

             ls_uid = uuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
             query.clear();
             sqlStr = "INSERT INTO Result(ResultId,ProjectId,DensityId,Project_DetailId,ResultNum,TestTime,Value,CreateTime,CreateUser,IfInput,InputBatchId) VALUES(:ResultId,:ProjectId,:DensityId,:Project_DetailId,:ResultNum,:TestTime,:Value,:CreateTime,:CreateUser,:IfInput,:InputBatchId)";
             query.prepare(sqlStr);

             query.bindValue(":ResultId",ls_uid);
             query.bindValue(":ProjectId",ls_projectId);
             query.bindValue(":DensityId",densityId);
             query.bindValue(":Project_DetailId",ls_projectDetailId);
             query.bindValue(":ResultNum",maxNum);
             query.bindValue(":TestTime",as_resultDateTime);
             query.bindValue(":Value",as_result);
             query.bindValue(":CreateTime",as_createDateTime);
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
    QSqlQuery query;
    if (!query.exec("SELECT TestTypeCode FROM TestType WHERE TestTypeCode IS NOT NULL ORDER BY TestTypeCode ASC"))
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

QStringList ASql::SearchProjects(QString projectname)
{
    QStringList list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");

    db.setDatabaseName(g_sSqlPath);

    if(db.open())
    {
        QSqlQuery query;

        query.prepare("select Project.CustomName from Project where Project.CustomName like :CustomName");
        query.bindValue(":CustomName","%"+projectname+"%");
        query.exec();
        while(query.next())
        {
            list.append(query.value(0).toString());
        }
    }

    return list;
}

QStringList ASql::SearchMaterials(QString materialname)
{
    QStringList list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName(g_sSqlPath);
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("SELECT MaterialName FROM Material WHERE MaterialName LIKE :MaterialName");
        query.bindValue(":MaterialName","%"+materialname+"%");
        query.exec();
        while(query.next())
        {
            list.append(query.value(0).toString());
        }
    }

    return list;
}

QStringList ASql::SearchTestTypes(QString materialname)
{
    QStringList list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName(g_sSqlPath);
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select TestType.TestTypeCode from TestType "
                      "inner join TestType_Material on TestType_Material.MaterialId = Material.MaterialId "
                      "inner join Material on Material.MaterialName = :MaterialName "
                      "where TestType.TestTypeId = TestType_Material.TestTypeId "
                      "order by TestType.TestTypeCode");
        query.bindValue(":MaterialName", materialname);
        query.exec();
        while(query.next())
        {
            list.append(query.value(0).toString());
        }
    }

    return list;
}

bool ASql::testConnection()
{
    QFile file(g_sSqlPath);
    if (!file.exists())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("错误"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(QObject::tr("数据库路径错误，请检查后重新打开"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,QObject::tr("确定"));
        msgBox.exec();
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName(g_sSqlPath);

    if (!db.open())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("错误"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(QObject::tr("无法连接数据库，请检查后重新打开"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,QObject::tr("确定"));
        msgBox.exec();
        return false;
    }

    return true;
}
