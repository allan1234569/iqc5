#include "w_lumino.h"

#include "lumino_setup.h"
W_Lumino::W_Lumino(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-LUMINO");
    loadConfig();
}

W_Lumino::~W_Lumino()
{

}

int W_Lumino::decode_NewMode(QString data)
{
    qint32 li_etx;
    qint32 li_seq;
    qint32 li_pos;
    qint32 li_cnt;

    QString ls_code;
    QString ls_item;
    QString ls_result;
    QString ls_flag;
    QStringList lsl_unit;

    m_sData += data;
    li_etx = m_sData.indexOf(QString(QChar(LF)));

    if (li_etx < 0)
    {
        li_etx = m_sData.indexOf(QString(QChar(CR)));
        if (li_etx < 0)
        {
            return -1;
        }
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 1);

    while(ls_code.left(1) == QString(QChar(LF)))
    {
        ls_code = ls_code.mid(1);
    }

    while(ls_code.left(1) == QString(QChar(CR)))
    {
        ls_code = ls_code.mid(1);
    }

    ls_code = ls_code.trimmed();
    li_pos = ls_code.indexOf(" ");

    if (li_pos >= 0)
    {
        ls_flag = ls_code.left(li_pos).toUpper();
        ls_code = ls_code.mid(li_pos + 1);

        if (ls_flag == "PROT.")
        {
            li_pos = ls_code.indexOf("Name :");

            if (li_pos >= 0)
            {
                ls_code = ls_code.mid(li_pos + 6);
                li_pos = ls_code.indexOf(" ");

                if (li_pos >= 0)
                {
                    ls_item = ls_code.left(li_pos);
                }
            }
            else
            {
                ls_item = "";
            }
        }
        else if (ls_flag == "PAT.")
        {
            m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");
            lsl_unit = ls_code.split(" ");

            if (lsl_unit.size() >= 4)
            {
                li_seq = lsl_unit.at(0).trimmed().toInt();
                m_sSampleNo = QString::number(li_seq);
                ls_result = lsl_unit.at(3).trimmed();
            }
            else
            {
                if (lsl_unit.size() >= 1)
                {
                    li_seq = lsl_unit.at(0).trimmed().toInt();
                    m_sSampleNo = QString::number(li_seq);
                    ls_result = "";
                }
                else
                {
                    m_sSampleNo = "";
                    ls_result = "";
                }
            }

            if (lsl_unit.size() >= 6)
            {
                ls_flag = lsl_unit.at(5).trimmed();
            }
            else
            {
                ls_flag = "";
            }

            sendResult(ls_item,ls_result);

        }
        else if (ls_flag == "STND")
        {

        }
    }

    return 0;
}

int W_Lumino::decode(QString data)
{
    QString ls_code;
    QString ls_item;
    QString ls_result;
    QString ls_flag;
    qint32 li_etx;
    qint32 li_seq;


    if (m_bNewMode)
    {
        return decode_NewMode(data);
    }

    m_sData += data;
    li_etx = m_sData.indexOf(QString(QChar(LF)));

    if (li_etx < 0)
    {
        li_etx = m_sData.indexOf(QString(QChar(CR)));
        if (li_etx < 0)
        {
            return -1;
        }
    }

    m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");
    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 1);

    while(ls_code.left(1) == QString(QChar(LF)))
    {
        ls_code = ls_code.mid(1);
    }

    while(ls_code.left(1) == QString(QChar(CR)))
    {
        ls_code = ls_code.mid(1);
    }

    if (ls_code.left(1) == "O")     //未知，待确认，猜测是O
    {
        ls_item = ls_code.mid(1).trimmed();

    }
    else if (ls_code.left(1) == "R")
    {
        li_seq = ls_code.mid(m_nSampleNoStart - 1, m_nSampleNoLen).toInt();
        m_sSampleNo = QString::number(li_seq);
        m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");
        ls_result = ls_code.mid(m_nResultStart - 1, m_nResultLen);
        sendResult(ls_item,ls_result);
    }

    if (m_sData.indexOf(QString(QChar(LF))) >= 0)
    {
        redecode();
    }

    return 0;
}

void W_Lumino::loadConfig()
{
    BaseWindow::loadConfig();
    m_nSampleNoStart = readSetting("LUMINO/samplestart",4).toInt();
    m_nSampleNoLen = readSetting("LUMINO/samplestart",3).toInt();
    m_nResultStart = readSetting("LUMINO/resultstart",20).toInt();
    m_nResultLen = readSetting("LUMINO/resultstart",9).toInt();
    m_nFlagStart = readSetting("LUMINO/flagstart",19).toInt();
    m_nFlagLen = readSetting("LUMINO/flagstart",1).toInt();

    int mode = readSetting("LUMINO/newmode",0).toInt();
    if (mode == 0)
    {
        m_bNewMode = false;
    }
    else if (mode == 1)
    {
        m_bNewMode = true;
    }
}

void W_Lumino::on_action_DecodeSetup_triggered()
{
    this->show();
    Lumino_Setup *setup = new Lumino_Setup(this);
    setup->exec();
}
