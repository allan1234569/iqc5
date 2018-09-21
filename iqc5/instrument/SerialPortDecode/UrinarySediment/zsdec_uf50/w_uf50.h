#ifndef W_UF50_H
#define W_UF50_H

#include "basewindow.h"

class W_UF50 : public BaseWindow
{
    Q_OBJECT

public:
    W_UF50(QWidget *parent = 0);
    ~W_UF50();

    //QString getRbcInfo(QString as_result);

    // BaseWindow interface
public:
    void decode(QString data);

private:
    bool m_bIsEnd;
    bool m_bIsQc;

    QString m_sTotal;

    qint32 m_nTotalItem;

    QVector<QString> m_vItemCode;
    QVector<QString> m_vItemValue;
};

#endif // W_UF50_H
