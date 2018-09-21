#include "w_e411.h"

#include "e411_setup.h"

W_E411::W_E411(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-E411");

    loadConfig();
}

W_E411::~W_E411()
{

}

void W_E411::loadConfig()
{
    BaseWindow::loadConfig();
    m_nSampleNoMode = readSetting("E411/samplenomode",1).toInt();


//    m_nResultMode = readSetting("E411/resultmode",1).toInt();

}

int W_E411::decode(QString data)
{
    qint32 li_this;
    qint32 li_next;
    qint32 li_pos;
    QString ls_code;
    QString ls_sampledate;
    QString ls_seqno;
    QString ls_itemno;
    QString ls_result;
    QString ls_temp;
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
        li_pos = ls_line.indexOf("|");

        if (li_pos >= 0)
        {
            if (ls_line.left(li_pos).right(1) == "P")
            {

            }
            else if (ls_line.left(li_pos).right(1) == "O")
            {
                ls_sampledate = m_dec.GetField(ls_line,"|",7).trimmed();

                if (ls_sampledate.isEmpty())
                {
                    ls_sampledate = m_dec.GetField(ls_line,"|",23);
                }

                m_sSampleDate = getSampleDate(ls_sampledate.left(4).toInt(),
                                              ls_sampledate.mid(4,2).toInt(),
                                              ls_sampledate.mid(6,2).toInt());

                m_bIsStat = (m_dec.GetField(ls_line,"|",6) == "S");

                if (m_dec.GetField(ls_line,"|",12).indexOf("Q") >= 0)
                {
                    m_bIsQc = true;
                }
                else
                {
                    m_bIsQc = false;
                }

                m_sSampleNo = m_dec.GetField(ls_line,"|",3);

                if (m_bIsQc)
                {
                }
                else
                {
                    ls_seqno = m_dec.GetField(m_dec.GetField(ls_line,"|",4),"^",1);

                    if (m_nSampleNoMode == 2)
                    {
                        if (ls_seqno.toInt() > 0)
                        {
                            m_sSampleNo = ls_seqno;
                        }
                    }

                    m_sSampleNo = m_sSampleNo.trimmed();

                    while(m_sSampleNo.left(1) == "^")
                    {
                        m_sSampleNo = m_sSampleNo.mid(1).trimmed();
                    }
                }
            }
            else if (ls_line.left(li_pos).right(1) == "R")
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
                    ls_result = m_dec.GetField(ls_result,"^",1).trimmed();

//                    if (!ls_temp.trimmed().isEmpty())   //定性结果是否为空的判断，暂不考虑
//                    {

//                    }

                    sendResult(ls_itemno,ls_result);
                }
            }
        }
    }

    if (m_sData.indexOf("L|1") >= 0)
    {
        redecode();
    }

    return 0;
}

void W_E411::on_action_DecodeSetup_triggered()
{
    this->show();
    E411_Setup *setup = new E411_Setup(this);
    setup->exec();
}
