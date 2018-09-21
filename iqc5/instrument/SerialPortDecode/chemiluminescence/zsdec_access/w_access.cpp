#include "w_access.h"

W_Access::W_Access(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-ACCESS");
}

W_Access::~W_Access()
{

}

int W_Access::decode(QString data)
{
    qint32 li_stx;
    qint32 li_etx;
    QString ls_data;
    QString ls_code;
    QString ls_itemno;
    QString ls_result;
    QString ls_date;
    QString ls_fielddelim;
    QString ls_itemdelim;

    m_sData += data;
    li_etx = m_sData.indexOf(QString(QChar(ETX)));

    if (li_etx < 0)
    {
        return -1;
    }

    li_stx = m_sData.indexOf(QString(QChar(STX)));
    ls_code = m_sData.mid(li_stx,li_etx - li_stx + 3);
    m_sData = m_sData.mid(li_etx + 3);

    if (ls_code.mid(2,1) == "H")
    {
        ls_fielddelim = ls_code.mid(3,1);
        ls_itemdelim = ls_code.mid(5,1);
    }
    else if (ls_code.mid(2,1) == "P")
    {
        m_sSampleNo = "";
    }
    else if (ls_code.mid(2,1) == "O")
    {
        m_sSampleNo = m_dec.GetField(m_dec.GetField(ls_code,ls_fielddelim,3),ls_itemdelim,1);
    }
    else if (ls_code.mid(2,1) == "R")
    {
        ls_date = m_dec.GetField(ls_code,ls_fielddelim,13).left(8);
        m_sSampleDate = getSampleDate(ls_data.left(4).toInt(),ls_date.mid(4,2).toInt(),ls_date.mid(6,2).toInt());
        ls_itemno = m_dec.GetField(m_dec.GetField(ls_code,ls_fielddelim,3),ls_itemdelim,4);
        ls_result = m_dec.GetField(ls_code,ls_fielddelim,4);
        sendResult(ls_itemno,ls_result);

    }
    else if (ls_code.mid(2,1) == "L")
    {
        m_sSampleNo = "";
    }

    if (m_sData.indexOf(QString(QChar(ETX))) >= 0)
    {
        redecode();
    }

    return 0;
}
