#ifndef TESTPARAMSERVICE_H
#define TESTPARAMSERVICE_H
#include "TestParam.h"
#include "Standard.h"

class TestParamService
{
public:
    TestParamService();

    TestParam GetById(QString TestParamId);
    TestParam GetByTestTypeAndStandard(QString testTypeId, QString standardId);

    QVector<TestParam> GetAll(QString categoryId, QString name, QString standId);
    QVector<TestParam> GetAll();
    QVector<Standard> GetStandard(QString testTypeId);
    QVector<Standard> GetAllStandard();

    void Insert(TestParam testParam);
    void Update(TestParam testParam);
    void DeleteById(QString TestParamId);
};

#endif // TESTPARAMSERVICE_H
