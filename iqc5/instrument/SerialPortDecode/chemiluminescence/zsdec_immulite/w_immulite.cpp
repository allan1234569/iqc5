#include "w_immulite.h"

W_Immulite::W_Immulite(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-IMMULITE");
}

W_Immulite::~W_Immulite()
{

}

int W_Immulite::decode(QString data)
{
    qint32 li_i;
    qint32 li_cnt;
    qint32 li_stx;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;
    qint32 li_pos;
    qint32 li_etx;

    QString ls_code;
    QString ls_data;
    QString ls_date;
    QString ls_result;
    QString ls_sign;
    QString ls_item;
    QStringList ls_pat;

    m_sData += data;
    li_etx = m_sData.indexOf(QString(QChar(ETX)));

    if (li_etx < 0)
    {
        return -1;
    }

    ls_code = m_sData.left(li_etx);
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
    else if (ls_code.left(1) == "R")
    {
        ls_date = m_dec.GetField(ls_code,"|",13);
        li_year = ls_date.left(4).toInt();
        li_month = ls_date.mid(4,2).toInt();
        li_day = ls_date.mid(6,2).toInt();
        m_sSampleDate = getSampleDate(li_year,li_month,li_day);

        ls_item = m_dec.GetField(ls_code,"|",3).mid(3);

        li_pos = ls_item.indexOf("^");

        if (li_pos >= 0)
        {
            ls_item = ls_item.left(li_pos);
        }

        ls_result = m_dec.GetField(ls_code,"|",4);
        ls_sign = m_dec.GetField(ls_code,"|",7);

        if ((ls_sign == "<") || (ls_sign == ">"))
        {
            if (isNumber(ls_result))
            {
                ls_result = ls_sign + ls_result;
            }
        }

        calcResult(ls_result);
        sendResult(ls_item,ls_result);
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

void W_Immulite::calcResult(QString &as_result)
{
    qint32 li_pos;

    li_pos = as_result.indexOf("!");

    if (li_pos >= 0)
    {
        as_result = as_result.left(li_pos);
    }

    if ((as_result.left(1) == ".") && (as_result.right(1) == "."))
    {
        as_result = "";
    }
    else
    {
        if (as_result.left(1) == ".")
        {
            as_result = QString("0%1").arg(as_result);
        }
        else
        {
            if (as_result.right(1) == ".")
            {
                as_result = as_result.left(as_result.length() - 1);
            }
        }
    }
}
