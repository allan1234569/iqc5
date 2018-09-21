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
#include <QListWidgetItem>
#include <QList>
#include <QAxObject>
#include "ui_basewindow.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include "adecodebase.h"
#include "asql.h"
#include "aexcel.h"
#include "common.h"
#include "messagebox.h"
#include "Delegate/trackdelegate.h"
#include "Delegate/ReadOnlyDelegate.h"

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

typedef QList< QList<QString> > DoubleList;

namespace Ui {
class BaseWindow;
}

class BaseWindow : public QMainWindow
{
    Q_OBJECT
public:
    typedef enum FileType{
        TXT,
        CSV,
        RES,
        EXP,
        XLS,
        XLSX,
        Clipboard

    }FileType;

    typedef enum ItemType{
        Item = 0,
        ComboBox,   //浓度水平
        LineEdit,   //项目名称
    }ItemType;

public:
    Ui::BaseWindow *ui;

    int m_nMaxSampleNo;
    QString m_sSampleNo;                //字符串样本号
    QString m_sSampleResultDateTime;    //样本时间和日期
    QString m_sSampleDate;              //样本日期
    bool m_bUseSysDate;
    int m_nResultCnt;                   //已经处理的结果数
    QString m_sSampleNoTrans;
    QString m_sEmptyResult;
    int m_nSampleNoTransLen;
    QReadWriteLock readWriteLock;   //读写锁

    QString m_sInstr;

    ADecodeBase m_dec;

    QString m_sInstallPlace;               //实验室编号

    ASql m_db;                          //数据库连接对象

    QString m_sDataFilePath;
    QString m_sFileSuffix;

    QString m_sFilePath;            //临时记录所选文件路径

    int m_importMode;

    DoubleList m_dataList;

    QString m_sWorkDay;

    FileType m_eFileType;

    //指定列表控件的头Label和相应的Item的类型
    QStringList m_slHeaders;
    QList<ItemType> m_slItemTypes;

    QVector<QString> m_ItemTables;

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

    QStringList m_fileLists;

    TrackDelegate *projectDelegate;
    TrackDelegate *densityDelegate;

    bool b_isEditing;

    QListWidget *listWidget;

    bool m_bIsReadState;

public:
    explicit BaseWindow(QWidget *parent = 0);
    ~BaseWindow();

    /**
     *@brief init   初始化函数，给子类调用
     */
    void init();   //供子类调用,

    /**
     * @brief initListWidget    初始化结果文件列表
     * @return
     */
    bool initListWidget();

    /**
     * @brief initItemCombox    初始化检测项目的下拉控件
     * @param as_list           检测项目的列表
     */
    void initItemCombox(const QStringList as_list);

    /**
     * @brief refreshData   刷新数据
     * @param list
     */
    void refreshData();

    void setFileSuffix(const QString suffix);

    void setFileType(FileType type);

    void showMessage(const QString title, const QString msg);


    int findColumn(QString HeaderItem);

    /**
     * @brief getColumn     获取指定列名称的索引
     * @param columnLabel   列名称
     * @return
     */
    int getColumn(const QString &columnLabel);

    /**
     * @brief setSampleNos  设置某一行的样本号值
     * @param row           行号      若行号值为-1则在最后一行，否则在指定行设置样本号
     * @param values        样本号值
     */
    void setSampleNos(int row,const QString values);

    /**
     * @brief resetTableWidget  表格数据重置
     * @param widget            指定对像(QTableWidget)
     */
    void ClearTableWidgetContents();


    /**
     * @brief getSampleResultTime   获取样本结果的时间
     * @param as_data
     */
    void getSampleResultTime(QString as_data);

    /**
     * @brief dealSampleNo
     * @param as_sampleNo
     * @param ab_flag
     * @return  0   正常结束
     *          -1  没有做任何处理结束
     */
    void dealSampleNo(QString &as_sampleNo, bool ab_flag);  //暂留

    int sendResult(QString as_id, QString as_item, QString as_result, int densityId, QString as_testTime, QString as_CreateTime);

    /**
     * @brief addResult         保存结果到本地
     * @param as_sampleNo       样本号
     * @param as_value          值
     * @param as_itemCode       检测项目
     * @param as_resultTime     时间
     */
    void addResult(const QString id, const QString as_sampleNo, const QString as_projectname, const QString as_value, const QString as_densityid, const QString as_resultTime, const QString as_createTime);

    /**
     * @brief packageToJson     打包成Jsons格式文件
     * @param as_sampleNo       样本号
     * @param as_value          值
     * @param as_itemCode       检测项目
     * @param as_deviceName
     * @return
     */
    QByteArray packageToJson(QString as_sampleNo, QString as_value, QString as_itemCode, QString as_deviceName);

    /**
     * @brief getContent    获取指定文件内容(带读写锁)
     * @param filename      文件名
     * @return
     */
    QString getContent(const QString &filename);

    /**
     * @brief readExcel     读取
     * @param as_filename
     * @param as_path
     * @return
     */
    int readExcel(const QString &as_filename);

    /**
     * @brief insertRow 插入一行
     * @return
     */
    quint32 insertRow();

    /**
     * @brief setResultHeader   设置结果对应的表头
     * @param column            指定列号
     */
    void setResultHeader(int column);

    quint32 getRowCount();

    /**
     * @brief getValue  获取列表中指定位置的值
     * @param row       行号
     * @param column    列号
     * @return
     */
    QString getItemValue(int row, int column);

    /**
     * @brief setItemValue  设置表格内容
     * @param row           指定行
     * @param column        指定列
     * @param value         指定内容
     */
    void setItemValue(int row, int column, QString value);

    void decode(QString file = "");


    /************************* 虚函数 *************************/

    /**
     * @brief set_TableWidgetHeader 设置表格头
     */
    virtual void set_TableWidgetHeader() = 0;

    /**
     * @brief file_decode   文件解友码
     * @param as_filename   文件名
     * @param as_path       路径
     * @return              -1  文件打开失败
     *                      0   解码成功
     */
    virtual void file_decode(const QString as_file, const QString as_path) = 0;

    virtual void excel_file_decode(const QString as_filepath) = 0;

    /**
     * @brief loadConfig    加载配置
     */
    virtual void loadConfig();

protected:

signals:
    void isChanged();

public slots:

    void slt_show();

    void slt_showTrayIcon(QSystemTrayIcon::ActivationReason reason);

    virtual void slt_timeout();

    void on_action_Exit_triggered();

    void on_action_DecodeSetup_triggered();

    void on_action_DecodeLog_triggered();

    void on_action_Help_triggered();

    void on_action_ReceiveSetup_triggered();

private:

    void createActions();

    void showTrayIcon();

    void setFileList(QString filename, bool remove = false);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *e);

private slots:
    // Custom slots
    /**
     * @brief slt_Editing   单元格被编辑时的处理函数
     * @param txt
     */
    void slt_Editing(const QString &txt);

    /**
     * @brief slt_EditFinished  单元格完成编辑时的处理函数
     */
    void slt_EditFinished();

    /**
     * @brief slt_listWidget_Clicked 下拉框被点击的处理函数
     * @param item
     */
    void slt_listWidget_Clicked(QListWidgetItem *item);

private slots:

    virtual void on_Select_PushButton_clicked();

    virtual void on_Import_PushButton_clicked() = 0;

    virtual void on_listWidget_itemSelectionChanged();

    void on_ItemCode_ComboBox_currentTextChanged(const QString &arg1);

    void on_autoAllocation_CheckBox_clicked(bool checked);

    virtual void on_Refresh_PushButton_clicked();

    void on_Allocation_PushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_comboBox_currentIndexChanged(int index);

    void on_Read_PushButton_clicked();

    void on_Result_TableWidget_itemSelectionChanged();

    // QObject interface
    void on_Result_TableWidget_itemChanged(QTableWidgetItem *item);

public:
    bool eventFilter(QObject *target, QEvent *event);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *keyevent);
};

#endif // BASEWINDOW_H
