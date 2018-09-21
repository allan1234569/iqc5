#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include "aserialport.h"
#include "anetworker.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init();        //窗口初始化

    void creatTrayIcon();

    void showTryaIcon();

    void restartApplication();

signals:

protected slots:

    void slt_show();

    void slt_displayTrayIcon(bool flag);

    void slt_showCurrentStatus(const QString &msg, const QString source);

    void slt_showTrayIcon(QSystemTrayIcon::ActivationReason reason);

    void on_action_Exit_triggered();

    void on_action_Setup_triggered();

    void on_action_ResultPath_triggered();

    void on_action_Data_triggered();

    void on_action_ComLog_triggered();

    void on_action_Clear_triggered();

    void on_action_About_triggered();

    // QWidget interface
protected:

    void closeEvent(QCloseEvent *event);

private:

private:
    Ui::MainWindow *ui;
    ASerialPort *m_spWidget;
    ANetWorker  *m_nwWidget;

    QSystemTrayIcon *m_systemTranIcon;
    QMenu   *m_tray_Menu;
    QAction *m_action_Show;
    QAction *m_action_Setup;
    QAction *m_action_Data;
    QAction *m_action_ComLog;
    QAction *m_action_Exit;

    QString m_Mode;

    bool f_exit;    //用来判断是否确认要退出的状，f_exit为ture退出，f_exit为false时隐藏显示



    // QWidget interface
protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
};

#endif // MAINWINDOW_H

