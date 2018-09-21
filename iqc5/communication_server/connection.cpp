#include "connection.h"


Connection::Connection()
{
    m_nSocketID = -1;
}

Connection::~Connection()
{
    if (m_pTcpSocket!=NULL)
    {
        delete m_pTcpSocket;
    }
}

void Connection::InitializeConnection(QTcpSocket *socket, int id)
{
    m_pTcpSocket = socket;
    m_pTcpSocket->setParent(this);
    m_nMsgReceived = 0;
    m_nMsgSent = 0;
    m_nSocketID = id;
}

void Connection::DeleteConnection()
{
    m_nSocketID = -1;
    m_pTcpSocket->disconnect();
//    	delete m_pTcpSocket; 若delete会报错
    m_pTcpSocket = NULL;
}
