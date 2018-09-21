#include "w_aia1800.h"

W_Aia1800::W_Aia1800(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-AIA1800");
}

W_Aia1800::~W_Aia1800()
{

}

int W_Aia1800::decode(QString data)
{
    qint32 li_stx;
    qint32 li_etx;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;
    qint32 li_pos;

    QString ls_code;
    QString ls_date;
    QString ls_result;
    QString ls_sign;
    QString ls_item;

    m_sData += data;
    li_etx = m_sData.indexOf(QString(QChar(ETX)));

    if (li_etx < 0)
    {
        return -1;
    }

    ls_code = ls_code.left(li_etx);
    m_sData = m_sData.mid(li_etx + 1);
    li_stx = ls_code.indexOf(QString(QChar(STX)));

    if (li_stx < 0)
    {
        return -1;
    }

    while(li_stx >= 0)
    {
        ls_code = ls_code.mid(li_stx + 2);
        li_stx = ls_code.indexOf(QString(QChar(STX)));
    }

    if (ls_code.left(1) == "O")
    {
        m_sSampleNo = m_dec.GetField(ls_code,"|",3);
        li_pos = m_sSampleNo.indexOf("^");

        if (li_pos >= 0)
        {
            m_sSampleNo = m_sSampleNo.left(li_pos);
        }
    }
    else if(ls_code.left(1) == "R")
    {
        ls_date = m_dec.GetField(ls_code,"|",13);
        li_year = ls_date.left(4).toInt();
        li_month = ls_date.mid(4,2).toInt();
        li_day = ls_date.mid(6,2).toInt();
        m_sSampleDate = QDate(li_year,li_month,li_day).toString("yyyy-MM-dd");

        ls_item = m_dec.GetField(ls_code,"|",3).mid(3).trimmed();

        li_pos = ls_item.indexOf("^");

        if (li_pos >= 0)
        {
            ls_item = ls_item.left(li_pos);
        }

        ls_result = m_dec.GetField(ls_code,"|",4);
        ls_sign = m_dec.GetField(ls_code,"|",7);

        if ((ls_sign == ">") || (ls_sign == "<"))
        {
            ls_result = ls_sign + ls_result;
        }

        sendResult(ls_item,ls_result);
    }
    else if(ls_code.left(1) == "L")
    {
        m_sSampleNo = "";
    }

    if (m_sData.indexOf(QString(QChar(ETX))) >= 0)
    {
        redecode();
    }

    return 0;
}
