#include "w_ac980.h"

W_AC980::W_AC980(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-AC980");
    loadConfig();
}

W_AC980::~W_AC980()
{

}

void W_AC980::decode(QString data)
{
    m_sData += data;

    QString ls_code;
    qint32 li_etx;
    qint32 li_stx;
    quint32 li_codeLen;

    li_etx = m_sData.indexOf(QChar(ETX));

    if (li_etx < 0)
    {
        m_db.close();
        return;
    }

    ls_code = m_sData.left(li_etx);
    li_codeLen = ls_code.length();
    m_sData = m_sData.mid(li_etx+1);
    li_stx = ls_code.indexOf(QChar(STX));

    while(li_stx >= 0)
    {
        ls_code = ls_code.mid(li_stx+1);
        li_stx = ls_code.indexOf(QChar(STX));
    }

    m_sSampleNo = ls_code.mid(m_nSampleNoStart-1,m_nSampleNoLen);

    ls_code = ls_code.mid(m_nSampleNoStart - 1 + m_nSampleNoLen);

    sendItemResult(ls_code,"K");
    sendItemResult(ls_code,"Na");
    sendItemResult(ls_code,"Cl");
    sendItemResult(ls_code,"Ca");

    m_nHandledSize += li_codeLen;
    writeSetting("handledsize",m_nHandledSize);

    if (m_sData.indexOf(QChar(ETX)) >= 0)
    {
        redecode();
    }
    else
    {
        m_db.close();
    }
}

void W_AC980::loadConfig()
{
    BaseWindow::loadConfig();
    m_nSampleNoStart = readSetting("AC980/samplenostart",20).toInt();
    m_nSampleNoLen = readSetting("AC980/samplenolen",5).toInt();
}
