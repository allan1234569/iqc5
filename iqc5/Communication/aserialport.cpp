#include "aserialport.h"
#include "ui_aserialport.h"
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>
#include <res.h>
#include <QDebug>

ASerialPort::ASerialPort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ASerialPort)
{
    ui->setupUi(this);
    init();

    m_serialPort = NULL;
    m_bufferSize = 512;
    QString tempStr;
    readSettings(tempStr,"PROTOCOL/TIMER");

    m_timerInterval = timeChangeover(tempStr);

    m_timer = new QTimer(this);
    m_timer->setInterval(m_timerInterval);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slt_timeOut()));

    m_flickerTimer = new QTimer(this);
    m_flickerTimer->setInterval(300);
    connect(m_flickerTimer,SIGNAL(timeout()),this,SLOT(slt_flickerTimeout()));
    m_flickerFlag = true;

    m_statTestTimer = new QTimer(this);
    m_statTestTimer->setInterval(500);
    connect(m_statTestTimer,SIGNAL(timeout()),this,SLOT(slt_statTestTimeout()));
    m_statTestTimer->start();

    m_isOpen = false;
    m_isDisplay = true;

    m_flickerCount = 0;

//    ui->baudRateComboBox->setEnabled(false); //设置各个组合框不可用
//    ui->dataBitsComboBox->setEnabled(false);
//    ui->parityComboBox->setEnabled(false);
//    ui->stopBitsComboBox->setEnabled(false);
//    ui->portNameComboBox->setEnabled(false);

    on_openPort_PushButton_clicked();//打开串口
}

ASerialPort::~ASerialPort()
{
    delete ui;

    if(m_isOpen)
    {
        m_serialPort->close();
        delete m_serialPort;
        m_serialPort = NULL;

        delete m_timer;
        m_timer = NULL;
    }
}

void ASerialPort::init()
{
    QString tempStr;

    readSettings(tempStr,"COMM/PORT");
    QString portName = tempStr.prepend("COM");
    ui->portNameComboBox->setCurrentText(portName);

    readSettings(tempStr,"COMM/BAUD");
    QString baudRate = tempStr;
    ui->baudRateComboBox->setCurrentText(baudRate);

    readSettings(tempStr,"COMM/DATA");
    QString dataBits = tempStr;
    ui->dataBitsComboBox->setCurrentText(dataBits);

    readSettings(tempStr,"COMM/STOP");
    QString stopBits = tempStr;
    ui->stopBitsComboBox->setCurrentText(stopBits);

    readSettings(tempStr,"COMM/PARITY");
    if (tempStr == "N")
    {
        ui->parityComboBox->setCurrentText("无校验");
    }
    else if (tempStr == "O")
    {
        ui->parityComboBox->setCurrentText("奇校验");
    }
    else if (tempStr == "E")
    {
        ui->parityComboBox->setCurrentText("偶校验");
    }

    readSettings(tempStr,"COMM/INBUFFER");
    m_bufferSize = tempStr.toLong();

    readSettings(tempStr,"PROTOCOL/TIMER");
}

void ASerialPort::clear_display()
{
    on_clearBufPushButton_clicked();
}

void ASerialPort::reStart()
{
    on_openPort_PushButton_clicked();   //先闭

}

void ASerialPort::on_openPort_PushButton_clicked()
{
    if (m_isOpen)//关闭
    {
        if (m_serialPort != NULL)
        {
            m_serialPort->close(); //关闭串口
            m_serialPort = NULL;
            m_isOpen = false;
            ui->openPort_PushButton->setText(tr("打开串口"));
            ui->portState_label->setText("<html><head/><body><p><img src=\":/pics/dot_red_24px.png\"/></p></body></html>");
            m_timer->stop();    //关闭定时器
        }
    }
    else//打开
    {
        if (m_serialPort != NULL)
        {
            m_serialPort = NULL;
        }
        //        QFile errorfile("./com_error.log");
        //        errorfile.open(QIODevice::WriteOnly | QFile::Append);
        //        QByteArray errorData;


        QString portName = ui->portNameComboBox->currentText(); //获取串口名

        //定义串口对象，并传递参数，在构造函数里对其进行初始化
        m_serialPort = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);

        if( !m_serialPort ->open(QIODevice::ReadWrite) )  //以可读写方式打开串口
        {
            QMessageBox::warning(this,tr("警告"),tr("串口打开失败"));
            f_log("串口打开失败，端口号%s",portName.toStdString().c_str());

            return;
        }
        else
        {
            f_log("串口打开成功，端口号%s",portName.toStdString().c_str());
        }

        //设置波特率
        if(ui->baudRateComboBox->currentText() == tr("300"))
        {
            m_serialPort->setBaudRate(BAUD300);
        }
        else if(ui->baudRateComboBox->currentText() == tr("600"))
        {
            m_serialPort->setBaudRate(BAUD600);
        }
        else if(ui->baudRateComboBox->currentText() == tr("1200"))
        {
            m_serialPort->setBaudRate(BAUD1200);
        }
        else if(ui->baudRateComboBox->currentText() == tr("2400"))
        {
            m_serialPort->setBaudRate(BAUD2400);
        }
        else if(ui->baudRateComboBox->currentText() == tr("4800"))
        {
            m_serialPort->setBaudRate(BAUD4800);
        }
        else if(ui->baudRateComboBox->currentText() == tr("9600"))
        {
            m_serialPort->setBaudRate(BAUD9600);
        }
        else if(ui->baudRateComboBox->currentText() == tr("14400"))
        {
            m_serialPort->setBaudRate(BAUD14400);
        }
        else if(ui->baudRateComboBox->currentText() == tr("19200"))
        {
            m_serialPort->setBaudRate(BAUD19200);
        }
        else if(ui->baudRateComboBox->currentText() == tr("38400"))
        {
            m_serialPort->setBaudRate(BAUD38400);
        }
        else if(ui->baudRateComboBox->currentText() == tr("56000"))
        {
            m_serialPort->setBaudRate(BAUD56000);
        }
        else if(ui->baudRateComboBox->currentText() == tr("57600"))
        {
            m_serialPort->setBaudRate(BAUD57600);
        }
        else if(ui->baudRateComboBox->currentText() == tr("115200"))
        {
            m_serialPort->setBaudRate(BAUD115200);
        }
        else if(ui->baudRateComboBox->currentText() == tr("128000"))
        {
            m_serialPort->setBaudRate(BAUD128000);
        }
        else if(ui->baudRateComboBox->currentText() == tr("256000"))
        {
            m_serialPort->setBaudRate(BAUD256000);
        }

        //设置数据位
        if(ui->dataBitsComboBox->currentText() == QString("8"))
        {
            m_serialPort->setDataBits(DATA_8);
        }
        else if(ui->dataBitsComboBox->currentText() == QString("7"))
        {
            m_serialPort->setDataBits(DATA_7);
        }
        else if(ui->dataBitsComboBox->currentText() == QString("6"))
        {
            m_serialPort->setDataBits(DATA_6);
        }

        //设置奇偶校验
        if(ui->parityComboBox->currentText() == tr("无校验"))
        {
            m_serialPort->setParity(PAR_NONE);
        }
        else if(ui->parityComboBox->currentText() == tr("奇校验"))
        {
            m_serialPort->setParity(PAR_ODD);
        }
        else if(ui->parityComboBox->currentText() == tr("偶校验"))
        {
            m_serialPort->setParity(PAR_EVEN);
        }

        //设置停止位
        if(ui->stopBitsComboBox->currentText()==tr("1"))
        {
            m_serialPort->setStopBits(STOP_1);
        }
        else if(ui->stopBitsComboBox->currentText()==tr("1.5"))
        {
            m_serialPort->setStopBits(STOP_1_5);
        }
        else if(ui->stopBitsComboBox->currentText()==tr("2"))
        {
            m_serialPort->setStopBits(STOP_2);
        }

        m_isOpen = true;
        ui->openPort_PushButton->setText(tr("关闭串口"));
        ui->portState_label->setText("<html><head/><body><p><img src=\":/pics/dot_green_24px.png\"/></p></body></html>");
        m_timer->start();   //打开定时器

    }
}

void ASerialPort::slt_timeOut()
{
    if (m_isOpen)
    {
        if(m_serialPort == NULL)
        {
            //TODO
            return;
        }

        if (m_serialPort->bytesAvailable() > 0)
        {
            QByteArray ba = m_serialPort->readAll();

            if (ba.size() > 0)
            {
                //用于托盘闪烁
                m_flickerTimer->start();
            }

            QString lastStr = ui->textBrowser->toPlainText();
            QString data = formatBytes2Visible(QString(ba),lastStr); //转换成可见字符

            if (m_isDisplay && !data.isEmpty())
            {
                ui->textBrowser->append(data);
            }

            m_mutexFileLock.lock();
            QFile rawFile(g_sRawDataDir + "//" + QDate::currentDate().toString("yyyyMMdd").append(".txt"));
            rawFile.open(QFile::WriteOnly | QFile::Append);
            rawFile.write(ba);
            rawFile.write("\r\n");
            rawFile.close();
            m_mutexFileLock.unlock();

        }
    }

}

void ASerialPort::slt_flickerTimeout()
{
    m_flickerCount++;
    emit sig_displayTrayIcon(!m_flickerFlag);
    m_flickerFlag = !m_flickerFlag;
    if (m_flickerCount == 10)
    {
        m_flickerTimer->stop();
        m_flickerCount = 0;
    }
}

void ASerialPort::slt_statTestTimeout()
{
    if (m_serialPort != NULL)
    {
        if (m_isOpen)
        {
            emit sig_curStatus(tr("串口状态：已打开"), "://pics/computers_256px.png");
        }
        else
        {
            emit sig_curStatus(tr("串口状态：已关闭"), "://pics/network_offline_256px.png");
        }
    }
}

void ASerialPort::on_clearBufPushButton_clicked()
{
    ui->textBrowser->clear();
}

void ASerialPort::on_displayPushButton_clicked()
{
    if (m_isDisplay)
    {
        m_isDisplay = false;
        ui->displayPushButton->setText("继续显示");
    }
    else
    {
        m_isDisplay = true;
        ui->displayPushButton->setText("停止显示");
    }
}

void ASerialPort::on_textBrowser_selectionChanged()
{

}
