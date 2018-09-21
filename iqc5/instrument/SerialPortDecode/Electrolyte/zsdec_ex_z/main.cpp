#include "w_ex_z.h"
#include <QApplication>
#include "common.h"
#include "single_application.h"


int main(int argc, char *argv[])
{

    SingleApplication a(argc, argv,"Electrolyte_EX-Z");

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


    W_Ex_Z w;
    w.show();

    return a.exec();
}
