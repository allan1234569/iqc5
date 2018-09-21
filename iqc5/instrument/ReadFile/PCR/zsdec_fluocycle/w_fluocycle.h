#ifndef W_FLUOCYCLE_H
#define W_FLUOCYCLE_H

#include "basewindow.h"

class W_Fluocycle : public  BaseWindow
{
    Q_OBJECT

public:
    W_Fluocycle(QWidget *parent = 0);
    ~W_Fluocycle();

    // BaseWindow interface
public:
    int decode(const QString &data);
};

#endif // W_FLUOCYCLE_H
