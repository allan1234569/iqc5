#ifndef TESTTYPE_H
#define TESTTYPE_H
#include <QString>
#include <QVector>
#include "Category.h"
#include "TestParam.h"

class TestType
{
public:
    TestType();

    QString TestTypeId;
    QString CategoryId;
    QString TestTypeCode;
    QString TestTypeName;
    int IfDefault;
    QString AddTime;
    int Status;

    QString SubjectId;
    QString SubjectName;
    QString CategoryName;

    QVector<TestType> Params;

    int flag;



};

#endif // TESTTYPE_H
