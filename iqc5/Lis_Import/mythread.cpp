#include "mythread.h"
#include "JlCompress.h"
#include <QDebug>

myThread::myThread(QObject *parent) :
    QThread(parent)
{
    lis = NULL;
    in_path = "";
    out_path = "";
}

myThread::~myThread()
{
    delete lis;
    lis = NULL;
}

bool myThread::extract(const QString &in_file_path, const QString &out_file_path)
{
    QuaZip archive(in_file_path);
    if (!archive.open(QuaZip::mdUnzip))
        return false;

    //    QString out_file_path = QString("./temp/");
    //    if (!path.endsWith("/") && !out_file_path.endsWith("\\"))
    //        path += "/";

    QDir dir(out_file_path);
    if (!dir.exists())
        dir.mkpath(out_file_path);


    for( bool f = archive.goToFirstFile(); f; f = archive.goToNextFile() )
    {
        QString filePath = archive.getCurrentFileName();
        qDebug() << filePath;
    }

    for( bool f = archive.goToFirstFile(); f; f = archive.goToNextFile() )
    {
        QString filePath = archive.getCurrentFileName();
        QuaZipFile zFile(archive.getZipName(), filePath);
        zFile.open(QIODevice::ReadOnly );
        QByteArray ba;
        if(zFile.size() > MAX_SIZE)
        {

            if (filePath.endsWith("/"))
            {
                dir.mkpath(filePath);
            }
            else
            {
                QFile dstFile(out_file_path + filePath);
                if (!dstFile.open(QIODevice::WriteOnly))
                    return false;

                while( !zFile.atEnd() )
                {
                    ba = zFile.read(MAX_SIZE);
                    dstFile.write(ba);
                }

                dstFile.close();
            }
        }
        else
        {
            ba.append(zFile.readAll());
            QFile dstFile(out_file_path + filePath);
            if (!dstFile.open(QIODevice::WriteOnly) )
                return false;
            dstFile.write(ba);
            dstFile.close();
        }

        zFile.close();
    }
    return true;

}

void myThread::import(Lis *lis)
{
    lis->importData();
}

void myThread::run()
{
    if( !in_path.isEmpty() && !out_path.isEmpty() )
    {
        qDebug() << "extract()";
        if( extract(in_path,out_path) )
            emit unCompressCompleted();
        else
        {
            emit unCompressFailed();
        }
    }
    else if(lis)
    {
        qDebug() << "importData()";
        if( lis->importData() )
        {
            emit importCompleted();
            qDebug() << "Complete import!";
        }
        else
        {
            emit importFailed();
        }
    }
}
