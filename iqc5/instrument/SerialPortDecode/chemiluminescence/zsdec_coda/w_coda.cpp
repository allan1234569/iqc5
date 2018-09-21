#include "w_coda.h"

W_Coda::W_Coda(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-CODA");

    loadConfig();
}

W_Coda::~W_Coda()
{

}

void W_Coda::loadConfig()
{
    BaseWindow::loadConfig();
    m_sSampleNoHead = readSetting("CODA/samplenohead","P4").toString();
    m_nSampleNoIndex = m_sSampleNoHead.mid(1).toInt();
    m_sSampleNoHead = m_sSampleNoHead.left(1);

    m_sSampleDateHead = readSetting("CODA/sampledatehead","O23").toString();
    m_nSampleDateIndex = m_sSampleDateHead.mid(1).toInt();
    m_sSampleDateHead = m_sSampleDateHead.left(1);

    m_nResultIndex = readSetting("CODA/resultidx",1).toInt();
}

int W_Coda::decode(QString data)
{
    qint32 li_this;
    qint32 li_next;
    qint32 li_pos;
    QString ls_code;
    QString ls_sampledate;
    QString ls_itemno;
    QString ls_result;
    QString ls_line;
    QStringList lsl_unit;

    m_sData += data;
    li_pos = m_sData.indexOf(QString(QChar(EOT)));

    if (li_pos < 0)
    {
        return -1;
    }

    ls_code = m_sData.left(li_pos);
    m_sData = m_sData.mid(li_pos + 1);

    li_this = ls_code.indexOf(QString(QChar(STX)));
    while(li_this >= 0)
    {
        ls_code.replace(li_this,2,"");
        li_this = ls_code.indexOf(QString(QChar(STX)));
    }

    li_next = ls_code.indexOf(QString(QChar(ETB)));
    while(li_next >= 0)
    {
        ls_code.replace(li_next,5,"");
        li_next = ls_code.indexOf(QString(QChar(ETB)));
    }

    li_this = ls_code.indexOf(QString(QChar(ENQ)));
    while(li_this >= 0)
    {
        ls_code = ls_code.mid(li_this + 1);
        li_this = ls_code.indexOf(QString(QChar(ENQ)));
    }


    m_bIsQc = false;
    m_bIsStat = false;

    lsl_unit = ls_code.split("\r");

    for(int i = 0; i < lsl_unit.size(); i++)
    {
        ls_line = lsl_unit.at(i);
        li_pos = ls_line.indexOf("|");

        if (li_pos >= 0)
        {
            if (ls_line.left(li_pos - 1).right(1) == "P")
            {
                if (m_sSampleNoHead == "P")
                {
                    m_sSampleNo = m_dec.GetField(ls_line,"|",m_nSampleNoIndex);
                }
            }
            else if (ls_line.left(li_pos - 1).right(1) == "O")
            {
                if (m_sSampleDateHead == "O")
                {
                    ls_sampledate = m_dec.GetField(ls_line,"|",m_nSampleDateIndex).trimmed();
                    m_sSampleDate = getSampleDate(ls_sampledate.left(4).toInt(),
                                                  ls_sampledate.mid(4,2).toInt(),
                                                  ls_sampledate.mid(6,2).toInt());
                }

                if (m_sSampleDateHead == "O")
                {
                    m_sSampleNo = m_dec.GetField(ls_line,"|",m_nSampleNoIndex);
                }

                m_bIsStat = (m_dec.GetField(ls_line,"|",6) == "S");
                m_bIsQc = (m_dec.GetField(ls_line,"|",12) == "Q");
            }
            else if (ls_line.left(li_pos - 1).right(1) == "R")
            {
                if (m_sSampleNoHead == "R")
                {
                    ls_sampledate = m_dec.GetField(ls_line,"|",m_nSampleDateIndex).trimmed();
                    m_sSampleDate = getSampleDate(ls_sampledate.left(4).toInt(),
                                                  ls_sampledate.mid(4,2).toInt(),
                                                  ls_sampledate.mid(6,2).toInt());
                }

                ls_itemno = m_dec.GetField(ls_line,"|",3);
                ls_result = m_dec.GetField(ls_line,"|",4);
                ls_result = m_dec.GetField(ls_result,"^",m_nResultIndex);
                sendResult(ls_itemno,ls_result);
            }
        }
    }

    if (m_sData.indexOf(QString(QChar(EOT))) >= 0)
    {
        redecode();
    }

    return 0;
}
