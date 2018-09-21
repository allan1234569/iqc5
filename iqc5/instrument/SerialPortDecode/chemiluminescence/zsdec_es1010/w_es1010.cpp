#include "w_es1010.h"
#include <QRegularExpression>

W_Es1010::W_Es1010(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-ES1010");
    m_bIsQc =false;
    loadConfig();
}

W_Es1010::~W_Es1010()
{

}

void W_Es1010::dealPatient(QString data)
{
    qint32 li_this;
    qint32 li_next = 0;
    QString ls_order;

    li_this = data.indexOf("O|",li_next);
    ls_order = data.mid(li_this);
    ls_order = ls_order.left(ls_order.length() - 2);

    dealOrder(ls_order);
}

void W_Es1010::dealOrder(QString data)
{
    qint32 li_this;
    qint32 li_next = 0;
    QString ls_result;

    if (m_nSampleIdType == 1)
    {
        m_sSampleNo = m_dec.GetField(data,"|",3);

        if (m_sSampleNo.contains("QC"))
        {
            m_sSampleNo = m_sSampleNo.mid(m_sSampleNo.indexOf("QC") + 2);
            m_bIsQc = true;
        }
        else
        {
            QRegularExpression reg("^[0-9]");

            while(reg.match(m_sSampleNo).hasMatch())
            {
                m_sSampleNo = m_sSampleNo.mid(1);

                if (m_sSampleNo.length() == 0)
                {
                    break;
                }
            }

            m_bIsQc = false;
        }
    }
    else
    {
        m_sSampleNo = m_dec.GetField(data,"|",4);
        m_sSampleNo = m_dec.GetField(m_sSampleNo,"^",1);
    }

    if (m_sSampleNo.toInt() == 0)
    {
        return;
    }

    li_next = data.indexOf("\r\n");

    do
    {
        li_this = data.indexOf("R|",li_next);
        li_next = data.indexOf("R|",li_this + 1);

        if (li_next >= 0)
        {
            ls_result = data.mid(li_this,li_next - li_this);
        }
        else
        {
            ls_result = data.mid(li_this);
        }

        dealResult(ls_result);
    }while(li_next < 0);
}

int W_Es1010::dealResult(QString data)
{
    QString ls_date;
    QString ls_itemalias;
    QString ls_result;
    QString ls_sign;
    QString ls_printresult;
    qint32 li_pos;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;

    ls_itemalias = m_dec.GetField(m_dec.GetField(data,"|",3),
                                  "^",
                                  4);

    ls_result = m_dec.GetField(data,"|",4);

    li_pos = ls_result.indexOf("^");

    if (li_pos >= 0)
    {
        ls_result = ls_result.mid(li_pos + 1);
    }

    if (ls_itemalias == "")
    {
        return 1;
    }

    ls_date = m_dec.GetField(data,"|",13);
    li_year = ls_date.left(4).toInt();
    li_month = ls_date.mid(4,2).toInt();
    li_day = ls_date.mid(6,2).toInt();

    m_sSampleDate = getSampleDate(li_year,li_month,li_day);
    calcResult(ls_result);
//    li_pos = makeResult(ls_itemalias,ls_result,ls_printresult);
//    if (!m_bIsQc)
//    {
//        switch (li_pos) {
//        case 0:
//            sendResult(ls_itemalias,ls_result);
//            break;
//        case 1:
//            sendResult(ls_itemalias,ls_result);
//            break;
//        default:
//            break;
//        }
//    }

    sendResult(ls_itemalias,ls_result);
}

void W_Es1010::calcResult(QString &result)
{
    qint32 li_pos;

    li_pos = result.indexOf("!");

    if (li_pos >= 0)
    {
        result = result.left(li_pos);
    }

    if ((result.left(1) == ".") && (result.right(1) == "."))
    {
        result = "";
    }
    else
    {
        if (result.left(1) == ".")
        {
            result = result.prepend("0");
        }
        else
        {
            if (result.right(1) == ".")
            {
                result = result.left(result.length() - 1);
            }
        }
    }
}

int W_Es1010::makeResult(QString &itemalais, QString result, QString &printResult)
{
    qint32 li_i;
    bool lb_found = false;
    QString ls_str;
    double ld_result;

    ls_str = result.left(1);

    if (ls_str == ">")
    {
        ld_result = result.mid(1).toDouble() + 1;
    }
    else if (ls_str == "<")
    {
        ld_result = result.mid(1).toDouble() - 1;
    }
    else
    {
        if (isNumber(result))
        {
            ld_result = result.toDouble();
        }
        else
        {
            ld_result = 0;  //暂定
        }
    }




}

void W_Es1010::loadConfig()
{
    BaseWindow::loadConfig();

    m_nSampleIdType = readSetting("ES1010/sampleidtype",1).toInt();
}

int W_Es1010::decode(QString data)
{
    qint32 li_this;
    qint32 li_next;
    QString ls_patient;
    QString ls_code;

    m_sData += data;
    li_this = m_sData.indexOf("L|1");

    if (li_this < 0)
    {
        return -1;
    }

    ls_code = m_sData.left(li_this - 3);
    m_sData = m_sData.mid(li_this + 8);
    li_next = ls_code.indexOf("\r\n") + 2;

    do
    {
        li_this = ls_code.indexOf("P|",li_next);
        li_next = ls_code.indexOf("P|",li_this + 1);

        if (li_next > 0)
        {
            if (ls_code.mid(li_this,1) == "|")
            {
                continue;
            }

            ls_patient = ls_code.mid(li_this,li_next - li_this - 2);
        }
        else
        {
            ls_patient = ls_code.mid(li_this);
        }

        dealPatient(ls_patient);

    }while(li_next >= 0);

    if (m_sData.indexOf("L|1") >= 0)
    {
        redecode();
    }

    return 0;

}

