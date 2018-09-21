#include "w_spife.h"

W_Spife::W_Spife(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电泳仪-SPIFE");

    loadConfig();
}

W_Spife::~W_Spife()
{

}

void W_Spife::loadConfig()
{
    BaseWindow::loadConfig();

    m_nNoMode = readSetting("SPIFE/sampleno","4 ID号").toInt();
    if (m_nNoMode <= 0)
    {
        m_nNoMode = 4;
    }
    m_sResultMode = readSetting("SPIFE/result","%").toString();
}

void W_Spife::decode(QString data)
{
    m_sData += data;

    int li_this;
    QStringList lsl_pat;
    QString ls_code;
    QString ls_line;

    li_this = m_sData.indexOf(QString("\n") + "L|1");

    if (li_this < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_this);
    m_sData = m_sData.mid(li_this + 3);
    lsl_pat = ls_code.split("\r");

    for(int i = 0; i < lsl_pat.size(); i++)
    {
        ls_line = lsl_pat.at(i);

        if (ls_line.left(1) == "P")
        {
            m_sSampleNo = m_dec.GetField(ls_line,"|",m_nNoMode);
        }
        else if (ls_line.left(1) == "R")
        {
            deal_result(ls_line);
        }
    }

    if (m_sData.indexOf(QString("\r") + "L|1") >= 0)
    {
        redecode();
    }
}

void W_Spife::deal_result(QString as_str)
{
    QString ls_date;
    QString ls_itemalis;
    QString ls_result;
    QString ls_sign;

    int li_year;
    int li_month;
    int li_day;

    ls_date = m_dec.GetField(as_str,"|",12);
    li_year = ls_date.left(4).toInt();
    li_month = ls_date.mid(4,2).toInt();
    li_day = ls_date.mid(6,2).toInt();

    m_sSampleDate = QDate(li_year,li_month,li_day).toString("yyyy-MM-dd");
    ls_itemalis = m_dec.GetField(as_str,"|",3);
    ls_sign = m_dec.GetField(ls_itemalis,"^",6).trimmed();
    ls_itemalis = m_dec.GetField(ls_itemalis,"^",5).trimmed();

    if (ls_itemalis.isEmpty())
    {
        return;
    }

    if ((ls_sign == m_sResultMode) || ls_sign.isEmpty())
    {
        ls_result = m_dec.GetField(as_str,"|",4);
        sendResult(ls_itemalis,ls_result);
    }
}
