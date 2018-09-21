#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

extern QSettings *settings;

extern QString readSetting(const char *key, QVariant defaultValue);

extern void writeSetting(const char *key, QVariant value);

#endif // SETTINGS_H
