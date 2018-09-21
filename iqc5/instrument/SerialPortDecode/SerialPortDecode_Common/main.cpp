#include "quickread.h"
#include <QApplication>
#include "common.h"
#include "single_application.h"


int main(int argc, char *argv[])
{

    SingleApplication a(argc, argv,"CRP_QUICKREAD");

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));


    if (a.isRunning())
    {
        f_log("一个解码程序已经运行");
        exit(1);
    }

    if (!f_init())
    {
        exit(1);
    }


    QuickRead w;
    w.show();

    return a.exec();
}
