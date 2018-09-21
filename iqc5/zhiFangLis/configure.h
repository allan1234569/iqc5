#ifndef CONFIGURE_H
#define CONFIGURE_H
#include <QSettings>
#include <QString>

class ConfigProjectDetail
{
public:
    QString file;
    QString path;
    QString projectDetailId;
    QString materialId;
    QString proecjtId;
};

class ConfigResult
{
public:
    QString file;
    QString path;
    QString projectId;
    QString value;
    QString createTime;
    ConfigProjectDetail detail;
};

class ConfigProject
{
public:
    QString file;
    QString path;
    QString projectId;
    QString projectName;
    QString englishName;
    QString customName;
    QString testTypeId;
};

class ConfigTestType
{
public:
    QString file;
    QString path;
    QString testTypeId;
    QString testTypeName;
    QString englishName;
    QString shortName;
    QString testTypeCode;

};

class ConfigCategory
{
public:
    QString file;
    QString path;
    QString categoryId;
    QString categoryName;
    QString parentId;
};

class ConfigMaterial
{
public:
    QString file;
    QString path;
    QString materialId;
    QString materialName;
    QString manufacturerName;
};

class Configure
{
public:
    Configure();
    ~Configure();
    void readSettings();
    Configure &operator =(Configure& config);
public:
    QString s;
    QString dt;
    QString rs;
    QString z;
    ConfigMaterial material;
    ConfigProject project;
    ConfigTestType testType;
    ConfigResult result;
    ConfigCategory category;


private:
    QSettings *setting;
};

#endif // CONFIGURE_H
