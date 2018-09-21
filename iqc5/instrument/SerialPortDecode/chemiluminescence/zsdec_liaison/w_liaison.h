#ifndef W_LIAISON_H
#define W_LIAISON_H

#include "basewindow.h"

class W_Liaison : public BaseWindow
{
    Q_OBJECT

public:
    W_Liaison(QWidget *parent = 0);
    ~W_Liaison();

    // BaseWindow interface
public:
    int decode(QString data);
};

#endif // W_LIAISON_H
