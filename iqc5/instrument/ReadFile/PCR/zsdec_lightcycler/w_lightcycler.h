#ifndef W_LIGHTCYCLER_H
#define W_LIGHTCYCLER_H

#include "basewindow.h"

class W_LightCycle : public BaseWindow
{
    Q_OBJECT

public:
    W_LightCycle(QWidget *parent = 0);
    ~W_LightCycle();

    // BaseWindow interface
public:
    int decode(const QString &data);
};

#endif // W_LIGHTCYCLER_H
