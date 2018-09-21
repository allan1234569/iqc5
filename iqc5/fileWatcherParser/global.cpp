#include "global.h"

QSettings *settings = new QSettings(QString("BNProspec.ini"),QSettings::IniFormat);
ClientSocket *client = new ClientSocket;
