#ifndef W_AVL9130_H
#define W_AVL9130_H

#include "basewindow.h"

class W_Avl9130 : public BaseWindow
{
    Q_OBJECT

public:
    W_Avl9130(QWidget *parent = 0);
    ~W_Avl9130();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_AVL9130_H
