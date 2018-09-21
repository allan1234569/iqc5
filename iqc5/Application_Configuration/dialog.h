#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QIcon>

typedef enum COMMUNICATION_MODE{
    SERIAL,
    USB,
    SOCKET,
    DATABASE,
    LOG
}COMMUNICATION_MODE;

struct Device_Info{
    /*
     * 所有的ID由程序自动生成,是个唯一的标识
     */
    QString DeviceName;     //记录仪器名称
    QString InstallPlace;      //记录型号
};

typedef struct Setting_Info{
    //仪器信息
    struct Device_Info deviceInfo;  //保存仪器相关信息

    //通信方式
    QString communicationMode;

    //串口通信参数
    qint16 serialPortNo;    //COM口
    qint16 baudRate;        //波特率
    qint16 dataBits;        //数据位
    float  stopBits;        //停止位
    QString parity;         //校验位
\
    //USB通信参数

    //网络通信参数
    bool isClient;          //true代表客户端,false代表服务端
    bool isTcp;             //true代表使用的是TCP协议,false代表使用的是UDP协议
    qint16 IpPort;          //服务端口或者监听端口
    QString ipAdress;       //服务端IP

    //仪器数据库路径
    QString databasePath;

    //log日志目录
    QString logDir;

    //服务数据库路径或IP
    QString serverDatabase;

}Seting_Info;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void record_Settings();
    void generate_Guid();

private slots:
    //custom slot
    void change_shows(qint16 index);

    void next_pushbutton_setEnenable(qint16 index);

    void save_settings();

    //UI_SLOT
    void on_pushButton_PreStep_clicked();

    void on_pushButton_NextStep_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_save_clicked();

    void on_lineEdit_DeviceName_textChanged(const QString &arg1);

    void on_lineEdit_InstallPlace_textChanged(const QString &arg1);

    void on_radioButton_SerialComm_clicked();

    void on_radioButton_SocketComm_clicked();

    void on_radioButton_Database_clicked();

    void on_radioButton_Log_clicked();

    void on_comboBox_PortName_editTextChanged(const QString &arg1);

    void on_comboBox_BuadRate_editTextChanged(const QString &arg1);

    void on_comboBox_DataBits_editTextChanged(const QString &arg1);

    void on_comboBox_StopBits_editTextChanged(const QString &arg1);

    void on_comboBox_Parity_editTextChanged(const QString &arg1);

    void on_lineEdit_IpPort_textChanged(const QString &arg1);

    void on_lineEdit_IpAdress_textChanged(const QString &arg1);

    void on_lineEdit_LogPath_textChanged(const QString &arg1);

    void on_radioButton_Clietnt_clicked(bool checked);

    void on_radioButton_Server_clicked(bool checked);

    void on_radioButton_Tcp_clicked(bool checked);

    void on_radioButton_Udp_clicked(bool checked);

    void on_radioButton_UseDefaultPath_clicked();

    void on_radioButton_CustomPath_clicked();

    void on_pushButton_browse_clicked();

    void on_PushButton_SelectLogPath_clicked();

    void on_radioButton_LocalServer_clicked();

    void on_radioButton_RemoteServer_clicked();

    void on_pushButton_SelectDbPath_clicked();


    void on_lineEdit_DataDbPath_textChanged(const QString &arg1);

    void on_pushButton_SelectDataDb_clicked();

private:
    Ui::Dialog *ui;

    /**
     * @brief m_currentSetp 表示当前的步数
     * 1 表示仪器设置
     * 2 表示通信配置
     * 3 表示详细
     * 4 表示汇总
     */
    qint16 m_currentSetp;

    COMMUNICATION_MODE m_Communication_mode;    //通信模式

    Setting_Info m_settingInfo;

};

#endif // DIALOG_H
