#include "w_nexgen4.h"
#include <QApplication>
#include "common.h"
#include "single_application.h"


int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv,"EnzymeImmunoassay_NEXGEN4");

    setting->setIniCodec("UTF-8");


    if (a.isRunning())
    {
        f_log("一个解码程序已经运行");
        exit(1);
    }

    if (!f_init())
    {
        exit(1);
    }


    W_Nexgen4 w;
    w.show();

    return a.exec();
}
