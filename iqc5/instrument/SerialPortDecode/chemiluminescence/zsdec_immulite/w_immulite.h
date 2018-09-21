#ifndef W_IMMULITE_H
#define W_IMMULITE_H

#include "basewindow.h"

class W_Immulite : public BaseWindow
{
    Q_OBJECT

public:
    W_Immulite(QWidget *parent = 0);
    ~W_Immulite();

    // BaseWindow interface
public:
    int decode(QString data);

    void calcResult(QString &as_result);
};

#endif // W_IMMULITE_H
