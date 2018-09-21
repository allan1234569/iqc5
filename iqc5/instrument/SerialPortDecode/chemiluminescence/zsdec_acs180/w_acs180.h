#ifndef W_ACS180_H
#define W_ACS180_H

#include "basewindow.h"

class W_Acs180 : public BaseWindow
{
    Q_OBJECT

public:
    W_Acs180(QWidget *parent = 0);
    ~W_Acs180();

    // BaseWindow interface
public:
    int decode(QString data);
};

#endif // W_ACS180_H
