#ifndef W_MD550_H
#define W_MD550_H

#include "basewindow.h"

class W_Md550 : public BaseWindow
{
    Q_OBJECT

public:
    W_Md550(QWidget *parent = 0);
    ~W_Md550();

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);

private:
    QString m_sItems;
    QString m_slItems;

    bool m_bAutoEtx;
    QString m_sIsEtx;
    QString m_sIsStx;
    qint32 m_nSampleNoPos;
    qint32 m_nSampleNolen;
    qint32 m_nSampleDatePos;
    qint32 m_nSampleDateLen;
};

#endif // W_MD550_H
