#include "clientsocket.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileSystemWatcher>

ClientSocket::ClientSocket(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(readClient()));
    connect(this,SIGNAL(disconnected()),this,SLOT(deleteLater()));
}

qint64 ClientSocket::sendMessage(const QByteArray &data)
{
    write(data);
}



//void ClientSocket::fileChanged(const QString &path)
//{

//    QFile file(path);
//    if( !file.open(QIODevice::ReadOnly) )
//    {
//        qDebug() << "open failed!";
//        return;
//    }
//    QTextStream in(&file);
//    QString content = in.readAll();
//    file.close();

//    QByteArray block;
////    //使用数据流写入数据
////    QDataStream out(&block,QIODevice::ReadWrite);
////    //设置数据流的版本，客户端和服务器端使用的版本要相同
////    out.setVersion(QDataStream::Qt_5_3);

////    //设置发送长度初始值为0
////    out << (quint16) 0;

////    //设置发送内容
////    out << content;

////    //回到字节流起始位置
////    out.device()->seek(0);
////    //重置字节流长度
////    out << (quint16) (block.size()-sizeof(quint16));

////    //往套接字缓存中写入数据，并发送

//    block.prepend("@filenameEnd\ncontentStart");
//    block.prepend(path.toStdString().c_str());
//    block.append(content);
//    block.append("contextEnd");
//    waitForBytesWritten();
//    qDebug() <<  write(block)/1024;

//}

//void ClientSocket::directoryChanged(const QString &path)
//{

//}

void ClientSocket::readClient()
{
    QByteArray arr;
    arr.append(read(1014));
    qDebug() << arr;
}
