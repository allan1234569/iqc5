#include "w_a2000.h"
#include "single_application.h"
#include "common.h"

int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv,"chemiluminescence_A2000");

//    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    setting->setIniCodec(QTextCodec::codecForName("system"));


    if (a.isRunning())
    {
        f_log("一个解码程序已经运行");
        exit(1);
    }

    if (!f_init())
    {
        exit(1);
    }

    W_A2000 w;
    w.show();

    return a.exec();
}
