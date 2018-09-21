#include "w_centaur.h"
#include "centaursetup.h"

W_Centaur::W_Centaur(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-Centaur");

    m_nSampleNoMode = 1;

    loadConfig();
}

W_Centaur::~W_Centaur()
{

}

int W_Centaur::decode(QString data)
{
    qint32 li_stx;
    qint32 li_etx;

    QString ls_code;
    QString ls_date;
    QString ls_itemno;
    QString ls_result;
    QString ls_patid;

    QStringList lsl_unit;
    QStringList lsl_line;
    QStringList lsl_no;

    m_sData += data;
    transData();

    li_etx = m_sData.indexOf("L|1");

    if (li_etx < 0)
    {
        return -1;
    }

    ls_code = m_sData.left(li_etx - 4);
    m_sData = m_sData.mid(li_etx + 4);

    lsl_line = ls_code.split("\r");

    for(int i = 0; i < lsl_line.size(); i++)
    {
        lsl_unit = lsl_line.at(i).split("|");

        if (lsl_unit.size() >= 1)
        {
            if(lsl_unit.at(0).right(1) == "P")
            {
                if (m_nSampleNoMode == 4)
                {
                    ls_patid = lsl_unit.at(5).trimmed();
                }
            }
            else if (lsl_unit.at(0).right(1) == "O")
            {
                if (m_nSampleNoMode == 4)
                {
                    if (lsl_unit.size() > 1)
                    {
                        m_sSampleNo = ls_patid;
                        continue;
                    }

                }


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
                                                  ls_date.mid(6,2).toInt()
                                                  );

                    if (lsl_unit.at(2).right(4) == "DOSE")
                    {
                        ls_itemno = m_dec.GetField(lsl_unit.at(2),"^",4);
                        ls_result = lsl_unit.at(4).trimmed();
                        sendResult(ls_itemno,ls_result);
                    }
                }
            }
        }
    }

    if (m_sData.indexOf("L|1") > 0)
    {
        redecode();
    }

    return 0;
}

void W_Centaur::transData()
{
    QString ls_data;
    QString ls_dat;
    qint32 li_pos;

    ls_dat = m_sData;
    li_pos = ls_dat.indexOf(QString(QChar(23)));

    while(li_pos >= 0)
    {
        ls_data += ls_dat.left(li_pos);

        if ((ls_dat.mid(3,3) == "\n") || (ls_dat.mid(3,3) == QString(QChar(STX))))
        {
            li_pos += 7;
        }

        ls_dat = ls_dat.mid(li_pos);
        li_pos = ls_dat.indexOf(QString(QChar(23)),1);
    }

    ls_data += ls_dat;

    m_sData = ls_data;
}

void W_Centaur::getSampleNo()
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

void W_Centaur::loadConfig()
{
    BaseWindow::loadConfig();

    m_nSampleNoMode = readSetting("CENTAUR/samplenomode",1).toInt();    //默认SID
}

void W_Centaur::on_action_DecodeSetup_triggered()
{
    this->show();
    CentaurSetup *setup = new CentaurSetup(this);
    setup->exec();
}
