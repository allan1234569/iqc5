#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include <QSqlDatabase>
#include <QMap>
#include "../iqc5/Model/Result.h"
#include "../iqc5/Model/Project.h"
#include "../iqc5/Model/ProjectDetail.h"
#include "../iqc5/Model/TestType.h"

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = 0);
    void getFromJsonData(const QByteArray& jsonData);
    void CommitToDatabase();

signals:

public slots:
    void readClient();
    void sendMessage(const QByteArray &data);

private:
    QSqlDatabase db;

    QByteArray receivedData;
    QVector<TestType*> TestTypeVec;
    QVector<Project*> ProjectVec;
    QVector<Result*> ResultVec;
    QMap<QString, Device*> DeviceMap;
};

#endif // CLIENTSOCKET_H
