#include "serversocket.h"
#include "clientsocket.h"
#include <QDebug>

int serverSocket::client_count = 0;

serverSocket::serverSocket(QObject *parent) :
    QTcpServer(parent)
{
}

void serverSocket::incomingConnection(int socketId)
{
    ClientSocket *socket = new ClientSocket(this);
    if( !socket->setSocketDescriptor(socketId) )
    {
//        emit error(socket->error());
        return;
    }
    qDebug() << socket->peerName();
    qDebug() << socket->peerAddress().toIPv4Address();
    qDebug() << socket->peerPort();
}


