#ifndef COMMON_H
#define COMMON_H

#include <QTextCodec>
#include <QSettings>
#include <QVariant>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QMessageBox>
#include <QString>
#include <QIcon>
#include <QObject>
#include <QDir>
#include <QFile>
#include <QCloseEvent>
#include <QFileDialog>
#include "single_application.h"


extern QSettings *setting;  //全局

extern QString g_sLogFilePath;  //解析日志文件

extern QString g_sRegInstr; //已注册的仪器

extern QString g_sInstallPlace;    //安装地点

extern QString g_sHostName;

extern QString g_sItemTables_file;

extern int g_nHostPort;

extern QString g_sSqlPath; //数据库路径

bool f_init();

QVariant readSetting(const char *key, const QVariant &defaultValue = QVariant());

void writeSetting(const char *key, const QVariant &value);

void f_loadConfig();

void f_log(char *format,...);

/**
 * @brief getRightStr   从指定的source中返回subStr右边字符串
 * @param source        给定字符串
 * @param subStr        子串
 * @return              返回结果
 */
QString getRightStr(const QString source, const QString subStr);

bool isNumber(QString str);


#endif // COMMON_H
