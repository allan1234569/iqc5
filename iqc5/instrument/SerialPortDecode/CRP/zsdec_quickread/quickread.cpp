#include "quickread.h"
#include <QDateTime>
#include <QTime>
#include <QDebug>
#include <QLabel>
#include "common.h"


QuickRead::QuickRead(QWidget *parent) :
    BaseWindow(parent)
{
    this->setWindowTitle(tr("quickread"));
    m_bIsWorking = false;
    m_nSampleNo = 1;

    loadConfig();
}

int QuickRead::getEndPos(QString as_data) const
{
    int li_pos = 0;

    QString ls_data = as_data;

    li_pos = ls_data.indexOf(QString(QChar(LF)) + "Result");

    if (li_pos > 0)
    {
        li_pos = ls_data.indexOf(QChar(LF), li_pos + 1);

        if (li_pos > 0)
        {
            return li_pos;
        }
    }

    return 0;
}

int QuickRead::decode(const QString &data)
{
    if (!m_db.open())
    {
        return -1;
    }

    BaseWindow::decode(data);

    int li_stx = 0;
    int li_etx = 0;

    QString ls_data;
    QString ls_code;
    int li_size = 0;

    QStringList lsl_valList;

    QString ls_recdt;

    ls_data = m_sData;
    ls_data = m_dec.Replace(ls_data,"~r",QString(QChar(LF)).toStdString().data());
    li_etx = getEndPos(ls_data);

    if (li_etx == 0)
    {
        return 1;
    }

    ls_code = ls_data.left(li_etx);
    li_size = ls_code.length();
    ls_data = ls_data.mid(li_etx + 1);
    m_sData = ls_data;
    li_stx = ls_code.indexOf("Sample:");

    if (li_stx >= 0)
    {
        if (li_stx >= 10)
        {
            li_stx -= 10;
        }

        ls_code = ls_code.mid(li_stx);
    }
    else
    {
        return 1;
    }

    QString tempDoubleLf = QString(QChar(LF)) + QString(QChar(LF));
    QString tempLf = QString(QChar(LF));

    while (ls_code.indexOf(tempDoubleLf) >= 0)
    {
        ls_code = m_dec.Replace(ls_code, tempDoubleLf.toStdString().data(),tempLf.toStdString().data());
    }


    ls_recdt = QDate::currentDate().toString("yyyy/MM/dd");
    if (ls_recdt != m_sWorkDay)
    {
        m_sWorkDay = QDate::currentDate().toString("yyyy/MM/dd");
        m_nSampleNo = 1;
        writeSetting("QuickRead/WORKDATE",m_sWorkDay);
    }

    int li_upper = m_dec.PutStrToArray(ls_code, QString(QChar(LF)), lsl_valList);

    QString ls_result;
    QString ls_item;
    QString ls_date;
    QString ls_time;
    QString ls_seq;
    int li_pos;

    for(int li_low = 0; li_low < li_upper; li_low++)
    {
        ls_result = lsl_valList.at(li_low).trimmed();
        li_pos = ls_result.indexOf(" ");

        if (li_pos >= 0)
        {
            ls_item = ls_result.left(li_pos);
            ls_result = ls_result.mid(li_pos + 1);

            if (ls_item.compare("Sample:") == 0)
            {
                li_pos = ls_result.indexOf("/");
                ls_date = ls_result.mid(li_pos + 1);


                if (li_low > 0)
                {
                    ls_time = lsl_valList.at(li_low - 1).trimmed(); //样本号前面一行是时间
                }
                else
                {
                    ls_time = "";
                }

                QTime is_time = QTime::fromString(ls_time);
                if (is_time.isValid())
                {
                    ls_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
                }

                getSampleResultTime(ls_time);

                ls_seq = ls_result.left(li_pos);    //序列号
            }
            else if (ls_item.compare("Result") == 0)
            {
                li_pos = ls_result.indexOf("mg/l");

                if (li_pos >= 0)
                {
                    ls_result = ls_result.left(li_pos).trimmed();
                }

                if (1 == m_nUseSeqAsSampleNo)
                {
                    if (m_db.sendResult(ls_seq,QString("CRP"),ls_result,g_sRegInstr,g_sLabNo,ls_time) == 0)
                    {
                        m_nHandledSize += li_size;
                        m_db.close();
                    }
                }
                else if(0 == m_nUseSeqAsSampleNo)
                {
                    if (m_db.sendResult(QString::number(m_nSampleNo),QString("CRP"),ls_result,g_sRegInstr,g_sLabNo,ls_time) == 0)
                    {
                        m_nHandledSize += li_size;
                        m_db.close();
                    }
                }

                writeSetting("QuickRead/handledsize",m_nHandledSize);

                m_nSampleNo++;  //样本号自增
            }
        }
    }

    return 0;
}

void QuickRead::loadConfig()
{
    BaseWindow::loadConfig();

    m_sWorkDay = readSetting("QuickRead/WORKDATE","").toString();

    if (m_sWorkDay != QDate::currentDate().toString("yyyy/MM/dd"))
    {
        m_sWorkDay = QDate::currentDate().toString("yyyy/MM/dd");
        m_nSampleNo = 1;
        writeSetting("QuickRead/WORKDATE",m_sWorkDay);
    }
}
