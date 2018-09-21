#include "w_eci.h"

#include "eci_setup.h"

W_Eci::W_Eci(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-ECI");

    loadConfig();
}

W_Eci::~W_Eci()
{

}


void W_Eci::loadConfig()
{
    BaseWindow::loadConfig();

    m_nYearPos = readSetting("ECI/yearpos",24).toInt();
    m_nMonthPos = readSetting("ECI/monthpos",26).toInt();
    m_nDayPos = readSetting("ECI/daypos",28).toInt();

    m_nSampleStart = readSetting("ECI/samplenostart",30).toInt();
    m_nSampleLen = readSetting("ECI/samplenolen",15).toInt();

    m_nQcPos = readSetting("ECI/qcpos",65).toInt();

    m_nLongResultMode = readSetting("ECI/longresultmode",1).toInt();
    if (m_nLongResultMode == 0)
    {
        m_nItemStart = readSetting("ECI/itemstart",6).toInt();
        m_nItemLen = readSetting("ECI/itemlen",4).toInt();
        m_nResultStart = readSetting("ECI/resultstart",10).toInt();
        m_nReslultLen = readSetting("ECI/resultlen",9).toInt();
        m_nResultFlagPos = readSetting("ECI/resultflagpos",27).toInt();
    }
    else
    {
        m_nItemStart = readSetting("ECI/itemstart",6).toInt();
        m_nItemLen = readSetting("ECI/itemlen",5).toInt();
        m_nResultStart = readSetting("ECI/resultstart",11).toInt();
        m_nReslultLen = readSetting("ECI/resultlen",9).toInt();
        m_nResultFlagPos = readSetting("ECI/resultflagpos",32).toInt();
    }
}

int W_Eci::decode(QString data)
{
    qint32 li_etx;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;
    QString ls_code;
    QString ls_itemno;
    QString ls_val;
    QString ls_result;

    data = m_dec.CutZeroChar(data);
    m_sData += data;

    li_etx = m_sData.indexOf("\r\n");

    if (li_etx < 0)
    {
        return -1;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 2);
    ls_val = ls_code.trimmed();

    if (ls_val.left(1) == "!")
    {
        if (ls_val.mid(4,1) == "a")
        {
            li_year = ls_val.mid(m_nYearPos - 1, 2).toInt();
            li_month = ls_val.mid(m_nMonthPos - 1, 2).toInt();
            li_day = ls_val.mid(m_nDayPos -2, 2).toInt();

            m_sSampleDate = getSampleDate(li_year,li_month,li_day);
            m_sSampleNo = ls_val.mid(m_nSampleStart - 1, m_nSampleLen);
            m_bIsQc = (ls_val.mid(m_nQcPos - 1, 1) == "T");

//            m_sSampleNo = getSampleNo(m_sSampleNo);
        }
        else if (ls_val.mid(4,1) == "f")
        {
            ls_itemno = ls_val.mid(m_nItemStart - 1, m_nItemLen).trimmed().toUpper();
            ls_result = ls_val.mid(m_nResultStart - 1, m_nReslultLen).trimmed();

            if (ls_result.contains("?") || ls_result.contains("99.99"))
            {
                ls_result = "";
            }
            else
            {
                if (ls_val.mid(m_nResultFlagPos - 1, 1) == "4")
                {
                    ls_result.prepend(">");
                }
                else if (ls_val.mid(m_nResultFlagPos - 1, 1) == "5")
                {
                    ls_result.prepend("<");
                }
            }

            if (m_bIsQc)
            {}
            else
            {
                sendResult(ls_itemno,ls_result);
            }
        }
        else if (ls_val.mid(4,1) == "h")
        {
            m_sSampleNo = "";
        }
    }

    if (m_sData.indexOf("\r\n") >= 0)
    {
        redecode();
    }

    if (m_sData.indexOf("\r\n") >= 0)
    {
        redecode();
    }

    return 0;
}

void W_Eci::on_action_DecodeSetup_triggered()
{
    this->show();
    Eci_Setup *setup = new Eci_Setup(this);
    setup->exec();
}
