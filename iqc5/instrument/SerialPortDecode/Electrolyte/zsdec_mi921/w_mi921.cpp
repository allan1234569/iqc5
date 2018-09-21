#include "w_mi921.h"

W_Mi921::W_Mi921(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-MI921");

    m_bAutoCrLf = false;

    m_bLastHaveData = false;

    loadConfig();
}

W_Mi921::~W_Mi921()
{

}

void W_Mi921::loadConfig()
{
    BaseWindow::loadConfig();

    m_sItems = readSetting("MSI921/items","K,NA,CL,iCa,PH,AB").toString();
    m_slItems = m_sItems.split(",");

    m_bAutoCrLf = readSetting("MSI921/autocrlf",0).toBool();

}

void W_Mi921::decode(QString data)
{
    QString ls_code;
    QString ls_result;

    qint32 li_etx;
    qint32 li_pos;
    qint32 li_i;

    if (m_bAutoCrLf)
    {
        decode_autoCrLf(data);
    }

    m_sData += data;
    li_etx = m_sData.indexOf("\r");

    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx).trimmed();
    m_sData = m_sData.mid(li_etx + 1);

    li_pos = ls_code.indexOf(QChar(LF));

    while (li_pos >= 0)
    {
        ls_code = ls_code.mid(li_pos + 1);
        li_pos = ls_code.indexOf(QChar(LF));
    }

    li_pos = ls_code.indexOf(QChar(ETX));

    while (li_pos >= 0)
    {
        ls_code = ls_code.mid(li_pos + 1);
        li_pos = ls_code.indexOf(QChar(ETX));
    }

    ls_code = ls_code.trimmed();
    li_pos = ls_code.indexOf(" ");

    if (li_pos >= 0)
    {
        m_sSampleNo = ls_code.left(li_pos);
        ls_code = ls_code.mid(li_pos + 1).trimmed() + " ";

//        使用样本ID做样本号暂留
//        li_pos = ls_code.indexOf(" ");
//        ls_sampleid = ls_code.left(li_pos);
//        m_sSampleNo = ls_sampleid;
//        ls_code = ls_code.mid(li_pos).trimmed();

        m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");

        while (li_pos >= 0)
        {
            ls_result = ls_code.left(li_pos);
            li_i++;

            if (li_i > m_slItems.size())
            {
                break;
            }

            if (!m_slItems[li_i - 1].isEmpty())
            {
                sendResult(m_slItems[li_i],ls_result);
                ls_code = ls_code.mid(li_pos + 1).trimmed() + " ";
                li_pos = ls_code.indexOf(" ");
            }
        }
    }

    if (m_sData.indexOf("\n") >= 0)
    {
        redecode();
    }
}

void W_Mi921::decode_autoCrLf(QString data)
{   //该函数待完善
    qint32 li_etx;
    qint32 li_pos;
    QString ls_code;
    QString ls_result;

    if (data.length() > 0)
    {
        m_bLastHaveData = true;
    }
    else
    {
        if (m_bLastHaveData)
        {
            m_sData += QString("\r\n");
        }

        m_bLastHaveData = false;
    }

    li_etx = m_sData.indexOf("\r\n");

    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx).trimmed();
    m_sData = m_sData.mid(li_etx + 2);

label_0:
    m_sData = m_sData.trimmed()+ "\r\n";
    li_pos = ls_code.indexOf(" ");

    if (li_pos >= 0)
    {
        m_sSampleNo = ls_code.left(li_pos);
        m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");
        ls_code = ls_code.mid(li_pos + 1).trimmed() + " ";
        li_pos = ls_code.indexOf(" ");

        int i = 0;

        while(li_pos >= 0)
        {
            ls_result = ls_code.left(li_pos);
            i++;

            if(i > m_slItems.size())
            {
                break;
            }

            sendResult(m_slItems.at(i - 1),ls_result);
            ls_code = ls_code.mid(li_pos + 1);

            if(i >= m_slItems.size())
            {
                goto label_0;
            }

            li_pos = ls_code.indexOf(" ");
        }
    }

    if (m_sData.indexOf("\r\n") >= 0)
    {
        decode(m_sData);
    }

}
