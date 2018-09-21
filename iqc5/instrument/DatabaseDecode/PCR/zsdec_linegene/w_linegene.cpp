#include "w_linegene.h"

W_Linegene::W_Linegene(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle(tr("linegene"));

    slt_setQuery();

    connect(this,SIGNAL(isChanged()),this,SLOT(slt_setQuery()));

}

W_Linegene::~W_Linegene()
{

}

int W_Linegene::decode(const QString &data)
{

}

void W_Linegene::slt_timeout()
{
    BaseWindow::slt_timeout();
}

void W_Linegene::slt_setQuery()
{

}
