#ifndef TESTPARAM_H
#define TESTPARAM_H
#include <QString>

class TestParam
{
public:
    TestParam();

    QString TestParamId;
    QString TestTypeId;
    QString StandardId;

    double CV;
    double Bias;
    double TEa;

    QString unit;

    QString TestTypeName;
    QString StandardName;

    QString CategoryId;
    QString CategoryName;
    QString SubjectId;
    QString SubjectName;
};

#endif // TESTPARAM_H
