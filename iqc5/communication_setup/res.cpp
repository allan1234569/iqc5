#include "res.h"
#include <QDir>
#include <QSettings>
#include <QFile>
#include <QDateTime>
#include <QMutexLocker>
#include <QDebug>

extern "C"{
    #include <stdarg.h>
}

enum TYPE g_eType = UNKNOW;
int     g_iComPort = INVALID_INT;
int     g_iBaudRate = INVALID_INT;
int     g_iDataBits = INVALID_INT;
float   g_fStopBits = INVALID_FLOAT;
QString g_sParity = INVALID_STRING;
int     g_iCommMode = INVALID_INT;
int     g_iRecvBufferSize = 0;

int     g_iLocalPort = INVALID_INT;
QString g_sRemoteIp = INVALID_STRING;
int     g_iRemotePort = INVALID_INT;

QString g_sTimer = "";

QDir dir;
QString g_sDestInstPath = QString("");
QString g_sFileIni = QString("communication.ini");
QString g_sFileLog = QString("com.log");
QString g_sRawDataDir = g_sDestInstPath.isEmpty()?QString("./raw"):g_sRawDataDir+"/raw";

QSettings *settings = new QSettings(dir.currentPath() + "/communication.ini",QSettings::IniFormat);

void readSettings(QString &value, const char *key)
{
    value = settings->value(key).toString();
}

void readSettings(int &value, const char *key)
{
     value = settings->value(key).toInt();
}

void readSettings(float &value, const char *key)
{
     value = settings->value(key).toInt();
}

void writeSettings(QString value, const char *key)
{
    settings->setValue(key,value);
}

void readAllSettings()
{
    QString tempStr;

    readSettings(tempStr,"COMM/TYPE");
    if(tempStr.compare("COM") ==  0)
    {
        g_eType = COM;
    }
    else if(tempStr.compare("NET") == 0)
    {
        g_eType = NET;
    }
    else
    {
        g_eType = UNKNOW;
    }

    readSettings(g_sTimer,"PROTOCOL/TIMER");

    readSettings(tempStr,"COMM/PORT");
    g_iComPort = tempStr.isEmpty()?INVALID_INT:tempStr.toInt();


    readSettings(tempStr,"COMM/BAUD");

    g_iBaudRate = tempStr.isEmpty()?INVALID_INT:tempStr.toInt();

    readSettings(tempStr,"COMM/DATA");
    g_iDataBits = tempStr.isEmpty()?INVALID_INT:tempStr.toInt();

    readSettings(tempStr,"COMM/STOP");
    g_fStopBits = tempStr.isEmpty()?INVALID_FLOAT:tempStr.toFloat();

    readSettings(g_sParity,"COMM/PARITY");

    readSettings(tempStr,"COMM/COMMMODE");
    g_iCommMode = tempStr.isEmpty()?INVALID_INT:tempStr.toInt();


    readSettings(tempStr,"COMM/INBUFFER");
        g_iRecvBufferSize = tempStr.isEmpty()?INVALID_INT:tempStr.toInt();

    readSettings(tempStr,"COMM/LOCALPORT");
    g_iLocalPort = tempStr.isEmpty()?INVALID_INT:tempStr.toInt();


    readSettings(g_sRemoteIp,"COMM/REMOTEHOST");

    readSettings(tempStr,"COMM/REMOTEPORT");
    g_iRemotePort = tempStr.isEmpty()?INVALID_INT:tempStr.toInt();
}

void writeAllSettings()
{
    switch (g_eType) {
    case COM:
        writeSettings(QString("COM"),"COMM/TYPE");
        break;
    case NET:
        writeSettings(QString("NET"),"COMM/TYPE");
        break;
    case UNKNOW:
        writeSettings(QString(""),"COMM/TYPE");
        break;
    default:
        break;
    }

    writeSettings(g_sTimer,"PROTOCOL/TIMER");

    writeSettings((g_iComPort   == INVALID_INT)?QString(""):QString::number(g_iComPort),"COMM/PORT");
    writeSettings((g_iBaudRate  == INVALID_INT)?QString(""):QString::number(g_iBaudRate),"COMM/BAUD");
    writeSettings((g_iDataBits  == INVALID_INT)?QString(""):QString::number(g_iDataBits),"COMM/DATA");
    writeSettings((g_fStopBits  == INVALID_FLOAT)?QString(""):QString::number(g_fStopBits),"COMM/STOP");
    writeSettings(g_sParity,"COMM/PARITY");
    writeSettings((g_iCommMode  == INVALID_INT)?QString(""):QString::number(g_iCommMode),"COMM/COMMMODE");
    writeSettings((g_iRecvBufferSize == INVALID_INT)?QString(""):QString::number(g_iRecvBufferSize),"COMM/INBUFFER");

    writeSettings((g_iLocalPort == INVALID_INT)?QString(""):QString::number(g_iLocalPort),"COMM/LOCALPORT");
    writeSettings(g_sRemoteIp,"COMM/REMOTEHOST");
    writeSettings((g_iRemotePort == INVALID_INT)?QString(""):QString::number(g_iRemotePort),"COMM/REMOTEPORT");

    writeSettings(g_sTimer,"PROTOCOL/TIMER");
}

void f_log(char*format...)
{
    char sprintf_buf[1024];

    va_list args;
    va_start(args,format);
    int n;
    n = vsprintf(sprintf_buf, format,args);
    va_end(args);

    QMutex mutex;
    mutex.lock();

    QString content = QString(sprintf_buf);
    QFile file(g_sFileLog);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Append);

    QString tempDateTime = QDateTime::currentDateTime().toString();
    content = tempDateTime.append("\t").append(content).append("\r\n");
    file.write(content.toStdString().c_str());

    file.close();

    mutex.unlock();
}


