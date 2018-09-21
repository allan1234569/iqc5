#ifndef W_E411_H
#define W_E411_H

#include "basewindow.h"

class W_E411 : public BaseWindow
{
    Q_OBJECT

public:
    W_E411(QWidget *parent = 0);
    ~W_E411();

    // BaseWindow interface
public:
    void loadConfig();

    int decode(QString data);

public slots:
    void on_action_DecodeSetup_triggered();

private:
    qint32 m_nSampleNoMode;
    qint32 m_nResultMode;

    bool m_bIsQc;
    bool m_bIsStat;
};

#endif // W_E411_H
