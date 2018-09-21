#ifndef ADATABASEFILE_CONN_H
#define ADATABASEFILE_CONN_H

#include <QSqlDatabase>
#include <QSqlQuery>

class ADatabaseFile_Conn
{
public:
    ADatabaseFile_Conn();
    void init();

    bool open();

    void close();


private:
    QSqlDatabase db;
};

#endif // ADATABASEFILE_CONN_H
