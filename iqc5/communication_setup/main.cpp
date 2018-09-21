#include "widget.h"
#include <QApplication>
#include "res.h"
#include <QTextCodec>
#include <QDir>
#include <QMessageBox>
#include <QDebug>

void init()
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
        else
        {

        }
    }
    readAllSettings();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    init();

    Widget w;
    w.show();

    return a.exec();
}


