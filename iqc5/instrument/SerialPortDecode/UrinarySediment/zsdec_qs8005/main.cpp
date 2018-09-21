#include "w_qs8005.h"
#include <QApplication>
#include "common.h"
#include "single_application.h"


int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv,"UrinarySediment-QS8005");

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


    W_Qs8005 w;
    w.show();

    return a.exec();
}
