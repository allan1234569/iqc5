#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* add depend library path */
    qApp->addLibraryPath("./Plugins");
    QString libPath = QObject::tr("");

    /* add  depend library */
    foreach(QString str,qApp->libraryPaths()){
        libPath.append(str);
        libPath.append("\n");
    }

    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    MainWindow w;

    w.show();

    return a.exec();
}
