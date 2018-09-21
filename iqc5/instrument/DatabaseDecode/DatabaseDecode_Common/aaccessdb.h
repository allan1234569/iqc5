#ifndef AACCESSDB_H
#define AACCESSDB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "common.h"

class AAccessDB
{
public:
    AAccessDB();

    bool connectDB(const QString& DatabasePath,
                   const QString& ConnectName,
                   const QString& HostName = "",
                   const QString& UserName = "",
                   const QString& Password = "");

    bool queryDB(const QString query);

    void newQuery();

    bool openDB();

    void closeDB();

    QSqlDatabase connection;
    QSqlQuery *m_query;
    QString m_sDriver;
    QString m_sDbName;
    QString m_sIdName;
    QString m_sUid;
    QString m_sPassword;
};

#endif // AACCESSDB_H
