#ifndef W_CENTAUR_H
#define W_CENTAUR_H

#include "basewindow.h"

class W_Centaur : public BaseWindow
{
    Q_OBJECT

public:
    W_Centaur(QWidget *parent = 0);
    ~W_Centaur();

    // BaseWindow interface
public:
    int decode(QString data);

    void transData();

    void getSampleNo();

private:
    qint32 m_nSampleNoMode;

    // BaseWindow interface
public:
    void loadConfig();

    // BaseWindow interface
public slots:
    void on_action_DecodeSetup_triggered();
};

#endif // W_CENTAUR_H
