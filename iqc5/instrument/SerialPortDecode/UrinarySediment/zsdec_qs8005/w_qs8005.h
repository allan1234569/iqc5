#ifndef W_QS8005_H
#define W_QS8005_H

#include "basewindow.h"

class W_Qs8005 : public BaseWindow
{
    Q_OBJECT

public:
    W_Qs8005(QWidget *parent = 0);
    ~W_Qs8005();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_QS8005_H
