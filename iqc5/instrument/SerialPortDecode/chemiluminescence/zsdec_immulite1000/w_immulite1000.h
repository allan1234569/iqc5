#ifndef W_IMMULITE1000_H
#define W_IMMULITE1000_H

#include "basewindow.h"

class W_Immulite1000 : public BaseWindow
{
    Q_OBJECT

public:
    W_Immulite1000(QWidget *parent = 0);
    ~W_Immulite1000();

    // BaseWindow interface
public:
    int decode(QString data);

    void dealResult(QString as_data);
};

#endif // W_IMMULITE1000_H
