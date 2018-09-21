#include "aclient.h"
#include <QHostAddress>
#include <QDebug>
#include <QFile>
#include <QDate>
#include "res.h"

AClient::AClient(QObject *parent) :
    QTcpSocket(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slt_on_timeout()));

    m_reconnectTimer = new QTimer(this);
    m_reconnectTimer->setInterval(500);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slt_on_reconnectTimer_timeout()));

    m_flickerTimer = new QTimer(this);
    m_flickerTimer->setInterval(300);
    connect(m_flickerTimer,SIGNAL(timeout()),this,SLOT(slt_flickerTimerout()));
    m_flickerFlag = true;
    m_flickerCount = 0;

    connect(this,SIGNAL(connected()),this,SLOT(slt_connected()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slt_disconnected()));
}

void AClient::slt_on_timeout()
{
    if (this->bytesAvailable() > 0)
    {
        QByteArray ba = this->readAll();

        if (ba.size() > 0)
        {
            //用于托盘闪烁
            m_flickerTimer->start();
        }

        QString data = QString(ba);
        emit sig_newData(data);



        m_mutexFileLock.lock();
        QFile rawFile(g_sRawDataDir + "//" + QDate::currentDate().toString("yyyyMMdd").append(".txt"));
        rawFile.open(QFile::WriteOnly | QFile::Append);
        rawFile.write(ba);
        rawFile.write("\r\n");
        rawFile.close();
        m_mutexFileLock.unlock();


    }
}

void AClient::slt_on_reconnectTimer_timeout()
{
    switch (this->state()) {
    case UnconnectedState:  //未连接
        emit sig_currentStatus(tr("网络状态：未连接"), QString("未连接"));

        this->connectToHost(QHostAddress(g_sRemoteIp),g_iRemotePort);
        emit sig_currentStatus(tr("网络状态：正在尝试连接"), QString("正在尝试连接"));

        break;
    case ConnectingState:   //正在连接
        emit sig_currentStatus(tr("网络状态：正在尝试连接"), QString("正在尝试连接"));
        break;
    case ConnectedState:    //已连接
        emit sig_currentStatus(tr("网络状态：已连接"), QString("已连接"));
        break;
    default:
        break;
    }
}

void AClient::slt_flickerTimerout()
{
    m_flickerCount++;
    emit sig_displayTrayIcon(!m_flickerFlag);
    m_flickerFlag = !m_flickerFlag;
    if (m_flickerCount ==  10)
    {
        m_flickerTimer->stop();
        m_flickerCount = 0;
    }
}

void AClient::slt_connected()
{
    f_log("已经建立连接");
}

void AClient::slt_disconnected()
{
    f_log("连接已断开");
}

void AClient::setTimer(const int value)
{
    m_timer->setInterval(value);
    m_timer->start();
}

void AClient::init_Client(const int timerInterval)
{
    this->connectToHost(QHostAddress(g_sRemoteIp),g_iRemotePort);
    emit sig_currentStatus(tr("正在尝试连接"), QString("正在尝试连接"));
    setTimer(timerInterval);
}
