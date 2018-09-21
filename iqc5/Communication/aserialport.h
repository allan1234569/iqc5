#ifndef ASERIALPORT_H
#define ASERIALPORT_H

#include <QWidget>
#include <QTimer>
#include "win_qextserialport.h"
#include <QMutex>

namespace Ui {
class ASerialPort;
}

class ASerialPort : public QWidget
{
    Q_OBJECT

public:
    explicit ASerialPort(QWidget *parent = 0);
    ~ASerialPort();

    void init();

    void clear_display();

    void reStart();

signals:
    void sig_displayTrayIcon(bool flag);    //托盘是否闪烁

    /**
     * @brief sig_curStatus
     * @param source        要显示的图标路径
     */
    void sig_curStatus(const QString &msg, const QString &source);

private slots:
    /**
     * @brief slt_timerOut  定时读取缓冲区数数
     */
    void slt_timeOut();

    void slt_flickerTimeout();

    void slt_statTestTimeout();

    void on_openPort_PushButton_clicked();

    void on_clearBufPushButton_clicked();

    void on_displayPushButton_clicked();

    void on_textBrowser_selectionChanged();

private:
    Ui::ASerialPort *ui;

    QTimer  *m_flickerTimer;            //托盘闪烁计时器
    bool    m_flickerFlag;              //托盘闪烁的标志
    int     m_flickerCount;             //闪烁统计，到某一个值时清零

    Win_QextSerialPort *m_serialPort;   //串口对象
    QTimer *m_timer;                    //缓冲区读取计时器
    int     m_timerInterval;            //缓冲区读取计时
    long    m_bufferSize;               //缓冲区大小
    bool    m_isOpen;                   //串口是否打开

    bool    m_isDisplay;                //是否显示接收的数据

    QMutex  m_mutexFileLock;            // 文件锁

    QTimer *m_statTestTimer;            //状态检查计时器


};

#endif // ASERIALPORT_H
