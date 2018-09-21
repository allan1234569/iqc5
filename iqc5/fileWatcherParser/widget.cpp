#include "widget.h"
#include <QDebug>
#include <QMutex>
#include <QDir>
#include <QMessageBox>

#include "parserthred.h"
#include "Device.h"
#include "global.h"

extern QSettings *settings;
extern ClientSocket *client;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    rawDataDirPath = RAWDATAPATH;
    timer = new QTimer(this);
    file.setFileName(CHANGEFILEPATH);

    dialog = new SetupDialog(this);
    connect(dialog,SIGNAL(on_exit()),this,SLOT(close()));

    initSystemTrayIcon();
    GetConfigInfo();

    connect(timer,SIGNAL(timeout()),this,SLOT(getChangedFiles()));

    timer->start(5000);
}

void Widget::initDirectoryAndFiles()
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
    QFile file(CHANGEFILEPATH);
    if(!file.exists())
    {
        qDebug() << "not exists";
        file.open(QIODevice::WriteOnly);
        file.close();
    }
}

Widget::~Widget()
{

}

void Widget::initSystemTrayIcon()
{
    createAction();
    setTrayIcon();
    translateActions();

    QIcon icon = QIcon("://setup.png");
    setWindowIcon(icon);
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("BNP解析程序");
    trayIcon->setContextMenu(menu);
    QString titlec=tr("Hello");
    QString textc=QString("BNP解析程序已启动!");
    trayIcon->show();
    trayIcon->showMessage(titlec,textc,QSystemTrayIcon::Information,5000);
}

void Widget::createAction()
{
//    setup_action = new QAction(this);
    exit_action = new QAction(this);

    menu = new QMenu(this);
//    menu->addAction(setup_action);
    menu->addAction(exit_action);

    connect(exit_action,SIGNAL(triggered()),this,SLOT(close()));
}

void Widget::setTrayIcon()
{
//    setup_action->setIcon(QIcon("://setup_1.png"));
    exit_action->setIcon(QIcon());
}

void Widget::translateActions()
{
//    setup_action->setText(tr("设置"));
    exit_action->setText(tr("退出"));
}

void Widget::GetConfigInfo()
{
    Device device;

    QString ipAdress = settings->value(QString("SERVER/ip")).toString();
    QString portNo = settings->value(QString("SERVER/port")).toString();
    device.DeviceName = settings->value(QString("DEVICE/DeviceName")).toString();
    device.ModelName = settings->value(QString("DEVICE/ModelName")).toString();
    device.BrandName = settings->value(QString("DEVICE/BrandName")).toString();

    device.DeviceId = settings->value(QString("DEVICE/DeviceId")).toString();
    device.ModelId = settings->value(QString("DEVICE/ModelId")).toString();
    device.BrandId = settings->value(QString("DEVICE/BrandId")).toString();

    timerInterval = settings->value(QString("SETUP/TIMER")).toString().toInt();
    hostAddress.setAddress(ipAdress);
    hostPort = portNo.toShort();

    if(ipAdress.isEmpty() || portNo.isEmpty() || device.DeviceId.isEmpty() || device.ModelId.isEmpty() || device.BrandId.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("仪器信息配置不正确，请配置后重新启动应用程序");
        msgBox.setInformativeText("是否要配置?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Yes:
            dialog->exec();
            break;
//        case QMessageBox::No:
//            // Don't Save was clicked
//            break;
//        default:
//            // should never be reached
//            break;
        }
    }
    else
    {
        connect(client,SIGNAL(disconnected()),client,SLOT(deleteLater()));
        client->connectToHost(hostAddress,hostPort);
        if( !client->waitForConnected(5000) )
        {
            QMessageBox msgBox;
            msgBox.setText("无法连接服务器，请检查配置信息或检查服务器是否启动");
            msgBox.setStandardButtons(QMessageBox::Yes);
            int ret = msgBox.exec();

        }
    }
}

void Widget::getChangedFiles()
{
    fileList.clear();
    QMutex mutex;
    mutex.lock();

    file.open(QIODevice::ReadWrite);

    QString str;
    while ( !(str = file.readLine()).isEmpty() ) {
//        instrLogDirPath = str;
        str = str.right(str.length() - str.indexOf(":    ") - QString(":    ").length());//去时间头
        fileList << str;
    }

    file.resize(0);
    file.close();

    mutex.unlock();
    if( fileList.size() <= 0 )
        return;
    else
    {
        parserThred *mThread = new parserThred(this,fileList);
        connect(mThread,SIGNAL(finished()),mThread,SLOT(deleteLater()));
        mThread->start();
    }
}
