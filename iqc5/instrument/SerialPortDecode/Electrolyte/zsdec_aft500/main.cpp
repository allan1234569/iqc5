#include "w_aft500.h"
#include <QApplication>
#include "common.h"
#include "single_application.h"


int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv,"Electrolyte_AFT500");

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


    W_Aft500 w;
    w.show();

    return a.exec();
}
