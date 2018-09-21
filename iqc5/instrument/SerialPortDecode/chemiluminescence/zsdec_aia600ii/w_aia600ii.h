#ifndef W_AIA600II_H
#define W_AIA600II_H

#include "basewindow.h"

class W_Aia600ii : public BaseWindow
{
    Q_OBJECT

public:
    W_Aia600ii(QWidget *parent = 0);
    ~W_Aia600ii();

    // BaseWindow interface
public:
    int decode(QString data);

private:
    bool m_bIsQc;
};

#endif // W_AIA600II_H
