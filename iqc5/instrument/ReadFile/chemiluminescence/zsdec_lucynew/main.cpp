#include <QApplication>
#include "single_application.h"
#include "common.h"

#include "w_lucynew.h"

int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv,"chemiluminescence_LUCYNEW");

    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));


    if (a.isRunning())
    {
        f_log("一个解码程序已经运行");
        exit(1);
    }


    if (!f_init())
    {
        exit(1);
    }

    W_Lucynew w;
    w.show();

    return a.exec();
}
