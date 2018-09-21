#include "w_xd685.h"

W_Xd685::W_Xd685(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-XD685");
}

W_Xd685::~W_Xd685()
{

}

void W_Xd685::decode(QString data)
{
    m_sData += data;

    QString ls_code;
    long ll_ext;
    long ll_str;
    long ll_end;

    ll_ext = m_sData.indexOf(QString("%1%2").arg(QChar(LF)).arg(" "));

    if (ll_ext >= 0)
    {
        ll_str = m_sData.indexOf("XD");

        if (ll_ext > ll_str)
        {
            ls_code = m_sData.mid(ll_str,ll_ext - ll_str);
            ll_end = m_sData.indexOf("XD",ll_str + 1);
            m_sData = m_sData.mid(ll_ext + 15);
        }
        else
        {
            m_sData = m_sData.mid(ll_ext + 2);
        }
    }

    if (!ls_code.isEmpty())
    {
        deal_sample(ls_code);
    }


}

void W_Xd685::deal_sample(QString data)
{
    long ll_temp;
    int li_year;
    int li_month;
    int li_day;
    long ll_str;
    long num = 0;
    QString ls_item;
    QString ls_result;
    QString ls_resulttemp;
    QString ls_rtemp;
    QStringList lsl_unit;

    m_sSampleNo = "";

    if (data.indexOf("failed") >= 0)
    {
        return;
    }

    lsl_unit = data.split(QChar(LF));

    if (lsl_unit.size() == 0)
    {
        return;
    }

    for(int i = 0; i < lsl_unit.size(); i++)
    {

        ll_temp = lsl_unit.at(i).indexOf(" ");
        ls_item = lsl_unit.at(i).mid(0,ll_temp);
        ls_result = lsl_unit.at(i).mid(ll_temp);

        if (ls_item.toUpper() != "XD")
        {
            if (ls_item.toUpper() == "DATE")
            {
                li_year = ls_result.mid(0,4).trimmed().toLong();
                li_month = ls_result.mid(5,2).trimmed().toLong();
                li_day = ls_result.mid(8,2).trimmed().toLong();
                m_sSampleDate = QDate(li_year,li_month,li_day).toString("yyyy-MM-dd");
            }
            else
            {
                if (ls_item.toUpper() != "TIME" && (ls_item.toUpper() != "TEST"))
                {
                    if (ls_item.toUpper() == "SAMPLE")
                    {
                        ll_temp = ls_result.indexOf(":");
                        m_sSampleNo = ls_result.mid(ll_temp + 1, 5);   //样本号
//                        ls_result.mid(ll_temp + 7,2);     //序列号

                    }
                    else
                    {
                        if ((ls_result.left(1) == "=") || (ls_result.left(1) == "*"))
                        {
                            ll_str = ls_result.indexOf("=");

                            if (ll_str < 0)
                            {
                                ll_str = ls_result.indexOf("*");
                            }

                            ls_result = ls_result.mid(ll_str + 1);
                        }

                        if (!ls_result.isEmpty())
                        {
                            ls_resulttemp = "";
                            num = 0;

                            while(1)
                            {

                                ls_rtemp = ls_result.mid(num,1);
                                if ((ls_rtemp != ".") && !isNumber(ls_rtemp))
                                {
                                    break;
                                }

                                ls_resulttemp  = ls_resulttemp +ls_rtemp;

                                num++;
                            }

                            if (ls_item.indexOf("=") >= 0)
                            {
                                ls_item = ls_item.mid(0,ls_item.indexOf("="));
                            }

                            sendResult(ls_item,ls_result);
                        }
                    }
                }
            }
        }
    }
}
