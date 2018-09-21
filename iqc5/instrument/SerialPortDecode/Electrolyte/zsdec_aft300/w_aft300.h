#ifndef W_AFT300_H
#define W_AFT300_H

#include "basewindow.h"

class W_AFT300 : public BaseWindow
{
    Q_OBJECT

public:
    W_AFT300(QWidget *parent = 0);
    ~W_AFT300();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_AFT300_H
