#ifndef W_DSI903_H
#define W_DSI903_H

#include "basewindow.h"

class W_Dsi903 : public BaseWindow
{
    Q_OBJECT

public:
    W_Dsi903(QWidget *parent = 0);
    ~W_Dsi903();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_DSI903_H
