#ifndef MY_TESTTYPE_H
#define MY_TESTTYPE_H
#include <QString>

class MyTestType
{
public:
    MyTestType();
    void clear();
    bool isEmpty();

    QString TestTypeCode;   //检测项目缩写
};

#endif // MY_TESTTYPE_H
