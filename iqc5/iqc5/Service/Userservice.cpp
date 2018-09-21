#include "Userservice.h"
#include <QSqlQuery>
#include <QDebug>

UserService::UserService()
{
}

bool UserService::check(User user)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    db.setDatabaseName("mytest.db");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("select UserName,UserPwd from User where UserName = :UserName and UserPwd = :UserPwd and Status = 1 ");
        query.bindValue(":UserName", user.UserName);
        query.bindValue(":UserPwd", user.UserPwd);
        query.exec();

        while (query.next())
        {
            return true;
        }
    }

    return false;
}
