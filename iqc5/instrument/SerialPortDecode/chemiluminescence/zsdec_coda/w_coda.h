#ifndef W_CODA_H
#define W_CODA_H

#include "basewindow.h"

class W_Coda : public BaseWindow
{
    Q_OBJECT

public:
    W_Coda(QWidget *parent = 0);
    ~W_Coda();

    // BaseWindow interface
public:
    void loadConfig();

    int decode(QString data);

private:
    QString m_sSampleNoHead;
    QString m_sSampleDateHead;
    qint32  m_nSampleNoIndex;
    qint32  m_nSampleDateIndex;
    qint32  m_nResultIndex;

    bool m_bIsQc;
    bool m_bIsStat;
};

#endif // W_CODA_H
