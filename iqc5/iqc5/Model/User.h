#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();

    QString UserId;
    QString UserName;
    QString UserPwd;
    int Status;
};

#endif // USER_H
