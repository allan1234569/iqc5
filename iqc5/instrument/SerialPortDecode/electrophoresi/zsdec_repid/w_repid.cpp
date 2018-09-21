#include "w_repid.h"

W_Repid::W_Repid(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电泳仪-REPID");

    loadConfig();
}

W_Repid::~W_Repid()
{

}

void W_Repid::loadConfig()
{
    QString ls_str;
    QString ls_key;

    BaseWindow::loadConfig();

    m_sSampleNo = QDate::currentDate().toString("yyyy-MM-dd");

    int i = 0;
    while(true)
    {
        ls_key = QString("REPID/item%1").arg(i+1);
        ls_str = readSetting(ls_key.toStdString().data(),"").toString();

        if (ls_str.isEmpty())
        {
            break;
        }

        m_slItems[i] = ls_str;
    }
}

void W_Repid::decode(QString data)
{
    m_sData += data;

    int li_stx;
    int li_etx;
    int li_pos;
    int li_year;
    int li_month;
    int li_day;
    int li_i = 0;
    QString ls_code;
    QString ls_result;
    QString ls_result1;
    QString ls_item;
    QString ls_temp;
    QString ls_sampleDate;
    QStringList lsl_string;

    li_stx = m_sData.indexOf(QString(QChar(STX)));

    if (li_stx < 0)
    {
        return;
    }

    li_etx = m_sData.indexOf(QString(QChar(ETX)));
    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.mid(li_stx + 2,li_etx - li_stx - 1);
    m_sData = m_sData.mid(li_etx + 1);

    ls_code = ls_code.trimmed();
    li_pos = ls_code.indexOf(" 20 ");
    ls_temp = ls_code.left(li_pos).trimmed();
    ls_code = ls_code.mid(li_pos + 4).trimmed();
    li_pos = ls_temp.indexOf(" ");
    m_sSampleNo = ls_temp.left(li_pos);
    ls_sampleDate = ls_temp.mid(li_pos);
    li_year = ls_sampleDate.left(4).toInt();
    li_month = ls_sampleDate.mid(4,2).toInt();
    li_day = ls_sampleDate.mid(6,2).toInt();
    m_sSampleDate = QDate(li_year,li_month,li_day).toString("yyyy-MM-dd");

    while(true)
    {
        li_pos = ls_code.indexOf(QString(QChar(49)));

        if (li_pos < 0)
        {
            break;
        }

        ls_code = ls_code.mid(li_pos + 1).trimmed();
        li_pos = ls_code.indexOf(" 20 ");

        if (li_pos < 0)
        {
            break;
        }

        ls_result = ls_code.left(li_pos);
        sendResult(m_slItems[li_i],ls_result);
        ls_code = ls_code.mid(li_pos + 3);
        li_i++;
    }

    if (m_sData.indexOf(QString(QChar(STX))) >= 0)
    {
        redecode();
    }
}
