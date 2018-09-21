#ifndef W_NEXGEN4NEW_H
#define W_NEXGEN4NEW_H

#include "basewindow.h"

class W_Nexgen4new : public BaseWindow
{
    Q_OBJECT

public:
    W_Nexgen4new(QWidget *parent = 0);
    ~W_Nexgen4new();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_NEXGEN4NEW_H
