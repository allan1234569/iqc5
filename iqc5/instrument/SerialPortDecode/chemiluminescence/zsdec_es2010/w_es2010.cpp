#include "w_es2010.h"

#include <QRegularExpression>

#include "es2010_setup.h"

W_Es2010::W_Es2010(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-ES2010");

    loadConfig();
}

W_Es2010::~W_Es2010()
{

}

int W_Es2010::getSegPos(QString data, QString find, qint32 from)
{
    qint32 li_pos;

    li_pos = data.indexOf(find,from);
    while(li_pos >= 0)
    {
        if (data.mid(li_pos,1) == QString(QChar(STX)))
        {
            return li_pos;
        }

        li_pos = data.indexOf(find,from);
    }

    return -1;
}

void W_Es2010::dealPatient(QString data)
{
    qint32 li_this;
    QString ls_order;

    m_sBarCodeSampleNo = m_dec.GetField(data,"|",4).trimmed();

    li_this = getSegPos(data,"O|");
    ls_order = data.mid(li_this);
    ls_order = ls_order.left(ls_order.length() - 2);

    dealOrder(ls_order);
}

void W_Es2010::dealOrder(QString data)
{
    qint32 li_this;
    qint32 li_next;
    QString ls_result;

    if (m_nSampleIdType == 1)
    {
        m_sSampleNo = m_dec.GetField(data,"|",3).toUpper();

        if (m_sSampleNo.contains("QC"))
        {
            m_sSampleNo = m_sSampleNo.mid(m_sSampleNo.indexOf("QC") + 2);
            m_bIsQc = true;
        }
        else
        {
            QRegularExpression reg("^[0-9]");
            while(!reg.match(m_sSampleNo).hasMatch())
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

    m_bBarCodeMode = readSetting("ES2010/barcodedual",false).toBool();
    if (m_bBarCodeMode)
    {
        if (m_sBarCodeSampleNo != "")
        {
            m_sSampleNo = m_sBarCodeSampleNo;
        }
    }

    if (m_sSampleNo.toInt() < 0)
    {
        return;
    }

    li_next = 4;

    do
    {
        li_this = getSegPos(data,"R|",li_next);
        li_next = getSegPos(data,"R|",li_this + 1);

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

void W_Es2010::dealResult(QString data)
{
    QString ls_date;
    QString ls_interno;
    QString ls_result;
    QString ls_sign;
    QString ls_printresult;
    qint32 li_pos;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;

    ls_interno = m_dec.GetField(m_dec.GetField(data,"|",3),
                                "^",
                                3);

    ls_result = m_dec.GetField(data,"|",4);
    li_pos = ls_result.indexOf("^");

    if (li_pos >= 0)
    {
        ls_result = ls_result.mid(li_pos + 1);
    }

    if (ls_interno == "")
    {
        return;
    }

    ls_date = m_dec.GetField(data,"|",13);
    li_year = ls_date.left(4).toInt();
    li_month = ls_date.mid(4,2).toInt();
    li_day = ls_date.mid(6,2).toInt();

    m_sSampleDate = getSampleDate(li_year,li_month,li_day);

    if (!m_bIsQc)
    {
        sendResult(ls_interno,ls_result);
    }

}

void W_Es2010::loadConfig()
{
    BaseWindow::loadConfig();

    m_bBarCodeMode = readSetting("ES2010/barcodedual",0).toBool();
    m_nSampleIdType = readSetting("ES2010/sampleidtype",1).toInt();
}

int W_Es2010::decode(QString data)
{
    qint32 li_this;
    qint32 li_next;
    QString ls_patient;
    QString ls_code;
    QString ls_data;

    m_sData += data;
    li_this = getSegPos(m_sData,"L|1");

    if (li_this < 0)
    {
        return -1;
    }

    ls_code = data.left(li_this - 3);
    m_sData = m_sData.mid(li_this + 8);
    li_next = 0;

    do
    {
        li_this = getSegPos(ls_code,"P|", li_next);
        li_next = getSegPos(ls_code,"P|", li_this + 1);

        if (li_next > 0)
        {
            if (ls_code.mid(li_this - 1,1) == "|")
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

    if (getSegPos(m_sData,"L|1") >= 0)
    {
        redecode();
    }

    return 0;
}

void W_Es2010::on_action_DecodeSetup_triggered()
{
    this->show();
    Es2010_setup *setup = new Es2010_setup(this);
    setup->exec();
    delete setup;
}
