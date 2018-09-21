#ifndef W_NEXGEN4_H
#define W_NEXGEN4_H

#include "basewindow.h"

class W_Nexgen4 : public BaseWindow
{
    Q_OBJECT

public:
    W_Nexgen4(QWidget *parent = 0);
    ~W_Nexgen4();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_NEXGEN4_H
