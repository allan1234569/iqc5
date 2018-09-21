#include "DataSheetService.h"
#include <QSqlQuery>
#include <QVariant>

#include <QDebug>

DataSheetService::DataSheetService()
{
}

QVector<DataSheet> DataSheetService::GetDetail(QString projectId)
{
    QVector<DataSheet> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(" select project.EnglishName as EnglishName, project.ProjectName as ChineseName, Category.CategoryName as Category,SubCategory.CategoryName as SubCategory, Result.DensityId as DensityId, result.ResultNum as ResultNum, Material.MaterialName as MaterialName, MaterialBatch.BatchNo as MaterialBatchNo, Reagent.ReagentName as ReagentName, ReagentBatch.BatchNo as ReagentBatchNo, Method.MethodName as MethodName, Device.DeviceName as DeviceName, result.value as Value, result.TestTime as TestTime from  Result "
                      " inner join project_detail on Result.Project_DetailId=  project_detail.Project_DetailId "
                      " inner join Material on Project_detail.MaterialId = Material.MaterialId "
                      " inner join MaterialBatch on Project_detail.MaterialBatchId = MaterialBatch.MaterialBatchId "
                      " inner join Reagent on Reagent.ReagentId = project_detail.ReagentId "
                      " inner join ReagentBatch on ReagentBatch.ReagentBatchId = project_detail.ReagentBatchId "
                      " inner join Method on Method.MethodId = Project_Detail.MethodId "
                      " inner join Device on Device.DeviceId = Project.DeviceId "
                      " inner join project on project.ProjectId = :ProjectId "
                      " inner join TestType on TestType.TestTypeId = Project.TestTypeId "
                      " inner join Category as SubCategory on SubCategory.CategoryId = TestType.CategoryId "
                      " inner join Category as Category on Category.CategoryId = SubCategory.ParentId "
                      " where Result.value > 0 and result.ProjectId= :ProjectId ");
        query.bindValue(":ProjectId",projectId);
        query.exec();

        while(query.next())
        {
            DataSheet d;
            d.englishName = query.value("EnglishName").toString();
            d.chineseName = query.value("ChineseName").toString();
            d.categoryName = query.value("Category").toString();
            d.subCategoryName = query.value("SubCategory").toString();
            d.densityId = query.value("DensityId").toString();
            d.testNum = query.value("ResultNum").toString();
            d.materialName = query.value("MaterialName").toString();
            d.materialBatchNo = query.value("MaterialBatchNo").toString();
            d.reagentName = query.value("ReagentName").toString();
            d.reagentBatchNo = query.value("ReagentBatchNo").toString();
            d.methodName = query.value("MethodName").toString();
            d.deviceName = query.value("DeviceName").toString();
            d.resultValue = query.value("Value").toString();
            d.testTime = query.value("TestTime").toString();
            list.append(d);
        }
    }

    return list;
}

QVector<DataSheet> DataSheetService::GetDetail(QString projectId, QString startDate, QString endDate)
{
    QVector<DataSheet> list;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare(" select project.EnglishName as EnglishName, project.ProjectName as ChineseName, Category.CategoryName as Category,SubCategory.CategoryName as SubCategory, Result.DensityId as DensityId, result.ResultNum as ResultNum, Material.MaterialName as MaterialName, MaterialBatch.BatchNo as MaterialBatchNo, Reagent.ReagentName as ReagentName, ReagentBatch.BatchNo as ReagentBatchNo, Method.MethodName as MethodName, Device.DeviceName as DeviceName, result.value as Value, result.TestTime as TestTime from  Result "
                      " inner join project_detail on Result.Project_DetailId=  project_detail.Project_DetailId "
                      " inner join Material on Project_detail.MaterialId = Material.MaterialId "
                      " inner join MaterialBatch on Project_detail.MaterialBatchId = MaterialBatch.MaterialBatchId "
                      " inner join Reagent on Reagent.ReagentId = project_detail.ReagentId "
                      " inner join ReagentBatch on ReagentBatch.ReagentBatchId = project_detail.ReagentBatchId "
                      " inner join Method on Method.MethodId = Project_Detail.MethodId "
                      " inner join Device on Device.DeviceId = Project.DeviceId "
                      " inner join project on project.ProjectId = :ProjectId "
                      " inner join TestType on TestType.TestTypeId = Project.TestTypeId "
                      " inner join Category as SubCategory on SubCategory.CategoryId = TestType.CategoryId "
                      " inner join Category as Category on Category.CategoryId = SubCategory.ParentId "
                      " where Result.value > 0 and result.ProjectId= :ProjectId and result.TestTime >= :startTime and result.TestTime <= :endTime ");
        query.bindValue(":ProjectId",projectId);
        query.bindValue(":startTime",startDate);
        query.bindValue(":endTime",endDate);
        query.exec();

        while(query.next())
        {
            DataSheet d;
            d.englishName = query.value("EnglishName").toString();
            d.chineseName = query.value("ChineseName").toString();
            d.categoryName = query.value("Category").toString();
            d.subCategoryName = query.value("SubCategory").toString();
            d.densityId = query.value("DensityId").toString();
            d.testNum = query.value("ResultNum").toString();
            d.materialName = query.value("MaterialName").toString();
            d.materialBatchNo = query.value("MaterialBatchNo").toString();
            d.reagentName = query.value("ReagentName").toString();
            d.reagentBatchNo = query.value("ReagentBatchNo").toString();
            d.methodName = query.value("MethodName").toString();
            d.deviceName = query.value("DeviceName").toString();
            d.resultValue = query.value("Value").toString();
            d.testTime = query.value("TestTime").toString();
            list.append(d);
        }
    }

    return list;
}
