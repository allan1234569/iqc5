#include "w_opticonmonitor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    W_Opticonmonitor w;
    w.show();

    return a.exec();
}
