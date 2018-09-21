#include "widget.h"

Widget::Widget(QWidget *parent) :
    BaseWindow(parent)
{
    setFileSuffix("*.o");
}
