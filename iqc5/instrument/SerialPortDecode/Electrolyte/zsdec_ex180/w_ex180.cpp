#include "w_ex180.h"

W_Ex180::W_Ex180(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-Ex180");

    loadConfig();
}

W_Ex180::~W_Ex180()
{

}

void W_Ex180::loadConfig()
{
    BaseWindow::loadConfig();

    m_nYearStart = readSetting("EX180/yearstart",1).toInt();
    m_nYearLen = readSetting("EX180/yearlen",2).toInt();

    m_nMonthStart = readSetting("EX180/monthstart",3).toInt();
    m_nMonthLen = readSetting("EX180/monthlen",2).toInt();

    m_nDayStart = readSetting("EX180/daystart",5).toInt();
    m_nDayLen = readSetting("EX180/daylen",2).toInt();

    m_nSampleNoStart = readSetting("EX180/samplenostart",13).toInt();
    m_nSampleNoLen = readSetting("EX180/samplenolen",4).toInt();

    m_nNaStart = readSetting("EX180/na_start",21).toInt();
    m_nNaLen = readSetting("EX180/na_len",8).toInt();

    m_nKStart = readSetting("EX180/k_start",31).toInt();
    m_nKLen = readSetting("EX180/k_len",7).toInt();

    m_nClStart = readSetting("EX180/cl_start",39).toInt();
    m_nClLen = readSetting("EX180/cl_len",6).toInt();
}

void W_Ex180::decode(QString data)
{


    qint32 li_stx;
    qint32 li_etx;

    QString ls_code;
    QString ls_year;
    QString ls_month;
    QString ls_day;
    QString ls_result;

    li_etx = m_sData.indexOf(QChar(ETX));

    if(li_etx < 0)
    {
        return;
    }

    m_sData += data;
    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 1);

    li_stx = ls_code.indexOf(QChar(STX));

    while(li_stx >= 0)
    {
        ls_code = ls_code.mid(li_stx + 1);
        li_stx = ls_code.indexOf(QChar(STX));
    }

    ls_year = ls_code.mid(m_nYearStart-1,m_nYearLen);
    ls_month = ls_code.mid(m_nMonthStart-1,m_nMonthLen);
    ls_day = ls_code.mid(m_nDayStart-1,m_nDayLen);
    m_sSampleResultDateTime = QDate(ls_year.toInt(),ls_month.toInt(),ls_day.toInt()).toString("yyyy-MM-dd") + QTime::currentTime().toString("hh:mm:ss");
    m_sSampleNo = ls_code.mid(m_nSampleNoStart-1,m_nSampleNoLen);

    ls_result = ls_code.mid(m_nNaStart-1,m_nNaLen).trimmed();
    sendResult("NA",ls_result);

    ls_result = ls_code.mid(m_nKStart-1,m_nKLen).trimmed();
    sendResult("K",ls_result);

    ls_result = ls_code.mid(m_nClStart-1,m_nClLen).trimmed();
    sendResult("CL",ls_result);

    if (m_sData.indexOf(QChar(ETX)) >= 0)
    {
        redecode();
    }
}

