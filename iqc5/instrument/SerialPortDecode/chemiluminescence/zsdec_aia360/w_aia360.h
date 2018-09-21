#ifndef W_AIA360_H
#define W_AIA360_H

#include "basewindow.h"

class W_Aia360 : public BaseWindow
{
    Q_OBJECT

public:
    W_Aia360(QWidget *parent = 0);
    ~W_Aia360();

    // BaseWindow interface
public:
    int decode(QString data);
};

#endif // W_AIA360_H
