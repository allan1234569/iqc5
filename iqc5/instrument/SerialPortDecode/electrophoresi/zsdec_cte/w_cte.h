#ifndef W_CTE_H
#define W_CTE_H

#include "basewindow.h"

class W_Cte : public BaseWindow
{
    Q_OBJECT

public:
    W_Cte(QWidget *parent = 0);
    ~W_Cte();

    int getStx();

    int getEtx();

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);

private:
    int m_nBlockSize;
    int m_nSampleNoStart;
    int m_nSampleNoLength;
    QStringList m_slItems;
    QStringList m_slItempos;
    int m_nItemCnt;
};

#endif // W_CTE_H
