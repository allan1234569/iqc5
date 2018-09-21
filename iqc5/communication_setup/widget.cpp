#include "widget.h"
#include "ui_widget.h"
#include "res.h"
#include <iostream>
#include <QDebug>
#include <QTimer>

#ifdef Q_OS_WIN

    #include <windows.h>
#pragma comment(lib,"user32.lib")

#elif Q_OS_UNIX

#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(509,537);
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);

    init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    if (g_eType == COM)
    {
        ui->radioButtonSerialPortComm->setChecked(true);
        on_radioButtonSerialPortComm_clicked();
    }
    else if (g_eType == NET)
    {
        ui->radioButtonNetComm->setChecked(true);
        on_radioButtonNetComm_clicked();
    }
    else
    {
         qDebug() << __LINE__;
    }

    if (g_iComPort == INVALID_INT)
    {
        ui->comboBoxComPort->setCurrentText("");
    }
    else
    {
        ui->comboBoxComPort->setCurrentIndex(g_iComPort-1);
    }

    ui->comboBoxBaudRate->setCurrentText((g_iBaudRate == INVALID_INT)?QString(""):QString::number(g_iBaudRate));

    ui->comboBoxDataBits->setCurrentText((g_iDataBits == INVALID_INT)?QString(""):QString::number(g_iDataBits));

    ui->comboBoxStopBits->setCurrentText((g_fStopBits == INVALID_FLOAT)?"":QString::number(g_fStopBits));

    if (g_sParity == "N")
    {
        ui->comboBoxParity->setCurrentIndex(0);
    }
    else if( g_sParity == "O")
    {
        ui->comboBoxParity->setCurrentIndex(1);
    }
    else if(g_sParity ==  "E")
    {
        ui->comboBoxParity->setCurrentIndex(2);
    }
    else
    {
        ui->comboBoxParity->setCurrentText("");
    }

    if (g_iCommMode == INVALID_INT)
    {
        ui->comboBoxCommMode->setCurrentText("");
    }
    else
    {
        ui->comboBoxCommMode->setCurrentIndex(g_iCommMode);
    }

    ui->comboBoxRecvBufferSize->setCurrentText((g_iRecvBufferSize == INVALID_INT)?QString(""):QString::number(g_iRecvBufferSize));

    ui->lineEditLocalPort->setText((g_iLocalPort == INVALID_INT)?QString(""):QString::number(g_iLocalPort));
    ui->lineEditRemoteIp->setText(g_sRemoteIp);
    ui->lineEditRemotePort->setText((g_iRemotePort == INVALID_INT)?QString(""):QString::number(g_iRemotePort));

    ui->comboBoxTimer->setCurrentText(g_sTimer);
}




void Widget::on_pushButtonEnsure_clicked()
{

    save();
    this->close();
}

void Widget::on_pushButtonApply_clicked()
{
    save();

#ifdef Q_OS_WIN

    HWND hWnd = ::FindWindowW(NULL,L"通信程序");
    if (hWnd != NULL)
    {
        QString str("command[immediately]");
        COPYDATASTRUCT cpd;
        cpd.dwData = 0;
        cpd.cbData = str.length()+1;
        cpd.lpData = str.data();
        ::SendMessageW(hWnd, WM_COPYDATA, NULL, (LPARAM)&cpd);
        ui->label_Status->setText("<html><head/><body><p style=\"color:#157DEC\"> </font> 参数修改已生效 </p></body></html>");
        QTimer *timer = new QTimer(this);
        timer->setInterval(3000);
        timer->start();
        connect(timer,SIGNAL(timeout()),this,SLOT(slt_on_timeout()));
    }
    else
    {
        ui->label_Status->setText("<html><head/><body><p style=\"color:#157DEC\"> </font> 通信程序未启动 </p></body></html>");
    }

#elif Q_OS_UNIX

#endif


}

void Widget::on_pushButtonCancel_clicked()
{
    this->close();
}

void Widget::save()
{
    writeAllSettings();
}

void Widget::on_radioButtonSerialPortComm_clicked()
{
    g_eType = COM;

    ui->comboBoxComPort->setEnabled(true);
    ui->comboBoxBaudRate->setEnabled(true);
    ui->comboBoxDataBits->setEnabled(true);
    ui->comboBoxStopBits->setEnabled(true);
    ui->comboBoxParity->setEnabled(true);
    ui->comboBoxCommMode->setEnabled(true);
    ui->comboBoxRecvBufferSize->setEnabled(true);

    ui->lineEditLocalPort->setEnabled(false);
    ui->lineEditRemoteIp->setEnabled(false);
    ui->lineEditRemotePort->setEnabled(false);
}

void Widget::on_radioButtonNetComm_clicked()
{
    g_eType = NET;

    ui->comboBoxComPort->setEnabled(false);
    ui->comboBoxBaudRate->setEnabled(false);
    ui->comboBoxDataBits->setEnabled(false);
    ui->comboBoxStopBits->setEnabled(false);
    ui->comboBoxParity->setEnabled(false);
    ui->comboBoxCommMode->setEnabled(false);
    ui->comboBoxRecvBufferSize->setEnabled(false);

    ui->lineEditLocalPort->setEnabled(true);
    ui->lineEditRemoteIp->setEnabled(true);
    ui->lineEditRemotePort->setEnabled(true);
}

void Widget::on_comboBoxComPort_currentTextChanged(const QString &arg1)
{
    QString tempStr = arg1;
    g_iComPort = tempStr.isEmpty()?INVALID_INT:tempStr.remove("COM").toInt();
}

void Widget::on_comboBoxBaudRate_currentTextChanged(const QString &arg1)
{
    QString tempStr = arg1;
    g_iBaudRate =  tempStr.isEmpty()?INVALID_INT:tempStr.toInt();
}

void Widget::on_comboBoxDataBits_currentTextChanged(const QString &arg1)
{
    QString tempStr = arg1;
    g_iDataBits =  tempStr.isEmpty()?INVALID_INT:tempStr.toInt();
}

void Widget::on_comboBoxStopBits_currentTextChanged(const QString &arg1)
{
    QString tempStr = arg1;
    g_fStopBits =  tempStr.isEmpty()?INVALID_FLOAT:tempStr.toFloat();
}


void Widget::on_comboBoxParity_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        g_sParity = "N";
        break;
    case 1:
        g_sParity = "O";
        break;
    case 2:
        g_sParity = "E";
        break;
    default:
        g_sParity = "";
        break;
    }
}

void Widget::on_comboBoxCommMode_currentIndexChanged(int index)
{
    g_iCommMode = index;
}

void Widget::on_comboBoxRecvBufferSize_currentTextChanged(const QString &arg1)
{
    QString tempStr = arg1;
    g_iRecvBufferSize =  tempStr.isEmpty()?INVALID_INT:tempStr.toInt();
}

void Widget::on_lineEditLocalPort_textChanged(const QString &arg1)
{
    QString tempStr = arg1;
    g_iLocalPort =  tempStr.isEmpty()?INVALID_INT:tempStr.toInt();
}

void Widget::on_lineEditRemoteIp_textChanged(const QString &arg1)
{
    g_sRemoteIp = arg1;
}

void Widget::on_lineEditRemotePort_textChanged(const QString &arg1)
{
    QString tempStr = arg1;
    g_iRemotePort =  tempStr.isEmpty()?INVALID_INT:tempStr.toInt();
}

void Widget::on_comboBoxTimer_currentTextChanged(const QString &arg1)
{
    g_sTimer = arg1;
}

void Widget::slt_on_timeout()
{
    ui->label_Status->setText("");
    QTimer *timer = qobject_cast<QTimer*>(sender());
    timer->stop();
}
