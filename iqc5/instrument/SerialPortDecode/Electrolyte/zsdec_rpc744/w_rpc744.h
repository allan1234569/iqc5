#ifndef W_RPC744_H
#define W_RPC744_H

#include "basewindow.h"

class W_Rpc744 : public BaseWindow
{
    Q_OBJECT

public:
    W_Rpc744(QWidget *parent = 0);
    ~W_Rpc744();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_RPC744_H
