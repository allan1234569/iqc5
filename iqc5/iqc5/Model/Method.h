#ifndef METHOD_H
#define METHOD_H
#include <QString>
#include <QVector>
#include "Category.h"
#include "TestType.h"

class Method
{
public:
    Method();

    QString MethodId;
    QString MethodName;
    int Status;

    QString CategoryId;
    QString CategoryName;
    QString SubjectId;
    QString SubjectName;

    QVector<TestType> types;

};

#endif // METHOD_H
