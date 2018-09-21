#include "w_md550.h"

W_Md550::W_Md550(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-MD550");

    loadConfig();
}

W_Md550::~W_Md550()
{

}

void W_Md550::loadConfig()
{
    BaseWindow::loadConfig();

    m_sItems = readSetting("MD550/items","K,NA,CL,iCa,nCa,TCa,PH").toString();
    m_slItems = m_sItems.split(",");

    m_bAutoEtx = readSetting("MD550/autoetx",false).toBool();
    m_sIsEtx = readSetting("MD550/is_etx","$&").toString();
    m_sIsStx = readSetting("MD550/is_stx","#$").toString();

    m_nSampleNoPos = readSetting("MD550/samplenopos",1).toInt();
    m_nSampleNolen = readSetting("MD550/samplenolen",3).toInt();
    m_nSampleDatePos = readSetting("MD550/samplenopos",7).toInt();
    m_nSampleDateLen = readSetting("MD550/samplenopos",15).toInt();

}

void W_Md550::decode(QString data)
{
    QString ls_code;
    QStringList lsl_unit;

    qint32 li_etx;
    qint32 li_pos;

    m_sData += data;
    li_etx = m_sData.indexOf(m_sIsEtx);

    if (li_etx < 0)
    {
        if (!m_bAutoEtx)
        {
            return;
        }

        if (m_sData.length() <= 0)
        {
            return;
        }

        li_etx = m_sData.length();

        if (li_etx < 49)
        {
            return;
        }

        m_sData = m_sData + QString(m_sIsEtx);
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + m_sIsEtx.length());

    if (m_sIsEtx.length() > 0)
    {
        li_pos = ls_code.mid(li_pos + m_sIsEtx.length());

        while (li_pos >= 0)
        {
            ls_code = ls_code.mid(li_pos + m_sIsEtx.length());
            li_pos = ls_code.indexOf(m_sIsEtx);
        }
    }

    m_sSampleNo = ls_code.mid(m_nSampleNoPos - 1,m_nSampleNolen);
    m_sSampleDate = m_dec.GetDateByFormat(ls_code.mid(m_nSampleDatePos - 1, m_nSampleDateLen),"YYYYMMDDhhmmss").date().toString("yyyy-MM-dd");

    ls_code = ls_code.mid(m_nSampleDatePos - 1 + m_nSampleDateLen).trimmed();
    lsl_unit = ls_code.split(" ");

    for(int i = 0; i < lsl_unit.size(); i++)
    {
        if (i > m_slItems.size())
        {
            break;
        }

        sendResult(m_slItems[i],lsl_unit[i];
    }

    if (m_sData.indexOf(m_sIsEtx) >= 0)
    {
        redecode();
    }
}
