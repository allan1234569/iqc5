#include "w_liaison.h"

W_Liaison::W_Liaison(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-LIAISON");
}

W_Liaison::~W_Liaison()
{

}

int W_Liaison::decode(QString data)
{
    qint32 li_etx;
    qint32 li_i;
    qint32 li_cnt;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;
    QString ls_code;
    QString ls_data;
    QString ls_item;
    QString ls_result;
    QString ls_ln;
    QString ls_date;
    QStringList lsl_unit;

    m_sData += data;
    li_etx = -1;

label_0:
    li_etx = m_sData.indexOf("L|1",li_etx + 1);

    if (li_etx < 0)
    {
        return -1;
    }

    if (m_sData.mid(li_etx - 2, 1) != QString(QChar(STX)))
    {
        goto label_0;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 3);
    lsl_unit = ls_code.split("\r\n");

    for(int i = 0; i < lsl_unit.size(); i++)
    {
        ls_ln = lsl_unit.at(i).trimmed();

        if (ls_ln.left(1) == QString(QChar(STX)))
        {
            if (ls_ln.mid(2,1) == "O")
            {
                m_sSampleNo = m_dec.GetField(ls_ln,"|",3);
            }
            else if (ls_ln.mid(2,1) == "R")
            {
                ls_item = m_dec.GetField(ls_ln,"|",3);
                ls_item = m_dec.GetField(ls_item,"^",4);
                ls_result = m_dec.GetField(ls_ln,"|",4);
                ls_date = m_dec.GetField(ls_ln,"|",13);
                li_year = ls_date.left(4).toInt();
                li_month = ls_date.mid(4,2).toInt();
                li_day = ls_date.mid(6,2).toInt();
                m_sSampleDate = getSampleDate(li_year,li_month,li_day);
                sendResult(ls_item,ls_result);
            }
        }
    }


    if (m_sData.indexOf("L|1") >= 0)
    {
        redecode();
    }

    return 0;
}
