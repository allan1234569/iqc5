#include "myTestType.h"

MyTestType::MyTestType()
{
}

void MyTestType::clear()
{
    TestTypeCode.clear();
}

bool MyTestType::isEmpty()
{
    return TestTypeCode.isEmpty();
}
