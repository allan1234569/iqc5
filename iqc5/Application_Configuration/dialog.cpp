#include "dialog.h"
#include "ui_dialog.h"
#include <QDir>
#include <QFileDialog>
#include <QSettings>
#include <QUuid>
#include <QRegularExpression>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setFixedSize(580,428);

    ui->toolButton_1->setIcon(QIcon("://images/point.png"));
    m_currentSetp = 1;
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_PreStep->setVisible(false);
    ui->pushButton_save->setVisible(false);
    ui->pushButton_NextStep->setEnabled(false);

    on_radioButton_UseDefaultPath_clicked();

    on_radioButton_LocalServer_clicked();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::record_Settings()
{
    switch (m_currentSetp) {
    case 1:
        m_settingInfo.deviceInfo.DeviceName = ui->lineEdit_DeviceName->text();
        m_settingInfo.deviceInfo.InstallPlace = ui->lineEdit_InstallPlace->text();
        break;
    case 2:
        if( ui->radioButton_SerialComm->isChecked() )
            m_settingInfo.communicationMode = "SERIAL";
//        else if( ui->radioButton_UsbComm->isChecked() )
//            m_settingInfo.communicationMode = "USB";
        else if( ui->radioButton_SocketComm->isChecked() )
            m_settingInfo.communicationMode = "SOCKET";
        else if( ui->radioButton_Log->isChecked() )
            m_settingInfo.communicationMode = "LOG";

        break;
    case 3:
        switch (m_Communication_mode) {
        case SERIAL:
            m_settingInfo.serialPortNo  = ui->comboBox_PortName->currentText().toShort();
            m_settingInfo.baudRate      = ui->comboBox_BuadRate->currentText().toShort();
            m_settingInfo.dataBits      = ui->comboBox_DataBits->currentText().toShort();
            m_settingInfo.stopBits      = ui->comboBox_StopBits->currentText().toFloat();
            m_settingInfo.parity        = ui->comboBox_Parity->currentText();
            break;
        case USB:

            break;
        case SOCKET:
            m_settingInfo.IpPort = ui->lineEdit_IpPort->text().toShort();
            m_settingInfo.ipAdress = ui->lineEdit_IpAdress->text();
            break;
        case DATABASE:

            break;
        case LOG:

            break;
        default:
            break;
        }

        break;
    case 4:

        break;
    default:
        break;
    }
}

void Dialog::generate_Guid()
{
//    QUuid uuid;
//    QString uid;
//    uid = uuid.createUuid().toString().replace(QRegularExpression("{[|]}"),"");
//    m_settingInfo.deviceInfo.DeviceId = uid;

//    uid = uuid.createUuid().toString().replace(QRegularExpression("{[|]}"),"");
//    m_settingInfo.deviceInfo.ModelId = uid;

//    uid = uuid.createUuid().toString().replace(QRegularExpression("{[|]}"),"");
//    m_settingInfo.deviceInfo.BrandId = uid;
}

void Dialog::on_pushButton_PreStep_clicked()
{
//    memset(&m_settingInfo,0,sizeof(Setting_Info));   //清空设置，以便重新写入
    m_currentSetp--;
    change_shows(m_currentSetp);
    next_pushbutton_setEnenable(m_currentSetp);
}

void Dialog::on_pushButton_NextStep_clicked()
{
    record_Settings();  //在当前步骤切换前记录已经设置好的参数

    m_currentSetp++;
    change_shows(m_currentSetp);
    next_pushbutton_setEnenable(m_currentSetp);
    ui->pushButton_NextStep->setEnabled(false);
}

void Dialog::on_pushButton_Cancel_clicked()
{
    this->close();
}

void Dialog::change_shows(qint16 index)
{
    switch (index) {
    case 1:     //仪器设置
       ui->toolButton_1->setIcon(QIcon("://images/point.png"));
       ui->toolButton_2->setIcon(QIcon(""));
       ui->toolButton_3->setIcon(QIcon(""));
       ui->toolButton_4->setIcon(QIcon(""));

       ui->pushButton_PreStep->setVisible(false);
       ui->pushButton_NextStep->setVisible(true);
       ui->pushButton_save->setVisible(false);

        break;
    case 2:     //通信方式
        ui->toolButton_1->setIcon(QIcon(""));
        ui->toolButton_2->setIcon(QIcon("://images/point.png"));
        ui->toolButton_3->setIcon(QIcon(""));
        ui->toolButton_4->setIcon(QIcon(""));

        ui->pushButton_PreStep->setVisible(true);
        ui->pushButton_NextStep->setVisible(true);
        ui->pushButton_save->setVisible(false);
        break;
    case 3:     //详情
        ui->toolButton_1->setIcon(QIcon(""));
        ui->toolButton_2->setIcon(QIcon(""));
        ui->toolButton_3->setIcon(QIcon("://images/point.png"));
        ui->toolButton_4->setIcon(QIcon(""));

        ui->pushButton_PreStep->setVisible(true);
        ui->pushButton_NextStep->setVisible(true);
        ui->pushButton_save->setVisible(false);

        switch (m_Communication_mode) {
        case SERIAL:
        case USB:
            ui->stackedWidget_2->setCurrentIndex(0);
            break;
        case SOCKET:
            ui->stackedWidget_2->setCurrentIndex(1);
            break;
        case DATABASE:
            ui->stackedWidget_2->setCurrentIndex(2);
            break;
        case LOG:
            ui->stackedWidget_2->setCurrentIndex(3);
            break;
        default:
            break;
        }
        break;
    case 4:     //汇总
        ui->toolButton_1->setIcon(QIcon(""));
        ui->toolButton_2->setIcon(QIcon(""));
        ui->toolButton_3->setIcon(QIcon(""));
        ui->toolButton_4->setIcon(QIcon("://images/point.png"));

        ui->pushButton_PreStep->setVisible(true);
        ui->pushButton_NextStep->setVisible(false);
        ui->pushButton_save->setVisible(true);
        break;
    default:
        break;
    }

    ui->stackedWidget->setCurrentIndex(index-1);
}

void Dialog::next_pushbutton_setEnenable(qint16 index)
{
    switch (m_currentSetp) {
    case 1: //仪器设置
        if( !ui->lineEdit_DeviceName->text().isEmpty()
                && !ui->lineEdit_InstallPlace->text().isEmpty()
                )
        {
            ui->pushButton_NextStep->setEnabled(true);
        }
        else
        {
            ui->pushButton_NextStep->setEnabled(false);
        }
        break;
    case 2: //
        if(ui->radioButton_SerialComm->isChecked()
//                || ui->radioButton_UsbComm->isCheckable()
                || ui->radioButton_SocketComm->isChecked()
                || ui->radioButton_Database->isChecked()
                || ui->radioButton_Log->isChecked())
        {
            ui->pushButton_NextStep->setEnabled(true);
        }
        else
        {
            ui->pushButton_NextStep->setEnabled(false);
        }
        break;
    case 3:
        switch (m_Communication_mode) {
        case SERIAL:        //串口通信
        case USB:       //USB通信
            if(     !ui->comboBox_PortName->currentText().isEmpty() &&
                    !ui->comboBox_BuadRate->currentText().isEmpty() &&
                    !ui->comboBox_DataBits->currentText().isEmpty() &&
                    !ui->comboBox_StopBits->currentText().isEmpty() &&
                    !ui->comboBox_Parity->currentText().isEmpty()
                    )
            {
                ui->pushButton_NextStep->setEnabled(true);
            }
            else
            {
                ui->pushButton_NextStep->setEnabled(false);
            }
            break;
        case SOCKET:    //网络通信
            if( ( ui->radioButton_Server->isChecked() || ui->radioButton_Clietnt->isChecked() ) &&
                ( ui->radioButton_Tcp->isChecked() || ui->radioButton_Udp->isChecked() ) &&
                  !ui->lineEdit_IpPort->text().isEmpty() &&
                  !ui->lineEdit_IpAdress->text().isEmpty()
                    )
            {
                ui->pushButton_NextStep->setEnabled(true);
            }
            else
            {
                ui->pushButton_NextStep->setEnabled(false);
            }
            break;
        case DATABASE:
            if(!ui->lineEdit_DataDbPath->text().isEmpty())
            {
                ui->pushButton_NextStep->setEnabled(true);
            }
            else
            {
                ui->pushButton_NextStep->setEnabled(false);
            }
            break;
        case LOG:       //LOG日志
            if(!ui->lineEdit_LogPath->text().isEmpty())
            {
                ui->pushButton_NextStep->setEnabled(true);
            }
            else
            {
                ui->pushButton_NextStep->setEnabled(false);
            }
            break;
        }
        break;
    default:
        break;
    }
}

void Dialog::save_settings()
{

    QSettings settings(ui->lineEdit_OnlineIniPath->text(),
                       QSettings::IniFormat);

    settings.setValue(tr("DEVICE/deviceName"),m_settingInfo.deviceInfo.DeviceName);
    settings.setValue(tr("DEVICE/installPlace"),m_settingInfo.deviceInfo.InstallPlace);

    settings.setValue(tr("COMC_MODE/communicationMode"),m_settingInfo.communicationMode);

    settings.setValue(tr("COMM/port"),QString::number(m_settingInfo.serialPortNo));
    settings.setValue(tr("COMM/baudRate"),QString::number(m_settingInfo.baudRate));
    settings.setValue(tr("COMM/dataBits"),QString::number(m_settingInfo.dataBits));
    settings.setValue(tr("COMM/stopBits"),QString::number(m_settingInfo.stopBits));
    settings.setValue(tr("COMM/parity"),m_settingInfo.serialPortNo);

    settings.setValue(tr("SOCKET/port"),QString::number(m_settingInfo.IpPort));
    settings.setValue(tr("SOCKET/ip"),m_settingInfo.ipAdress);

}

void Dialog::on_pushButton_save_clicked()
{
    generate_Guid();    //产生唯一的GUID写入结构体
    save_settings();
    this->close();
}

void Dialog::on_lineEdit_DeviceName_textChanged(const QString &arg1)
{
    if( !ui->lineEdit_DeviceName->text().isEmpty()
            && !ui->lineEdit_InstallPlace->text().isEmpty()
            )
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_lineEdit_InstallPlace_textChanged(const QString &arg1)
{
    if( !ui->lineEdit_DeviceName->text().isEmpty()
            && !ui->lineEdit_InstallPlace->text().isEmpty()
            )
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_radioButton_SerialComm_clicked()
{
    ui->pushButton_NextStep->setEnabled(true);
    m_Communication_mode = SERIAL;
}

void Dialog::on_radioButton_Database_clicked()
{
    ui->pushButton_NextStep->setEnabled(true);
    m_Communication_mode = DATABASE;
}

void Dialog::on_radioButton_SocketComm_clicked()
{
    ui->pushButton_NextStep->setEnabled(true);
    m_Communication_mode = SOCKET;
}

void Dialog::on_radioButton_Log_clicked()
{
    ui->pushButton_NextStep->setEnabled(true);
    m_Communication_mode = LOG;
}

void Dialog::on_comboBox_PortName_editTextChanged(const QString &arg1)
{
    if(     !ui->comboBox_PortName->currentText().isEmpty() &&
            !ui->comboBox_BuadRate->currentText().isEmpty() &&
            !ui->comboBox_DataBits->currentText().isEmpty() &&
            !ui->comboBox_StopBits->currentText().isEmpty() &&
            !ui->comboBox_Parity->currentText().isEmpty()
            )
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_comboBox_BuadRate_editTextChanged(const QString &arg1)
{
    if(     !ui->comboBox_PortName->currentText().isEmpty() &&
            !ui->comboBox_BuadRate->currentText().isEmpty() &&
            !ui->comboBox_DataBits->currentText().isEmpty() &&
            !ui->comboBox_StopBits->currentText().isEmpty() &&
            !ui->comboBox_Parity->currentText().isEmpty()
            )
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_comboBox_DataBits_editTextChanged(const QString &arg1)
{
    if(     !ui->comboBox_PortName->currentText().isEmpty() &&
            !ui->comboBox_BuadRate->currentText().isEmpty() &&
            !ui->comboBox_DataBits->currentText().isEmpty() &&
            !ui->comboBox_StopBits->currentText().isEmpty() &&
            !ui->comboBox_Parity->currentText().isEmpty()
            )
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_comboBox_StopBits_editTextChanged(const QString &arg1)
{
    if(     !ui->comboBox_PortName->currentText().isEmpty() &&
            !ui->comboBox_BuadRate->currentText().isEmpty() &&
            !ui->comboBox_DataBits->currentText().isEmpty() &&
            !ui->comboBox_StopBits->currentText().isEmpty() &&
            !ui->comboBox_Parity->currentText().isEmpty()
            )
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_comboBox_Parity_editTextChanged(const QString &arg1)
{
    if(     !ui->comboBox_PortName->currentText().isEmpty() &&
            !ui->comboBox_BuadRate->currentText().isEmpty() &&
            !ui->comboBox_DataBits->currentText().isEmpty() &&
            !ui->comboBox_StopBits->currentText().isEmpty() &&
            !ui->comboBox_Parity->currentText().isEmpty()
            )
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_lineEdit_IpPort_textChanged(const QString &arg1)
{
    if(     (ui->radioButton_Server->isChecked() || ui->radioButton_Clietnt->isChecked()) &&
            (ui->radioButton_Tcp->isChecked() || ui->radioButton_Udp->isChecked()) &&
            !ui->lineEdit_IpPort->text().isEmpty() &&
            !ui->lineEdit_IpAdress->text().isEmpty()
            )
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_lineEdit_IpAdress_textChanged(const QString &arg1)
{
    if(     (ui->radioButton_Server->isChecked() || ui->radioButton_Clietnt->isChecked()) &&
            (ui->radioButton_Tcp->isChecked() || ui->radioButton_Udp->isChecked()) &&
            !ui->lineEdit_IpPort->text().isEmpty() &&
            !ui->lineEdit_IpAdress->text().isEmpty()
            )
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_lineEdit_LogPath_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty())
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_radioButton_Clietnt_clicked(bool checked)
{
    if(     (ui->radioButton_Server->isChecked() || ui->radioButton_Clietnt->isChecked()) &&
            (ui->radioButton_Tcp->isChecked() || ui->radioButton_Udp->isChecked()) &&
            !ui->lineEdit_IpPort->text().isEmpty() &&
            !ui->lineEdit_IpAdress->text().isEmpty()
            )
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_radioButton_Server_clicked(bool checked)
{
    if(     (ui->radioButton_Server->isChecked() || ui->radioButton_Clietnt->isChecked()) &&
            (ui->radioButton_Tcp->isChecked() || ui->radioButton_Udp->isChecked()) &&
            !ui->lineEdit_IpPort->text().isEmpty() &&
            !ui->lineEdit_IpAdress->text().isEmpty()
            )
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_radioButton_Tcp_clicked(bool checked)
{
    if(     (ui->radioButton_Server->isChecked() || ui->radioButton_Clietnt->isChecked()) &&
            (ui->radioButton_Tcp->isChecked() || ui->radioButton_Udp->isChecked()) &&
            !ui->lineEdit_IpPort->text().isEmpty() &&
            !ui->lineEdit_IpAdress->text().isEmpty()
            )
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_radioButton_Udp_clicked(bool checked)
{
    if(     (ui->radioButton_Server->isChecked() || ui->radioButton_Clietnt->isChecked()) &&
            (ui->radioButton_Tcp->isChecked() || ui->radioButton_Udp->isChecked()) &&
            !ui->lineEdit_IpPort->text().isEmpty() &&
            !ui->lineEdit_IpAdress->text().isEmpty()
            )
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_radioButton_UseDefaultPath_clicked()
{
    QDir dir;
    QString onlineIniPath = dir.absolutePath() + QString("/online.ini");
    QString parserIniPath = dir.absolutePath() + QString("/setting.ini");

    ui->lineEdit_OnlineIniPath->setText(QDir::toNativeSeparators(onlineIniPath));
    ui->lineEdit_OnlineIniPath->setEnabled(false);
    ui->lineEdit_ParserIniPath->setText(QDir::toNativeSeparators(parserIniPath));
    ui->lineEdit_ParserIniPath->setEnabled(false);
    ui->pushButton_browse->setEnabled(false);
    ui->radioButton_UseDefaultPath->setChecked(true);
    ui->radioButton_CustomPath->setChecked(false);

}

void Dialog::on_radioButton_CustomPath_clicked()
{
    ui->lineEdit_OnlineIniPath->setEnabled(true);
    ui->lineEdit_ParserIniPath->setEnabled(true);
    ui->pushButton_browse->setEnabled(true);
    ui->radioButton_UseDefaultPath->setChecked(false);
    ui->radioButton_CustomPath->setChecked(true);
}

void Dialog::on_pushButton_browse_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(0,
                                      tr("选择文件路径"),
                                      tr("./"));
    if( !dirPath.isEmpty() )
    {
        QString onlineIniPath = dirPath + QString("/online.ini");
        QString parserIniPath = dirPath + QString("/setting.ini");
        ui->lineEdit_OnlineIniPath->setText(QDir::toNativeSeparators(onlineIniPath));
        ui->lineEdit_ParserIniPath->setText(QDir::toNativeSeparators(parserIniPath));
    }
}

void Dialog::on_PushButton_SelectLogPath_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                      tr("请选择路径"),
                                      tr("./"));
    if(!path.isEmpty())
    {
        ui->lineEdit_LogPath->setText(QDir::toNativeSeparators(path));
    }
}


void Dialog::on_radioButton_LocalServer_clicked()
{
    ui->pushButton_SelectDbPath->setVisible(true);

    ui->label_Port->setVisible(false);
    ui->lineEdit_Port->setVisible(false);
    ui->label_UserName->setVisible(false);
    ui->lineEdit_UserName->setVisible(false);
    ui->label_Password->setVisible(false);
    ui->lineEdit_Password->setVisible(false);
}

void Dialog::on_radioButton_RemoteServer_clicked()
{
    ui->pushButton_SelectDbPath->setVisible(false);

    ui->label_Port->setVisible(true);
    ui->lineEdit_Port->setVisible(true);
    ui->label_UserName->setVisible(true);
    ui->lineEdit_UserName->setVisible(true);
    ui->label_Password->setVisible(true);
    ui->lineEdit_Password->setVisible(true);
}

void Dialog::on_pushButton_SelectDbPath_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("请选择数据库文件"),
                                                tr("./"),
                                                tr("*.db"));
    if(!path.isEmpty())
    {
        ui->lineEdit_ServerDb->setText(QDir::toNativeSeparators(path));
    }
}


void Dialog::on_lineEdit_DataDbPath_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty())
    {
        ui->pushButton_NextStep->setEnabled(true);
    }
    else
    {
        ui->pushButton_NextStep->setEnabled(false);
    }
}

void Dialog::on_pushButton_SelectDataDb_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("请选择数据库文件"),
                                                tr("./"),
                                                tr("全部 (*.*);;*.db;;*.mdb"));
    if(!path.isEmpty())
    {
        ui->lineEdit_DataDbPath->setText(QDir::toNativeSeparators(path));
    }
}
