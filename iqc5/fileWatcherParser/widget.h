#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QStringList>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QHostAddress>

#include "clientsocket.h"
#include "setupdialog.h"

#define RAWDATAPATH "./rawdata"
#define CHANGEFILEPATH "./changedFiles.txt"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void initSystemTrayIcon();
    void createAction();
    void setTrayIcon();
    void translateActions();

    void GetConfigInfo();

    void initDirectoryAndFiles();

public slots:
    void getChangedFiles();

private:
    QTimer *timer;
    int timerInterval;
    QHostAddress hostAddress;
    short hostPort;

    QFile file;
    QStringList fileList;
    QString rawDataDirPath;

    QSystemTrayIcon *trayIcon;
    QMenu *menu;

    QAction *start_action;
    QAction *exit_action;
    QAction *setup_action;

    SetupDialog *dialog;
};

#endif // WIDGET_H
