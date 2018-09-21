#include "nycocard.h"
#include <QApplication>
#include "common.h"
#include "single_application.h"


int main(int argc, char *argv[])
{

    SingleApplication a(argc, argv,"CRP_NYCOCARD");

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


    Nycocard w;
    w.show();

    return a.exec();
}
