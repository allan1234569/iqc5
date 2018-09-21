#ifndef W_XD683_H
#define W_XD683_H

#include "basewindow.h"

class W_Xd683 : public BaseWindow
{
    Q_OBJECT

public:
    W_Xd683(QWidget *parent = 0);
    ~W_Xd683();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_XD683_H
