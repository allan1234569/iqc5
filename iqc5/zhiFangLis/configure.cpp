#include "configure.h"
#include <QDebug>
Configure::Configure()
{
//    setting = new QSettings()
}

Configure::~Configure()
{
}

void Configure::readSettings()
{
//    s = setting->value(QString("General/s")).toString();
//    dt = setting->value(QString("General/dt")).toString();
//    rs = setting->value(QString("General/rs")).toString();
//    z = setting->value(QString("General/z")).toString();

//    result.file = setting->value(QString("Result/File")).toString();
//    result.path = setting->value(QString("Result/Path")).toString();
//    result.detailId = setting->value(QString("Result/Project_DetailId")).toString();
//    result.value = setting->value(QString("Result/Value")).toString();
//    result.createTime = setting->value(QString("Result/CreateTime")).toString();

//    project.file = setting->value(QString("Project/File")).toString();
//    project.path = setting->value(QString("Project/Path")).toString();
//    project.projectId = setting->value(QString("Project/ProjectId")).toString();
//    project.projectName = setting->value(QString("Project/ProjectName")).toString();
//    project.englishName = setting->value(QString("Project/EnglishName")).toString();
//    project.customName = setting->value(QString("Project/CustomName")).toString();

//    material.file = setting->value(QString("Material/File")).toString();
//    material.path = setting->value(QString("Material/Path")).toString();
//    material.materialId = setting->value(QString("Material/MaterialId")).toString();
//    material.materialName = setting->value(QString("Material/MaterialName")).toString();
}

Configure &Configure::operator =(Configure &config)
{
//    this->result.file       = config.result.file;
//    this->result.path       = config.result.path;
//    this->result.detailId   = config.result.detailId;
//    this->result.value      = config.result.value;
//    this->result.createTime = config.result.createTime;

//    this->project.file          = config.project.file;
//    this->project.path          = config.project.path;
//    this->project.projectId     = config.project.projectId;
//    this->project.projectName   = config.project.projectName;
//    this->project.englishName   = config.project.englishName;
//    this->project.customName    = config.project.customName;

//    this->material.file         = config.material.file;
//    this->material.path         = config.material.path;
//    this->material.materialId   = config.material.materialId;
//    this->material.materialName = config.material.materialName;

    return (*this);
}
