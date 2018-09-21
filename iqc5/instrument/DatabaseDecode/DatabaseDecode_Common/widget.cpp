#include "widget.h"
#include "common.h"

Widget::Widget(QWidget *parent) :
    BaseWindow(parent)
{
    qDebug() << __LINE__;
}

void Widget::loadConfig()
{

}

int Widget::decode(const QString &data)
{
    BaseWindow::decode();
    qDebug() << __FUNCTION__ << __LINE__;
}

void Widget::slt_timeout()
{
    qDebug() << __FUNCTION__ << __LINE__;

    decode("");
}

void Widget::slt_setQuery()
{

}
