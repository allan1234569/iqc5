#ifndef W_AIA1800_H
#define W_AIA1800_H

#include "basewindow.h"

class W_Aia1800 : public BaseWindow
{
    Q_OBJECT

public:
    W_Aia1800(QWidget *parent = 0);
    ~W_Aia1800();

    // BaseWindow interface
public:
    int decode(QString data);
};

#endif // W_AIA1800_H
