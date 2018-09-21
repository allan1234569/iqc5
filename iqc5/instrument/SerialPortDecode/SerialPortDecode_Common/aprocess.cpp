#include "aprocess.h"
#include <QProcess>
#include <QDebug>

AProcess::AProcess(QObject *parent) :
    QThread(parent)
{
    m_sProgram = "";
}

AProcess::~AProcess()
{

}

void AProcess::setProgram(const QString &path)
{
    m_sProgram = path;
}

void AProcess::run()
{
    QProcess::execute(m_sProgram);
}
