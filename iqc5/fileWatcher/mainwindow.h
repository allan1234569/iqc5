#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include "clientsocket.h"
#include <QFileSystemWatcher>
#include <QStringList>
#include <QTimer>

class Mainwindow : public QWidget
{
    Q_OBJECT
public:
    explicit Mainwindow(QWidget *parent = 0);
//    bool initClient();
    void initDirectoryAndFiles();
    void initSystemTray();
    void createAction();
    void setTrayIcon();
    void translateActions();    
    void readCongigure();
    QStringList analyzingDirectory();

signals:

public slots:
    void restartCliet();
    void showConfigureForm();
    void directorHasChanged(const QString &path);
    void fileHasChanged(const QString &path);
    void sendResult(const QString &path);
    void changeIco();
    void connectedToHost();
    void disconnectFromServer();

protected:
    void closeEvent(QCloseEvent* event);

private:
    QSystemTrayIcon *trayIcon;
    QMenu *menu;
    QAction *action_connect_status;
    QAction *action_setup;
    QAction *action_restart;
    QAction *action_quit;

    ClientSocket *client;
    QString logDir;
    QString ipAdress;
    qint32  port;


    QFileSystemWatcher *watcher;
    QFileSystemWatcher *resultWatcher;

    QStringList lastFiles;

    QTimer *timer;

};

#endif // MAINWINDOW_H
