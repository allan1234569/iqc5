#include <QApplication>
#include "common.h"

#include "widget.h"

int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv,"some unique key string");

    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    if (a.isRunning())
    {
        f_log("一个解码程序已经运行");
        exit(1);
    }

    if (!f_init())
    {
        exit(1);
    }

//    Widget w;
//    w.show();

    return a.exec();
}
