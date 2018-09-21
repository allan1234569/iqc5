#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QDir>
#include <QTimer>
#include <QReadWriteLock>
#include <QTableWidget>

#include "adecodebase.h"
#include "asql.h"
#include "aaccessdb.h"

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
#define SIB char(26)

namespace Ui {
class BaseWindow;
}

class BaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::BaseWindow *ui;

    int m_nSampleNo;                    //样本号
    QString m_sSampleDate;
    QString m_sSampleNoRangeMax;
    QString m_sSampleNoRangeMin;
    QString m_sSampleResultDateTime;    //样本时间和日期
    bool m_bUseSysDate;
    int m_nRedecodeCnt;
    QString m_sSampleNoTrans;
    int m_nSampleNoTransLen;
    QReadWriteLock readWriteLock;   //读写锁

    QString m_sInstr;

    ADecodeBase m_dec;

    QString m_sLabNumber;               //实验室编号

    ASql m_db;                          //数据库连接对象
    AAccessDB m_accessDB;               //数据文件连接对象
    QString m_queryStr;                 //查询字符串

    ///ODBC
    QString driver;         //驱动
    QString databasePath;   //数据文件路径
    QString uid;            //用户ID
    QString password;       //登录密码

    int cnt;

private:
    //系统托盘，菜单，动作
    QSystemTrayIcon *m_sysTrayIcon;         //系统托盘
    QMenu   *m_trayIconmenu;                //托盘菜单
    ///菜单下的选项
    QAction *m_action_Show;                 //显示
//    QAction *m_action_ReadFile;             //读取文件
//    QAction *m_action_ReHandle;             //重新处理
    QAction *m_action_Exit;                 //退出
    QAction *m_action_Setup;                //设置
//    QAction *m_action_CheckOriginalData;    //查看原始数据
    QAction *m_action_CheckDecLog;          //查看Log日志
    QAction *m_action_Help;                 //帮助

    QTimer *m_Timer;

    bool m_bCanClose;

public:
    explicit BaseWindow(QWidget *parent = 0);
    ~BaseWindow();

    void init();   //供子类调用,


    void setDatabaseFilePath(const QString path);

    /**
     * @brief updateOriginalTableWidget 更新数据库文件对应原表格
     * @param query                     查询的结果
     * @param fields                    需要显示的字段，按顺序
     */
    void updateOriginalTableWidget(QSqlQuery *query, QStringList &fields);

    /**
     * @brief updateAfterTableWidget    更新已入库的表格，一次添加一行内容
     * @param row                       增加的行号
     */
    void updateAfterTableWidget(int row);

    void clearAllData(QTableWidget *widget);

    virtual void loadConfig();

    void getSampleResultTime(QString as_data);

    /**
     * @brief decode
     * @param data
     * @return
     */
    virtual int decode(const QString &data = QString());

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

    void addResult(QString as_sampleNo, QString as_value, QString as_itemCode);

    QByteArray packageToJson(QString as_sampleNo, QString as_value, QString as_itemCode, QString as_deviceName);

    QString getContent(const QString &filename);

signals:
    void isChanged();

public slots:

    void slt_show();

    void slt_showTrayIcon(QSystemTrayIcon::ActivationReason reason);

    virtual void slt_timeout();

    virtual void slt_setQuery() = 0;

    void on_action_Exit_triggered();

    void on_action_DecodeSetup_triggered();

    void on_action_DecodeLog_triggered();

    void on_action_Help_triggered();

private:

    void createActions();

    void showTrayIcon();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *e);
private slots:
    virtual void on_Select_PushButton_clicked();
    void on_Import_PushButton_clicked();
    void on_AutoIn_CheckBox_clicked(bool checked);
    void on_SampleDate_DateEdit_dateChanged(const QDate &date);
};

#endif // BASEWINDOW_H
