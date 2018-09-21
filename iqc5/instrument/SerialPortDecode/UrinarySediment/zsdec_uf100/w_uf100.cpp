
#include "w_uf100.h"

W_UF100::W_UF100(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("酶免仪-UF100");

    m_bNoGraph = true;

    loadConfig();
}

W_UF100::~W_UF100()
{

}

void W_UF100::transResult()
{
    qint32 li_startpos;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;
    qint32 li_sub;
    qint32 li_len;
    qint32 li_pos;
    QString ls_result;

    if (m_sTotal.mid(2,2) == "41")
    {
        m_sDcdMode = "1";
    }
    else
    {
        m_sDcdMode = "2";
    }

    if (m_sDcdMode == "1")
    {
        m_sSampleNo = m_sTotal.mid(27,15);
    }
    else
    {
        m_sSampleNo = m_sTotal.mid(25,13);
    }

    li_sub = readSetting("UF100/samplenostart",27).toInt();
    li_len =readSetting("UF100/samplenolen",15).toInt();

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

    li_startpos = m_sTotal.indexOf("QC");

    if (li_sub >= 0 && li_len >= 0)
    {
        m_sSampleNo = m_sTotal.mid(li_startpos + li_sub - 1, li_len);
        writeSetting("UF100/lastsamplenotext",m_sTotal.mid(li_startpos + li_sub - 1, 50));
    }

    li_pos = m_sSampleNo.indexOf("000000");
    if (li_pos >= 0)
    {
        m_sSampleNo = m_sSampleNo.mid(li_pos);
    }

    li_pos = m_sSampleNo.lastIndexOf(" ");

    if (li_pos >= 0)
    {
        m_sSampleNo = m_sSampleNo.left(li_pos);
    }

    li_year = m_sTotal.mid(li_startpos + 8, 2).toInt();
    li_month = m_sTotal.mid(li_startpos + 10, 2).toInt();
    li_day = m_sTotal.mid(li_startpos + 12, 2).toInt();

    m_sSampleDate = getSampleDate(li_year,li_month,li_day);

    if (!m_bIsQc)
    {
        m_vItemCode.push_back("COND");

        if (m_sDcdMode == "1")
        {
            m_vItemValue.push_back(QString::number(m_sTotal.mid(50, 4).toInt()));
        }
        else
        {
             m_vItemValue.push_back(QString::number(m_sTotal.mid(46, 4).toInt()));
        }
        m_nTotalItem++;

        m_vItemCode.push_back("TOTAL");
        if (m_sDcdMode == "1")
        {
            m_vItemValue.push_back(QString::number(m_sTotal.mid(90, 6).toInt()));
        }
        else
        {
            m_vItemValue.push_back(QString::number(m_sTotal.mid(86, 6).toInt()));
        }
        m_nTotalItem++;

        m_vItemCode.push_back("RBCI");
        if (m_sDcdMode == "1")
        {
            ls_result = QString::number(m_sTotal.mid(49,1).toDouble());
        }
        else
        {
            ls_result = QString::number(m_sTotal.mid(46,1).toDouble());
        }

        m_vItemValue.push_back(ls_result);
        m_nTotalItem++;
    }

    for (int i = 0; i < m_nTotalItem; i++)
    {
        if (!m_bIsQc)
        {
            sendResult(m_vItemCode[i],m_vItemValue[i]);
        }
    }
}

void W_UF100::loadConfig()
{
    BaseWindow::loadConfig();

//    m_bNoGraph = (readSetting("UF100/nograph","0").toString() == "1");
    m_sEndBlock = readSetting("UF100/endblock","DE").toString();
}

void W_UF100::decode(QString data)
{
    QString ls_code;
    qint32 li_stx;
    qint32 li_etx;
    qint32 li_itemcount;

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
        m_bResultTok = false;
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

        if (m_bNoGraph)
        {
            if (m_sTotal.length() > 550)
            {
                m_bIsEnd = true;
            }
        }
    }
    else if (ls_code.mid(0,2).toUpper() == "DC")
    {
        m_sTotal += ls_code;
        m_sData = m_sData.mid(li_etx + 1);
    }
    else if (ls_code.mid(0,2).toUpper() == "DI")
    {
        m_sTotal += ls_code;

        if (m_bResultFirst)
        {
            if (!m_bResultTok)
            {
                transResult();
                m_bResultTok = true;
            }
        }

        m_sData = m_sData.mid(li_etx + 1);
    }
    else if (ls_code.mid(0,2).toUpper() == "D1")
    {
        if (ls_code.mid(2,1) == "C")
        {
            //QC相关处理，忽略

            m_bIsQc = true;
            m_sTotal = "";
            m_sData = m_sData.mid(li_etx);
            goto label_0;
        }
        else
        {
            m_sTotal += ls_code;
            m_sData = m_sData.mid(li_etx + 1);
        }
    }
    else if (ls_code.mid(0,2).toUpper() == "DE")
    {
        m_sTotal += ls_code;
        m_bIsEnd = true;
        m_sData = m_sData.mid(li_etx + 1);
    }
    else
    {
        m_sTotal += ls_code;
        m_sData = m_sData.mid(li_etx + 1);
    }

    if (m_sEndBlock == ls_code.left(2).toUpper())
    {
        m_bIsEnd = true;
    }

    if (m_bIsEnd)
    {
        if (!m_bResultFirst)
        {
            transResult();
        }

        m_sTotal = "";
        m_nTotalItem = 0;
    }

label_0:
    if (m_sData.indexOf(QString(QChar(ETX))) >= 0)
    {
        redecode();
    }

}
