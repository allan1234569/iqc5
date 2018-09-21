#ifndef W_MAGIMUZYME_I_H
#define W_MAGIMUZYME_I_H

#include "basewindow.h"

class W_Magimuzyme_i : public BaseWindow
{
    Q_OBJECT

public:
    W_Magimuzyme_i(QWidget *parent = 0);
    ~W_Magimuzyme_i();

    int getEndPos(QString as_data);

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);

private:
    qint32 m_nSampleStart;
    qint32 m_nSampleLen;
    qint32 m_nResultStart;
    qint32 m_nResultLen;
    qint32 m_nFlagStart;
    qint32 m_nFlagLen;

    QString m_sItemHead;
    QString m_sResultHead;
};

#endif // W_MAGIMUZYME_I_H
