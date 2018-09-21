#ifndef W_ALEGRIA_H
#define W_ALEGRIA_H

#include "basewindow.h"

class W_Alegria : public BaseWindow
{
    Q_OBJECT

public:
    W_Alegria(QWidget *parent = 0);
    ~W_Alegria();

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);

private:

};

#endif // W_ALEGRIA_H
