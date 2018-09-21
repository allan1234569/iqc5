#ifndef RES_H
#define RES_H

#include <QString>
#include <QSettings>

extern QString g_sDestInstPath;
extern QString g_sFileIni;
extern QString g_sFileLog;
extern QString g_sRawDataDir;

const int INVALID_INT = -1;
const int INVALID_FLOAT = -1.0;
const char INVALID_CHAR = ' ';
const QString INVALID_STRING = "";

typedef enum TYPE{
    COM,
    NET,
    UNKNOW
}COMM_TYPE;

//GLOBAL VARIABLE
extern COMM_TYPE g_eType;       //通信方式，串口或网络或未知
extern int g_iComPort;          //串口通信端口
extern int g_iBaudRate;         //波特率
extern int g_iDataBits;         //数据位
extern float g_fStopBits;       //停止位
extern QString g_sParity;       //校验位
extern int g_iCommMode;         //通信模式，0代表文本模式，1代表流模式
extern int g_iRecvBufferSize;   //接收缓冲区大小

extern int g_iLocalPort;        //本地监听端口
extern QString g_sRemoteIp;     //远程IP
extern int g_iRemotePort;       //远程监听端口

extern QString g_sTimer;        //多久读一次缓存区

//LOCAL VARIABLE
extern QSettings *settings;
/**
 * @brief readSettings
 * @param value
 * @param key
 */
extern void readSettings(QString &value, const char  *key);

/**
 * @brief readSettings
 * @param value
 * @param key
 */
extern void readSettings(int &value, const char *key);

/**
 * @brief readSettings
 * @param value
 * @param key
 */
extern void readSettings(float &value, const char *key);

/**
 * @brief writeSettings
 * @param value
 * @param key
 */
extern void writeSettings(QString value, const char  *key);

/**
 * @brief readAllSettings
 */
extern void readAllSettings();

/**
 * @brief writeAllSettings
 */
extern void writeAllSettings();

extern void f_log(char *format,...);

#endif  //RES_H
