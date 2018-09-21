#include "w_mx3000p.h"
#include <QApplication>
#include "single_application.h"
#include "common.h"

int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv,"PCR_MX3000P");

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

    W_MX3000P w;
    w.show();

    return a.exec();
}
