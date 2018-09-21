#include "aserver.h"
#include <QDebug>
#include <QFile>
#include <QDate>
#include <res.h>

AServer::AServer(QObject *parent) :
    QTcpServer(parent)
{
    m_nSurveillanceID = 1;
    m_nSurveillanceConnected = 0;
    m_pConnection = new Connection;

    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slt_on_timeout()));

    m_statusTimer = new QTimer(this);
    m_statusTimer->setInterval(200);
    connect(m_statusTimer,SIGNAL(timeout()),this,SLOT(slt_on_statusTimer_timeout()));
    m_statusTimer->start();

    m_flickerTimer = new QTimer(this);
    m_flickerTimer->setInterval(300);
    connect(m_flickerTimer,SIGNAL(timeout()),this,SLOT(slt_flickerTimeout()));
    m_flickerFlag = true;

    m_flickerCount = 0;

}

void AServer::setTimer(const int value)
{
    m_timer->setInterval(value);
    m_timer->start();
}

void AServer::slt_onNewConnection()
{

    if (m_nSurveillanceConnected == 1)
    {
        return;
    }

    if (m_pConnection->m_nSocketID == -1)
    {
        m_mutexConnection.lock();

        m_pConnection->InitializeConnection(this->nextPendingConnection(),m_nSurveillanceID);

        connect(m_pConnection->m_pTcpSocket,SIGNAL(disconnected()),
                this,SLOT(slt_on_disconnect()));

        connect(m_pConnection,SIGNAL(sig_interceptedMessage(QByteArray)),
                this,SLOT(slt_hasInterceptedMessage(QByteArray)));

        connect(m_pConnection,SIGNAL(sig_connectStatus(QString)),this,SLOT(slt_connectStatus(QString)));

        m_mutexConnection.unlock();

        m_nSurveillanceID++;
        m_nSurveillanceConnected++;

        if (m_nSurveillanceConnected == 1)
        {
            this->close();
        }

        m_timer->start();
        f_log("一台设备上线");
    }
}

void AServer::slt_on_disconnect()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    Connection* connection = qobject_cast<Connection*>(socket->parent());

    //delete the connection
    m_mutexConnection.lock();
    connection->DeleteConnection();
    m_pConnection = new Connection;
    m_mutexConnection.unlock();
    m_nSurveillanceConnected--;

    if (m_nSurveillanceConnected == 0)
    {
        this->listen(QHostAddress::Any,g_iLocalPort);
    }

    f_log("一台设备离线");
}

void AServer::slt_on_timeout()
{
    if (m_buffer.size() > 0)
    {
        qDebug() << __FILE__ << __LINE__;
        //用于托盘闪烁
        m_flickerTimer->start();
        m_statusTimer->stop();
        if (m_pConnection != NULL)
        {
            m_pConnection->stopStatusTest();
        }

        QString data = QString(m_buffer);
        emit sig_newData(data);

        m_mutexFileLock.lock();
        QFile rawFile(g_sRawDataDir + "//" + QDate::currentDate().toString("yyyyMMdd").append(".txt"));
        rawFile.open(QFile::WriteOnly | QFile::Append);
        rawFile.write(m_buffer);
        rawFile.write("\r\n");
        rawFile.close();
        m_mutexFileLock.unlock();

        m_buffer.clear();
    }
}

void AServer::slt_connectStatus(const QString &status)
{
    if (status.compare("未连接") == 0)
    {
        emit sig_currentStatus(tr("网络状态：未连接"), QString("未连接"));
    }
    else if (status.compare("已连接") == 0)
    {
        emit sig_currentStatus(tr("网络状态：已连接"), QString("已连接"));
    }
}

void AServer::slt_on_statusTimer_timeout()
{
    if (m_pConnection == NULL || m_pConnection->m_pTcpSocket == NULL)
    {
        emit sig_currentStatus(tr("网络状态：未连接"), QString("未连接"));
    }

    if (m_pConnection != NULL && m_pConnection->m_pTcpSocket != NULL)
    {
        switch (m_pConnection->m_pTcpSocket->state()) {
        case QTcpSocket::UnconnectedState:  //未连接
            emit sig_currentStatus(tr("网络状态：未连接"), QString("未连接"));
            break;
        case QTcpSocket::ConnectedState:    //已连接
            if (m_pConnection->m_pServerSocket != NULL)
            {
                switch (m_pConnection->m_pServerSocket->state()) {
                case QTcpSocket::UnconnectedState:  //未连接
                    m_pConnection->m_pServerSocket->connectToHost(QHostAddress(g_sRemoteIp),g_iRemotePort);
                    emit sig_currentStatus(tr("网络状态：未连接"), QString("未连接"));
                    break;
                case QTcpSocket::ConnectingState:

                    break;
                case QTcpSocket::ConnectedState:
                    emit sig_currentStatus(tr("网络状态：已连接"), QString("已连接"));
                    break;
                default:
                    break;
                    }
            }

            break;
        default:
            break;
            }
    }
}

void AServer::slt_flickerTimeout()
{
    qDebug() << __FILE__ << __LINE__;
    m_flickerCount++;
    emit sig_displayTrayIcon(!m_flickerFlag);
    m_flickerFlag = !m_flickerFlag;

    if (m_flickerCount == 10)
    {
        m_flickerTimer->stop();
        m_statusTimer->start();
        if (m_pConnection != NULL)
        {
            m_pConnection->startStatusTest();

        }
        m_flickerCount = 0;
    }
}

void AServer::slt_hasInterceptedMessage(const QByteArray &message)
{
    m_buffer.append(message);
}
