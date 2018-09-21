#ifndef W_BYR744_H
#define W_BYR744_H

#include "basewindow.h"

class W_Byr744 : public BaseWindow
{
    Q_OBJECT

public:
    W_Byr744(QWidget *parent = 0);
    ~W_Byr744();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_BYR744_H
