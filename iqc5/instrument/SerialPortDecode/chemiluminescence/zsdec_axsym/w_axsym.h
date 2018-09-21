#ifndef W_AXSYM_H
#define W_AXSYM_H

#include "basewindow.h"

class W_Axsym : public BaseWindow
{
    Q_OBJECT

public:
    W_Axsym(QWidget *parent = 0);
    ~W_Axsym();

    // BaseWindow interface
public:
    void loadConfig();

    int decode(QString data);

private:
    qint32 m_nItemPos;
    qint32 m_nResultPos;
    qint32 m_nResult2Pos;

    bool  m_bIsQc;

    QString m_sResult;
};

#endif // W_AXSYM_H
