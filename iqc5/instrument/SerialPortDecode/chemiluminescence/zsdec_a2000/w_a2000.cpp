#include "w_a2000.h"

W_A2000::W_A2000(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-A20000");
}

W_A2000::~W_A2000()
{

}

int W_A2000::decode(QString data)
{
    qDebug() << __LINE__;
    return 0;
}
