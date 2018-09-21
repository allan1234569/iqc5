#include "zhiFangInterface.h"
#include <QDebug>
#include <QFile>
#include <QXmlQuery>
#include "xmlquery.h"

zhiFangLisInterface::zhiFangLisInterface()
{
    data = new LisData();
    setting = new QSettings(QString("zhiFangLisConfig.ini"),QSettings::IniFormat);
}

zhiFangLisInterface::~zhiFangLisInterface()
{
    delete data;
    delete setting;
}

LisData* zhiFangLisInterface::getData(const QString dir)
{
    qDebug() << " In zhiFangLis getData";
    QFile file;
//    QXmlQuery query;
    QString namespaceStr = QString(buildNameSpaceStr(QString("s"),configure.s) +
                                   buildNameSpaceStr("dt",configure.dt) +
                                   buildNameSpaceStr("rs",configure.rs) +
                                   buildNameSpaceStr("z",configure.z)
                                   );


    {//result
        XmlQuery myQuery;
        QString resultFileName = QString("%1/%2").arg(dir).arg(configure.result.file);
        QDomNodeList nodeList = myQuery.query(resultFileName,configure.result.path, namespaceStr);
        file.close();

        for(int i = 0; i < nodeList.count(); i++)
        {
            Result *result = new Result;
            result->ProjectId = nodeList.at(i).toElement().attribute(configure.result.projectId);
            result->value = nodeList.at(i).toElement().attribute(configure.result.value).toDouble();
            result->CreateTime = nodeList.at(i).toElement().attribute(configure.result.createTime);
            result->detail.ProjectId = nodeList.at(i).toElement().attribute(configure.result.projectId);

            data->resultVec.push_back(result);
        }
    }
    {//project
        QString projectFileName = QString("%1/%2").arg(dir).arg(configure.project.file);
        XmlQuery myQuery;
        QDomNodeList nodeList = myQuery.query(projectFileName, configure.project.path,namespaceStr);

        for(int i = 0; i < nodeList.count(); i++)
        {
            Project *project = new Project;
            project->ProjectId = nodeList.at(i).toElement().attribute(configure.project.projectId);
            project->ProjectName = nodeList.at(i).toElement().attribute(configure.project.projectName);
            project->testType.TestTypeId = nodeList.at(i).toElement().attribute(configure.project.testTypeId);
            project->EnglishName = nodeList.at(i).toElement().attribute(configure.project.englishName);
            project->CustomName = nodeList.at(i).toElement().attribute(configure.project.customName);
            data->projectVec.push_back(project);
        }
    }
    {//testType
        QString testTypeFileName = QString("%1/%2").arg(dir).arg(configure.testType.file);
        XmlQuery myQuery;
        QDomNodeList nodeList = myQuery.query( testTypeFileName, configure.testType.path,namespaceStr);

        for(int i = 0; i < nodeList.count(); i++)
        {
            TestType *testType = new TestType;
            testType->TestTypeId = nodeList.at(i).toElement().attribute(configure.testType.testTypeId);
            testType->TestTypeName = nodeList.at(i).toElement().attribute(configure.testType.testTypeName);
            testType->TestTypeCode = nodeList.at(i).toElement().attribute(configure.testType.testTypeCode);
            data->testTypeVec.push_back(testType);
        }
    }

//    {//material
//        QString materialFileName = QString("%1/%2").arg(dir).arg(configure.material.file);
//        XmlQuery myQuery;
//        QDomNodeList nodeList = myQuery.query( materialFileName, configure.material.path,namespaceStr);

//        for(int i = 0; i < nodeList.count(); i++)
//        {
//            Material *material = new Material;
//            material->MaterialId = nodeList.at(i).toElement().attribute(configure.material.materialId);
//            material->MaterialName = nodeList.at(i).toElement().attribute(configure.material.materialName);
//            material->ManufacturerName = nodeList.at(i).toElement().attribute(configure.material.manufacturerName);
//            data->materialVec.push_back(material);
//        }
//    }

    return data;
}

QStringList zhiFangLisInterface::readSetting()
{
    configure.s = setting->value(QString("s")).toString();
    configure.dt = setting->value(QString("dt")).toString();
    configure.rs = setting->value(QString("rs")).toString();
    configure.z = setting->value(QString("z")).toString();

    configure.result.file = setting->value(QString("Result/File")).toString();
    configure.result.path = setting->value(QString("Result/Path")).toString();
    configure.result.projectId = setting->value(QString("Result/ProjectId")).toString();
    configure.result.value = setting->value(QString("Result/Value")).toString();
    configure.result.createTime = setting->value(QString("Result/CreateTime")).toString();
    configure.result.detail.proecjtId = setting->value(QString("Result/ProjectId")).toString();

//    configure.result.detail.file = setting->value(QString("Project_Detail/File")).toString();
//    configure.result.detail.path = setting->value(QString("Project_Detail/Path")).toString();
//    configure.result.detail.projectDetailId = setting->value(QString("Project_Detail/Project_DetailId")).toString();
//    configure.result.detail.materialId = setting->value(QString("Project_Detail/MaterialId")).toString();
//    configure.result.detail.proecjtId = setting->value(QString("Project_Detail/ProjectId")).toString();


    configure.project.file = setting->value(QString("Project/File")).toString();
    configure.project.path = setting->value(QString("Project/Path")).toString();
    configure.project.projectId = setting->value(QString("Project/ProjectId")).toString();
    configure.project.projectName = setting->value(QString("Project/ProjectName")).toString();
    configure.project.englishName = setting->value(QString("Project/EnglishName")).toString();
    configure.project.customName = setting->value(QString("Project/CustomName")).toString();
    configure.project.testTypeId = setting->value(QString("Project/TestTypeId")).toString();

//    configure.material.file = setting->value(QString("Material/File")).toString();
//    configure.material.path = setting->value(QString("Material/Path")).toString();
//    configure.material.materialId = setting->value(QString("Material/MaterialId")).toString();
//    configure.material.materialName = setting->value(QString("Material/MaterialName")).toString();
//    configure.material.manufacturerName = setting->value(QString("Material/ManufacturerName")).toString();

    configure.testType.file = setting->value(QString("TestType/File")).toString();
    configure.testType.path = setting->value(QString("TestType/Path")).toString();
    configure.testType.testTypeId = setting->value(QString("TestType/TestTypeId")).toString();
    configure.testType.testTypeName = setting->value(QString("TestType/TestTypeName")).toString();
    configure.testType.testTypeCode = setting->value(QString("TestType/TestTypeCode")).toString();

    QStringList fileList;
    fileList << configure.result.file << configure.project.file << configure.material.file << configure.result.detail.file;

    return fileList;
}

QString zhiFangLisInterface::InterfaceName()
{
    return QString("质方Lis系统");
}

QString zhiFangLisInterface::buildNameSpaceStr(QString key,QString str)
{
    return str.isEmpty()?"":QString("declare namespace %1 = %2;").arg(key).arg(str).replace("'","\'");
}
