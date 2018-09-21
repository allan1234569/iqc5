#ifndef USERINPUT_H
#define USERINPUT_H
#include <QString>
#include <QVector>
#include "Model/UserInput_Detail.h"

class UserInput
{
public:
    UserInput();

    QString UserInputid;
    QString RuleName;
    QString LisId;
    QString DeviceId;
    QString CreateUser;
    QString CreateTime;
    int DataFlag;
    int InputType;
    int Status;

    QVector<UserInput_Detail> details;



};

#endif // USERINPUT_H
