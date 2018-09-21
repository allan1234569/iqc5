#include "Settings.h"
#include <QTextCodec>

QSettings *settings = new QSettings("iqc.ini",QSettings::IniFormat);


QString readSetting(const char *key,QVariant defaultValue)
{
    settings->setIniCodec("UTF-8");
    return settings->value(key,defaultValue).toString();
}

void writeSetting(const char *key, QVariant value)
{
    settings->setIniCodec("UTF-8");
    settings->setValue(QString::fromUtf8(key),value);
}
