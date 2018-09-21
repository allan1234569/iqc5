#ifndef W_AVL9180_H
#define W_AVL9180_H

#include "basewindow.h"

class W_Avl9180 : public BaseWindow
{
    Q_OBJECT

public:
    W_Avl9180(QWidget *parent = 0);
    ~W_Avl9180();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_AVL9180_H
