#include "ftc2000.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    W_Ftc2000 w;
    w.show();

    return a.exec();
}
