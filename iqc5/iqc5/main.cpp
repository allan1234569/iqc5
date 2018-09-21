#include "MainWindow.h"
#include <QApplication>
#include <QtSql/QSqlQuery>
#include <QTextCodec>
#include <math.h>
#include <time.h>
#include <QFileInfo>
#include <QDebug>
#include "UI/NewProjectBatch.h"
#include "UI/InputDataMulti.h"
#include "UI/InputDataSingle.h"
#include "UI/ManageMaterial.h"
#include "UI/ManageReagent.h"
#include "UI/ManageDevice.h"
#include "UI/ManageMethod.h"
#include "UI/ManageType.h"
#include "UI/ManageMaterialBatch.h"
#include "UI/ManageMaterialTestType.h"
#include "UI/NewMaterialBatch.h"
#include "UI/EditDevice.h"
#include "UI/AnalyzeProject.h"
#include "UI/AnalyzeRule.h"
#include "UI/Circle.h"
#include "LoginMainWindow.h"

int main(int argc, char *argv[])
{
    //不加跑不起来
    QTextCodec *xcodec = QTextCodec::codecForLocale();
    QString exeDir = xcodec->toUnicode(QByteArray(argv[0]));
    QString currentPath = QFileInfo(exeDir).path();
    QApplication::setLibraryPaths(QApplication::libraryPaths()<<currentPath);

    qApp->addLibraryPath(currentPath);

    //解决中文乱码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));

    //生成随机数种子，否则每次开机之后随机数种子都会一样
    srand(time(NULL));

    //初始化数据库
    QSqlDatabase::addDatabase("QSQLITE");

    QApplication a(argc, argv);
    a.setApplicationName("智晟生物");
    a.setOrganizationName("智晟生物");

    LoginMainWindow loginMain;
//    loginMain.show();

#ifdef QT_NO_DEBUG

    a.setStyle(new RibbonStyle);

#else
    //NewProjectBatch w;
    //InputDataSingle w;
    //NewMaterialBatch w;
    //AnalyzeProject w;
    //AnalyzeRule w;
    //AnalyzeProject w;
    //w.showMaximized();
#endif




    MainWindow w;
    w.showMaximized();
    a.connect(&loginMain,SIGNAL(correct_login_password()),&w,SLOT(showMaximized()));
    a.connect(&loginMain,SIGNAL(correct_login_password()),&loginMain,SLOT(close()));
    a.setWindowIcon(QIcon("://images/clipboard.png"));

    return a.exec();
}
