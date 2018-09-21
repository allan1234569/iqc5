#include "w_easyreader.h"

W_EasyReader::W_EasyReader(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("快束读卡-EASYREADER");

    loadConfig();
}

W_EasyReader::~W_EasyReader()
{

}

void W_EasyReader::loadConfig()
{
    BaseWindow::loadConfig();

    m_nItemIndex = readSetting("EASYREADER/itemindex",1).toInt();
    m_nSampleDateIndex = readSetting("EASYREADER/sampledateindex",1).toInt();
    m_nSampleNoIndex = readSetting("EASYREADER/samplenoindex",1).toInt();
    m_nResultIndex = readSetting("EASYREADER/resultindex",1).toInt();
}

void W_EasyReader::decode(QString data)
{
    QString ls_data;
    QString ls_code;
    QString ls_itemno;
    QString ls_result;
    QString ls_date;
    QString ls_time;
    QString ls_key;
    QStringList lsl_line;

    qint32 li_etx;
    qint32 li_stx;
    qint32 li_pos;
    qint32 li_cnt;
    qint32 li_i;

    m_sData += data;
    li_etx = m_sData.indexOf(QString(QChar(ETX)));
    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 1);
    li_stx = ls_code.indexOf(QString(QChar(STX)));

    while(li_stx >= 0)
    {
        ls_code = ls_code.mid(li_stx + 1);
        li_stx = ls_code.indexOf(QString(QChar(STX)));
    }

    lsl_line = ls_code.split("\r");

    if ( (m_nItemIndex > 0) && (m_nItemIndex <= lsl_line.size()) )
    {
        ls_itemno = lsl_line.at(m_nItemIndex - 1).trimmed();
        li_pos = ls_itemno.indexOf("SYSTEM:");

        if (li_pos > 0)
        {
            ls_itemno = ls_itemno.mid(li_pos + 7).trimmed();
        }

        ls_key = QString("EASYREADER_Items/%1").arg(ls_itemno);
        ls_itemno = readSetting(ls_key.toStdString().data(),ls_itemno.left(10)).toString();
    }
    else
    {
        goto label_0;
    }

    if ( (m_nSampleDateIndex > 0) && (m_nSampleDateIndex <= lsl_line.size()) )
    {
        ls_date = lsl_line.at(m_nSampleDateIndex - 1).trimmed();
        li_pos = ls_date.indexOf(" ");
        ls_time = ls_date.mid(li_pos + 1).trimmed();

        m_sSampleDate = getSampleDate(ls_date.mid(6,4).toInt(),
                                      ls_date.mid(3,2).toInt(),
                                      ls_date.left(2).toInt());

    }
    else
    {
        goto label_0;
    }

    if ( (m_nSampleNoIndex > 0) && (m_nSampleNoIndex <= lsl_line.size()) )
    {
        m_sSampleNo = lsl_line.at(m_nSampleNoIndex - 1).trimmed();
    }
    else
    {
        goto label_0;
    }

    if ( (m_nResultIndex > 0)&& (m_nResultIndex <= lsl_line.size()) )
    {
        for (int i = m_nResultIndex - 1; i < lsl_line.size(); i++)
        {
            ls_result = lsl_line.at(i).trimmed();
            li_pos = ls_result.indexOf("RESULT:");

            if (li_pos > 0)
            {
                ls_result = ls_result.mid(li_pos + 7);
            }
            else
            {
                continue;
            }

            li_pos = ls_result.indexOf(" ");

            if (li_pos >= 0)
            {
                ls_result = ls_result.left(li_pos);
            }

            ls_key = QString("EASYREADER_results/%1").arg(ls_result);
            ls_result = readSetting(ls_key.toStdString().data(),ls_result).toString();

            sendResult(ls_itemno,ls_result);
        }
    }

label_0:
    if (m_sData.indexOf(QString(QChar(ETX))) >= 0)
    {
        redecode();
    }
}
