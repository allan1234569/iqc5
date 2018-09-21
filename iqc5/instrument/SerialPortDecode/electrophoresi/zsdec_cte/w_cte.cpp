#include "w_cte.h"

W_Cte::W_Cte(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电泳仪-CTE");

    m_nItemCnt = 0;

    loadConfig();
}

W_Cte::~W_Cte()
{

}

int W_Cte::getStx()
{
    int li_len;
    QString ls_str;

    li_len = m_sData.length() - m_nBlockSize + 10;

    for(int i = 0; i < li_len; i++)
    {
        if (m_sData.left(1) == QString(QChar(STX)))
        {
            ls_str = m_sData.mid(i,6);

            if (ls_str.length() < 6)
            {
                continue;
            }

            ls_str = QDate::currentDate().toString().left(2) + ls_str.left(2) + "/" + ls_str.mid(2,2) + "/" + ls_str.mid(4,2);

            if (!QDate::fromString(ls_str,"yyyy/MM/dd").isValid())
            {
                continue;
            }

            return i;
        }
    }

    return -1;
}

int W_Cte::getEtx()
{
    int li_len;
    int li_i;

    if (m_sData.mid(m_nBlockSize-1,1) == QString(QChar(ETX)))
    {
        return (m_nBlockSize - 1);
    }

    li_len = m_sData.length();
    li_i = m_nBlockSize - 10;

    while(li_i <= li_len)
    {
        if (m_sData.mid(li_i - 1, 1) == QString(QChar(ETX)))
        {
            return (li_i - 1);
        }
        li_i++;
    }

    return -1;
}

void W_Cte::loadConfig()
{
    QString ls_item;
    QString ls_str;
    QStringList lsl_data;

    BaseWindow::loadConfig();

    m_nBlockSize = readSetting("CTE/blockSize", 640).toInt();
    m_nSampleNoStart = readSetting("CTE/samplenostart",8).toInt();
    m_nSampleNoLength = readSetting("CTE/samplenolen",4).toInt();

    for(int i = 1;; i++)
    {
        ls_item = QString("CTE/item%1").arg(i);
        ls_str = readSetting(ls_item.toStdString().data(),"").toString();

        if (ls_str.isEmpty() || ls_str.trimmed().isEmpty())
        {
            break;
        }
        else
        {
            lsl_data = ls_str.split(",");
            if(lsl_data.size() == 2)
            {
                m_slItems[i] = lsl_data[0];
                m_slItempos[i] = lsl_data[1];
                m_nItemCnt = i;
            }
            else
            {
                continue;
            }
        }
    }
}

void W_Cte::decode(QString data)
{
    m_sData += data;

    int li_stx;
    int li_etx;
    QString ls_code;
    QString ls_result;

    if (m_sData.length() < m_nBlockSize)
    {
        return;
    }

    li_stx = getStx();

    if (li_stx < 0)
    {
        return;
    }

    m_sData = m_sData.mid(li_stx + 1);
    li_etx = getEtx();

    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 1);

    m_sSampleNo = ls_code.mid(m_nSampleNoStart-1, m_nSampleNoLength).trimmed();

    for(int i = 1; i < m_nItemCnt; i++)
    {
        ls_result = ls_code.mid(m_slItempos[i].toInt(),5).trimmed();

        if (isNumber(ls_result))
        {
            ls_result = QString::number(ls_result.toInt());
        }

        if (i > 5)
        {
            if(ls_result.toInt() == 0)
            {
                continue;
            }

            sendResult(m_slItems[i],ls_result);
        }
    }
}
