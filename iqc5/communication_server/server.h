#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QMutex>
#include <QSqlDatabase>

#include <QMap>
#include "../iqc5/Model/Result.h"
#include "../iqc5/Model/Project.h"
#include "../iqc5/Model/ProjectDetail.h"
#include "../iqc5/Model/TestType.h"

#include "connection.h"
#include "configureform.h"
#include "menu.h"
//#include "clientsocket.h"
//#include "serversocket.h"

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

    void createAction();
    void setTrayIcon();
    void translateActions();
    void initSystemTray();
    void readSetting();
protected:
    void closeEvent(QCloseEvent *event);



public:
    bool InitializeServers();
    void ShowStatusMessage(const QString str);
    void getFromJsonData(const QByteArray& jsonData);
    void CommitToDatabase();
public slots:
    void OnNewConnection();
    void OnReadyRead();
    void OnDisconnected();

private:
    //托盘相关
    Menu    *menu;
    QAction*            action_status;
    QAction*            action_restart;
//    QAction*            action_setup;
    QAction*            action_quit;
    QSystemTrayIcon*    trayIcon;

    //TCP相关
    QTcpServer  *m_pTcpServer;
    Connection  *m_pConnection;
    QMutex  m_mutexConnection;
    int m_nSurveillanceID;
    int m_nSurveillanceConnected;
    QString logDir;
    qint32  port;
    int m_nClientCount;

    //SQL关
    QSqlDatabase db;
    QByteArray receivedData;
    QVector<TestType*> TestTypeVec;
    QVector<Project*> ProjectVec;
    QVector<Result*> ResultVec;
    QMap<QString, Device*> DeviceMap;

signals:

public slots:
    void showConfigureForm();
};

#endif // SERVER_H
