#ifndef W_XD685_H
#define W_XD685_H

#include "basewindow.h"

class W_Xd685 : public BaseWindow
{
    Q_OBJECT

public:
    W_Xd685(QWidget *parent = 0);
    ~W_Xd685();

    // BaseWindow interface
public:
    void decode(QString data);

    void deal_sample(QString data);
};

#endif // W_XD685_H
