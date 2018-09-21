#include <QApplication>
#include "single_application.h"
#include "common.h"

#include "w_jetlia962.h"

int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv,"chemiluminescence_JETLIA962");

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

    W_Jetlia962 w;
    w.show();

    return a.exec();
}
