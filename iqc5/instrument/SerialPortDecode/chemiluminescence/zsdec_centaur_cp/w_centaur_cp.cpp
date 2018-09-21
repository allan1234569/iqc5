#include "w_centaur_cp.h"
#include "centaurcp_setup.h"

W_Centaur_Cp::W_Centaur_Cp(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-CENTAUR_CP");

    m_nSampleNoMode = 1;

    loadConfig();
}

W_Centaur_Cp::~W_Centaur_Cp()
{

}

int W_Centaur_Cp::decode(QString data)
{
    qint32 li_stx;
    qint32 li_etx;
    qint32 li_add;

    QString ls_code;
    QString ls_date;
    QString ls_item;
    QString ls_result;
    QStringList lsl_line;
    QStringList lsl_unit;

    m_sData += data;
    m_dec.CutAstmCheckSum(m_sData);
    li_etx = m_sData.indexOf("L|1");

    while(li_etx >= 0)
    {
        if (m_sData.mid(li_etx - 2,1) == "\r")
        {
            break;
        }

        li_etx = m_sData.indexOf("L|1",li_etx + 3);
    }

    if (li_etx < 0)
    {
        return -1;
    }

    ls_code = m_sData.left(li_etx + 4);
    m_sData = m_sData.mid(li_etx + 4);
    lsl_line = ls_code.split("\r");

    for(int i = 0; i < lsl_line.size(); i++)
    {
        lsl_unit = lsl_line.at(i).split("|");

        if (lsl_unit.size() >= 1)
        {
            if (lsl_unit.at(0).right(1) == "O")
            {
                if (lsl_unit.size() > 2)
                {
                    m_sSampleNo = lsl_unit.at(2);
                    getSampleNo();
                }
                else
                {
                    m_sSampleNo = "";
                }
            }
            else if (lsl_unit.at(0).right(1) == "R")
            {
                if (lsl_unit.size() > 3)
                {
                    if (lsl_unit.size() > 12)
                    {
                        ls_date = lsl_unit.at(12);
                    }

                    m_sSampleDate = getSampleDate(ls_date.left(4).toInt(),
                                                  ls_date.mid(4,2).toInt(),
                                                  ls_date.mid(6,2).toInt());

                    if (lsl_unit.at(2).right(4) == "DOSE")
                    {
                        ls_item = m_dec.GetField(lsl_unit.at(2),"^",4);
                        ls_result = lsl_unit.at(3).trimmed();
                        sendResult(ls_item,ls_result);
                    }
                }
            }
            else if (lsl_unit.at(0).right(1) == "L")
            {

            }
        }
    }

    if (m_sData.indexOf("L|1") >= 0)
    {
        redecode();
    }

    return 0;
}

void W_Centaur_Cp::loadConfig()
{
    BaseWindow::loadConfig();

    m_nSampleNoMode = readSetting("CENTAUR_CP/samplenomode",1).toInt();
}

void W_Centaur_Cp::getSampleNo()
{
    QStringList lsl_no;
    QString ls_sid;
    qint32 li_rack;
    qint32 li_cup;
    qint32 li_no;

    lsl_no = m_sSampleNo.split("^");

    if (lsl_no.size() <= 0)
    {
        return;
    }

    ls_sid = lsl_no.at(0);

    if (lsl_no.size() < 3)
    {
        return;
    }

    li_rack = lsl_no.at(2).toInt();

    if (li_rack < 0)
    {
        li_rack = 0;
    }

    if (lsl_no.at(2).trimmed().toUpper() == "A")
    {
        li_cup = 1;
    }
    else if (lsl_no.at(2).trimmed().toUpper() == "B")
    {
        li_cup = 2;
    }
    else if (lsl_no.at(2).trimmed().toUpper() == "C")
    {
        li_cup = 3;
    }
    else if (lsl_no.at(2).trimmed().toUpper() == "D")
    {
        li_cup = 4;
    }
    else if (lsl_no.at(2).trimmed().toUpper() == "E")
    {
        li_cup = 5;
    }

    if (m_nSampleNoMode == 3)
    {
        li_no = li_rack * 5 + li_cup;
    }
    else
    {
        li_no = li_rack * 10 + li_cup;
    }

    if (m_nSampleNoMode == 1)
    {
        m_sSampleNo = ls_sid;

        if (m_sSampleNo.trimmed().isEmpty())
        {
            m_sSampleNo = QString::number(li_no);
        }
    }
    else
    {
        if (li_no > 0)
        {
            m_sSampleNo = QString::number(li_no);
        }
        else
        {
            m_sSampleNo = ls_sid;
        }
    }

}

void W_Centaur_Cp::on_action_DecodeSetup_triggered()
{
    this->show();
    CentaurCp_Setup *setup = new CentaurCp_Setup(this);
    setup->exec();
}
