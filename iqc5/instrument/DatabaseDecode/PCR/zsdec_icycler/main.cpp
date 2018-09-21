#include "w_icycler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    W_Icycler w;
    w.show();

    return a.exec();
}
