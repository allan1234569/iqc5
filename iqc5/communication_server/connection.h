#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QList>
#include <QMutex>

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection();
    ~Connection();

public:
    void InitializeConnection(QTcpSocket* socket, int id);
    void DeleteConnection();

public:
    int m_nSocketID;//-1 indicate the socket is invalid; else is the global id of the connection
    int m_nMsgReceived;
    int m_nMsgSent;
    QTcpSocket* m_pTcpSocket;
};

#endif // CONNECTION_H
