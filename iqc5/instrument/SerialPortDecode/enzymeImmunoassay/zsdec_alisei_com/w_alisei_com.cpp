#include "w_alisei_com.h"

W_Alisei_Com::W_Alisei_Com(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("酶免仪-ALISEI-COM");
}

W_Alisei_Com::~W_Alisei_Com()
{

}

void W_Alisei_Com::decode(QString data)
{
    m_sData += data;

    qint32 li_len;
    qint32 li_i;
    qint32 li_pos;
    QString ls_data;
    QString ls_code;

    if (data.length() <= 0)
    {
        return;
    }

    li_len = data.length();
    li_i = 0;
    while(1)
    {
        if (li_i > li_len)
        {
            break;
        }

        if ( m_sData.mid(li_i,1).toInt() < QString(QChar(SOH)).toInt() )
        {
            if ( m_sData.mid(li_i - 1, 1) == QString(QChar(SOH)) )
            {
                goto label_0;
            }
        }
        else
        {
            label_0:
            ls_data += m_sData.mid(li_i + 3, 128);
            li_i += 131;
        }
    }

    li_pos = ls_data.indexOf("]");

    while (li_pos >= 0)
    {
        ls_data = ls_data.mid(li_pos + 1);
        li_pos = ls_data.indexOf("[");

        if (li_pos >= 0)
        {
            ls_code = ls_data.left(li_pos);
            ls_data = ls_data.mid(li_pos + 1);
            wf_decode(ls_code);
        }
        else
        {
            wf_decode(ls_data);
            break;
        }

        li_pos = ls_data.indexOf("]");
    }

    m_sData.clear();
}

int W_Alisei_Com::wf_decode(QString data)
{
    QString ls_year;
    QString ls_month;
    QString ls_day;
    QString ls_tests;
    QString ls_results;
    QString ls_itemno;
    QString ls_sco;
    QString ls_pn;
    QString ls_pnflag;
    QStringList lsl_item;
    QStringList lsl_result;

    qint32 ll_i;
    qint32 ll_cnt;
    qint32 ll_cnt1;
    QDate ldt_date;

    data = data.toUpper();

    if (getLineVal(data,"ID",m_sSampleNo) != 0)
    {
        return 1;
    }

    if (getLineVal(data,"Ins_Day",ls_day) != 0)
    {
        ls_day =QString::number( ldt_date.currentDate().day());
    }

    if (getLineVal(data,"Ins_Month",ls_month) != 0)
    {
        ls_month = QString::number(ldt_date.currentDate().month());
    }

    if (getLineVal(data,"Ins_Year",ls_year) != 0)
    {
        ls_year = QString::number(ldt_date.currentDate().year());
    }

    m_sSampleDate = getSampleDate(ls_year.toInt(), ls_month.toInt(), ls_day.toInt());

    if (getLineVal(data,"Test",ls_tests) != 0)
    {
        return 1;
    }

    if (getLineVal(data,"Result",ls_results) != 0)
    {
        return 1;
    }

    lsl_item = ls_tests.split(",");
    lsl_result = ls_results.split(",");

    for (int i = 0; i < lsl_item.size(); i++)
    {
        ls_itemno = lsl_item.at(i).trimmed();

        if (!ls_itemno.isEmpty())
        {
            if (i >= lsl_result.size())
            {
                break;
            }

            //TODO

//            sendResult(ls_itemno,ls_results)
        }

    }

}

int W_Alisei_Com::getLineVal(QString data, QString key, QString &ret)
{
    qint32 li_pos;
    qint32 li_len;
    QString ls_find;
    QString ls_ret;

    ls_find = QString("\r\n") + key.toUpper() + "=";
    li_len = ls_find.length();

    li_pos = data.indexOf(ls_find);

    if (li_pos < 0)
    {
        return 1;
    }

    ret = data.mid(li_pos + li_len);
    li_pos = ls_ret.indexOf("\r\n");

    if (li_pos >= 0)
    {
        ret = ret.left(li_pos);
    }

    ret = ret.trimmed();
    if (ret.isEmpty())
    {
        return 2;
    }

    return 0;
}
