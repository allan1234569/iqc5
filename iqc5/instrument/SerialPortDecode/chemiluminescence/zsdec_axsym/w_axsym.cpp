#include "w_axsym.h"

W_Axsym::W_Axsym(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-AXSYM");

    loadConfig();
}

W_Axsym::~W_Axsym()
{

}

void W_Axsym::loadConfig()
{
    BaseWindow::loadConfig();

    m_nItemPos = readSetting("AXSYM/itempos",5).toInt();
    m_nResultPos = readSetting("AXSYM/resultpos",1).toInt();
    m_nResult2Pos = readSetting("AXSYM/result2pos",3).toInt();

}

int W_Axsym::decode(QString data)
{
    QString ls_code;
    QString ls_str;
    QString ls_flag;
    QString ls_result;
    QString ls_item;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;
    qint32 li_pos1;
    qint32 li_pos2;

    m_sData += data;
    li_pos2 = m_sData.indexOf(QString(QChar(EOT)));

    if (li_pos2 < 0)
    {
        return -1;
    }

    li_pos1 = m_sData.indexOf(QString(QChar(ENQ)));
    ls_code = m_sData.mid(li_pos1 + 1, li_pos2 - li_pos1 - 1);
    m_sData = m_sData.mid(li_pos2 + 1);

    li_pos2 = ls_code.indexOf(QString(QChar(ETX)));
    while(li_pos2 >= 0)
    {
        ls_flag = "";
        ls_str = ls_code.left(li_pos2 - 3);
        ls_code = ls_code.mid(li_pos2 + 5);

        if (ls_str.mid(2,1) ==  "O")
        {
            m_sSampleNo = m_dec.GetField(m_dec.GetField(ls_str,"|",4),
                                         "^",
                                         1);

            if (m_sSampleNo.length() > 8)
            {
                if (isDate(m_sSampleNo.left(4) + m_sSampleNo.mid(4,2) + m_sSampleNo.mid(6,2)))
                {
                    m_sSampleNo = m_sSampleNo.mid(8);
                }
            }

            m_sSampleNo = m_sSampleNo.trimmed();

            if (m_sSampleNo.right(2) == "-L")
            {
                m_bIsQc = true;
                m_sSampleNo = "1";
            }
            else if (m_sSampleNo.right(2) == "-M")
            {
                m_bIsQc = true;
                m_sSampleNo = "2";
            }
            else if (m_sSampleNo.right(2) == "-H")
            {
                m_bIsQc = true;
                m_sSampleNo = "3";
            }
            else
            {
                m_bIsQc = false;
            }

            ls_item = m_dec.GetField(m_dec.GetField(ls_str,"|",5),
                                     "^",
                                     m_nItemPos - 1);
            m_sResult = "";
        }
        else if (ls_str.mid(2,1) ==  "R")
        {
            if (m_dec.GetField(ls_str,"|",2).toInt() == m_nResultPos)
            {
                m_sResult = m_dec.GetField(ls_str,"|",4);
                ls_str = m_dec.GetField(ls_str,"|",13);
                li_year = ls_str.mid(0,4).toInt();
                li_month = ls_str.mid(4,2).toInt();
                li_day = ls_str.mid(6,2).toInt();
                m_sSampleDate = getSampleDate(li_year,li_month,li_day);

//                /*********定性结果*********/
//                if (m_sResult.contains(">"))
//                {
//                    ls_flag = "H";
//                }
//                else
//                {
//                    if (m_sResult.contains("<"))
//                    {
//                        ls_flag = "L";
//                    }
//                    else
//                    {
//                        ls_flag = "";
//                    }
//                }

//
//                if (m_sResult.contains("NEGATIVE") || m_sResult.contains("NONREACTIVE"))
//                {
//                    m_sResult = "阴性";
//                    ls_flag = "N";
//                }
//                else
//                {
//                    if (m_sResult.contains("REACTIVE"))
//                    {
//                        m_sResult = "阳性";
//                        ls_flag = "P";
//                    }
//                    else
//                    {
//                        ls_flag = "";
//                    }
//                }

                if (m_bIsQc)
                {

                }
                else
                {
                    sendResult(ls_item,m_sResult);
                }
            }
            else if (m_dec.GetField(ls_str,"|",2).toInt() == m_nResult2Pos)
            {
                ls_result = m_dec.GetField(ls_str,"|",4);
                ls_str = m_dec.GetField(ls_str,"|",13);
                li_year = ls_str.mid(0,4).toInt();
                li_month = ls_str.mid(4,2).toInt();
                li_day = ls_str.mid(6,2).toInt();
                m_sSampleDate = getSampleDate(li_year,li_month,li_day);

//                /*********定性结果*********/
//                if (ls_result.contains(">"))
//                {
//                    ls_flag = "H";
//                }
//                else
//                {
//                    if (ls_result.contains("<"))
//                    {
//                        ls_flag = "<";
//                    }
//                    else
//                    {
//                        ls_flag = "";
//                    }
//                }

//                if (ls_result.contains("NEGATIVE") || ls_result.contains("NONREACTIVE"))
//                {
//                    ls_result = "阴性";
//                    ls_flag = "N";
//                }
//                else
//                {
//                    if (ls_result.contains("REACTIVE"))
//                    {
//                        ls_result = "阳性";
//                        ls_flag = "P";
//                    }
//                    else
//                    {
//                        ls_flag = "";
//                    }
//                }

                if (!m_bIsQc)
                {
                    sendResult(ls_item,ls_result);
                }
            }
        }

        li_pos2 = ls_code.indexOf(QString(QChar(ETX)));
    }

    return 0;
}
