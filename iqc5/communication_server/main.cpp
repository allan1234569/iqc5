
#include "server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server w;
    w.showMinimized();
    w.hide();

    QApplication::setQuitOnLastWindowClosed(false);


    return a.exec();
}
