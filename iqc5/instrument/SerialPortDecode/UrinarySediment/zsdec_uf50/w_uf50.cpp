#include "w_uf50.h"

W_UF50::W_UF50(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("酶免仪-UF50");
}

W_UF50::~W_UF50()
{

}

void W_UF50::decode(QString data)
{
    QString ls_code;
    QString ls_result;
    qint32 li_stx;
    qint32 li_etx;
    qint32 li_itemcount;
    qint32 li_startpos;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;

    m_sData += data;
    li_etx = m_sData.indexOf(QString(QChar(ETX)));

    if (li_etx < 0)
    {
        return;
    }

    li_stx = m_sData.indexOf(QString(QChar(STX)));
    ls_code = m_sData.mid(li_stx + 1, li_etx - li_stx - 1);

    if (ls_code.mid(0,2).toUpper() == "DS")
    {
        m_bIsEnd = false;
        m_sTotal = "";
        m_sTotal += ls_code;
        m_sData = m_sData.mid(li_etx + 1);
    }
    else if (ls_code.mid(0,2).toUpper() == "DP")
    {
        m_sTotal += ls_code;
        li_itemcount = ls_code.mid(8,2).toInt();

        for (int i = 0; i < li_itemcount; i++)
        {
            m_vItemCode.push_back(m_sData.mid(1 + 10 + 12 * i, 4).toUpper());
            m_vItemValue.push_back(QString::number(m_sData.mid(1 + 14 + 12 * i, 8).toDouble()));
            m_nTotalItem++;
        }

        m_sData = m_sData.mid(li_etx + 1);
    }
    else if (ls_code.mid(0,2).toUpper() == "DC")
    {
        m_sTotal += ls_code;
        m_sData = m_sData.mid(li_etx + 1);

    }
    else if (ls_code.mid(0,2).toUpper() == "DI")
    {
        m_sTotal += ls_code;
        m_sData = m_sData.mid(li_etx + 1);
    }
    else if (ls_code.mid(0,2).toUpper() == "D1C")
    {
        m_sTotal += ls_code;
        m_sData = m_sData.mid(li_etx + 1);
    }
    else if (ls_code.mid(0,2).toUpper() == "DE")
    {
        m_sTotal += ls_code;
        m_sData = m_sData.mid(li_etx + 1);
        m_bIsEnd = true;
    }
    else
    {
        m_sTotal += ls_code;
        m_sData = m_sData.mid(li_etx + 1);
    }

    if (m_bIsEnd)
    {
        if (m_sTotal.contains("DS"))
        {
            m_bIsQc = false;
        }
        else
        {
            if (m_sTotal.contains("D1C"))
            {
                m_bIsQc = true;
            }
        }

        li_startpos = m_sTotal.indexOf("DS");
        m_sSampleNo = m_sTotal.mid(li_startpos  + 27, 15);
        m_bIsQc = m_sSampleNo.contains("QC");
        li_year = m_sTotal.mid(li_startpos + 9, 2).toInt();
        li_month = m_sTotal.mid(li_startpos + 11, 2).toInt();
        li_day = m_sTotal.mid(li_startpos + 13, 2).toInt();

        m_sSampleDate = getSampleDate(li_year,li_month,li_day);

        if (!m_bIsQc)
        {
            m_vItemCode.push_back("COND");
            m_vItemValue.push_back(QString::number(m_sData.mid(50,4).toDouble()));
            m_nTotalItem++;

            m_vItemCode.push_back("TOTAL");
            m_vItemValue.push_back(QString::number(m_sData.mid(90,6).toDouble()));
            m_nTotalItem++;


//            m_vItemCode.push_back("RBCI");
//            ls_result = QString::number(m_sTotal.mid(49,1).toDouble());
//            m_vItemValue.push_back(getRbcInfo(ls_result));
//            m_nTotalItem++;
        }

        for (int i = 0; i < m_nTotalItem; i++)
        {
            if (!m_bIsQc)
            {
                sendResult(m_vItemCode[i],m_vItemValue[i]);
            }
        }
    }

    if (m_sData.indexOf(QString(QChar(ETX))) >= 0)
    {
        return;
    }
}
