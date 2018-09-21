#ifndef W_EX_Z_H
#define W_EX_Z_H

#include "basewindow.h"

class W_Ex_Z : public BaseWindow
{
    Q_OBJECT

public:
    W_Ex_Z(QWidget *parent = 0);
    ~W_Ex_Z();

    // BaseWindow interface
public:
    void decode(QString data);

    QString getItem(QString as_str);
};

#endif // W_EX_Z_H
