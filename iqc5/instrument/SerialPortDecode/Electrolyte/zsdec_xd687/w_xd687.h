#ifndef W_XD687_H
#define W_XD687_H

#include "basewindow.h"

class W_Xd687 : public BaseWindow
{
    Q_OBJECT

public:
    W_Xd687(QWidget *parent = 0);
    ~W_Xd687();

    // BaseWindow interface
public:
    void decode(QString data);

    void deal_sample(QString data);
};

#endif // W_XD687_H
