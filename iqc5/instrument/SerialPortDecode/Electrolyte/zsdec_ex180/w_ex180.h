#ifndef W_EX180_H
#define W_EX180_H

#include "basewindow.h"

class W_Ex180 : public BaseWindow
{
    Q_OBJECT

public:
    W_Ex180(QWidget *parent = 0);
    ~W_Ex180();

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);

private:
    qint32 m_nYearStart;    //年
    qint32 m_nYearLen;

    qint32 m_nMonthStart;   //月
    qint32 m_nMonthLen;

    qint32 m_nDayStart;     //日
    qint32 m_nDayLen;

    qint32 m_nSampleNoStart;    //样本号
    qint32 m_nSampleNoLen;

    qint32 m_nNaStart;          //钠
    qint32 m_nNaLen;

    qint32 m_nKStart;           //钾
    qint32 m_nKLen;

    qint32 m_nClStart;          //氯
    qint32 m_nClLen;
};

#endif // W_EX180_H
