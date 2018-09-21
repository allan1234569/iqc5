#ifndef COMMON_H
#define COMMON_H

#include <QTextCodec>
#include <QSettings>
#include <QVariant>
#include <string>
#include <QDebug>
#include <QMessageBox>


extern QSettings *setting;  //全局

extern QString g_sLogFilePath;  //解析日志文件

extern QString g_sRegInstr; //已注册的仪器

extern QString g_sLabNo;    //实验室编号

extern QString g_sUseSeqAsSample;

extern QString g_sHostName;

extern int g_nHostPort;

bool f_init();

QVariant readSetting(const char *key, const QVariant &defaultValue = QVariant());

void writeSetting(const char *key, const QVariant &value);

void f_loadConfig();

void f_log(char *format,...);

bool isDate(QString as_date);

bool isTime(QString as_time);

bool isNumber(QString str);

/**
 * @brief getRightStr   从指定的source中返回subStr右边字符串
 * @param source        给定字符串
 * @param subStr        子串
 * @return              返回结果
 */
QString getRightStr(const QString source, const QString subStr);




#endif // COMMON_H
