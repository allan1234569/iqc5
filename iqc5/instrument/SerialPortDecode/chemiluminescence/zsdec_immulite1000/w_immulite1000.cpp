#include "w_immulite1000.h"

W_Immulite1000::W_Immulite1000(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-IMMULITE");
}

W_Immulite1000::~W_Immulite1000()
{

}

int W_Immulite1000::decode(QString data)
{
    qint32 li_this;
    qint32 li_stx;
    qint32 li_pos;
    QString ls_code;
    QString ls_line;

    m_sData += data;
    li_pos = m_sData.indexOf(QString(QChar(ETX)));

    if (li_pos < 0)
    {
        return -1;
    }

    ls_code = m_sData.left(li_pos);
    m_sData = m_sData.mid(li_pos + 1);

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

    ls_line = ls_code;
    li_pos = ls_line.indexOf("|");

    if (li_pos >= 0)
    {
        if (ls_line.left(li_pos).right(1) == "P")
        {
            m_sSampleNo = "";
        }
        else if (ls_line.left(li_pos).right(1) == "O")
        {
            m_sSampleNo = m_dec.GetField(ls_line,"|",3);
        }
        else if (ls_line.left(li_pos).right(1) == "R")
        {
            dealResult(ls_line);
            m_sSampleNo = "";
        }
    }

    if (m_sData.indexOf(QString(QChar(ETX))) >= 0)
    {
        redecode();
    }

    return 0;
}

void W_Immulite1000::dealResult(QString as_data)
{
    QString ls_date;
    QString ls_itemalias;
    QString ls_result;
    QString ls_sign;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;

    ls_date = m_dec.GetField(as_data,"|",3);
    li_year = ls_date.left(4).toInt();
    li_month = ls_date.mid(4,2).toInt();
    li_day = ls_date.mid(6,2).toInt();
    m_sSampleDate = getSampleDate(li_year,li_month,li_day);

    ls_itemalias = m_dec.GetField(as_data,"|",3).mid(3);
    ls_result = m_dec.GetField(as_data,"|",4);
    ls_sign = m_dec.GetField(as_data,"|",7);

    if ((ls_sign == "<") || (ls_sign == ">"))
    {
        ls_result = ls_sign + ls_result;
    }

    sendResult(ls_itemalias,ls_result);


}
