#ifndef W_CENTAUR_CP_H
#define W_CENTAUR_CP_H

#include "basewindow.h"

class W_Centaur_Cp : public BaseWindow
{
    Q_OBJECT

public:
    W_Centaur_Cp(QWidget *parent = 0);
    ~W_Centaur_Cp();

    // BaseWindow interface
public:
    int decode(QString data);

    void loadConfig();

    void getSampleNo();


public slots:
    void on_action_DecodeSetup_triggered();

private:
    int m_nSampleNoMode;
};

#endif // W_CENTAUR_CP_H
