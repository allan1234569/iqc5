#ifndef W_PSD_H
#define W_PSD_H

#include "basewindow.h"

class W_Psd : public BaseWindow
{
    Q_OBJECT

public:
    W_Psd(QWidget *parent = 0);
    ~W_Psd();

    // BaseWindow interface
public:
    void decode(QString data);
};

#endif // W_PSD_H
