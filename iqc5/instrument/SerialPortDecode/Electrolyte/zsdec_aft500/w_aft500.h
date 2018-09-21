#ifndef W_AFT500_H
#define W_AFT500_H

#include "basewindow.h"

class W_Aft500 : public BaseWindow
{
    Q_OBJECT

public:
    W_Aft500(QWidget *parent = 0);
    ~W_Aft500();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_AFT500_H
