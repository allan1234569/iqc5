#include "common.h"
#include <QObject>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QIcon>
#include <QMutex>
#include <stdarg.h>
#include <QDateTime>
#include <QRegularExpression>

QDir dir;
QString path = dir.currentPath().append("/setting.ini");


QSettings *setting = new QSettings(path,QSettings::IniFormat);

QString g_sLogFilePath = dir.currentPath().append("/log.txt");

QString g_sRegInstr = "";

QString g_sLabNo = "0";

QString g_sUseSeqAsSample = "0";

QString g_sHostName = "127.0.0.1";

int g_nHostPort = 3306;


bool f_init()
{
    QFile iniFile(path);
    if (!iniFile.exists())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("错误"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(QObject::tr("\n没有找到配置文件(setting.ini)无法启动解析程序"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,QObject::tr("确定"));
        msgBox.exec();
        return false;
    }

    return true;
}

QVariant readSetting(const char *key, const QVariant &defaultValue)
{
    return setting->value(QString::fromLatin1(key),defaultValue);
}


void writeSetting(const char *key, const QVariant &value)
{
    setting->setValue(QString::fromLatin1(key),value);
}

void f_loadConfig()
{
    g_sRegInstr = readSetting("INSTR/devicename","").toString();
    g_sHostName = readSetting("SERVER/hostname","127.0.0.1").toString();
    g_nHostPort = readSetting("SERVER/port",3306).toInt();
    g_sLabNo = readSetting("LABORATORY/labno","").toString();
    g_sUseSeqAsSample = readSetting("QuickRead/useseqassampleno",0).toInt();
}


void f_log(char *format...)
{
    char sprintf_buf[1024];

    va_list args;
    va_start(args,format);
//    int n;
//    n = vsprintf(sprintf_buf, format,args);
    vsprintf(sprintf_buf, format,args);
    va_end(args);

    QMutex mutex;
    mutex.lock();

    QString content = QString(sprintf_buf);
    QFile file(g_sLogFilePath);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Append);

    QString tempDateTime = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    content = tempDateTime.append("\t").append(content).append("\r\n");
    file.write(content.toStdString().c_str());

    file.close();

    mutex.unlock();
}

bool isDate(QString as_date)
{
    return QDate::fromString(as_date,"yyyyMMdd").isValid();
}


bool isTime(QString as_time)
{
    return QTime::fromString(as_time,"HH:mm:ss").isValid();
}


bool isNumber(QString str)
{
    QRegularExpression reg("^-?\\d+$");
    QRegularExpression reg1("^(-?\\d+)(\\.\\d+)?$");

    return (reg.match(str).hasMatch() || reg1.match(str).hasMatch());
}

QString getRightStr(const QString source, const QString subStr)
{
    return source.right(source.length() - (source.indexOf(subStr) + subStr.length() +1));
}
