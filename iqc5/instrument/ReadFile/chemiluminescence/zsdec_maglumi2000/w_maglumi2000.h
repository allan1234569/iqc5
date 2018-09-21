#ifndef W_MAGLUMI2000_H
#define W_MAGLUMI2000_H

#include "basewindow.h"

class W_Maglumi2000 : public BaseWindow
{
    Q_OBJECT

public:
    W_Maglumi2000(QWidget *parent = 0);
    ~W_Maglumi2000();


    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);

public slots:
    void slt_timeout();

    void on_action_DecodeSetup_triggered();

private:
    qint32 m_nSampleDateIndex;
    qint32 m_nSampleNoIndex;
    qint32 m_nItemIndex;
    qint32 m_nResultIndex;
};

#endif // W_MAGLUMI2000_H
