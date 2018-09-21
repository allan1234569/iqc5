#include "w_acs180.h"

W_Acs180::W_Acs180(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-ACS180");
}

W_Acs180::~W_Acs180()
{

}

int W_Acs180::decode(QString data)
{
    qint32 li_etx;
    qint32 li_start;
    qint32 li_pos;

    QString ls_code;
    QString ls_date;
    QString ls_itemno;
    QString ls_result;
    QString ls_char;

    QStringList lsl_unit;
    QStringList lsl_line;

    m_sData += data;

    li_start = 0;

    label_0:
    li_etx = m_sData.indexOf("L|1",li_start);

    if (li_etx < 0)
    {
        return -1;
    }

    if (m_sData.mid(li_etx - 2, 1) != QString(QChar(STX)))
    {
        li_start = li_etx + 3;
        goto label_0;
    }

    ls_code = m_sData.left(li_etx - 4);
    m_sData = m_sData.mid(li_etx + 4);

    lsl_line = ls_code.split("\r\n");

    for(int i = 0; i < lsl_line.size(); i++)
    {
        lsl_unit = lsl_line.at(i).split("|");

        if (lsl_unit.size() >= 1)
        {
            ls_char = lsl_unit.at(0).right(1);
            if (ls_char == "O")
            {
                if (lsl_unit.size() > 2)
                {
                    m_sSampleNo = lsl_unit.at(2);
                    li_pos = m_sSampleNo.indexOf("^");

                    if (li_pos >= 0)
                    {
                        m_sSampleNo = m_sSampleNo.left(li_pos);
                    }
                }
                else
                {
                    m_sSampleNo = "";
                }
            }
            else if (ls_char == "R")
            {
                if (lsl_unit.size() > 3)
                {
                    if (lsl_unit.at(1) == "1")
                    {
                        if (lsl_unit.size() > 11)
                        {
                            ls_date = lsl_unit.at(12);
                        }
                        m_sSampleDate = getSampleDate(ls_date.left(4).toInt(),ls_date.mid(4,2).toInt(),ls_date.mid(6,2).toInt());
                    }
                }

                ls_itemno = m_dec.GetField(lsl_unit.at(2),"^",4);
                ls_result = lsl_unit.at(4).trimmed();
                sendResult(ls_itemno,ls_result);
            }
        }
    }

    if (m_sData.indexOf("L|1") >= 0)
    {
        redecode();
    }

    return 0;
}
