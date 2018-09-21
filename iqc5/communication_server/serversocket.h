#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QTcpServer>
#include <QStringList>
#include <QMap>

typedef QMap<QString, int> mMap;

typedef struct ClientInfo{
    QString Ip;
    QString HostName;
}ClientInfo;

class serverSocket : public QTcpServer
{
    Q_OBJECT
public:
    explicit serverSocket(QObject *parent = 0);
    static int client_count;//客户端数
signals:

public slots:

private:
    void incomingConnection(int socketId);
};

#endif // SERVERSOCKET_H
