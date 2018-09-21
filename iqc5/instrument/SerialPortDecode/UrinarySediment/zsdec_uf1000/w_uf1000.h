#ifndef W_UF1000_H
#define W_UF1000_H

#include "basewindow.h"

class W_Uf1000 : public BaseWindow
{
    Q_OBJECT

public:
    W_Uf1000(QWidget *parent = 0);
    ~W_Uf1000();

    void decode_old(QString data);

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);

public slots:
    void on_action_DecodeSetup_triggered();

private:
    bool m_bIsEnd;
    bool m_bIsQc;
    bool m_bOldMode;
    bool m_bUseDcEnd;
    bool m_bUseDdEnd;
    bool m_bUseDfEnd;

    QString m_sTotal;

    qint32 m_nTotalItem;

    QVector<QString> m_vItemCode;
    QVector<QString> m_vItemValue;
};

#endif // W_UF1000_H
