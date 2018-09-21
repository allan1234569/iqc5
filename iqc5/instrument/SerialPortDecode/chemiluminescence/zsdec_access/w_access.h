#ifndef W_ACCESS_H
#define W_ACCESS_H

#include "basewindow.h"

class W_Access : public BaseWindow
{
    Q_OBJECT

public:
    W_Access(QWidget *parent = 0);
    ~W_Access();

    // BaseWindow interface
public:
    int decode(QString data);
};

#endif // W_ACCESS_H
