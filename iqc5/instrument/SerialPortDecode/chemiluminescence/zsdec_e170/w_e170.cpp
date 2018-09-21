#include "w_e170.h"

#include "e170_setup.h"

W_E170::W_E170(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-E170");

    loadConfig();
}

W_E170::~W_E170()
{

}

void W_E170::loadConfig()
{
    BaseWindow::loadConfig();

    m_nSampleIdMode = readSetting("E170/sampleidtype",1).toInt();
    m_bBarCodeMode = (readSetting("E170/barcodedual",0).toInt() == 1) ? true : false;
}

int W_E170::decode(QString data)
{
    qint32 li_this;
    qint32 li_next;
    qint32 li_pos;
    QString ls_code;
    QString ls_type;
    QString ls_sampledate;
    QString ls_sampletype;
    QString ls_tempno;
    QString ls_seqno;
    QString ls_itemno;
    QString ls_result;
    QString ls_temp;
    QString ls_tempsampleno;
    QString ls_line;
    QStringList lsl_unit;

    m_sData += data;
    li_pos = m_sData.indexOf(QString(QChar(EOT)));

    if (li_pos < 0)
    {
        return -1;
    }

    ls_code = m_sData.left(li_pos);
    m_sData = m_sData.mid(li_pos + 1);

    li_this = ls_code.indexOf(QString(QChar(STX)));
    while(li_this >= 0)
    {
        ls_code = ls_code.replace(li_this,2,"");
        li_this = ls_code.indexOf(QString(QChar(STX)));
    }

    li_next = ls_code.indexOf(QString(QChar(ETB)));
    while(li_next > 0)
    {
        ls_code = ls_code.replace(li_next,5,"");
        li_next = ls_code.indexOf(QString(QChar(ETB)));
    }

    ls_code = ls_code.mid(ls_code.indexOf(QString(QChar(ENQ))) + 1);
    m_bIsQc = false;

    lsl_unit = ls_code.split("\r");

    for (int i = 0 ; i< lsl_unit.size(); i++)
    {
        ls_line = lsl_unit.at(i);

        if (ls_line.left(1).toUpper() == "O")
        {
            ls_sampledate = m_dec.GetField(ls_line,"|",23);
            m_sSampleDate = getSampleDate(ls_sampledate.left(4).toInt(),
                                          ls_sampledate.mid(4,2).toInt(),
                                          ls_sampledate.mid(6,2).toInt());
            m_sSampleNo = m_dec.GetField(ls_line,"|",3);

            if (!m_sSampleNo.contains("^"))
            {
                ls_tempsampleno = m_sSampleNo.trimmed();
                ls_seqno = m_dec.GetField(m_dec.GetField(ls_line,"|",4),
                                          "^",
                                          1);
            }
            else
            {
                ls_tempsampleno = m_dec.GetField(m_sSampleNo,"^",2);
                ls_seqno = m_dec.GetField(m_sSampleNo,"^",1);
            }

            ls_sampletype = m_dec.GetField(m_sSampleNo,"^",3);

            if (m_nSampleIdMode == 2)
            {
                if (ls_seqno.toInt() > 0)
                {
                    m_sSampleNo = ls_seqno;
                }
                else
                {
                    m_sSampleNo = ls_tempsampleno;
                }
            }
            else
            {
                m_sSampleNo = ls_tempsampleno;
            }

            if (m_sSampleNo == "")
            {
                if (ls_tempsampleno != "")
                {
                    m_sSampleNo = ls_tempsampleno;
                }
                else
                {
                    if (ls_seqno != "")
                    {
                        m_sSampleNo = ls_seqno;
                    }
                }
            }

            ls_type = m_dec.GetField(ls_line,"|",6);

            if ((ls_type == "R") || (ls_type == "S"))
            {

            }
            else
            {
                ls_type = m_dec.GetField(ls_line,"|",12);

                if (ls_type == "Q")
                {
                    m_bIsQc = true;
                }
                else
                {
                    break;
                }
            }

            if (m_bBarCodeMode)
            {
                ls_tempno = m_dec.GetField(ls_line,"|",20);

                if (ls_tempno.contains("ITEMS FROM BARCODE"))
                {
                    m_sSampleNo = m_dec.GetField(ls_tempno,"^",3);
                }
            }
        }
        else if (ls_line.left(1).toUpper() == "C")
        {
            if (!m_bBarCodeMode)
            {
                continue;
            }

            if (!ls_line.contains("ITEMS FROM BARCODE"))
            {
                continue;
            }

            m_sSampleNo = m_dec.GetField(ls_line,"|",4);
            m_sSampleNo = m_dec.GetField(m_sSampleNo,"^",3);
        }
        else if (ls_line.left(1).toUpper() == "R")
        {
            if (m_bIsQc)
            {

            }
            else
            {
                ls_itemno = m_dec.GetField(ls_line,"|",3);
                ls_itemno = m_dec.GetField(ls_itemno,"^",4);
                ls_itemno = m_dec.GetField(ls_itemno,"/",1);

                if (ls_itemno.trimmed().isEmpty())
                {
                    continue;
                }

                ls_result = m_dec.GetField(ls_line,"|",4);
                ls_temp = m_dec.GetField(ls_result,"^",2);
                ls_result = m_dec.GetField(ls_result,"^",1);

                if (m_dec.GetField(ls_line,"|",7) == "HH")
                {
                    ls_result.prepend(">");
                }
                else if (m_dec.GetField(ls_line,"|",7) == "LL")
                {
                    ls_result.prepend("<");
                }
                else if (m_dec.GetField(ls_line,"|",7) == "A")
                {

                }

                sendResult(ls_itemno,ls_result);
            }
        }
        else if (ls_line.left(1).toUpper() == "L")
        {

        }
    }

    if (m_sData.indexOf("L|1") >= 0)
    {
        redecode();
    }

    return 0;
}

void W_E170::on_action_DecodeSetup_triggered()
{
    this->show();
    E170_Setup *setup = new E170_Setup(this);
    setup->exec();
}
