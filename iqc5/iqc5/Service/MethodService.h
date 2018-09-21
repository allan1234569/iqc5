#ifndef METHODSERVICE_H
#define METHODSERVICE_H
#include "Method.h"
#include <QString>

class MethodService
{
public:
    MethodService();

    Method GetById(QString MethodId);
    QVector<Method> GetByCategoryId(QString categoryId);
    QVector<Method> GetByTestTypeId(QString testTypeId);

    QVector<Method> GetMethods();
    QVector<Method> GetMethods(QString subjectId,QString categoryId, QString name,int if_user_first);
    void Insert(Method method);
    void Update(Method method);
    void DeleteById(QString MethodId);
    void UpdateTestType(Method method);
};

#endif // METHODSERVICE_H
