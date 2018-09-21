#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <User.h>

class UserService
{
public:
    UserService();

    bool check(User user);
};

#endif // USERSERVICE_H
