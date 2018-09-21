#include "w_dsi905.h"

W_Dsi905::W_Dsi905(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-DSI905");

    loadConfig();
}

W_Dsi905::~W_Dsi905()
{

}

void W_Dsi905::decode(QString data)
{
    m_sData += data;

    QString ls_code;

    qint32 li_pos;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;

    li_pos = m_sData.indexOf(QChar(SUB));

    if (li_pos < 0)
    {
        return;
    }

    QDate date = QDate::currentDate();

    ls_code = m_sData.left(li_pos);
    m_sData = m_sData.mid(li_pos + 1);

    li_year = date.year();
    li_month = ls_code.left(2).toInt();
    li_day = ls_code.mid(2,2).toInt();

    if ((li_month > date.month()) || (li_month = date.month() &&    li_day > date.day()))
    {
        li_year--;
    }

    m_sSampleResultDateTime = QDate(li_year,li_month,li_day).toString("yyyy-MM-dd") + " " + QTime::currentTime().toString("hh:mm:ss");

    m_sSampleNo = ls_code.mid(m_nSampleNoStart-1,m_nSampleNoLen).trimmed();

    sendResult("K",ls_code.mid(15,1) + "." + ls_code.mid(16,2));
    sendResult("NA",ls_code.mid(19,3) + "." + ls_code.mid(22,1));
    sendResult("CL",ls_code.mid(24,3) + "." + ls_code.mid(27,1));
    sendResult("Ca",ls_code.mid(29,1) + "." + ls_code.mid(30,2));
    sendResult("nCa",ls_code.mid(33,1) + "." + ls_code.mid(34,2));
    sendResult("pH",ls_code.mid(37,1) + "." + ls_code.mid(38,2));

    if (m_sData.indexOf(QChar(SUB)) >= 0)
    {
        redecode();
    }
}

void W_Dsi905::loadConfig()
{
    BaseWindow::loadConfig();

    m_nSampleNoStart = readSetting("DSI905/samplenostart",10).toInt();
    m_nSampleNoLen = readSetting("DSI905/samplelen",5).toInt();

}
