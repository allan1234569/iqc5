#include "w_access2.h"
#include "access2_setup.h"

W_Access2::W_Access2(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-ACCESS2");
    loadConfig();
}

W_Access2::~W_Access2()
{

}

int W_Access2::checkEtx(QString as_data)
{
    if (as_data.mid(0,1) == QString(QChar(LF)))
    {
        return 0;
    }

    if (as_data.mid(1,1) == QString(QChar(LF)))
    {
        return 0;
    }

    if (as_data.mid(1,1) == QString(QChar(STX)))
    {
        return 0;
    }

    if (as_data.mid(2,1) == QString(QChar(STX)))
    {
        return 0;
    }

    return 1;
}

void W_Access2::getSampleNo(QString as_sampleno, QString as_posno)
{
    QString ls_sid;
    QStringList lsl_no;
    qint32 li_cup;
    qint32 li_rack;
    qint32 li_no;

    lsl_no = as_posno.split("^");
    ls_sid = as_sampleno;

    if (lsl_no.size() > 2)
    {
        li_rack = lsl_no.at(1).toInt() - 1;
        li_cup = lsl_no.at(2).toInt();
    }

    li_no = li_rack * 10 + li_cup;

    if (m_nSampleNoMode == 1)
    {
        m_sSampleNo = ls_sid;

        if (m_sSampleNo.trimmed().isEmpty())
        {
            m_sSampleNo = li_no;
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

void W_Access2::loadConfig()
{
    BaseWindow::loadConfig();
    m_nSampleNoMode = readSetting("ACCESS2/samplenomode",1).toInt();
}

int W_Access2::decode(QString data)
{
    qint32 li_etx;
    qint32 li_start;
    QString ls_code;

    QString ls_date;
    QString ls_itemno;
    QString ls_result;
    QStringList lsl_unit;
    QStringList lsl_line;

    m_sData += data;
    li_start = 0;

label_0:
    li_etx = m_sData.indexOf("L|1",li_start);

    if (li_etx < 2)
    {
        return -1;
    }

    if (checkEtx(m_sData.mid(li_etx - 3)) != 0)
    {
        li_start = li_etx + 3;
        goto label_0;
    }


    ls_code = m_sData.left(li_etx - 4);
    m_sData = m_sData.mid(li_etx + 4);
    lsl_line = ls_code.split("\r\n");

    for(int i = 0; i < lsl_line.size(); i++)
    {
        lsl_unit = lsl_line.at(i).split("|");
        if (lsl_unit.size() > 1)
        {
            if (lsl_unit.at(0).right(1) == "O")
            {
                getSampleNo(lsl_unit.at(2),lsl_unit.at(3));
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

                    ls_itemno = m_dec.GetField(lsl_unit.at(2),"^",4);
                    ls_result = lsl_unit.at(3).trimmed();
                    sendResult(ls_itemno,ls_result);
                }
            }
        }
    }

    return 0;
}

void W_Access2::on_action_DecodeSetup_triggered()
{
    this->show();
    Access2_Setup *setup = new Access2_Setup(this);
    setup->exec();
}
