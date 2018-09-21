#ifndef TESTTYPESERVICE_H
#define TESTTYPESERVICE_H
#include "TestType.h"

class TestTypeService
{
public:
    TestTypeService();

    TestType GetById(QString id);
    QVector<TestType> GetByCategoryId(QString categoryId);
    QVector<TestType> GetByCategoryIdAndMaterialId(QString categoryId, QString materialId);


    QVector<TestType> GetTestTypes(QString subjectId, QString categoryId, QString name);
    QVector<TestType> GetTestTypes();//add by heyi
    QVector<TestType> GetTestTypesBy3Name(QString name);
    static QStringList SearchTestTypesByName(QString name);
    void Insert(TestType testType);
    void Update(TestType testType);
    void DeleteById(QString TestTypeId);

    QVector<TestType> GetTestTypesWithMaterialChecked(QString materialId);
    QVector<TestType> GetTestTypesWithReagentChecked(QString reagentId, QString testTypeName);
    QVector<TestType> GetTestTypesWithMethodChecked(QString methodId);
};

#endif // TESTTYPESERVICE_H
