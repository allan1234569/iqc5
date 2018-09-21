#ifndef W_HK2003_H
#define W_HK2003_H

#include "basewindow.h"

class W_Hk2003 : public BaseWindow
{
    Q_OBJECT

public:
    W_Hk2003(QWidget *parent = 0);
    ~W_Hk2003();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_HK2003_H
