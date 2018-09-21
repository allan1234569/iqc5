#include "nycocard.h"
#include <QDebug>
#include <QDateTime>

#include "common.h"

Nycocard::Nycocard(QWidget *parent) :
    BaseWindow(parent)
{
}

void Nycocard::loadConfig()
{
    ls_stx = readSetting("NYCOCARD/STX",QString("CRP Whole blood Result:")).toString();
    ls_etx = readSetting("NYCOCARD/ETX","mg/L").toString();
    if (ls_etx.isEmpty())
    {
        ls_etx = "mg/L";
    }
}

void Nycocard::decode( QString &data)
{
    BaseWindow::decode(data);   //调用父类的方法，做一些通用的处理

    QString ls_code;
    QString ls_data;
    QString ls_lastDate;


    if ( -1 == data.indexOf(ls_etx) )   //
    {
        return;
    }

    ls_code = m_sData.left(data.indexOf(ls_etx)-1);      //待处理的数据
    m_sData = getRightStr(m_sData,ls_etx);               //下次处理的数据

    if (ls_code.indexOf(ls_stx) >= 0)
    {
        ls_code = getRightStr(ls_code,ls_stx);
        ls_code.trimmed();
        if (!ls_code.isEmpty())
        {
            QString tempDateTime = QDateTime::currentDateTime().toString("yyyyMMdd");
            QString tempResultDataTime = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
            ls_lastDate = readSetting("NYCOCARD/sampledate","").toString();

            if (ls_lastDate == tempDateTime)
            {
                li_sampleNo = readSetting("NYCOCARD/sampleno",0).toInt();
                if (li_sampleNo > 0)
                {
                    ++li_sampleNo;
                }
                else
                {
                    li_sampleNo = 1;
                }
            }
            else
            {
                writeSetting("NYCOCARD/sampledate",tempDateTime);
                li_sampleNo = 1;
            }

            m_nSampleNo = li_sampleNo;
            writeSetting("NYCOCARD/sampleno",m_nSampleNo);
            //TODO  数据分析，发送
        }

    }

    if (ls_data.indexOf(ls_etx) > 0 )
    {
        redecode();
    }
}
