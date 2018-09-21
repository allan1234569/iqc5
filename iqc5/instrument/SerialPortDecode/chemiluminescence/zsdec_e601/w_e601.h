#ifndef W_E601_H
#define W_E601_H

#include "basewindow.h"

class W_E601 : public BaseWindow
{
    Q_OBJECT

public:
    W_E601(QWidget *parent = 0);
    ~W_E601();

    // BaseWindow interface
public:
    void loadConfig();

    int decode(QString data);

public slots:
    void on_action_DecodeSetup_triggered();

private:
    bool m_bIsQc;
    bool m_bIsStat;

    qint32 m_nSampleNoMode;
    bool m_bBarCode;    //条码双工模式
};

#endif // W_E601_H
