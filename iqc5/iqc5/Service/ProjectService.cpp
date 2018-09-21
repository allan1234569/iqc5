#include "ProjectService.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QObject>
#include <QVariantList>
#include <QTextCodec>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QUuid>
#include <QRegularExpression>
#include "MaterialBatchService.h"
#include "ReagentBatchService.h"
#include "MethodService.h"
#include "MaterialService.h"
#include "ReagentService.h"

ProjectService::ProjectService()
{
}

Project ProjectService::GetById(QString ProjectId)
{
    Project proj;
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select project.projectId,project.projectName, EnglishName,CustomName,Category.parentId SubjectId,TestType.CategoryId, Category.CategoryName,TestType.TestTypeId, "
                      " project.deviceId,deviceName, DensityCount,PerDayBatch,DispIdx,Material.MaterialId,Material.MaterialName,Reagent.ReagentId,Reagent.ReagentName,Method.methodId,Method.MethodName "
                      " from Project "
                      " inner join project_detail d on  project.projectId=d.projectid and d.useflag=1 "
                      " inner join TestType on project.TestTypeId=TestType.TestTypeId "
                      " inner join Category on TestType.CategoryId=Category.CategoryId "
                      " left join Material on d.MaterialId=Material.MaterialId "
                      " left join Reagent on d.ReagentId=Reagent.ReagentId "
                      " left join Device on project.deviceId=Device.DeviceId "
                      " left join Method on d.MethodId=Method.MethodId "
                      " where project.ProjectId = :ProjectId "
                      " order by project.ProjectId ");
        query.bindValue(":ProjectId", ProjectId);
        query.exec();
        while(query.next())
        {
            proj.ProjectId=query.value(0).toString();
            proj.ProjectName=query.value(1).toString();
            proj.EnglishName=query.value(2).toString();
            proj.CustomName=query.value(3).toString();
            proj.testType.SubjectId=query.value(4).toString();
            proj.testType.CategoryId =query.value(5).toString();
            proj.testType.CategoryName =query.value(6).toString();
            proj.testType.TestTypeId=query.value(7).toString();
            proj.DeviceId=query.value(8).toString();
            proj.DeviceName=query.value(9).toString();
            proj.level=query.value(10).toInt();
            proj.PerDayBatch=query.value(11).toInt();
            proj.DispIdx=query.value(12).toInt();
            proj.MaterialId=query.value(13).toString();
            proj.MaterialName=query.value(14).toString();
            proj.ReagentId=query.value(15).toString();
            proj.ReagentName=query.value(16).toString();
            proj.MethodId=query.value(17).toString();
            proj.MethodName=query.value(18).toString();


            query.prepare(" select Result.ResultId,Result.ProjectId,Result.DensityId,Result.Project_DetailId,ResultNum,TestTime,Value,Result.CreateTime,Result.CreateUser,IfInput,InputBatchId from Result "
                          " inner join Project_Detail on Result.Project_DetailId=Project_Detail.Project_DetailId where Result.ProjectId=:ProjectId ");
            query.bindValue(":projectId", proj.ProjectId);
            query.exec();
            while(query.next())
            {
                Result result;
                result.ResultId=query.value(0).toString();
                result.ProjectId=query.value(1).toString();
                result.level=query.value(2).toInt();
                result.detail.Project_DetailId=query.value(3).toString();
                result.ResultNum=query.value(4).toInt();
                result.TestTime=query.value(5).toString();
                result.value=query.value(6).toDouble();

                proj.results.append(result);
            }

            proj.Init();

            return proj;
        }
    }
    return proj;
}


QVector<Project> ProjectService::SearchProject(QString SubjectId,QString CategoryId,QString keyword,QString DeviceName)
{
    QVector<Project> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select distinct project.projectId,project.projectName, EnglishName,CustomName,Category.parentId SubjectId,TestType.CategoryId, Category.CategoryName,Subject.CategoryName SubjectName,TestType.TestTypeId, "
                      " project.deviceId,deviceName, DensityCount,PerDayBatch,DispIdx,UnitName "
                      " from Project "
                      " inner join TestType on project.TestTypeId=TestType.TestTypeId "
                      " inner join Category on TestType.CategoryId=Category.CategoryId "
                      " inner join Category Subject on Category.parentId=Subject.CategoryId "
                      " left join Device on project.deviceId=Device.DeviceId "
                      " left join Device_Unit on Device.DeviceId=Device_Unit.DeviceId "
                      " left join Unit on Device_Unit.UnitId=Unit.UnitId "
                      " where Category.parentId like :SubjectId "
                      " and Category.CategoryId like :CategoryId "
                      " and (project.ProjectName like :keyword or project.EnglishName like :keyword or project.CustomName like :keyword) "
                      " and (Device.DeviceName like :DeviceName or Device.DeviceName is null) "
                      " order by project.deviceId,project.DispIdx "
                      );
        query.bindValue(":SubjectId", "%"+SubjectId+"%");
        query.bindValue(":CategoryId", "%"+CategoryId+"%");
        query.bindValue(":keyword", "%"+keyword+"%");
        query.bindValue(":DeviceName", "%"+DeviceName+"%");
        query.exec();
        while(query.next())
        {
            Project proj;
            proj.ProjectId=query.value(0).toString();
            proj.ProjectName=query.value(1).toString();
            proj.EnglishName=query.value(2).toString();
            proj.CustomName=query.value(3).toString();
            proj.testType.SubjectId=query.value(4).toString();
            proj.testType.CategoryId =query.value(5).toString();
            proj.testType.CategoryName =query.value(6).toString();
            proj.testType.SubjectName =query.value(7).toString();
            proj.testType.TestTypeId=query.value(8).toString();
            proj.DeviceId=query.value(9).toString();
            proj.DeviceName=query.value(10).toString();
            proj.level=query.value(11).toInt();
            proj.PerDayBatch=query.value(12).toInt();
            proj.DispIdx=query.value(13).toInt();
            proj.UnitName=query.value(14).toString();

            list.append(proj);
        }
    }
    return list;
}

QVector<Project> ProjectService::SearchProject(QString SubjectId,QString CategoryId,QString keyword,QString MaterialName,QString ReagentName,QString MethodName,QString DeviceName)
{
    QVector<Project> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select distinct project.projectId,project.projectName, EnglishName,CustomName,Category.parentId SubjectId,TestType.CategoryId, Category.CategoryName,Subject.CategoryName SubjectName,TestType.TestTypeId, "
                      " project.deviceId,deviceName, DensityId,PerDayBatch,DispIdx,Material.MaterialId,Material.MaterialName,Reagent.ReagentId,Reagent.ReagentName,Method.methodId,Method.MethodName,UnitName "
                      " from Project "
                      " inner join project_detail d on  project.projectId=d.projectid and d.useflag=1 "
                      " inner join TestType on project.TestTypeId=TestType.TestTypeId "
                      " inner join Category on TestType.CategoryId=Category.CategoryId "
                      " inner join Category Subject on Category.parentId=Subject.CategoryId "
                      " left join Material on d.MaterialId=Material.MaterialId "
                      " left join Reagent on d.ReagentId=Reagent.ReagentId "
                      " left join Device on project.deviceId=Device.DeviceId "
                      " left join Method on d.MethodId=Method.MethodId "
                      " left join Device_Unit on Device.DeviceId=Device_Unit.DeviceId "
                      " left join Unit on Device_Unit.UnitId=Unit.UnitId "
                      " where Category.parentId like :SubjectId "
                      " and Category.CategoryId like :CategoryId "
                      " and (project.ProjectName like :keyword or project.EnglishName like :keyword or project.CustomName like :keyword) "
                      " and Material.MaterialName like :MaterialName "
                      " and Reagent.ReagentName like :ReagentName "
                      " and Method.MethodName like :MethodName "
                      " and (Device.DeviceName like :DeviceName or Device.DeviceName is null) "
                      " order by project.DispIdx "
                      );
        query.bindValue(":SubjectId", "%"+SubjectId+"%");
        query.bindValue(":CategoryId", "%"+CategoryId+"%");
        query.bindValue(":keyword", "%"+keyword+"%");
        query.bindValue(":MaterialName", "%"+MaterialName+"%");
        query.bindValue(":ReagentName", "%"+ReagentName+"%");
        query.bindValue(":MethodName", "%"+MethodName+"%");
        query.bindValue(":DeviceName", "%"+DeviceName+"%");
        query.exec();
        while(query.next())
        {

            Project proj;
            proj.ProjectId=query.value(0).toString();
            proj.ProjectName=query.value(1).toString();
            proj.EnglishName=query.value(2).toString();
            proj.CustomName=query.value(3).toString();
            proj.testType.SubjectId=query.value(4).toString();
            proj.testType.CategoryId =query.value(5).toString();
            proj.testType.CategoryName =query.value(6).toString();
            proj.testType.SubjectName =query.value(7).toString();
            proj.testType.TestTypeId=query.value(8).toString();
            proj.DeviceId=query.value(9).toString();
            proj.DeviceName=query.value(10).toString();
            proj.level=query.value(11).toInt();
            proj.PerDayBatch=query.value(12).toInt();
            proj.DispIdx=query.value(13).toInt();
            proj.MaterialId=query.value(14).toString();
            proj.MaterialName=query.value(15).toString();
            proj.ReagentId=query.value(16).toString();
            proj.ReagentName=query.value(17).toString();
            proj.MethodId=query.value(18).toString();
            proj.MethodName=query.value(19).toString();
            proj.UnitName=query.value(20).toString();

            list.append(proj);

        }
    }
    return list;
}


QString ProjectService::Insert(Project project)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into project (ProjectId,ProjectName,EnglishName,CustomName,TestTypeId,DeviceId,MethodId,DensityCount,PerDayBatch,DispIdx,CreateTime,CreateUser,Status) "
                      " values (:ProjectId,:ProjectName,:EnglishName,:CustomName,:TestTypeId,:DeviceId,:MethodId,:DensityCount,:PerDayBatch,:DispIdx,:CreateTime,:CreateUser,:Status)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":ProjectId", guid);
        query.bindValue(":ProjectName", project.ProjectName);
        query.bindValue(":EnglishName", project.EnglishName);
        query.bindValue(":CustomName", project.CustomName);
        query.bindValue(":TestTypeId", project.testType.TestTypeId);
        query.bindValue(":DeviceId", project.DeviceId);
        query.bindValue(":MethodId", project.MethodId);
        query.bindValue(":DensityCount", project.level);
        query.bindValue(":PerDayBatch", project.PerDayBatch);
        query.bindValue(":DispIdx", project.DispIdx);
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        query.bindValue(":CreateTime", time);
        query.bindValue(":CreateUser", project.CreatorId);
        query.bindValue(":Status", "1");

        query.exec();

//        MaterialBatchService mbs;
//        QString materialBatchId="";
//        if(project.CurrentMaterialBatch != "")
//        {
//            MaterialBatch b;
//            b.MaterialId = project.MaterialId;
//            b.BatchNo = project.CurrentMaterialBatch;
//            b.CreateTime = time;
//            b.StartDate = time;
//            b.Status = 1;
//            materialBatchId = mbs.Insert(b);
//        }
//        ReagentBatchService rbs;
//        QString reagentBatchId="";
//        if(project.CurrentReagentBatch != "")
//        {
//            ReagentBatch b;
//            b.ReagentId = project.ReagentId;
//            b.BatchNo = project.CurrentReagentBatch;
//            b.CreateTime = time;
//            b.StartDate = time;
//            b.Status = 1;
//            reagentBatchId = rbs.Insert(b);
//        }

//        for(int i=1;i<=project.level;i++)
//        {
//            ProjectDetail detail;
//            detail.ProjectId=guid;
//            detail.CreateTime=time;
//            detail.DensityId=i;
//            detail.MaterialId=project.MaterialId;
//            detail.MaterialBatchId = materialBatchId;
//            detail.ReagentId=project.ReagentId;
//            detail.ReagentBatchId = reagentBatchId;
//            detail.MethodId=project.MethodId;
//            detail.Status=1;
//            detail.Useflag=1;
//            detail.CreateUser=project.CreatorId;
//            InsertDetail(detail);
//        }

        return guid;
    }
    return "";
}


QString ProjectService::InsertDetail(ProjectDetail detail)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;

        query.prepare("update project_detail set useflag=0 where ProjectId=:ProjectId and DensityId=:DensityId");
        query.bindValue(":ProjectId", detail.ProjectId);
        query.bindValue(":DensityId", detail.DensityId);
        query.exec();

        query.prepare("insert into project_detail (Project_DetailId,ProjectId,DensityId,DensityName,MaterialId,MaterialBatchId,ReagentId,ReagentBatchId,Useflag,CreateTime,CreateUser,Status,MethodId) "
                      " values (:Project_DetailId,:ProjectId,:DensityId,:DensityName,:MaterialId,:MaterialBatchId,:ReagentId,:ReagentBatchId,:Useflag,:CreateTime,:CreateUser,:Status,:MethodId)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":Project_DetailId", guid);
        query.bindValue(":ProjectId", detail.ProjectId);
        query.bindValue(":DensityId", detail.DensityId);
        query.bindValue(":DensityName", detail.DensityName);
        query.bindValue(":MaterialId", detail.MaterialId);
        query.bindValue(":MaterialBatchId", detail.MaterialBatchId);
        query.bindValue(":ReagentId", detail.ReagentId);
        query.bindValue(":ReagentBatchId", detail.ReagentBatchId);
        query.bindValue(":Useflag", "1");
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        query.bindValue(":CreateTime", time);
        query.bindValue(":CreateUser", detail.CreateUser);
        query.bindValue(":Status", "1");
        query.bindValue(":MethodId", detail.MethodId);

        query.exec();


        return guid;
    }
    return "";
}

QString ProjectService::UpdateDetail(ProjectDetail detail)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update project_detail set ProjectId=:ProjectId,DensityId=:DensityId,DensityName=:DensityName,"
                      "MaterialId=:MaterialId,MaterialBatchId=:MaterialBatchId,ReagentId=:ReagentId,ReagentBatchId=:ReagentBatchId,MethodId=:MethodId where Project_DetailId=:Project_DetailId  ");
        query.bindValue(":Project_DetailId", detail.Project_DetailId);
        query.bindValue(":ProjectId", detail.ProjectId);
        query.bindValue(":DensityId", detail.DensityId);
        query.bindValue(":DensityName", detail.DensityName);
        query.bindValue(":MaterialId", detail.MaterialId);
        query.bindValue(":MaterialBatchId", detail.MaterialBatchId);
        query.bindValue(":ReagentId", detail.ReagentId);
        query.bindValue(":ReagentBatchId", detail.ReagentBatchId);
        query.bindValue(":MethodId", detail.MethodId);

        query.exec();


        return "";
    }
    return "";
}

QString ProjectService::InsertResult(Result result)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("insert into result (ResultId,ProjectId,DensityId,Project_DetailId,ResultNum,TestTime,Value,CreateTime) values (:ResultId,:ProjectId,:DensityId,:Project_DetailId,:ResultNum,:TestTime,:Value,:CreateTime)");
        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        query.bindValue(":ResultId", guid);
        query.bindValue(":ProjectId", result.ProjectId);
        query.bindValue(":DensityId", result.level);
        query.bindValue(":Project_DetailId", result.detail.Project_DetailId);
        query.bindValue(":ResultNum", result.ResultNum);
        query.bindValue(":TestTime", result.TestTime);
        query.bindValue(":Value", result.value);
        query.bindValue(":CreateTime", result.CreateTime);

        query.exec();

        return guid;
    }
    return "";
}


void ProjectService::UpdateResult(Result result)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;

        query.prepare("update result set ProjectId=:ProjectId,DensityId=:DensityId,Project_DetailId=:Project_DetailId,ResultNum=:ResultNum,TestTime=:TestTime,value =:value where ResultId=:ResultId");

        query.bindValue(":ProjectId", result.ProjectId);
        query.bindValue(":DensityId", result.level);
        query.bindValue(":Project_DetailId", result.detail.Project_DetailId);
        query.bindValue(":ResultNum", result.ResultNum);
        query.bindValue(":TestTime", result.TestTime);
        query.bindValue(":value", result.value);
        query.bindValue(":ResultId", result.ResultId);
        query.exec();
    }
}

bool ProjectService::DeleteResult(QString ResultId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from Result where ResultId =:ResultId");
        query.bindValue(":ResultId", ResultId);
        return query.exec();
    }

    return false;
}

void ProjectService::UpdateModel(Project project)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("update project set ProjectName=:ProjectName,EnglishName=:EnglishName,CustomName=:CustomName,TestTypeId=:TestTypeId,DeviceId=:DeviceId, "
                      " DensityCount=:DensityCount,PerDayBatch=:PerDayBatch,DispIdx=:DispIdx where ProjectId=:ProjectId ");

        query.bindValue(":ProjectName", project.ProjectName);
        query.bindValue(":EnglishName", project.EnglishName);
        query.bindValue(":CustomName", project.CustomName);
        query.bindValue(":TestTypeId", project.testType.TestTypeId);

        query.bindValue(":DeviceId", project.DeviceId);
        query.bindValue(":DensityCount", project.level);
        query.bindValue(":PerDayBatch", project.PerDayBatch);
        query.bindValue(":DispIdx", project.DispIdx);
        query.bindValue(":ProjectId", project.ProjectId);

        query.exec();
    }
}


void ProjectService::UpdateDetailAndResult(Result result)
{
    MaterialBatchService materialBatchService;
    ReagentBatchService reagentBatchService;

    //质控品批号
    QVector<MaterialBatch> mb = materialBatchService.GetMaterialBatchs(result.detail.MaterialId, result.detail.MaterialBatchName);
    if(mb.count()>0)
    {
        result.detail.MaterialBatchId=mb[0].MaterialBatchId;
    }
    else
    {
        if(result.detail.MaterialBatchName.length()>0)
        {
            MaterialBatch b;
            b.MaterialId=result.detail.MaterialId;
            b.BatchNo=result.detail.MaterialBatchName;
            b.StartDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
            result.detail.MaterialBatchId = materialBatchService.Insert(b);
        }
    }
    //试剂批号
    QVector<ReagentBatch> rb = reagentBatchService.GetReagentBatchs(result.detail.ReagentId, result.detail.ReagentBatchName);
    if(rb.count()>0)
    {
        result.detail.ReagentBatchId=rb[0].ReagentBatchId;
    }
    else
    {
        if(result.detail.ReagentBatchName.length()>0)
        {
            ReagentBatch b;
            b.ReagentId=result.detail.ReagentId;
            b.BatchNo=result.detail.ReagentBatchName;
            b.StartDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
            result.detail.ReagentBatchId = reagentBatchService.Insert(b);
        }
    }

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;

        query.prepare("select Project_DetailId from Project_Detail where projectId=:projectId and (MaterialId=:MaterialId ) and (ReagentId=:ReagentId) and (MethodId=:MethodId) "
                      " and (MaterialBatchId=:MaterialBatchId or MaterialBatchId is null) and (ReagentBatchId=:ReagentBatchId or ReagentBatchId is null) " );
        query.bindValue(":projectId", result.detail.ProjectId);
        query.bindValue(":MaterialId", result.detail.MaterialId);
        query.bindValue(":ReagentId", result.detail.ReagentId);
        query.bindValue(":MethodId", result.detail.MethodId);
        query.bindValue(":MaterialBatchId", result.detail.MaterialBatchId);
        query.bindValue(":ReagentBatchId", result.detail.ReagentBatchId);
        query.exec();
        if(query.next())
        {
            result.detail.Project_DetailId = query.value(0).toString();
            UpdateDetail(result.detail);

        }
        else
        {
            QString detailId = InsertDetail(result.detail);
            result.detail.Project_DetailId = detailId;
        }

        if(QString::compare(result.ResultId, "") !=0)
        {
            UpdateResult(result);
        }
        else
        {
            InsertResult(result);
        }
    }
}

void ProjectService::UpdateDetailAndResultBatch(QVector<QVector<Result> > results)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        db.transaction();

        for(int l = 0; l < results.count(); l++)
        {
            for(int i = 0; i < results[l].count(); i++)
            {
                Result result = results[l][i];
                MaterialBatchService materialBatchService;
                ReagentBatchService reagentBatchService;

                //质控品批号
                QSqlQuery query;
                query.prepare("select MaterialBatchId,materialBatch.MaterialId,Unit,package,RegisterNo,materialBatch.BatchNo,ValidDate,a.StartDate from materialBatch "
                              "left join (select project_Detail.MaterialId,batchno,min(testTime) startDate from result "
                              "inner join project_Detail on  result.project_DetailId=project_Detail.project_DetailId "
                              "inner join materialbatch on project_Detail.materialbatchId=materialbatch.materialbatchId "
                              "group by  project_Detail.MaterialId,batchno) a "
                              "on MaterialBatch.batchno=a.batchno and MaterialBatch.MaterialId=a.MaterialId "
                              "where materialBatch.MaterialId = :MaterialId and materialBatch.BatchNo like :BatchNo order by MaterialBatch.CreateTime ");
                query.bindValue(":MaterialId", result.detail.MaterialId);
                query.bindValue(":BatchNo", QString("%%1%").arg(result.detail.MaterialBatchName));
                query.exec();

                if(query.next())
                {
                    result.detail.MaterialBatchId = query.value(0).toString();
                }
                else
                {
                    if(result.detail.MaterialBatchName.length()>0)
                    {
                        MaterialBatch b;
                        b.MaterialId=result.detail.MaterialId;
                        b.BatchNo=result.detail.MaterialBatchName;
                        b.StartDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
                        result.detail.MaterialBatchId = materialBatchService.Insert(b);
                    }
                }
                //试剂批号
                query.clear();
                query.prepare("select ReagentBatchId,reagentBatch.ReagentId,Unit,package,RegisterNo,reagentBatch.BatchNo,ValidDate,a.StartDate from reagentBatch "
                              "left join (select project_Detail.ReagentId,batchno,min(testTime) startDate from result "
                              "inner join project_Detail on  result.project_DetailId=project_Detail.project_DetailId "
                              "inner join reagentBatch on project_Detail.ReagentBatchId=reagentBatch.ReagentBatchId "
                              "group by  project_Detail.ReagentId,batchno) a "
                              "on reagentBatch.batchno=a.batchno and reagentBatch.ReagentId=a.ReagentId "
                              "where reagentBatch.ReagentId = :ReagentId and reagentBatch.BatchNo like :BatchNo order by ReagentBatch.CreateTime ");
                query.bindValue(":ReagentId", result.detail.ReagentId);
                query.bindValue(":BatchNo", QString("%%1%").arg(result.detail.ReagentBatchName));
                query.exec();
                if(query.next())
                {
                    result.detail.ReagentBatchId = query.value(0).toString();
                }
                else
                {
                    if(result.detail.ReagentBatchName.length()>0)
                    {
                        ReagentBatch b;
                        b.ReagentId=result.detail.ReagentId;
                        b.BatchNo=result.detail.ReagentBatchName;
                        b.StartDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
                        result.detail.ReagentBatchId = reagentBatchService.Insert(b);
                    }
                }


                query.clear();
                query.prepare("select Project_DetailId from Project_Detail where projectId=:projectId and (MaterialId=:MaterialId ) and (ReagentId=:ReagentId) and (MethodId=:MethodId) "
                              " and (MaterialBatchId=:MaterialBatchId or MaterialBatchId is null) and (ReagentBatchId=:ReagentBatchId or ReagentBatchId is null) " );
                query.bindValue(":projectId", result.detail.ProjectId);
                query.bindValue(":MaterialId", result.detail.MaterialId);
                query.bindValue(":ReagentId", result.detail.ReagentId);
                query.bindValue(":MethodId", result.detail.MethodId);
                query.bindValue(":MaterialBatchId", result.detail.MaterialBatchId);
                query.bindValue(":ReagentBatchId", result.detail.ReagentBatchId);
                query.exec();
                if(query.next())
                {
                    result.detail.Project_DetailId = query.value(0).toString();
                    UpdateDetail(result.detail);

                }
                else
                {
                    QString detailId = InsertDetail(result.detail);
                    result.detail.Project_DetailId = detailId;
                }

                query.clear();
                if(QString::compare(result.ResultId, "") !=0)
                {
                    query.prepare("update result set ProjectId=:ProjectId,DensityId=:DensityId,Project_DetailId=:Project_DetailId,ResultNum=:ResultNum,TestTime=:TestTime,value =:value where ResultId=:ResultId");

                    query.bindValue(":ProjectId", result.ProjectId);
                    query.bindValue(":DensityId", result.level);
                    query.bindValue(":Project_DetailId", result.detail.Project_DetailId);
                    query.bindValue(":ResultNum", result.ResultNum);
                    query.bindValue(":TestTime", result.TestTime);
                    query.bindValue(":value", result.value);
                    query.bindValue(":ResultId", result.ResultId);
                    query.exec();
                }
                else
                {
                    query.prepare("insert into result (ResultId,ProjectId,DensityId,Project_DetailId,ResultNum,TestTime,Value,CreateTime) values (:ResultId,:ProjectId,:DensityId,:Project_DetailId,:ResultNum,:TestTime,:Value,:CreateTime)");
                    QUuid quuid;
                    QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
                    result.ResultId = guid;
                    query.bindValue(":ResultId", guid);
                    query.bindValue(":ProjectId", result.ProjectId);
                    query.bindValue(":DensityId", result.level);
                    query.bindValue(":Project_DetailId", result.detail.Project_DetailId);
                    query.bindValue(":ResultNum", result.ResultNum);
                    query.bindValue(":TestTime", result.TestTime);
                    query.bindValue(":Value", result.value);
                    query.bindValue(":CreateTime", result.CreateTime);

                    query.exec();
                }
            }
        }

        db.commit();
    }
}


QVector<Result> ProjectService::GetResult(QString ProjectId,QString date,int num,int level)
{
    QVector<Result> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select ResultId,Project_DetailId,value "
                      " from Result "
                      " where ProjectId=:ProjectId "
                      " and TestTime=:date "
                      " and ResultNum=:num "
                      " and DensityId=:level "
                      );
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":date", date);
        query.bindValue(":num", num);
        query.bindValue(":level", level);
        query.exec();
        while(query.next())
        {
            Result r;
            r.ResultId=query.value(0).toString();
            r.detail.Project_DetailId=query.value(1).toString();
            r.value=query.value(2).toDouble();

            list.append(r);
        }
    }
    return list;
}

QVector<Result> ProjectService::GetResult(QString ProjectId,int level, bool showAll)
{
    QVector<Result> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        if(showAll)
        {
            query.prepare("select ResultId,result.TestTime,ResultNum,result.Project_DetailId,value,Result.DensityId "
                      " from Result "
                      " where value>0 and result.ProjectId=:ProjectId "
                      " and result.DensityId=:level "
                      " order by result.TestTime,Result.ResultNum "
                      );
        }
        else
        {
            query.prepare("select ResultId,result.TestTime,ResultNum,result.Project_DetailId,value,Result.DensityId "
                      " from Result "
                      " inner join project_detail on Result.Project_DetailId=  project_detail.Project_DetailId "
                      " where value>0 and result.ProjectId=:ProjectId "
                      " and result.DensityId=:level and materialBatchId in (select materialBatchId from result inner join "
                      " (select projectId, DensityId, max(testtime) TestTime from  result group by projectId, DensityId) A "
                      " on result.projectid=A.projectid and result.DensityId=A.DensityId and result.TestTime=A.TestTime and "
                      " result.ProjectId=:ProjectId "
                      " inner join project_detail on Result.Project_DetailId=  project_detail.Project_DetailId) "
                      " order by result.TestTime,Result.ResultNum "
                      );
        }
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.exec();
        while(query.next())
        {
            Result r;
            r.ResultId=query.value(0).toString();
            r.ProjectId = ProjectId;
            r.TestTime=query.value(1).toString();
            r.ResultNum=query.value(2).toInt();
            r.detail.Project_DetailId=query.value(3).toString();
            r.value=query.value(4).toDouble();
            r.level=query.value(5).toInt();
            list.append(r);
        }
    }
    return list;
}

QVector<Result> ProjectService::GetResult(QString ProjectId, int level, QString startTime, QString endTime, bool showAll)
{
    QVector<Result> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        if(showAll)
        {
            query.prepare("select ResultId,result.TestTime,ResultNum,result.Project_DetailId,value,Result.DensityId "
                      " from Result "
                      " where value>0 and result.ProjectId=:ProjectId and result.TestTime >= :StartTime and result.TestTime <= :EndTime "
                      " and result.DensityId=:level "
                      " order by result.TestTime,Result.ResultNum "
                      );
        }
        else
        {
            query.prepare("select ResultId,result.TestTime,ResultNum,result.Project_DetailId,value,Result.DensityId "
                      " from Result "
                      " inner join project_detail on Result.Project_DetailId=  project_detail.Project_DetailId "
                      " where value>0 and result.ProjectId=:ProjectId and result.TestTime >= :StartTime and result.TestTime <= :EndTime "
                      " and result.DensityId=:level and materialBatchId in (select materialBatchId from result inner join "
                      " (select projectId, DensityId, max(testtime) TestTime from  result group by projectId, DensityId) A "
                      " on result.projectid=A.projectid and result.DensityId=A.DensityId and result.TestTime=A.TestTime and "
                      " result.ProjectId=:ProjectId "
                      " inner join project_detail on Result.Project_DetailId=  project_detail.Project_DetailId) "
                      " order by result.TestTime,Result.ResultNum "
                      );
        }
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.bindValue(":StartTime",startTime);
        query.bindValue(":EndTime",endTime);
        query.exec();
        while(query.next())
        {
            Result r;
            r.ResultId=query.value(0).toString();
            r.ProjectId = ProjectId;
            r.TestTime=query.value(1).toString();
            r.ResultNum=query.value(2).toInt();
            r.detail.Project_DetailId=query.value(3).toString();
            r.value=query.value(4).toDouble();
            r.level=query.value(5).toInt();
            list.append(r);
        }
    }
    return list;
}

QVector<Result> ProjectService::GetResult(QString ProjectId, QString startTime, QString endTime, int level, int n)
{
    QVector<Result> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;

        query.prepare("select ResultId,result.TestTime,ResultNum,result.Project_DetailId,value,Result.DensityId "
                      " from Result "
                      " where value>0 and result.ProjectId=:ProjectId and result.TestTime >= :StartTime and result.TestTime <= :EndTime "
                      " and result.DensityId=:level "
                      " order by result.TestTime,Result.ResultNum "
                      );

        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.bindValue(":StartTime",startTime);
        query.bindValue(":EndTime",endTime);
        query.exec();

        int count = 0;
        while(query.next())
        {
            if(n != -1)
            {
                count++;
                if(count > n)
                {
                    break;
                }
            }
            Result r;
            r.ResultId=query.value(0).toString();
            r.ProjectId = ProjectId;
            r.TestTime=query.value(1).toString();
            r.ResultNum=query.value(2).toInt();
            r.detail.Project_DetailId=query.value(3).toString();
            r.value=query.value(4).toDouble();
            r.level=query.value(5).toInt();
            list.append(r);

        }
    }
    return list;
}


QVector<ProjectDetail> ProjectService::GetDetail(QString ProjectId,int level)
{
    QVector<ProjectDetail> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select Project_DetailId,ProjectId,DensityId,DensityName,"
                      " Project_Detail.MaterialId,Project_Detail.MaterialBatchId,Project_Detail.ReagentId,Project_Detail.ReagentBatchId,Project_Detail.MethodId,MaterialBatch.BatchNo MaterialBatchName,ReagentBatch.BatchNo ReagentBatchName  "
                      " ,Material.MaterialName,Reagent.ReagentName,Method.MethodName "
                      " from Project_Detail "
                      " left join MaterialBatch on Project_Detail.MaterialBatchId=MaterialBatch.MaterialBatchId "
                      " left join ReagentBatch on Project_Detail.ReagentBatchId=ReagentBatch.ReagentBatchId "

                      " left join Material on Project_Detail.MaterialId=Material.MaterialId "
                      " left join Reagent on Project_Detail.ReagentId=Reagent.ReagentId "
                      " left join Method on Project_Detail.MethodId=Method.MethodId "

                      " where useflag=1 and ProjectId=:ProjectId "
                      " and DensityId=:level "
                      );
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.exec();
        while(query.next())
        {
            ProjectDetail d;
            d.Project_DetailId=query.value(0).toString();
            d.ProjectId=query.value(1).toString();
            d.DensityId=query.value(2).toInt();
            d.DensityName=query.value(3).toString();
            d.MaterialId=query.value(4).toString();
            d.MaterialBatchId=query.value(5).toString();
            d.ReagentId=query.value(6).toString();
            d.ReagentBatchId=query.value(7).toString();
            d.MethodId=query.value(8).toString();
            d.MaterialBatchName=query.value(9).toString();
            d.ReagentBatchName=query.value(10).toString();

            d.MaterialName=query.value(11).toString();
            d.ReagentName=query.value(12).toString();
            d.MethodName=query.value(13).toString();


            list.append(d);
        }
    }
    return list;
}

QVector<Project> ProjectService::GetProjectByCategoryId(QString categoryId)
{
    QVector<Project> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select distinct Project.ProjectId,ProjectName,EnglishName,CustomName "
                      " from Project "
                      " inner join testtype on Project.testtypeId=testtype.testtypeId "
                      " where   categoryId=:categoryId "
                      );
        query.bindValue(":categoryId", categoryId);
        query.exec();
        while(query.next())
        {
            Project proj;
            proj.ProjectId=query.value(0).toString();
            proj.ProjectName=query.value(1).toString();
            proj.EnglishName=query.value(2).toString();
            proj.CustomName=query.value(3).toString();

            list.append(proj);
        }
    }
    return list;
}

QVector<Project> ProjectService::GetProjectByCategoryAndDay(QString categoryId, QString date)
{
    QVector<Project> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select distinct Project.ProjectId,ProjectName,EnglishName,CustomName "
                      " from Project "
                      " inner join testtype on Project.testtypeId=testtype.testtypeId "
                      " inner join result on result.projectId=Project.projectId "
                      " where   categoryId=:categoryId and result.TestTime =:date "
                      );
        query.bindValue(":categoryId", categoryId);
        query.bindValue(":date", date);
        query.exec();
        while(query.next())
        {
            Project proj;
            proj.ProjectId=query.value(0).toString();
            proj.ProjectName=query.value(1).toString();
            proj.EnglishName=query.value(2).toString();
            proj.CustomName=query.value(3).toString();

            list.append(proj);
        }
    }
    return list;
}


QVector<ProjectDetail> ProjectService::SearchDetail(QString projectId, int level, QString material, QString materialBatch, QString reagent, QString reagentBatch)
{
    QVector<ProjectDetail> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select Project_DetailId,ProjectId,DensityId,DensityName,"
                      " Project_Detail.MaterialId,Project_Detail.MaterialBatchId,Project_Detail.ReagentId,Project_Detail.ReagentBatchId,Project_Detail.MethodId,MaterialBatch.BatchNo MaterialBatchName,ReagentBatch.BatchNo ReagentBatchName  "
                      " ,Material.MaterialName,Reagent.ReagentName,Method.MethodName "
                      " from Project_Detail "
                      " left join MaterialBatch on Project_Detail.MaterialBatchId=MaterialBatch.MaterialBatchId "
                      " left join ReagentBatch on Project_Detail.ReagentBatchId=ReagentBatch.ReagentBatchId "

                      " left join Material on Project_Detail.MaterialId=Material.MaterialId "
                      " left join Reagent on Project_Detail.ReagentId=Reagent.ReagentId "
                      " left join Method on Project_Detail.MethodId=Method.MethodId "

                      " where materialName like :material and materialBatch.batchNo like :materialBatch and reagentName like :reagent and reagentBatch.batchNo like :reagentBatch "
                      " and Project_Detail.projectId=:projectId and DensityId=:level"
                      );
        query.bindValue(":projectId", projectId);
        query.bindValue(":level", level);
        query.bindValue(":material", "%"+material+"%");
        query.bindValue(":materialBatch", "%"+materialBatch+"%");
        query.bindValue(":reagent", "%"+reagent+"%");
        query.bindValue(":reagentBatch", "%"+reagentBatch+"%");
        query.exec();

        while(query.next())
        {
            ProjectDetail d;
            d.Project_DetailId=query.value(0).toString();
            d.ProjectId=query.value(1).toString();
            d.DensityId=query.value(2).toInt();
            d.DensityName=query.value(3).toString();
            d.MaterialId=query.value(4).toString();
            d.MaterialBatchId=query.value(5).toString();
            d.ReagentId=query.value(6).toString();
            d.ReagentBatchId=query.value(7).toString();
            d.MethodId=query.value(8).toString();
            d.MaterialBatchName=query.value(9).toString();
            d.ReagentBatchName=query.value(10).toString();

            d.MaterialName=query.value(11).toString();
            d.ReagentName=query.value(12).toString();
            d.MethodName=query.value(13).toString();


            list.append(d);
        }
    }
    return list;
}

ProjectDetail ProjectService::GetDetail(QString ProjectDetailId)
{
    ProjectDetail d;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select Project_DetailId,ProjectId,DensityId,DensityName,MaterialId,MaterialBatchId,ReagentId,ReagentBatchId,MethodId  "
                      " from Project_Detail "
                      " where Project_DetailId=:ProjectDetailId "
                      );
        query.bindValue(":ProjectDetailId", ProjectDetailId);
        query.exec();
        while(query.next())
        {
            d.Project_DetailId=query.value(0).toString();
            d.ProjectId=query.value(1).toString();
            d.DensityId=query.value(2).toInt();
            d.DensityName=query.value(3).toString();
            d.MaterialId=query.value(4).toString();
            d.MaterialBatchId=query.value(5).toString();
            d.ReagentId=query.value(6).toString();
            d.ReagentBatchId=query.value(7).toString();
            d.MethodId=query.value(8).toString();

        }
    }
    return d;
}

Result ProjectService::GetResultById(QString ResultId)
{
    Result r;
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select distinct result.ResultId,d.Project_DetailId,result.DensityId,ResultNum,TestTime,Value,"
                      " Material.MaterialId,Material.MaterialName,Reagent.ReagentId,Reagent.ReagentName,Method.methodId,Method.MethodName,"
                      " MaterialBatch.MaterialBatchId,MaterialBatch.BatchNo MaterialBatchName,ReagentBatch.ReagentBatchId,ReagentBatch.BatchNo ReagentBatchName,result.projectId"
                      " from result "
                      " inner join project_detail d on  result.project_DetailId=d.project_DetailId "
                      " left join Material on d.MaterialId=Material.MaterialId "
                      " left join Reagent on d.ReagentId=Reagent.ReagentId "
                      " left join MaterialBatch on MaterialBatch.MaterialBatchId=d.MaterialBatchId "
                      " left join ReagentBatch on ReagentBatch.ReagentBatchId=d.ReagentBatchId "
                      " left join Method on d.MethodId=Method.MethodId "
                      " where result.ResultId = :ResultId "
                      " order by result.Testtime  "
                      );
        query.bindValue(":ResultId", ResultId);
        query.exec();
        while(query.next())
        {
            r.ResultId=query.value(0).toString();
            r.detail.Project_DetailId=query.value(1).toString();
            r.level=query.value(2).toInt();
            r.ResultNum=query.value(3).toInt();
            r.TestTime=query.value(4).toString();
            r.value=query.value(5).toDouble();
            r.detail.MaterialId=query.value(6).toString();
            r.detail.MaterialName=query.value(7).toString();
            r.detail.ReagentId=query.value(8).toString();
            r.detail.ReagentName=query.value(9).toString();
            r.detail.MethodId=query.value(10).toString();
            r.detail.MethodName=query.value(11).toString();
            r.detail.MaterialBatchId=query.value(12).toString();
            r.detail.MaterialBatchName=query.value(13).toString();
            r.detail.ReagentBatchId=query.value(14).toString();
            r.detail.ReagentBatchName=query.value(15).toString();
            r.ProjectId=query.value(16).toString();
        }
    }
    return r;
}

QVector<Result> ProjectService::GetResultByProject(QString ProjectId, int level)
{
    QVector<Result> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select distinct result.ResultId,d.Project_DetailId,result.DensityId,ResultNum,TestTime,Value,"
                      " Material.MaterialId,Material.MaterialName,Reagent.ReagentId,Reagent.ReagentName,Method.methodId,Method.MethodName,"
                      " MaterialBatch.MaterialBatchId,MaterialBatch.BatchNo MaterialBatchName,ReagentBatch.ReagentBatchId,ReagentBatch.BatchNo ReagentBatchName"
                      " from result "
                      " inner join project_detail d on  result.project_DetailId=d.project_DetailId "
                      " left join Material on d.MaterialId=Material.MaterialId "
                      " left join Reagent on d.ReagentId=Reagent.ReagentId "
                      " left join MaterialBatch on MaterialBatch.MaterialBatchId=d.MaterialBatchId "
                      " left join ReagentBatch on ReagentBatch.ReagentBatchId=d.ReagentBatchId "
                      " left join Method on d.MethodId=Method.MethodId "
                      " where result.ProjectId = :ProjectId "
                      " and result.DensityId = :level "
                      " order by result.Testtime  "
                      );
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.exec();
        while(query.next())
        {
            Result r;
            r.ResultId=query.value(0).toString();
            r.detail.Project_DetailId=query.value(1).toString();
            r.level=query.value(2).toInt();
            r.ResultNum=query.value(3).toInt();
            r.TestTime=query.value(4).toString();
            r.value=query.value(5).toDouble();
            r.detail.MaterialId=query.value(6).toString();
            r.detail.MaterialName=query.value(7).toString();
            r.detail.ReagentId=query.value(8).toString();
            r.detail.ReagentName=query.value(9).toString();
            r.detail.MethodId=query.value(10).toString();
            r.detail.MethodName=query.value(11).toString();
            r.detail.MaterialBatchId=query.value(12).toString();
            r.detail.MaterialBatchName=query.value(13).toString();
            r.detail.ReagentBatchId=query.value(14).toString();
            r.detail.ReagentBatchName=query.value(15).toString();

            list.append(r);
        }
    }
    return list;
}

QStringList ProjectService::GetResultIdFromComputatonResult(QString ProjectId)
{
    QStringList resultids;
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select ResultId from Computation_Result "
                      "inner join Computation on Computation.ComputationId = Computation_Result.ComputationId "
                      "where Computation.ProjectId = :ProjectId ");
        query.bindValue(":ProjectId",ProjectId);
        query.exec();
        while(query.next())
        {
            resultids.append(query.value(0).toString());
        }

        return resultids;

    }

    return resultids;
}

void ProjectService::DeleteById(QString ProjectId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from Project where ProjectId =:ProjectId");
        query.bindValue(":ProjectId", ProjectId);
        query.exec();
    }
}

void ProjectService::SetDefaultRule(QString testTypeId, QVector<QString> rules)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from TestType_Rule where TestTypeId=:testTypeId ");
        query.bindValue(":testTypeId", testTypeId);
        query.exec();

        for(int i=0;i<rules.count();i++)
        {
            query.prepare("insert into TestType_Rule (TestType_RuleId,TestTypeId, ruleId) values(:TestType_RuleId,:testTypeId,:rule) ");
            QUuid quuid;
            QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
            query.bindValue(":TestType_RuleId", guid);
            query.bindValue(":testTypeId", testTypeId);
            query.bindValue(":rule", rules[i]);
            query.exec();
        }
    }
}

QVector<QString> ProjectService::GetRules(QString testTypeId)
{
    QVector<QString> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select ruleId from TestType_Rule where TestTypeId = :TestTypeId ");
        query.bindValue(":TestTypeId", testTypeId);
        query.exec();
        while(query.next())
        {
            list.append(query.value(0).toString());
        }
    }
    return list;
}

QVector<QString> ProjectService::GetAllRules()
{
    QVector<QString> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select distinct ruleId from TestType_Rule order by ruleId");
        query.exec();
        while(query.next())
        {
            list.append(query.value(0).toString());
        }
    }
    return list;
}

QVector<Project> ProjectService::GetSumProjectByType(QString testTypeId)
{
    QVector<Project> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select CustomName from project "
                      " where testTypeId = :testTypeId "

                      );
        query.bindValue(":testTypeId", testTypeId);
        query.exec();
        while(query.next())
        {
            Project r;
            r.ProjectName=query.value(0).toString();
            list.append(r);
        }
    }
    return list;
}

void ProjectService::InsertComputation(QString ProjectId, QString batchId, int level, QString startTime, QString endTime)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QString OldComputationId;
        QSqlQuery query;
        query.prepare("select ComputationId from Computation where ProjectId = :ProjectId and level = :level");
        query.bindValue(":ProjectId",ProjectId);
        query.bindValue(":level",level);
        if (query.exec())
        {
            if (query.next())
            {
                OldComputationId = query.value(0).toString();
            }
        }

        query.clear();
        query.prepare("delete from Computation where ProjectId=:ProjectId and level=:level");
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.exec();


        Project p = this->GetById(ProjectId);

        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        QVector<Result> results = this->GetResult(ProjectId,level,true);
        int n = this->GetCount(ProjectId, level, startTime, endTime);
        double Avg = p.GetAverage(results, startTime, endTime);
        double Sd = p.GetStandardDeviation(results, startTime, endTime);

        QString sql = QString("insert into Computation (ComputationId,ProjectId,Project_BatchId,level,Avg,Sd,n,StartTime,EndTime,CreateTime) "
                              " values(:ComputationId,:ProjectId,:Project_BatchId,:level,:Avg,:Sd,:n,:StartTime,:EndTime,:CreateTime)");

        query.clear();
        query.prepare(sql);
        query.bindValue(":ComputationId",guid);
        query.bindValue(":ProjectId",ProjectId);
        query.bindValue(":Project_BatchId",batchId);
        query.bindValue(":level",level);
        query.bindValue(":Avg",Avg);
        query.bindValue(":Sd",Sd);
        query.bindValue(":n",n);
        query.bindValue(":StartTime",startTime);
        query.bindValue(":EndTime",endTime);
        query.bindValue(":CreateTime",QDate::currentDate().toString("yyyy-MM-dd"));

        if (query.exec())   //初始化数据插入数据库成功
        {
            QString computationId = guid;
            QVariantList computation_resultids;
            QVariantList computationids;
            QVariantList resultids;
            for(int i = 0; i < results.size(); i++)
            {
                QUuid quuid;
                QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
                computation_resultids << guid;
                computationids << computationId;
                resultids << results[i].ResultId;

            }
            //删除旧数据
            query.clear();
            query.prepare("delete from Computation_Result where ComputationId = :ComputationId");
            query.bindValue(":ComputationId",OldComputationId);
            query.exec();

            query.clear();
            query.prepare("insert into Computation_Result values(?,?,?)");
            query.addBindValue(computation_resultids);
            query.addBindValue(computationids);
            query.addBindValue(resultids);
            query.execBatch();

        }
    }
}

void ProjectService::InsertComputation(QString ProjectId, QString batchId, int level, QString startTime, int n)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QString OldComputationId;
        QSqlQuery query;
        query.prepare("select ComputationId from Computation where ProjectId = :ProjectId and level = :level");
        query.bindValue(":ProjectId",ProjectId);
        query.bindValue(":level",level);
        if (query.exec())
        {
            if (query.next())
            {
                OldComputationId = query.value(0).toString();

            }
        }

        query.clear();
        query.prepare("delete from Computation where ProjectId=:ProjectId and level=:level");
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.exec();


        Project p = this->GetById(ProjectId);

        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        QVector<Result> results = this->GetResult(ProjectId,level,true);
        double Avg = p.GetAverage(results, startTime, n);
        double Sd = p.GetStandardDeviation(results, startTime, n);

        QString sql = QString("insert into Computation (ComputationId,ProjectId,Project_BatchId,level,Avg,Sd,n,StartTime,EndTime,CreateTime) "
                              "values(:ComputationId,:ProjectId,:Project_BatchId,:level,:Avg,:Sd,:n,:StartTime,:EndTime,:CreateTime)");

        query.clear();
        query.prepare(sql);
        query.bindValue(":ComputationId",guid);
        query.bindValue(":ProjectId",ProjectId);
        query.bindValue(":Project_BatchId",batchId);
        query.bindValue(":level",level);
        query.bindValue(":Avg",Avg);
        query.bindValue(":Sd",Sd);
        query.bindValue(":n",n);
        query.bindValue(":StartTime",startTime);
        query.bindValue(":EndTime","");
        query.bindValue(":CreateTime",QDate::currentDate().toString("yyyy-MM-dd"));

        if (query.exec())   //初始化数据插入数据库成功
        {
            QString computationId = guid;
            QVariantList computation_resultids;
            QVariantList computationids;
            QVariantList resultids;
            for(int i = 0; i < n; i++)
            {
                QUuid quuid;
                QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
                computation_resultids << guid;
                computationids << computationId;
                resultids << results[i].ResultId;

            }

            //删除旧数据
            query.clear();
            query.prepare("delete from Computation_Result where ComputationId = :ComputationId");
            query.bindValue(":ComputationId",OldComputationId);
            query.exec();

            query.clear();
            query.prepare("insert into Computation_Result values(?,?,?)");
            query.addBindValue(computation_resultids);
            query.addBindValue(computationids);
            query.addBindValue(resultids);
            query.execBatch();

        }
    }
}

void ProjectService::InsertComputation(QVector<Result> results, QString startTime, QString endTime)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("delete from Computation where ProjectId='399005' and level=1");
        query.exec();

        Project p;

        QUuid quuid;
        QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
        int n = p.GetN(results, startTime, endTime);
        double Avg = p.GetAverage(results, startTime, endTime);
        double Sd = p.GetStandardDeviation(results, startTime, endTime);

        QString sql = QString("insert into Computation ([ComputationId],[ProjectId],[Project_BatchId],[level],[Avg],[Sd],[n],[StartTime],[EndTime],[CreateTime]) values('%1','%2','%3',%4,%5,%6,%7,'%8','%9','%10   ')").arg(guid).arg("399005").arg("").arg("1").arg(Avg).arg(Sd).arg(n).arg(startTime).arg(endTime).arg(QDate::currentDate().toString("yyyy-MM-dd"));
        query.exec(sql);
    }
}

void ProjectService::UpdateComputationDate(QString projectId, int level, QString startTime, QString endTime)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM Computation WHERE ProjectId = :ProjectId AND level = :level");
        query.bindValue(":ProjectId", projectId);
        query.bindValue(":level", level);
        query.exec();
        if (query.next())
        {
            query.clear();
            query.prepare("UPDATE Computation SET StartTime = :StartTime, EndTime = :EndTime WHERE ProjectId = :ProjectId AND level = :level");
            query.bindValue(":StartTime",startTime);
            query.bindValue(":EndTime",endTime);
            query.bindValue(":ProjectId",projectId);
            query.bindValue(":level",level);
            query.exec();
        }
        else
        {
            query.clear();
            query.prepare("INSERT INTO Computation(ProjectId, level) VALUES(:ProjectId, :level)");
            query.bindValue(":ProjectId", projectId);
            query.bindValue(":level", level);
            query.exec();
        }


    }
}

void ProjectService::Import(QString strFilePath, bool needDelete, bool needCaculate)
{
    QString line;
    QStringList arr;
    QString projectId = "";
    QString beginTime = "";
    QString endTime = "";
    int a[10] = {0,0,0,0,0,0,0,0,0,0};

    QFile file(strFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;


        while (!file.atEnd())
        {
            line = file.readLine().replace("\n", "");
            arr = line.split(",");

            QVector<Project> list = this->SearchProject("","",arr[0],"");

            if(list.count()==0)
            {
                return;
            }
            projectId =list[0].ProjectId;
            if(beginTime == "")
            {
                beginTime = arr[2];
            }
            endTime = arr[2];
            int level = arr[1].replace("L","").toInt();
            a[level] = 1;
            if(needDelete)
            {
                query.prepare("delete from result where projectId = :projectId and DensityId=:level");
                query.bindValue(":projectId", projectId);
                query.bindValue(":level", level);
                query.exec();
                needDelete = false;
            }

            QString Project_DetailId;
            QVector<ProjectDetail> details = SearchDetail(projectId, arr[1].replace("L","").toInt(), arr[4], arr[5], arr[6], arr[7]);
            if(details.count()>0)
            {
                Project_DetailId = details[0].Project_DetailId;
            }
            else
            {
                ProjectDetail d;
                d.ProjectId = projectId;
                d.DensityId = arr[1].replace("L","").toInt();

                d.MaterialName = arr[4];
                d.MaterialBatchName = arr[5];
                d.ReagentName = arr[6];
                d.ReagentBatchName = arr[7];

//                MethodService methodService;
//                QVector<Method> Methods = methodService.GetMethods("", "", arr[8],1);
//                if(Methods.count()>0)
//                {
//                    d.MethodId = Methods[0].MethodId;
//                }
                MaterialService materialService;
                QVector<Material> Materials = materialService.GetMaterials("", "", arr[4],"","",1);
                if(Materials.count()>0)
                {
                    d.MaterialId = Materials[0].MaterialId;
                }
                ReagentService reagentService;
                QVector<Reagent> Reagents = reagentService.GetReagents("", "", arr[6],"","",1);
                if(Reagents.count()>0)
                {
                    d.ReagentId = Reagents[0].ReagentId;
                }

                MaterialBatchService mbs;
                QVector<MaterialBatch> lb = mbs.GetMaterialBatchs(d.MaterialId,arr[5]);
                if(lb.count()>0)
                {
                    d.MaterialBatchId = lb[0].MaterialBatchId;
                }
                else
                {
                    MaterialBatch b;
                    b.MaterialId = d.MaterialId;
                    b.BatchNo = arr[5];
                    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
                    b.CreateTime = time;
                    b.StartDate = time;
                    b.Status = 1;
                    d.MaterialBatchId = mbs.Insert(b);
                }

                ReagentBatchService rbs;
                QVector<ReagentBatch> lr = rbs.GetReagentBatchs(d.ReagentId,arr[7]);
                if(lr.count()>0)
                {
                    d.ReagentBatchId = lr[0].ReagentBatchId;
                }
                else
                {
                    ReagentBatch b;
                    b.ReagentId = d.ReagentId;
                    b.BatchNo = arr[7];
                    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
                    b.CreateTime = time;
                    b.StartDate = time;
                    b.Status = 1;
                    d.ReagentBatchId = rbs.Insert(b);
                }

                Project_DetailId = InsertDetail(d);
            }

            QUuid quuid;
            QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");

//            query.prepare("insert into result (ResultId,ProjectId,DensityId,Project_DetailId,ResultNum,TestTime,Value,CreateTime) "
//                          " values (:ResultId,:ProjectId,:DensityId,:Project_DetailId,:ResultNum,:TestTime,:Value,:CreateTime)");
//            query.bindValue(":ResultId", guid);
//            query.bindValue(":ProjectId", projectId);
//            query.bindValue(":DensityId", arr[1].replace("L",""));
//            query.bindValue(":Project_DetailId", Project_DetailId);
//            query.bindValue(":ResultNum", "1");
//            query.bindValue(":TestTime", arr[2]);
//            query.bindValue(":Value", arr[3]);
//            query.bindValue(":CreateTime", arr[2]);
//            query.exec();

            QString sql = QString("insert into result (ResultId,ProjectId,DensityId,Project_DetailId,ResultNum,TestTime,Value,CreateTime) "
                          " values ('%1','%2',%3,'%4',%5,'%6','%7','%8')")
                    .arg(guid).arg(projectId).arg(arr[1].replace("L","")).arg(Project_DetailId).arg("1").arg(arr[2]).arg(arr[3]).arg(arr[2]);

            query.exec(sql);

        }

        for(int i=1;i<10;i++)
        {
            if(a[i]==1 && needCaculate)
            {
                //重新计算
                InsertComputation(projectId,"",i,beginTime, endTime);
            }
        }
    }

    file.close();

}

double ProjectService::getAvg(QString ProjectId,int level)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select [Avg] from Computation where ProjectId = :ProjectId and level=:level ");
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.exec();
        while(query.next())
        {
            return query.value(0).toDouble();
        }
    }
    return 0;
}
double ProjectService::getSd(QString ProjectId,int level)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select [Sd] from Computation where ProjectId = :ProjectId and level=:level ");
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.exec();
        while(query.next())
        {
            return query.value(0).toDouble();
        }
    }
    return 0;
}
int ProjectService::getN(QString ProjectId,int level)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select [n] from Computation where ProjectId = :ProjectId and level=:level ");
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.exec();
        while(query.next())
        {
            return query.value(0).toInt();
        }
    }
    return 0;
}

double ProjectService::getMax(QString ProjectId, int level)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select [Max] from Computation where ProjectId = :ProjectId and level=:level ");
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.exec();
        while(query.next())
        {
            return query.value(0).toInt();
        }
    }
    return 0;
}

double ProjectService::getMin(QString ProjectId, int level)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select [Min] from Computation where ProjectId = :ProjectId and level=:level ");
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.exec();
        while(query.next())
        {
            return query.value(0).toInt();
        }
    }
    return 0;
}
QString ProjectService::getStartTime(QString ProjectId,int level)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select StartTime from Computation where ProjectId = :ProjectId and level=:level ");
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.exec();
        while(query.next())
        {
            return query.value(0).toString();
        }
    }
    return 0;
}
QString ProjectService::getEndTime(QString ProjectId,int level)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select EndTime from Computation where ProjectId = :ProjectId and level=:level ");
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.exec();
        while(query.next())
        {
            return query.value(0).toString();
        }
    }
    return 0;
}

int ProjectService::GetCount(QString ProjectId, int level,QString startTime,QString endTime)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        if(endTime != "")
        {
            query.prepare("select count(1) from result where ProjectId = :ProjectId and DensityId=:level and CreateTime >= :startTime and CreateTime<=:endTime ");
            query.bindValue(":endTime", endTime);
        }
        else
        {
            query.prepare("select count(1) from result where ProjectId = :ProjectId and DensityId=:level and CreateTime >= :startTime ");
        }
        query.bindValue(":ProjectId", ProjectId);
        query.bindValue(":level", level);
        query.bindValue(":startTime", startTime);
        query.exec();
        while(query.next())
        {
            return query.value(0).toInt();
        }
    }
    return 0;
}



QVector<QString> ProjectService::GetProjectsDay(QString categotyId)
{
    QVector<QString> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select distinct testTime from Result "
                      " inner join project on result.projectId=project.projectId "
                      " inner join testtype on  project.testtypeId=testtype.testtypeId "
                      " where categoryid = :categoryid "

                      );
        query.bindValue(":categoryid", categotyId);
        query.exec();
        while(query.next())
        {
            QString s=query.value(0).toString();
            list.append(s);
        }
    }
    return list;
}

int ProjectService::GetLevelByCategoryId(QString categoryId)
{
    int i = 0;
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select max(DensityCount) from project "
                      " inner join testtype on  project.testtypeId=testtype.testtypeId "
                      " where categoryId = :categoryId "

                      );
        query.bindValue(":categoryId", categoryId);
        query.exec();
        while(query.next())
        {
            i=query.value(0).toInt();
        }
    }
    return i;
}
