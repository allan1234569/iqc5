#include <QLocalSocket>
#include "single_application.h"
#include <QDir>

SingleApplication::SingleApplication(int &argc, char *argv[])
    : QApplication(argc, argv)

{
    QDir dir;
    QString path = dir.currentPath().append("/lock.lck");


    m_lockFile = new QFile(path);

    if(m_lockFile->exists())
    {
        _isRunning = true;
    }
    else
    {
        _isRunning = false;
       m_lockFile->open(QIODevice::ReadWrite | QIODevice::Text);    //程序启动，创建
       m_lockFile;
    }
}

SingleApplication::~SingleApplication()
{
    m_lockFile->close();
    m_lockFile->remove();   //程序关闭，删除
    delete m_lockFile;
    m_lockFile = NULL;
}

bool SingleApplication::isRunning()
{
    return _isRunning;
}
