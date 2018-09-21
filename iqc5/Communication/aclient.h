#ifndef ACLIENT_H
#define ACLIENT_H

#include <QTcpSocket>
#include <QTimer>
#include <QMutex>

class AClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit AClient(QObject *parent = 0);

    void setTimer(const int value);

    void init_Client(const int timerInterval);

signals:
    void sig_newData(const QString &text);

    void sig_currentStatus(const QString &msg, const QString &status);

    void sig_displayTrayIcon(bool flag);

public slots:

    void slt_on_timeout();

    void slt_on_reconnectTimer_timeout();

    void slt_flickerTimerout();

    void slt_connected();

    void slt_disconnected();




private:
    QTimer *m_timer;            //接收数据定时器
    QTimer *m_reconnectTimer;   //连接状态判断计时器
    QMutex m_mutexFileLock;
    QTimer *m_flickerTimer; //托盘闪烁计时器
    bool m_flickerFlag;
    int m_flickerCount;

};

#endif // ACLIENT_H
