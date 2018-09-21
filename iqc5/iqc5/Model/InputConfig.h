#ifndef INPUTCONFIG_H
#define INPUTCONFIG_H
#include <QString>

class InputConfig
{
public:
    InputConfig();

    QString InputConfigID;
    QString TableName;
    QString FieldName;
    QString FieldLength;
    QString FieldType;
    int Status;
};

#endif // INPUTCONFIG_H
