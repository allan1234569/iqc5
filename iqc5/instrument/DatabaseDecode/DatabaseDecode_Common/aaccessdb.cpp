#include "aaccessdb.h"
#include <QString>

AAccessDB::AAccessDB()
{
}

bool AAccessDB::connectDB(const QString &DatabasePath, const QString &ConnectName, const QString &HostName, const QString &UserName, const QString &Password)
{
    const QString connID(ConnectName);
    connection = QSqlDatabase::database(connID,false);

    if (connection.isValid())
    {
        if (connection.open())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        connection = QSqlDatabase::addDatabase("QODBC",connID);

        QString dsn = QString("DRIVER={%1};DBQ=%2;UID=%3;PWD=%3")
                .arg(m_sDriver)
                .arg(DatabasePath)
                .arg(m_sUid)
                .arg(Password);
        connection.setDatabaseName(dsn);

        //connection.setUserName(UserName);
        //connection.setPassword(Password);
        if(!connection.open())
        {
            f_log("无法连接本地数据库(%s)",connection.lastError().text().toStdString().data());
            return false;
        }
        else
        {
            newQuery();
            return true;
        }
    }
}

bool AAccessDB::queryDB(const QString query)
{
    if (m_query == NULL)
        return false;

    if (!m_query->prepare(query))
    {
        connection.close();
        if (!openDB())
        {
            return false;
        }
    }

    if (m_query->exec())
    {
        return true;
    }
    else
    {
        return false;
    }


}

void AAccessDB::newQuery()
{
    m_query = new QSqlQuery(connection);
}

bool AAccessDB::openDB()
{
    if(!connectDB(m_sDbName,m_sIdName,"",m_sUid,m_sPassword))
    {
        return false;
    }
    return true;
}

void AAccessDB::closeDB()
{
    const QString connID(m_sIdName);
    connection.close();
    connection.removeDatabase(connID);
}
