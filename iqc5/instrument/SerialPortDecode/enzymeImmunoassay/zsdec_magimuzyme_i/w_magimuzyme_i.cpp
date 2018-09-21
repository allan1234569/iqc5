#include "w_magimuzyme_i.h"

W_Magimuzyme_i::W_Magimuzyme_i(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("酶免仪-MAGIMUZYME-I");

    loadConfig();
}

W_Magimuzyme_i::~W_Magimuzyme_i()
{

}

int W_Magimuzyme_i::getEndPos(QString as_data)
{
    QString ls_stx;
    QString ls_etx;
    qint32 li_pos;

    ls_stx = QString("\r\nID");
    ls_etx = QString("\r\n\r\n\r\n");
    li_pos = as_data.indexOf(ls_stx);

    while (li_pos >= 0)
    {
        li_pos = as_data.indexOf("\r\n",li_pos + 5);

        if (li_pos < 0)
        {
            return -1;
        }

        if (as_data.mid(li_pos,6) == ls_etx)
        {
            return (li_pos + 6);
        }
    }

    return -1;
}

void W_Magimuzyme_i::loadConfig()
{
    BaseWindow::loadConfig();

    m_nSampleStart = readSetting("MAGIMUZYME/samplestart",4).toInt();
    m_nSampleLen = readSetting("MAGIMUZYME/sampleslen",3).toInt();
    m_nResultStart = readSetting("MAGIMUZYME/resultstart",20).toInt();
    m_nResultLen = readSetting("MAGIMUZYME/resultlen",9).toInt();
    m_nFlagStart = readSetting("MAGIMUZYME/flagstart",19).toInt();
    m_nFlagLen = readSetting("MAGIMUZYME/flaglen",1).toInt();

    m_sItemHead = readSetting("MAGIMUZYME/itemhead","STAT PROTOCOL :").toString();
    m_sResultHead = readSetting("MAGIMUZYME/resulthead","Pat.#").toString();
}

void W_Magimuzyme_i::decode(QString data)
{
    QString ls_data;
    QString ls_code;
    QString ls_itemno;
    QString ls_result;
    QStringList lsl_line;
    QString ls_sampleno;
    qint32 li_etx;
    qint32 li_state;

    m_sData += data;
    ls_data = m_sData;
    li_etx = getEndPos(ls_data);

    if (li_etx < 0)
    {
        return;
    }

    ls_code = ls_data.left(li_etx);
    ls_data = ls_data.mid(li_etx + 1);
    m_sData = ls_data;

    lsl_line = ls_code.split("\r\n");

    for (int i = 0; i < lsl_line.size(); i++)
    {
        ls_result = lsl_line.at(i).trimmed();

        if (ls_result.indexOf(m_sItemHead) == 0)
        {
            ls_itemno = ls_result.mid(m_sItemHead.length()).trimmed();
            li_state = 1;
        }
        else
        {
            if (li_state == 1)
            {
                if (ls_result.indexOf(m_sResultHead) == 0)
                {
                    li_state == 2;
                    continue;
                }
            }

            if (li_state == 2)
            {
                ls_sampleno = lsl_line.at(i).left(6);
                if (ls_sampleno.toLong() > 0)
                {
                    m_sSampleNo = ls_sampleno;
                    ls_result = lsl_line.at(i).mid(15,7).trimmed();
                    m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");
                    sendResult(ls_itemno,ls_result);
                }
            }
        }
    }

}
