#include "myProject.h"

MyProject::MyProject()
{
    subProjectCount = 0;
}

void MyProject::clear()
{
    sampleId.clear();
    testTypeCode.clear();
    testType.clear();
    subProjectCount = 0;
}

bool MyProject::isEmpty()
{
    return sampleId.isEmpty() && testTypeCode.isEmpty() && subProjectCount == 0;
}
