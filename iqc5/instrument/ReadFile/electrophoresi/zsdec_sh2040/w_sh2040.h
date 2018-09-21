#ifndef W_SH2040_H
#define W_SH2040_H

#include "basewindow.h"

class W_Sh2040 : public BaseWindow
{
    Q_OBJECT

public:
    W_Sh2040(QWidget *parent = 0);
    ~W_Sh2040();

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);


private:
    int m_nSampleNoIndex;
    int m_nItemIndex;
    int m_nResultIndex;
    QString m_sResultFile;


    // BaseWindow interface
public slots:
    void on_action_DecodeSetup_triggered();

    void slt_timeout();
};

#endif // W_SH2040_H
