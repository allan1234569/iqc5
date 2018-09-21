#include "w_dsi905.h"
#include <QApplication>
#include "common.h"
#include "single_application.h"


int main(int argc, char *argv[])
{

    SingleApplication a(argc, argv,"Electrolyte_DSI905");

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));


    if (a.isRunning())
    {
        f_log("一个解码程序已经运行");
        exit(1);
    }

    if (!f_init())
    {
        exit(1);
    }


    W_Dsi905 w;
    w.show();

    return a.exec();
}
