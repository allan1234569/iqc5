#include "w_xd683.h"

W_Xd683::W_Xd683(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-XD683");
}

W_Xd683::~W_Xd683()
{

}

void W_Xd683::decode(QString data)
{
    m_sData += data;

    long ll_stx;
    long ll_etx;
    long ll_pos;
    QString ls_code;
    QString ls_start;
    QString ls_end;
    QString ls_year;
    QString ls_month;
    QString ls_day;
    QString ls_result;
    QString ls_item;
    QString ls_seqno;
    QString ls_sampleno;
    QStringList lsl_line;

    ls_start = "XD  683";
    ls_end = QString("%1%2%1%2").arg(char(10)).arg(char(32));

    ll_etx = m_sData.indexOf(ls_end);

    if (ll_etx < 0)
    {
        return;
    }

    ll_stx = m_sData.indexOf(ls_start);
    ls_code = m_sData.mid(ll_stx,ll_etx - ll_stx);
    m_sData = m_sData.mid(ll_etx + 4);

    m_sSampleNo = "";
    lsl_line = ls_code.split('\n');

    for(int i = 0; i < lsl_line.size(); i++)
    {
        ls_code = lsl_line.at(i).trimmed();
        ll_pos = ls_code.indexOf(" ");

        ls_item = ls_code.left(ll_pos).toUpper();
        ls_result = ls_code.mid(ll_pos + 1).trimmed();

        if (ls_item == "DATE")
        {
            ls_year = ls_result.left(4);
            ls_month = ls_result.mid(5,2);
            ls_day = ls_result.mid(8,2);
            m_sSampleDate = QDate(ls_year.toInt(),ls_month.toInt(),ls_day.toInt()).toString("yyyy-MM-dd");
        }
        else if(ls_item == "SAMPLE")
        {
            ll_pos = ls_result.indexOf(":");
            ls_result = ls_result.mid(ll_pos).trimmed();
            ll_pos = ls_result.indexOf("(");

            if (ll_pos >= 0)
            {
                ls_sampleno = ls_result.left(ll_pos).trimmed();
                ls_seqno = ls_result.mid(ll_pos + 1);
                ll_pos = ls_seqno.indexOf(")");
                ls_seqno = ls_seqno.left(ll_pos);

                if (ls_sampleno.isEmpty())
                {
                    ls_sampleno = ls_seqno;
                }
            }
            else
            {
                ls_sampleno = ls_result;
            }
        }
        else if((ls_item == "K") || (ls_item == "NA") || (ls_item == "CL"))
        {
            ll_pos = ls_result.indexOf("=");
            ls_result = ls_result.mid(ll_pos + 1);
            ll_pos = ls_result.indexOf(" ");
            ls_result = ls_result.left(ll_pos);
            sendResult(ls_item,ls_result);

        }
    }

    if (m_sData.indexOf(ls_end) >= 0)
    {
        redecode();
    }

}
