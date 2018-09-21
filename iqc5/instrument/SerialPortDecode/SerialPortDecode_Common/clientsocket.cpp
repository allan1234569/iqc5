#include "clientsocket.h"
#include <QtNetwork/QHostAddress>

#include <QDebug>

ClientSocket::ClientSocket(QObject *parent) :
    QTcpSocket(parent)
{
    m_pRegServer = new QSettings("HKEY_CURRENT_USER\\Software\\iqc",QSettings::NativeFormat);
}

bool ClientSocket::tryConnect()
{
    if (this->state() == QTcpSocket::ConnectedState)
    {
        return true;
    }
    QString host = m_pRegServer->value("ServerHost","").toString();
    qint32 port = m_pRegServer->value("ServerPort",-1).toInt();

    if (host.isEmpty() || port == -1)
    {
        return false;
    }
    this->connectToHost(QHostAddress(host),port);

    return this->waitForConnected();
}
