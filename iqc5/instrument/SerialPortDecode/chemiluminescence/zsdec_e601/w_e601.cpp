#include "w_e601.h"
#include "e601_setup.h"

W_E601::W_E601(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-E601");
    loadConfig();
}

W_E601::~W_E601()
{

}

void W_E601::loadConfig()
{
    BaseWindow::loadConfig();

    m_bBarCode = readSetting("E601/barcodemode",1).toBool();
    m_nSampleNoMode = readSetting("E601/samplenomode",1).toInt();
}

int W_E601::decode(QString data)
{
    qint32 li_this;
    qint32 li_next;
    qint32 li_pos;
    QString ls_data;
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

    ls_code = ls_data.left(li_pos);
    m_sData = m_sData.mid(li_pos + 1);

    li_this = ls_code.indexOf(QString(QChar(STX)));
    while(li_this >= 0)
    {
        ls_code = ls_code.replace(li_this,2,"");
        li_this = ls_code.indexOf(QString(QChar(STX)));
    }

    li_next = ls_code.indexOf(QString(QChar(ETB)));
    while(li_next >= 0)
    {
        ls_code = ls_code.replace(li_next,5,"");
        li_next = ls_code.indexOf(QString(QChar(ETB)));
    }

    ls_code = ls_code.mid(ls_code.indexOf(QString(QChar(ENQ))) + 1);

    m_bIsQc = false;
    m_bIsStat = false;

    lsl_unit = ls_code.split("\r");

    for (int i = 0; i < lsl_unit.size(); i++)
    {
        ls_line = lsl_unit.at(i);

        if (ls_line.left(1).toUpper() == "O")
        {
            ls_sampledate = m_dec.GetField(ls_line,"|",23);
            m_sSampleDate = getSampleDate(ls_sampledate.left(4).toInt(),
                                          ls_sampledate.mid(4,2).toInt(),
                                          ls_sampledate.mid(6,2).toInt());
            m_sSampleNo = m_dec.GetField(ls_line,"|",3);

            if (m_sSampleNo.indexOf("^") < 0)
            {
                ls_tempsampleno = m_sSampleNo.trimmed();
                ls_seqno = m_dec.GetField(m_dec.GetField(ls_line,"|",4),
                                          "^",
                                          1);
            }
            else
            {
                ls_seqno = m_dec.GetField(m_sSampleNo,"^",1).trimmed();
                ls_tempsampleno = m_dec.GetField(m_sSampleNo,"^",2).trimmed();
            }

            ls_sampletype = m_dec.GetField(m_sSampleNo,"^",3);

            if (m_nSampleNoMode == 2)
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

            if (m_sSampleNo.isEmpty())
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

            if (ls_type == "R")
            {
                m_bIsStat = false;
            }
            else if (ls_type == "S")
            {
                m_bIsStat = true;
                m_sSampleNo = ls_tempsampleno.trimmed();
            }
            else
            {
                m_bIsStat = false;
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

            if (m_bBarCode)
            {
                ls_tempno = m_dec.GetField(ls_line,"|",20);

                if (ls_tempno.indexOf("ITEMS FROM BARCODE") >= 0)
                {
                    m_sSampleNo = m_dec.GetField(ls_tempno,"^",3).trimmed();
                }
            }

        }
        else if (ls_line.left(1).toUpper() == "C")
        {
            if (!m_bBarCode)
            {
                continue;
            }

            if (ls_line.indexOf("ITEMS FROM BARCODE") >= 0)
            {
                continue;
            }

            m_sSampleNo = m_dec.GetField(ls_line,"|",4);
            m_sSampleNo = m_dec.GetField(m_sSampleNo,"^",3).trimmed();
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

                if (m_dec.GetField(ls_line,"|",7) == "LL")
                {
                    ls_result = QString("<%1").arg(ls_result);
                }
                else if (m_dec.GetField(ls_line,"|",7) == "HH")
                {
                    ls_result = QString(">%1").arg(ls_result);
                }

                //定性结果是否为空的判断，暂不考虑

                sendResult(ls_itemno,ls_result);
            }
        }
    }

    if (m_sData.indexOf("L|1") >= 0)
    {
        redecode();
    }

    return 0;
}

void W_E601::on_action_DecodeSetup_triggered()
{
    this->show();
    E601_Setup *setup = new E601_Setup(this);
    setup->exec();
}
