#include "w_easylyte.h"

W_Easylyte::W_Easylyte(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-Easylyte");

    loadConfig();
}

W_Easylyte::~W_Easylyte()
{

}

void W_Easylyte::loadConfig()
{
    BaseWindow::loadConfig();

    m_nAutoSample = readSetting("EASYLYTE/autosample",0).toInt();
}

void W_Easylyte::decode(QString data)
{
    m_sData += data;

    qint32 li_stx;
    qint32 li_etx;
    qint32 li_pos;
    qint32 li_pos1;
    qint32 li_pos2;
    qint32 li_pos3;

    QString ls_code;
    QString ls_start;
    QString ls_end;
    QString ls_result;
    QStringList lsl_line;

    if (m_nAutoSample == 1)
    {
       decode_autoSample(data);
       return;
    }

    ls_start = "PATIENT'S NAME";
    ls_end.fill('\n',3);
    li_etx = m_sData.indexOf(ls_end);

    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + ls_end.length());

    li_stx = ls_code.indexOf(ls_start);

    while (li_stx >= 0)
    {
        ls_code = ls_code.mid(li_stx + ls_start.length());
        li_stx = ls_code.indexOf(ls_start);
    }

    m_sSampleNo = "";
    m_sSampleResultDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    lsl_line = ls_code.split("\n");

    for(int i = 0; i < lsl_line.size(); i++)
    {
        ls_code = lsl_line.at(i).trimmed();
        li_pos = ls_code.indexOf("SAMPLE");

        if (li_pos >= 0)
        {
            m_sSampleNo = ls_code.mid(li_pos + 6).trimmed();
        }
        else
        {
            li_pos = ls_code.indexOf("ID#");

            if (li_pos < 0)
            {
                continue;
            }
            m_sSampleNo = ls_code.mid(li_pos + 3);
        }

        if (i >= (lsl_line.size() - 1))
        {
            break;
        }

        ls_code = lsl_line.at(i+1);
        li_pos1 = ls_code.indexOf("Na");
        li_pos2 = ls_code.indexOf("K");
        li_pos3 = ls_code.indexOf("Cl");

        if ((li_pos1 < 0) || (li_pos2 < 0) || (li_pos3 < 0))
        {
            break;
        }

        ls_result = ls_code.mid(li_pos1 + 2,li_pos2 - li_pos1 - 2);
        sendResult("Na",ls_result);

        ls_result = ls_code.mid(li_pos2 + 1,li_pos3 - li_pos2 - 1);
        sendResult("K",ls_result);

        ls_result = ls_code.mid(li_pos3 + 2);
        sendResult("Cl",ls_result);
    }

    if (m_sData.indexOf(ls_end) >= 0)
    {
        redecode();
    }


}

void W_Easylyte::decode_autoSample(QString data)
{
    qint32 li_stx;
    qint32 li_etx;
    qint32 li_pos;
    qint32 li_pos1;
    qint32 li_pos2;
    qint32 li_pos3;
    qint32 li_tray = 0;

    QString ls_code;
    QString ls_data;
    QString ls_start;
    QString ls_end;
    QString ls_result;
    QStringList lsl_line;

    ls_data = data;

    ls_start = "TRAY =";
    ls_end = "\r\nBLOOD Na,K,Cl";

    li_etx = ls_data.indexOf(ls_end);

    if (li_etx < 0)
    {
        return;
    }

    ls_code = ls_data.left(li_etx);
    ls_data = ls_data.mid(li_etx + ls_end.length());
    li_stx = ls_code.indexOf(ls_start);

    if (li_stx >= 0)
    {
        ls_code = ls_code.mid(li_stx);
    }

    m_sSampleNo = "";
    m_sSampleResultDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    lsl_line = ls_code.split("\r\n");

    for(int i = 0; i < lsl_line.size(); i++)
    {
        ls_code = lsl_line.at(i);
        li_pos = ls_code.indexOf("TRAY =");

        if (li_pos >= 0)
        {
            li_tray = ls_code.mid(li_pos + 6).toInt();
        }
        else
        {
            if (li_tray > 0)
            {
                if (ls_code.indexOf("SAMPLE") == 0)
                {
                    ls_code = ls_code.mid(6).trimmed();
                    li_pos1 = ls_code.indexOf("Na");
                    li_pos2 = ls_code.indexOf("K");
                    li_pos3 = ls_code.indexOf("Cl");

                    if ((li_pos1 >= 0) && (li_pos1 >= 0) && (li_pos1 >= 0))
                    {
                        m_sSampleNo = ls_code.left(li_pos1).trimmed();
                        int num = li_tray *100 + m_sSampleNo.toInt();   //根据瑞美的方式来构造样本号
                        m_sSampleNo = QString::number(num);

                        ls_result = ls_code.mid(li_pos1 + 2,li_pos2 - li_pos1 - 2);
                        sendResult("Na",ls_result);

                        ls_result = ls_code.mid(li_pos2 + 1,li_pos3 - li_pos2 - 1);
                        sendResult("K",ls_result);

                        ls_result = ls_code.mid(li_pos3 + 2);
                        sendResult("Cl",ls_result);
                    }
                }
            }
        }
    }

    if (ls_data.indexOf(ls_end) >= 0)
    {
        decode(ls_data);
    }
}
