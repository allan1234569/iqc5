#include "LisData.h"

LisData::LisData()
{
}

bool LisData::isNull()
{
    return  (0 == resultVec.size()          ) &&
            (0 == testTypeVec.size()        ) &&
            (0 == materialVec.size()        ) &&
            (0 == materialBatchVec.size()   ) &&
            (0 == projectDetailVec.size()   ) &&
            (0 == projectVec.size()         );
}

void LisData::clear()
{
    resultVec.clear();
    materialBatchVec.clear();
    materialVec.clear();
    projectDetailVec.clear();
    projectVec.clear();
    testTypeVec.clear();
}

LisData &LisData::operator =(LisData &other)
{
    this->materialVec = other.materialVec;
    this->materialBatchVec = other.materialBatchVec;
    this->projectVec = other.projectVec;
    this->projectDetailVec = other.projectDetailVec;
    this->resultVec = other.resultVec;
    return (*this);
}
