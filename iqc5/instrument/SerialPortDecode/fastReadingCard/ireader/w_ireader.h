#ifndef W_IREADER_H
#define W_IREADER_H

#include "basewindow.h"

class W_Ireader : public BaseWindow
{
    Q_OBJECT

public:
    W_Ireader(QWidget *parent = 0);
    ~W_Ireader();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_IREADER_H
