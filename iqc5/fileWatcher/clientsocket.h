#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include <QStringList>

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = 0);

signals:

public slots:
    void readClient();
    void sendMessage(const QByteArray &data);

private:

};

#endif // CLIENTSOCKET_H
