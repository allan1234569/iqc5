#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QDir>
#include <QTimer>
#include <QReadWriteLock>
#include <QDateTime>

#include "adecodebase.h"
#include "asql.h"
#include "common.h"

#define NUL char(0)
#define SOH char(1)
#define STX char(2)
#define ETX char(3)
#define EOT char(4)
#define ENQ char(5)
#define ACK char(6)
#define CR  char(13)
#define LF  char(10)
#define DC1 char(17)
#define DC2 char(18)
#define DC3 char(19)
#define DC4 char(20)
#define NAK char(21)
#define ETB char(23)
#define SUB char(26)
#define GS  char(29)
#define RS  char(30)

//char *lf;
//sprintf(lf,"%c",LF);

namespace Ui {
class BaseWindow;
}

class BaseWindow : public QMainWindow
{
    Q_OBJECT

    enum DecodeMode{
        SerialPort = 0,
        Log
    };

public:
    int m_nSampleNo;                    //样本号
    QString m_sSampleNo;                //字符串样本号
    QString m_sSampleDate;              //样本日期
    QString m_sData;                    //保存要处理的数据
    QString m_sSampleResultDateTime;    //样本时间和日期
    bool m_bUseSysDate;                 //使用系统日期
    quint64 m_nHandledSize;             //已经处理的文件大小
    int m_nResultCnt;                   //已经处理的结果数

    QString m_sInstr;                   //仪器
    QString m_sSampleNoTrans;           //
    int m_nSampleNoTransLen;

    ADecodeBase m_dec;                  //解析用的基础对象

    QString m_sLabNumber;               //实验室编号

    ASql m_db;                          //数据库连接对象

    QString m_sFileName;                //解码文件名

    QTimer *m_Timer;                    //计时器
    QTimer *m_sysTrayTimer;             //托盘闪烁计时器

    QReadWriteLock readWriteLock;           //读写锁

    DecodeMode m_enumDecodeMode;

private:
    Ui::BaseWindow *ui;

    //系统托盘，菜单，动作
    QSystemTrayIcon *m_sysTrayIcon;         //系统托盘
    QMenu   *m_trayIconmenu;                //托盘菜单
    ///菜单下的选项
    QAction *m_action_Show;                 //显示
    QAction *m_action_ReadFile;             //读取文件
    QAction *m_action_ReHandle;             //重新处理
    QAction *m_action_Exit;                 //退出
    QAction *m_action_Setup;                //设置
    QAction *m_action_CheckOriginalData;    //查看原始数据
    QAction *m_action_CheckDecLog;          //查看Log日志
    QAction *m_action_Help;                 //帮助

    QDir m_applicationDir;                  //应用程序目录

    bool m_bCanClose;

    bool m_bSysIconIsShow;

    int m_nRedecodeCnt;                     //次数统计



public:
    explicit BaseWindow(QWidget *parent = 0);
    ~BaseWindow();

    void showSystemTrayMessage(const QString &msg);

    void showSysTrayIcon(bool state); //显示托盘图标

    virtual void loadConfig();

    void getSampleResultTime(QString as_date);

    /**
     * @brief decode
     * @param data
     * @return  0   解码成功
     *          -1  数据库打开失败
     *          1   未做任何处理
     */
    virtual int decode(QString data) = 0;

    /**
     * @brief redecode
     */
    void redecode();

    /**
     * @brief dealSampleNo
     * @param as_sampleNo
     * @param ab_flag
     * @return  0   正常结束
     *          -1  没有做任何处理结束
     */
    void dealSampleNo(QString &as_sampleNo, bool ab_flag);  //暂留

    QString dateToByteString(QString as_str);

    /**
     * @brief hex       将一个字符转换成16进制(如果传入一个字符串则取字符串第一个字符)
     * @param as_str    字符参数
     * @return          返回16进制字符串
     */
    QString hex(QString as_str);

    /**
     * @brief getAsc    获取某个字符的ASCII值(如果传入一个字符串则取字符串第一个字符)
     * @param as_str    字符参数
     * @return          返回整型值
     */
    int getAsc(QString as_str);

    int sendResult(QString as_item, QString as_result);

    void addResult( const QString as_sampleNo, const QString as_value, const QString as_itemCode, const QString as_resultTime);

    /**
     * @brief sendItemResult
     * @param as_code
     * @param as_item
     * @return      2   传入的字符串为空或传入的字符中未找到对应项目名
     *              3   结果为空值
     *              -1，0，1返回的是ASql类中sendResult()的返回值
     */
    int sendItemResult(QString as_code, const QString as_item);

    QByteArray packageToJson(QString as_sampleNo, QString as_value, QString as_itemCode, QString as_deviceName);

    QString getContent(const QString &filename);

    QString getSampleDate(int ai_year, int ai_month, int ai_day);

public slots:

    void slt_show();

    void slt_showTrayIcon(QSystemTrayIcon::ActivationReason reason);

    virtual void slt_timeout();

    void on_action_ReadFile_triggered();

    void on_action_ReHandle_triggered();

    void on_action_Exit_triggered();

    virtual void on_action_DecodeSetup_triggered();

    void on_action_OriginalData_triggered();

    void on_action_DecodeLog_triggered();

    void on_action_Help_triggered();

    /**
     * @brief modifyState   //改变托盘状态
     */
    void modifyState();

private:

    void createActions();

    void showTrayIcon();


    // QWidget interface
protected:
    void closeEvent(QCloseEvent *e);
};

#endif // BASEWINDOW_H
