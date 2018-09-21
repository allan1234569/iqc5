#ifndef W_TIGSUN1_H
#define W_TIGSUN1_H

#include "basewindow.h"

class W_Tigsun1 : public BaseWindow
{
    Q_OBJECT

public:
    W_Tigsun1(QWidget *parent = 0);
    ~W_Tigsun1();

    // BaseWindow interface
public:
    void decode(QString data);

public slots:
    void slt_timeout();

    void on_action_DecodeSetup_triggered();
};

#endif // W_TIGSUN1_H
