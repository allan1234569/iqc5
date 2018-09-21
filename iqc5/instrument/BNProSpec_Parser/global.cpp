#include "global.h"

QSettings *settings = new QSettings(QString("BNProspec.ini"),QSettings::IniFormat);
QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

