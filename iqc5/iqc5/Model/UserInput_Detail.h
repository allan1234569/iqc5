#ifndef USERINPUT_DETAIL_H
#define USERINPUT_DETAIL_H
#include <QString>

class UserInput_Detail
{
public:
    UserInput_Detail();

    QString UserInput_Detailid;
    QString UserInputid;
    QString FieldName;
    int FieldLocation;
    int FieldLength;
    int FieldBound;
    QString FieldType;

};

#endif // USERINPUT_DETAIL_H
