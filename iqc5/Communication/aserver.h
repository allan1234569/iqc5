#ifndef ASERVER_H
#define ASERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include <QTimer>
#include "connection.h"

class AServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit AServer(QObject *parent = 0);

    void setTimer(const int value);

signals:

    void sig_newData(const QString &text);

    void sig_currentStatus(const QString &msg, const QString &status);

    void sig_displayTrayIcon(bool flag);

public slots:

    /**
     * @brief slt_onNewConnection
     */
    void slt_onNewConnection();

    void slt_on_disconnect();

    void slt_on_timeout();

    void slt_connectStatus(const QString &status);

    void slt_on_statusTimer_timeout();

    void slt_flickerTimeout();

    /**
     * @brief slt_hasInterceptedMessage 截取到数据时使用的槽
     * @param message   截取到的信息
     */
    void slt_hasInterceptedMessage(const QByteArray &message);

private:
    Connection *m_pConnection;          //一条连接
    QMutex  m_mutexConnection;          //连接锁
    QMutex  m_mutexFileLock;            //文件锁
    int     m_nSurveillanceID;          //当前连接的客户端分配的ID值
    int     m_nSurveillanceConnected;   //当前客户端连接数

    QTimer  *m_timer;                   //读缓存计时器
    QTimer  *m_statusTimer;             //当前状态检测计时器
    QTimer  *m_flickerTimer;            //托盘闪烁计时器
    bool    m_flickerFlag;              //闪烁标识，true和false时用来标识显示不同的图标
    int     m_flickerCount;             //闪烁统计，到某一个值时清零

    QByteArray m_buffer;

};

#endif // ASERVER_H
