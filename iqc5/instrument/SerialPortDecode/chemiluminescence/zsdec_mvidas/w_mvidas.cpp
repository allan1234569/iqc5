#include "w_mvidas.h"

W_Mvidas::W_Mvidas(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-MVIDAS");
}

W_Mvidas::~W_Mvidas()
{

}

int W_Mvidas::decode(QString data)
{
    QString ls_itemno;
    QString ls_result;
    QString ls_data;
    QString ls_code;
    QString ls_resultql;
    QString ls_key;
    qint32 li_stx;
    qint32 li_etx;
    qint32 li_slp;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;
    qint32 li_pos;

    m_sData += data;
    li_etx = ls_data.indexOf(QString(QChar(EOT)));

    if (li_etx < 0)
    {
        return -1;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 1);
    li_stx = ls_code.indexOf(QString(QChar(STX)));

    if (li_stx < 0)
    {
        return -1;
    }

    ls_code = ls_code.mid(li_stx + 1);

    while(ls_code != "")
    {
        li_pos = ls_code.indexOf("|");
        if (li_pos < 0)
        {
            ls_data = ls_code;
            ls_code = "";
        }
        else
        {
            ls_data = ls_code.left(li_pos);
            ls_code = ls_code.mid(li_pos + 1);
        }

        while (true)
        {
            li_slp = ls_data.indexOf(QString(QChar(slp)));

            if (li_slp >= 0)
            {
                ls_data = ls_data.left(li_slp) + ls_data.mid(li_slp + 1);
            }
            else
            {
                break;
            }
        }

        if (ls_data.left(2) == "td")
        {
            li_year = ls_data.mid(8,2).toInt();
            li_month = ls_data.mid(2,2).toInt();
            li_day = ls_data.mid(5,2).toInt();

            m_sSampleDate = getSampleDate(li_year,li_month,li_day);
        }
        else if (ls_data.left(2) == "ci")
        {
            m_sSampleNo = ls_data.mid(2).trimmed();
        }
        else if (ls_data.left(2) == "rt")
        {
            ls_itemno = ls_data.mid(2).trimmed();
            ls_result = "";
        }
        else if (ls_data.left(2) == "ql")
        {
            ls_resultql = ls_data.mid(2).trimmed();

            if (ls_resultql != "")
            {
                ls_key = QString("MVIDAS/%1").arg(ls_resultql);
                ls_resultql = readSetting(ls_key.toStdString().data(),ls_resultql).toString();
            }
        }
        else if (ls_data.left(2) == "qn")
        {
            ls_result = ls_data.mid(2).trimmed();
            li_pos = ls_result.lastIndexOf(" ");
            if (li_pos >= 0)
            {
                ls_result = ls_result.left(li_pos).trimmed();
            }

            ls_key = QString("MVIDAS/%1").arg(ls_itemno);
            switch (readSetting(ls_key.toStdString().data(),3).toInt())
            {
            case 1:
                if (ls_result == "")
                {
                    ls_result = ls_resultql;
                }
                break;

            case 2:
                if (ls_resultql != "")
                {
                    ls_result = ls_resultql;
                }
                break;

            case 3:
                ls_result = (ls_resultql + " " + ls_result).trimmed();

                break;
            case 4:
                ls_result = (ls_result + " " + ls_resultql).trimmed();
                break;
            default:
                break;
            }

            sendResult(ls_itemno,ls_result);
        }
    }

    return 0;
}
