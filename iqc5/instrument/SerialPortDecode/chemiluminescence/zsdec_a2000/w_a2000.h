#ifndef W_A2000_H
#define W_A2000_H

#include "basewindow.h"

class W_A2000 : public BaseWindow
{
    Q_OBJECT

public:
    W_A2000(QWidget *parent = 0);
    ~W_A2000();

    // BaseWindow interface
public:
    int decode(QString data);
};

#endif // W_A2000_H
