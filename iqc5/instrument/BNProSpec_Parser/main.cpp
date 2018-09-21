#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::addLibraryPath("./plugins");
    Widget w;
    w.showMinimized();
    w.hide();
    a.setQuitOnLastWindowClosed(false);
    return a.exec();
}
