#include "mainwindow.h"
#include "awarningdialog.h"
#include "single_application.h"
#include "res.h"

#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QTextCodec>

bool init()
{
    readSettings(g_sDestInstPath,"PROTOCOL/DESTINSTR");
    if (!g_sDestInstPath.isEmpty())
    {
        QDir dir;
        dir.setPath(g_sDestInstPath);
        if (dir.exists())
        {
            QString path = g_sDestInstPath + "/communication.ini";

            settings = new QSettings(path,QSettings::IniFormat);
            g_sRawDataDir = g_sDestInstPath.isEmpty()?QString("./raw"):g_sDestInstPath + "/raw";
        }
    }

    //初始化raw目录
    QDir rawDir;
    rawDir.setPath(g_sRawDataDir);
    if (!rawDir.exists())
    {
        QDir dir;
        if(!dir.mkdir(g_sRawDataDir))
        {
            return false;
        }
    }
    else
    {
        f_log("初始化目录成功");
    }



    QDir dir;
    g_sFileIni.prepend(dir.currentPath() + "/");
    g_sFileLog.prepend(dir.currentPath() + "/");

    QFile iniFile(g_sFileIni);
    if (!iniFile.exists())
    {
        QString tempStr = "没有找到配置文件communication.ini，无法启动应用程序";
        AWarningDialog warningDialog;
        warningDialog.showMessage(tempStr);
        f_log("没有找到配置文件，无法启动应用程序");
        return false;
    }

    readAllSettings();

    return true;
}

int main(int argc, char *argv[])
{
//    SingleApplication a(argc, argv,"some unique key string");
    SingleApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    if (!init())
    {
        return 0;
    }

    if (a.isRunning())
    {
        f_log("有一个实例已经运行");
        return 0;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
