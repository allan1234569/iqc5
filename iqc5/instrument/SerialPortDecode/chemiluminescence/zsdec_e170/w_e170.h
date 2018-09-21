#ifndef W_E170_H
#define W_E170_H

#include "basewindow.h"

class W_E170 : public BaseWindow
{
    Q_OBJECT

public:
    W_E170(QWidget *parent = 0);
    ~W_E170();

    // BaseWindow interface
public:
    void loadConfig();

    int decode(QString data);

public slots:
    void on_action_DecodeSetup_triggered();

private:
    qint32 m_nSampleIdMode;
    bool m_bBarCodeMode;    //条码双工模式
    bool m_bIsQc;
};

#endif // W_E170_H
