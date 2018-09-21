#ifndef W_MVIDAS_H
#define W_MVIDAS_H

#include "basewindow.h"



class W_Mvidas : public BaseWindow
{
    Q_OBJECT

public:
    W_Mvidas(QWidget *parent = 0);
    ~W_Mvidas();

    // BaseWindow interface
public:
    int decode(QString data);

private:
    char brk = GS;
    char slp = RS;
};

#endif // W_MVIDAS_H
