#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QList>
#include <QTimer>
#include <QMutex>

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection();
    ~Connection();

public:
    bool InitializeConnection(QTcpSocket* socket, int id);
    void DeleteConnection();

    void startStatusTest();

    void stopStatusTest();

public:
    int m_nSocketID;//-1 indicate the socket is invalid; else is the global id of the connection
    int m_nMsgReceived;
    QTcpSocket *m_pTcpSocket;
    QTcpSocket *m_pServerSocket;    //转发的Socket,连接到另一个Server上

signals:
    void sig_interceptedMessage(const QByteArray &message);

    void sig_connectStatus(const QString &status);

protected slots:
    void slt_transmitToSocket();    //向仪器转发Host发送过来的数据

    void slt_transmitToServer();    //向Host转发仪器发送过来的数据

    void slt_timeout();

private:
    QTimer *m_reConnectTimer;

    QTcpSocket *m_pTempSocket;
    int m_nTempId;

};

#endif // CONNECTION_H
