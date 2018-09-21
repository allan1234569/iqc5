#include "adatabasefile_conn.h"

ADatabaseFile_Conn::ADatabaseFile_Conn()
{
}

void ADatabaseFile_Conn::init()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=I:/mycode/ConnectAccess/test.mdb");
}

bool ADatabaseFile_Conn::open()
{

}

void ADatabaseFile_Conn::close()
{

}
