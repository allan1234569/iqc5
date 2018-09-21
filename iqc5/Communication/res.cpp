#include "res.h"
#include <QDir>
#include <QSettings>
#include <QFile>
#include <QDateTime>
#include <QMutexLocker>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <math.h>
#include <stdarg.h>

QString Ascii_Array[128] = {
    "<NUL>",    "<SOH>",    "<STX>",    "<ETX>",    "<EOT>",    "<ENQ>",    "<ACK>",    "<BEL>",
    "<BS>",     "<HT>",     "<LF>",     "<VT>",     "<FF>",     "<CR>",     "<SO>",     "<SI>",
    "<DLE",     "<DC1>",    "<DC2>",    "<DC3>",    "<DC4>",    "<NAK>",    "<SYN>",    "<ETB>",
    "<CAN",     "<EM>",     "<SUB>",    "<ESC>",    "<FS>",     "<GS>",     "<RS>",     "<US>",
    " ",        "!",        "\"",       "#",        "$",        "%",        "&",        "'",
    "(",        ")",        "*",        "+",        ",",        "-",        ".",        "/",
    "0",        "1",        "2",        "3",        "4",        "5",        "6",        "7",
    "8",        "9",        ":",        ";",        "<",        "=",        ">",        "?",
    "@",        "A",        "B",        "C",        "D",        "E",        "F",        "G",
    "H",        "I",        "J",        "K",        "L",        "M",        "N",        "O",
    "P",        "Q",        "R",        "S",        "T",        "U",        "V",        "W",
    "X",        "Y",        "Z",        "[",        "\\",       "]",        "^",        "_",
    "`",        "a",        "b",        "c",        "d",        "e",        "f",        "g",
    "h",        "i",        "j",        "k",        "l",        "m",        "n",        "o",
    "p",        "q",        "r",        "s",        "t",        "u",        "v",        "w",
    "x",        "y",        "z",        "{",        "|",        "}",        "~",        "<DEL>"
};

///串口相关参数
enum TYPE g_eType = UNKNOW;
int     g_iComPort = INVALID_INT;
int     g_iBaudRate = INVALID_INT;
int     g_iDataBits = INVALID_INT;
float   g_fStopBits = INVALID_FLOAT;
QString g_sParity = INVALID_STRING;
int     g_iCommMode = INVALID_INT;

///网络相关参数
int     g_iLocalPort = INVALID_INT;
QString g_sRemoteIp = INVALID_STRING;
int     g_iRemotePort = INVALID_INT;

///通用参数
int     g_iRecvBufferSize = 0;
QString g_sTimer = "";

///文件及目录配置参数
QDir dir;
QString g_sDestInstPath = QString("");
QString g_sDestInst = QString("");
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

    readSettings(tempStr,"PROTOCOL/DESTINSTR");
    g_sDestInst = tempStr;

    f_log("读取配置文件成功");
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
//    int n;
//    n = vsprintf(sprintf_buf, format,args);
    vsprintf(sprintf_buf, format,args);
    va_end(args);

    QMutex mutex;
    mutex.lock();

    QString content = QString(sprintf_buf);
    QFile file(g_sFileLog);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Append);

    QString tempDateTime = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    content = tempDateTime.append("\t").append(content).append("\r\n");
    file.write(content.toStdString().c_str());

    file.close();

    mutex.unlock();
}


double timeChangeover(QString &time)
{
    if (time.isEmpty())
    {
        return 0;
    }

    QRegularExpression reg("\\d+.{0,1}\\d{0,}");
    QRegularExpressionMatch match = reg.match(time);
    if(!match.hasMatch())   //判断是不是一个数
    {
        return 0;
    }

    QString strTime = time;
    if(strTime.contains("."))
    {
        double value = time.toDouble() * 1000;
        return (int)value;
    }
    else
    {
        return time.toInt()*1000;
    }
}

QString formatBytes2Visible(const QString &newStr, const QString lastestStr)
{
    QString tempLastStr = lastestStr;
    if (newStr.isEmpty())
    {
        return "";
    }
    QString resultStr = newStr;
    QString copyStr = newStr;
    int size = copyStr.size();
    for(int i = size -1; i >= 0; i--)
    {
        int decValue = (int)copyStr.at(i).toLatin1();

        resultStr.replace(i,1,Ascii_Array[decValue]);
    }

#ifdef Q_OS_WIN
    QString crlf = "<CR><LF>";
    QString crlfAfter = crlf + "\r\n";

    resultStr.replace(crlf,crlfAfter);

    //mabey invalid
    if (!tempLastStr.isEmpty())
    {
        tempLastStr.remove("\r\n");                 //去掉换行干扰
        QString right4str = tempLastStr.right(4);   //旧字符串取最后四个字符
        if (right4str.contains("<CR>"))
        {
            QString newLeft4Str = resultStr.left(4);   //新字符串取最前面四个字符

            if (newLeft4Str.contains("<LF>"))
            {
                resultStr.insert(4,"\r\n");
            }
        }
    }

#elif Q_OS_UNIX

    QString crlf = "<LF>";
    QString crlfAfter = crlf + "\n";

    resultStr.replace(crlf,crlfAfter);

#endif

    resultStr.prepend("\b");
    return resultStr;
}
