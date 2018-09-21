#include "mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent) :
    BaseWindow(parent)
{
    this->setWindowTitle("主窗口");
}

void Mainwindow::decode(const QString &data)
{
    ClientSocket * socket = SingletonSocket::GetSocketInstance();
    if (socket->tryConnect())
    {
        qDebug() << "Can send data";
    }
    else {
       qDebug() << "can not send data";
    }
}
