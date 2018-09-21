#ifndef RES_H
#define RES_H

#include <QString>
#include <QSettings>

extern QString Ascii_Array[128];


extern QString g_sDestInstPath; //目标仪器路径
extern QString g_sDestInst;     //目标仪器
extern QString g_sFileIni;      //配置文件
extern QString g_sFileLog;      //日志文件
extern QString g_sRawDataDir;   //数据保存目录

///各种变量类型无效值
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
void readSettings(QString &value, const char  *key);

/**
 * @brief readSettings
 * @param value
 * @param key
 */
void readSettings(int &value, const char *key);

/**
 * @brief readSettings
 * @param value
 * @param key
 */
void readSettings(float &value, const char *key);

/**
 * @brief writeSettings
 * @param value
 * @param key
 */
void writeSettings(QString value, const char  *key);

/**
 * @brief readAllSettings
 */
void readAllSettings();

/**
 * @brief writeAllSettings
 */
void writeAllSettings();

void f_log(char *format,...);


/**
 * @brief timeChangeover    将字符串转换成整型时间，单位: 秒/s
 * @param time              传入的QString类型的字符串
 * @return
 */
double timeChangeover(QString &time);

/**
 * @brief ascii2str
 * @param l
 */

/**
 * @brief formatBytes2Visible   转换成可见字符，格式化并且加上接收时间
 *                              例如：将ASCII值为05的请求控制符转换成可见的<ENQ>字符串,'5' -> "<ENQ>"
 * @param newStr                新字符串
 * @param lastestStr            最近一次的字符串（前一次）,防止加入换行时漏了
 * @return
 */
QString formatBytes2Visible(const QString &newStr, const QString lastestStr);

#endif  //RES_H
