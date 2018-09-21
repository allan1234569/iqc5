#ifndef W_SEIBACOM_H
#define W_SEIBACOM_H

#include "basewindow.h"

class W_SeibaCom : public BaseWindow
{
    Q_OBJECT

public:
    W_SeibaCom(QWidget *parent = 0);
    ~W_SeibaCom();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_SEIBACOM_H
