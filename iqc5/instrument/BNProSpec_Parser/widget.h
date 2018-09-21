#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QFileSystemWatcher>
#include <QSqlDatabase>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QDir>
#include <QSettings>
#include <QTimer>
#include <QHostAddress>

//#include "../../iqc5/Model/TestType.h"
//#include "../../iqc5/Model/Project.h"
//#include "../../iqc5/Model/Result.h"
#include "../../iqc5/Model/Device.h"

#include "myProject.h"
#include "clientsocket.h"

#include "setupdialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void initSystemTray();
    void createAction();
    void setTrayIcon();
    void translateActions();
    ~Widget();
private:
    void GetConfigInfo();

private:
    Ui::Widget *ui;
//    QFileSystemWatcher *watcher;
    SetupDialog *dialog;

    ClientSocket *client;
    bool m_bConnected;

    QByteArray rawdata;
    QMenu *menu;
    QSystemTrayIcon *trayIcon;
    QAction *action_setup;
    QAction *action_quit;
    QDir dir;
    Device device;
    QHostAddress hostAddress;
    quint16 hostPort;
    QTimer *timer;
    int timerInterval;  //毫秒

    //解析相关定义
    QVector<MyProject*> ProjectVec;

    void parser(const QString &content);
    QStringList	split(const QString &desStr, const QRegularExpression & re, QString::SplitBehavior behavior = QString::KeepEmptyParts) const;
    QByteArray convertToJson();
    bool SendMessage(QByteArray message);

protected:
    void closeEvent(QCloseEvent *event);

protected slots:
    void GetData();
    void OnConnected();
    void OnDisconnected();


};

#endif // WIDGET_H
