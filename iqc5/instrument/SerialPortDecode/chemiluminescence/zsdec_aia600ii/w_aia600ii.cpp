#include "w_aia600ii.h"

W_Aia600ii::W_Aia600ii(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-AIA600ii");

    m_bIsQc = false;
}

W_Aia600ii::~W_Aia600ii()
{

}

int W_Aia600ii::decode(QString data)
{
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;
    qint32 li_pos;
    qint32 li_stx;
    qint32 li_etx;

    QString ls_code;
    QString ls_date;
    QString ls_result;
    QString ls_item;
    QString ls_sign;
    QString ls_head;

    m_sData += data;
    li_etx = m_sData.indexOf(QString(QChar(ETX)));

    if (li_etx < 0)
    {
        return -1;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx);
    li_stx = ls_code.indexOf(QString(QChar(STX)));

    if (li_stx < 0)
    {
        return -1;
    }

    while(li_stx >= 0)
    {
        ls_code = ls_code.mid(li_stx + 2);
        li_pos = ls_code.indexOf(QString(QChar(STX)));
    }

    if (ls_code.left(1) == "O")
    {
        m_sSampleNo = m_dec.GetField(ls_code,"|",3);
        li_pos = m_sSampleNo.indexOf("^");

        if (li_pos >= 0)
        {
            m_sSampleNo = m_sSampleNo.left(li_pos);
        }

        m_sSampleNo = m_sSampleNo.trimmed();
        ls_head = m_sSampleNo.left(4).toUpper();

        if ((ls_head == "STAT") || (ls_head == "CTRL") || (ls_head == "SMPL"))
        {
            m_bIsQc = (ls_head == "CTRL");

            if (!m_bIsQc)
            {
                m_sSampleNo = m_sSampleNo.mid(4).trimmed();
            }
        }
        else
        {
            m_bIsQc = false;
        }
    }
    else if (ls_code.left(1) == "R")
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

        if (!m_bIsQc)
        {
            ls_sign  = m_dec.GetField(ls_code,"|",7);
            if ((ls_sign == ">") || (ls_sign == "<"))
            {
                ls_result = ls_sign + ls_result;
            }

            sendResult(ls_item,ls_result);
        }
    }
    else if (ls_code.left(1) == "L")
    {
        m_sSampleNo = "";
    }

    if (m_sData.indexOf(QString(QChar(ETX))) >= 0)
    {
        redecode();
    }

    return 0;
}
