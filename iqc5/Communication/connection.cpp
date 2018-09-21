#include "connection.h"
#include "res.h"

Connection::Connection()
{
    m_nSocketID = -1;
    m_pTempSocket = NULL;
    m_nTempId = -1;

    m_pTcpSocket = NULL;
    m_pServerSocket = NULL;
}

Connection::~Connection()
{
    if (m_pTcpSocket != NULL)
    {
        delete m_pTcpSocket;
    }

    if (m_pServerSocket != NULL)
    {
        delete m_pServerSocket;
    }
}

bool Connection::InitializeConnection(QTcpSocket *socket, int id)
{
    m_pTcpSocket = socket;
    m_pTcpSocket->setParent(this);
    m_nMsgReceived = 0;
    m_nSocketID = id;

    m_pServerSocket = new QTcpSocket(this);
    m_pServerSocket->connectToHost(QHostAddress(g_sRemoteIp),g_iRemotePort);

    connect(m_pTcpSocket,SIGNAL(readyRead()),
            this,SLOT(slt_transmitToServer()));     //转发到Lis
    connect(m_pServerSocket,SIGNAL(readyRead()),
            this,SLOT(slt_transmitToSocket()));     //转发到仪器v

    m_reConnectTimer = new QTimer(this);
    connect(m_reConnectTimer,SIGNAL(timeout()),
            this,SLOT(slt_timeout()));
    m_reConnectTimer->setInterval(2000);
    m_reConnectTimer->start();
}

void Connection::DeleteConnection()
{
    qDebug() << __FUNCTION__ << __LINE__;
    m_nSocketID = -1;
    m_pTcpSocket->disconnect();
//    	delete m_pTcpSocket; 若delete会报错
    m_pTcpSocket = NULL;

    m_pServerSocket->disconnect();
    delete m_pServerSocket;
    m_pServerSocket = NULL;

    delete m_reConnectTimer;
    m_reConnectTimer = NULL;
}

void Connection::startStatusTest()
{
    m_reConnectTimer->start();
}

void Connection::stopStatusTest()
{
    m_reConnectTimer->stop();
}

void Connection::slt_transmitToSocket()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket->bytesAvailable() > 0)
    {
        QByteArray ba = socket->readAll();

        switch (m_pTcpSocket->state()) {
        case QTcpSocket::UnconnectedState:  //未连接
            f_log("通信程序与仪器通信断开，转发失败%d");
            break;
        case QTcpSocket::ConnectingState:   //正在连接
            f_log("通信程序正在与仪器建立通信，转发失败");
            break;
        case QTcpSocket::ConnectedState:    //已连接

            m_pTcpSocket->write(ba);    //转发到仪器
            emit sig_interceptedMessage(ba);

            break;
        default:
            break;
        }

    }
}

void Connection::slt_transmitToServer()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket->bytesAvailable() > 0)
    {
        QByteArray ba = socket->readAll();
        switch (m_pServerSocket->state()) {
        case QTcpSocket::UnconnectedState:  //未连接
            f_log("通信程序与Lis服务端通信已断开， 转发失败");
            break;
        case QTcpSocket::ConnectingState:   //正在连接
            f_log("通信程序正在与Lis服务端建立通信，转发失败");
            break;
        case QTcpSocket::ConnectedState:    //已连接

            m_pServerSocket->write(ba); //转发到Lis
            emit sig_interceptedMessage(ba);

            break;
        default:
            break;
        }

    }
}

void Connection::slt_timeout()
{
    switch (m_pServerSocket->state()) {
    case QTcpSocket::UnconnectedState:  //未连接
        m_pServerSocket->connectToHost(QHostAddress(g_sRemoteIp),g_iRemotePort);
        emit sig_connectStatus(tr("未连接"));
        break;
    case QTcpSocket::ConnectingState:   //正在连接
        emit sig_connectStatus(tr("正在连接"));
        break;
    case QTcpSocket::ConnectedState:    //已连接
        emit sig_connectStatus(tr("已连接"));
        break;
    default:
        break;
    }
}
