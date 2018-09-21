#include "w_ex_z.h"

W_Ex_Z::W_Ex_Z(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-EX-Z");
}

W_Ex_Z::~W_Ex_Z()
{

}

void W_Ex_Z::decode(QString data)
{
    qint32 li_stx;
    qint32 li_etx;
    QString ls_code;
    QString ls_data;
    QDateTime ldt_dateTime;

    m_sData += data;
    li_etx = m_sData.indexOf(QChar(ETX));

    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx);
    ls_data = m_sData.mid(li_etx + 1);
    li_stx = ls_code.indexOf(QChar(STX));

    while(li_stx >= 0)
    {
        ls_code = ls_code.mid(li_stx + 1);
        li_stx = ls_code.indexOf(QChar(STX));
    }

    ldt_dateTime = m_dec.GetDateByFormat(ls_code.left(14),"yyyyMMddhhmmss");
    m_sSampleDate = ldt_dateTime.date().toString("yyyy-MM-dd");
    m_sSampleNo = ls_code.mid(18,4);

//    ls_code.mid(22,17); //id号

    sendResult(getItem(ls_code.mid(42,2)),ls_code.mid(44,5));
    sendResult(getItem(ls_code.mid(51,2)),ls_code.mid(53,5));
    sendResult(getItem(ls_code.mid(60,2)),ls_code.mid(62,5));

    if (m_sData.indexOf(QChar(ETX)) >= 0)
    {
        redecode();
    }
}

QString W_Ex_Z::getItem(QString as_str)
{
    if (as_str == "01")
    {
        return "NA";
    }
    else if (as_str == "02")
    {
        return "K";
    }
    else if (as_str == "03")
    {
        return "CL";
    }
    else
    {
        return as_str;
    }
}
