#include "w_epalyzer2.h"

W_Epalyzer2::W_Epalyzer2(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电泳仪-泳霸EPALYZER2");

    loadConfig();
}

W_Epalyzer2::~W_Epalyzer2()
{

}

void W_Epalyzer2::loadConfig()
{
    m_nSampleNoStart = readSetting("EPALYZER2/samplenostart",20).toInt();
    m_nSampleNoLen = readSetting("EPALYZER2/samplenolen",6).toInt();

    m_nSampleDateStart = readSetting("EPALYZER2/sampledatestart",36).toInt();
    m_nSampleDateLen = readSetting("EPALYZER2/sampledatelen",8).toInt();

    m_nResultSegStart = readSetting("EPALYZER2/resultsegstart",85).toInt();
    m_nResultSegLen = readSetting("EPALYZER2/resultseglen",28).toInt();

    m_nItemStart = readSetting("EPALYZER2/itemtart",9).toInt();
    m_nItemLen = readSetting("EPALYZER2/itemlen",6).toInt();

    m_nResultStart = readSetting("EPALYZER2/resultstart",22).toInt();
    m_nResultLen = readSetting("EPALYZER2/resultlen",7).toInt();
}

void W_Epalyzer2::decode(QString data)
{
    m_sData += data;

    QString ls_code;
    QString ls_item;
    QString ls_result;
    QString ls_seg;
    int li_stx;
    int li_etx;
    int li_etb;

    li_etx = m_sData.indexOf(QString(QChar(ETX)));

    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 1);

    li_stx = ls_code.indexOf(QString(QChar(STX)));

    while(li_stx >= 0)
    {
        ls_code = ls_code.mid(li_stx + 1);
        li_stx = ls_code.indexOf(QString(QChar(STX)));
    }

    m_sSampleNo = ls_code.mid(m_nSampleNoStart - 1, m_nSampleNoLen);
    m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");

    ls_code = ls_code.mid(m_nResultSegStart - 1);

    while(ls_code.length() >= m_nResultSegLen)
    {
        ls_seg = ls_code.left(m_nResultSegLen);
        ls_code = ls_code.mid(m_nResultSegLen);
        ls_item = ls_seg.mid(m_nItemStart - 1,m_nItemLen).trimmed();
        ls_result = ls_seg.mid(m_nResultStart - 1, m_nResultLen);

        if (!ls_item.isEmpty())
        {
            sendResult(ls_item,ls_result);
        }
    }

    if (m_sData.indexOf(QString(QChar(ETX))) >= 0)
    {
        redecode();
    }

}
