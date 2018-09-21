#ifndef W_IQ200_H
#define W_IQ200_H

#include "basewindow.h"

class W_Iq200 : public BaseWindow
{
    Q_OBJECT

public:
    W_Iq200(QWidget *parent = 0);
    ~W_Iq200();

    inline QString translate(QString as_data);
    int deal_result(QString as_result);

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_IQ200_H
