#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QtNetwork/QTcpSocket>
#include <QSettings>

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = 0);

    bool tryConnect();
signals:

public slots:

private:
    QSettings *m_pRegServer;    //服务器注册表配置对象

};

#endif // CLIENTSOCKET_H
