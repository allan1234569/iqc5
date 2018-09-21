#ifndef W_IMMULITE2000_H
#define W_IMMULITE2000_H

#include "basewindow.h"

class W_Immulite2000 : public BaseWindow
{
    Q_OBJECT

public:
    W_Immulite2000(QWidget *parent = 0);
    ~W_Immulite2000();

    // BaseWindow interface
public:
    int decode(QString data);

    void calcResult(QString &as_result);
};

#endif // W_IMMULITE2000_H
