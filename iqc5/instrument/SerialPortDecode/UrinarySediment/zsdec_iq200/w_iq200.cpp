#include "w_iq200.h"

W_Iq200::W_Iq200(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("尿沉渣-IQ200");
}

W_Iq200::~W_Iq200()
{

}

QString W_Iq200::translate(QString as_data)
{
    QByteArray data;
    data.append(as_data);

    return QByteArray::fromHex(data);
}


int W_Iq200::deal_result(QString as_result)
{
    QString ls_date;
    QString ls_item;
    QString ls_result;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;
    qint32 li_stx;
    qint32 li_etx;
    bool lb_mustitem = false;

    if (m_dec.GetSeg(as_result," ID=\"","\"",m_sSampleNo) != 0)
    {
        return 1;
    }

    if (m_dec.GetSeg(as_result," REDTS=\"","\"",ls_date) != 0)
    {
        m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");
    }
    else
    {
        li_year = ls_date.left(4).toInt();
        li_month = ls_date.mid(4,2).toInt();
        li_day = ls_date.mid(6,2).toInt();
        m_sSampleDate = getSampleDate(li_year,li_month,li_day);
    }

    li_stx = as_result.indexOf("<AR Key=\"");

    while (li_stx >= 0)
    {
        as_result = as_result.mid(li_stx + 9);
        li_stx = as_result.indexOf("\"");

        if (li_stx >= 0)
        {
            ls_item = as_result.left(li_stx).trimmed().toUpper();

            li_etx = as_result.indexOf("</AR>");

            if (li_etx  >= 0)
            {
                ls_result = as_result.left(li_etx);
                ls_result = m_dec.reverseStr(ls_result);
            }

            if (    (ls_result == "-") ||
                    (ls_result == "+") ||
                    (ls_result == "+-")||
                    (ls_result == "[none]")
                )
            {
                goto label_0;
            }
            else
            {
                li_etx = ls_result.indexOf(" ");
                if (li_etx >= 0)
                {
                    ls_result = ls_result.left(li_etx);
                }
            }

            sendResult(ls_item,ls_result);
        }

label_0:
        li_stx = as_result.indexOf("<AR Key=\"");
    }
}

void W_Iq200::decode(QString data)
{
    qint32 li_this;
    qint32 li_i;
    qint32 li_cnt;
    qint32 li_stx;
    qint32 li_etx;
    qint32 li_etb;
    QStringList lsl_unit;
    QString ls_code;
    QString ls_data;
    QString ls_line;
    QString ls_result;

    m_sData += data;
    li_etx = m_sData.indexOf(QString(QChar(ETX)));

    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 1);
    lsl_unit = ls_code.split("\r\n");

    for (int i = 0; i < lsl_unit.size(); i++)
    {
        ls_line = lsl_unit[i];
        li_etb = ls_line.indexOf(QString(QChar(ETB)));

        if (li_etb >= 0)
        {
            ls_line = ls_line.left(li_etb);
        }

        li_stx = ls_line.indexOf(QString(QChar(STX)));

        if (li_stx >= 0)
        {
            while (li_stx >= 0)
            {
                ls_line = ls_line.mid(li_stx + 2);
                li_stx = ls_line.indexOf(QString(QChar(STX)));
            }

            ls_line = translate(ls_line);
            ls_result += ls_line;
        }
    }

    deal_result(ls_result);

    if (m_sData.indexOf(QString(QChar(ETX))) >= 0)
    {
        redecode();
    }
}
