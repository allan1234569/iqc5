#ifndef W_ECI_H
#define W_ECI_H

#include "basewindow.h"

class W_Eci : public BaseWindow
{
    Q_OBJECT

public:
    W_Eci(QWidget *parent = 0);
    ~W_Eci();


    // BaseWindow interface
public:
    void loadConfig();

    int decode(QString data);

public slots:
    void on_action_DecodeSetup_triggered();

private:
    qint32 m_nYearPos;
    qint32 m_nMonthPos;
    qint32 m_nDayPos;

    bool m_bIsQc;
    qint32 m_nQcPos;

    qint32 m_nLongResultMode;

    qint32 m_nSampleStart;
    qint32 m_nSampleLen;
    qint32 m_nItemStart;
    qint32 m_nItemLen;
    qint32 m_nResultStart;
    qint32 m_nReslultLen;
    qint32 m_nResultFlagPos;
};

#endif // W_ECI_H
