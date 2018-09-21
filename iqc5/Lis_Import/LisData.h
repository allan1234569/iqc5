#ifndef LISDATA_H
#define LISDATA_H

#include "Result.h"
#include "Material.h"
#include "Project.h"
#include "ProjectDetail.h"
#include "MaterialBatch.h"
#include "TestType.h"
#include "Category.h"
#include <QVector>

class LisData
{
public:
    LisData();
    bool isNull();
    void clear();
    QVector<Result*> resultVec;
    QVector<Material*>  materialVec;
    QVector<MaterialBatch*> materialBatchVec;
    QVector<ProjectDetail*>   projectDetailVec;
    QVector<TestType*> testTypeVec;
    QVector<Category*> categoryVec;
    QVector<Project*>  projectVec;
    LisData &operator =(LisData &other);
};

#endif // LISDATA_H
