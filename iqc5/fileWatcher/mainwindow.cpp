#include "mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>
#include "configureform.h"
#include "global.h"
#include <QDir>
#include <QDateTime>
#include <QMutex>
#include <QGuiApplication>
#include <QFileDialog>
#include <QHostInfo>
#include <QStatusBar>

extern QSettings *setting;

Mainwindow::Mainwindow(QWidget *parent) :
    QWidget(parent)
{
    initDirectoryAndFiles();
    initSystemTray();
    readCongigure();

    lastFiles = analyzingDirectory();

    watcher = new QFileSystemWatcher(this);
    watcher->addPath(logDir);
    watcher->addPaths(lastFiles);

//    resultWatcher = new QFileSystemWatcher(this);
    QDir dir;

//    resultWatcher->addPath(dir.currentPath() + "/parserResult.json");

//    initClient();

    connect(watcher,SIGNAL(directoryChanged(QString)),
            this,SLOT(directorHasChanged(QString)));

    connect(watcher,SIGNAL(fileChanged(QString)),
            this,SLOT(fileHasChanged(QString)));

//    connect(resultWatcher,SIGNAL(fileChanged(QString)),this,SLOT(sendResult(QString)));
}

//bool Mainwindow::initClient()
//{
//    client = new ClientSocket(this);
//    connect(client,SIGNAL(connected()),this,SLOT(connectedToHost()));
//    connect(client,SIGNAL(disconnected()),this,SLOT(disconnectFromServer()));

//    client->connectToHost(ipAdress,port);

//    switch ( client->state() ) {
//    case QAbstractSocket::UnconnectedState :
//        trayIcon->showMessage(tr("连接提示"),tr("未连接"),QSystemTrayIcon::Information,5000);
//        break;
//    case QAbstractSocket::ConnectingState :
//        trayIcon->showMessage(tr("连接提示"),tr("正在连接"),QSystemTrayIcon::Information,5000);
//        break;
//    case QAbstractSocket::ConnectedState :
//        trayIcon->showMessage(tr("连接提示"),tr("已连接"),QSystemTrayIcon::Information,5000);
//        break;
//    case QAbstractSocket::ClosingState :
//        trayIcon->showMessage(tr("连接提示"),tr("断开连接"),QSystemTrayIcon::Information,5000);
//        break;
//    default:
//        break;
//    }
//}

void Mainwindow::initDirectoryAndFiles()
{
    QDir dir(QDir::currentPath());
    if(!dir.exists("./rawdata/"))
    {
        dir.mkdir("./rawdata/");
    }
    if(!dir.exists("./result/"))
    {
        dir.mkdir("./result/");
    }
    if(!dir.exists("./received/"))
    {
        dir.mkdir("./received/");
    }
    QFile file("./share.txt");
    if(!file.exists())
    {
        qDebug() << "not exists";
        file.open(QIODevice::WriteOnly);
        file.close();
    }
}

void Mainwindow::createAction()
{
    menu = new QMenu(this);

    action_connect_status = new QAction(this);
    action_restart = new QAction(this);
    action_setup = new QAction(this);
    action_quit = new QAction(this);

    menu->addAction(action_connect_status);
    menu->addAction(action_restart);
    menu->addAction(action_setup);
    menu->addAction(action_quit);

    connect(action_quit,SIGNAL(triggered()),this,SLOT(close()));
    connect(action_setup,SIGNAL(triggered()),this,SLOT(showConfigureForm()));
    connect(action_restart,SIGNAL(triggered()),this,SLOT(restartCliet()));
}

void Mainwindow::setTrayIcon()
{
    action_restart->setIcon(QIcon("://Koala.jpg"));
    action_setup->setIcon(QIcon("://Koala.jpg"));
    action_quit->setIcon(QIcon("://Koala.jpg"));
}

void Mainwindow::translateActions()
{
    action_restart->setText(tr("重启"));
    action_setup->setText(tr("设置"));
    action_quit->setText(tr("退出"));
}

void Mainwindow::initSystemTray()
{
    createAction();
    setTrayIcon();
    translateActions();

    QIcon icon = QIcon("://client.png");
    setWindowIcon(icon);
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("文件监控程序");
    trayIcon->setContextMenu(menu);
    QString titlec=tr("Hello");
    QString textc=QString("文件监控程序已启动!");
    trayIcon->show();
    trayIcon->showMessage(titlec,textc,QSystemTrayIcon::Information,5000);
}

void Mainwindow::readCongigure()
{
    ipAdress = setting->value("SETTINGS/ip").toString();
    port = setting->value("SETTINGS/port").toInt();
    logDir = setting->value("SETTINGS/logDir").toString();
}

QStringList Mainwindow::analyzingDirectory()
{
    QDir dir;
    dir.cd(logDir);
    QStringList files = dir.entryList();
    QStringList list;
    foreach (QString file,files) {
        list << logDir+"/"+file;
    }

    return list;
}

void Mainwindow::restartCliet()
{
//    client->close();
//    delete client;
//    client = NULL;

//    readCongigure();

//    if( initClient() )
//    {
//        trayIcon->showMessage(tr("提示"),tr("客户端已重启"),QSystemTrayIcon::Information,5000);
//    }

}

void Mainwindow::showConfigureForm()
{
    configureForm *window = new configureForm;
    window->show();
}

void Mainwindow::directorHasChanged(const QString &path)
{
    qDebug() << __FUNCTION__ << __LINE__ << path;
    QDir dir(path);
    QFileInfoList fileInfoList = dir.entryInfoList();

    QString changedFile;
    bool canFind = false;
    if(fileInfoList.size() > lastFiles.size())  //新增了文件
    {
        foreach (QFileInfo fileInfo, fileInfoList) {
            canFind = false;
            foreach (QString file, lastFiles) {
                if( fileInfo.fileName() == file )
                {
                    canFind = true;
                    continue;
                }
            }
            if( !canFind )
            {
                changedFile = fileInfo.fileName();
            }
        }
        watcher->addPath(logDir+"/"+changedFile);
    }
    else if( fileInfoList.size() < lastFiles.size() )   //删除了文件
    {
        foreach (QString file, lastFiles) {
            canFind = false;
            foreach (QFileInfo fileInfo, fileInfoList) {
                if(file != fileInfo.fileName() )
                {
                    canFind = true;
                    continue;
                }
            }
            if( !canFind )
            {
                changedFile = file;
            }
        }
        watcher->removePath(logDir+"/"+changedFile);
    }
    else    //文件名被修改
    {
        QString originalFile = "";
        foreach (QString file, lastFiles) { //得到原文件名
            canFind = false;
            foreach (QFileInfo fileInfo, fileInfoList) {
                if(file != fileInfo.fileName() )
                {
                    canFind = true;
                    continue;
                }
            }
            if( !canFind )
            {
                originalFile = file;
            }
        }

        foreach (QFileInfo fileInfo, fileInfoList) {    //得到改变后的文件名
            canFind = true;
            foreach (QString file, lastFiles) {
                if(file != fileInfo.fileName() )
                {
                    canFind = false;
                }
            }
            if( !canFind )
            {
                changedFile = fileInfo.fileName();
            }
        }

        watcher->removePath(logDir+"/"+originalFile);
        watcher->addPath(logDir+"/"+changedFile);
    }

    lastFiles.clear();
    foreach (QFileInfo fileinfo, fileInfoList) {
        lastFiles <<  fileinfo.fileName();
    }

//    QStringList list = watcher->files();
//    qDebug() << "changed file : " << changedFile;
//    qDebug() << "Now those files are being watched:";
//    qDebug() << list.size();
}

void Mainwindow::fileHasChanged(const QString &path)
{
    qDebug() <<__FUNCTION__ << __LINE__;
    QMutex mutex;
    mutex.lock();

    QFile file("./changedFiles.txt");
    if( !file.open(QIODevice::WriteOnly | QFile::Append) )
    {
        return;
    }
    QByteArray content;
    QString changedfile = path.right(path.length() - path.lastIndexOf("/") -1);
    content.append(QDateTime::currentDateTime().toString()).append(":    ").append(changedfile).append("\r\n");
    file.write(content);
    file.close();
    //读源文件内容
    QFile srcfile(path);
    if( !srcfile.open(QIODevice::ReadOnly) )
    {

    }
    QByteArray text = srcfile.readAll();
    srcfile.close();

    //写入新文件
    QString filename = path.right(path.length() - path.lastIndexOf("/") - 1);
    QFile dstfile("./received/"+filename);
    if( !dstfile.open(QIODevice::WriteOnly) )
    {

    }
    dstfile.write(text);
    dstfile.close();

    mutex.unlock();
}

void Mainwindow::sendResult(const QString &path)
{
//    qDebug() << __FUNCTION__ << __LINE__ << path;
//    QFile file(path);
//    file.open(QIODevice::ReadOnly);
//    QByteArray data = file.readAll();
//    file.close();
//    data.prepend("#<DataStart ");
//    data.append(" DataEnd>#");

//    qDebug() << "Client sendResult: " << client->write(data);
}

void Mainwindow::changeIco()
{
    int m = 4;


    if(m == 0)
        return;

    if(m%2 == 0)
    {
        trayIcon->setIcon(QIcon("://Koala.jpg"));
    }
    else
    {
        trayIcon->setIcon(QIcon());
    }

    m--;
}

void Mainwindow::connectedToHost()
{
//    timer->start(1000);
    switch ( client->state() ) {
    case QAbstractSocket::UnconnectedState :
        trayIcon->showMessage(tr("连接提示"),tr("未连接"),QSystemTrayIcon::Information,5000);
        break;
    case QAbstractSocket::ConnectingState :
        trayIcon->showMessage(tr("连接提示"),tr("正在连接"),QSystemTrayIcon::Information,5000);
        break;
    case QAbstractSocket::ConnectedState :
        trayIcon->showMessage(tr("连接提示"),tr("已连接"),QSystemTrayIcon::Information,5000);
        action_connect_status->setText(tr("连接到服务器。。。"));
        break;
    case QAbstractSocket::ClosingState :
        trayIcon->showMessage(tr("连接提示"),tr("断开连接"),QSystemTrayIcon::Information,5000);
        break;
    default:
        break;
    }

}

void Mainwindow::disconnectFromServer()
{
    switch ( client->state() ) {
    case QAbstractSocket::UnconnectedState :
        trayIcon->showMessage(tr("连接提示"),tr("未连接"),QSystemTrayIcon::Information,5000);
        break;
    case QAbstractSocket::ConnectingState :
        trayIcon->showMessage(tr("连接提示"),tr("正在连接"),QSystemTrayIcon::Information,5000);
        break;
    case QAbstractSocket::ConnectedState :
        trayIcon->showMessage(tr("连接提示"),tr("已连接"),QSystemTrayIcon::Information,5000);
        action_connect_status->setText(tr("连接到服务器。。。"));
        break;
    case QAbstractSocket::ClosingState :
        trayIcon->showMessage(tr("连接提示"),tr("断开连接"),QSystemTrayIcon::Information,5000);
        action_connect_status->setText(tr("已经从服务器断开连接！！！"));
        break;
    default:
        break;
    }
}

void Mainwindow::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出程序"),
                                   QString(tr("警告：程序有一个任务正在运行中，是否结束操作退出?")),
                                   QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No) {
        event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes) {
        QGuiApplication::setQuitOnLastWindowClosed(true);
        trayIcon->deleteLater();
        event->accept();  //接受退出信号，程序退出
    }
}
