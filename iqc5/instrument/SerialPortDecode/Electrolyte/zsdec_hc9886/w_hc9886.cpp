#include "w_hc9886.h"

#include <QTextBrowser>

W_Hc9886::W_Hc9886(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-HC9886");


    loadConfig();
}

W_Hc9886::~W_Hc9886()
{

}

void W_Hc9886::decode(QString data)
{
    qint32 li_etx;
    qint32 li_pos;
    qint32 li_i = 0;
    QString ls_code;
    QString ls_result;

    li_etx = m_sData.indexOf(QChar(LF));

    if (li_etx < 0)
    {
        return;
    }

    m_sData += data;
    ls_code = m_sData.left(li_etx).trimmed();
    m_sData = m_sData.mid(li_etx + 1);

    li_pos = ls_code.indexOf("\r");

    while (li_pos >= 0)
    {
        if (li_pos > 9)
        {
            ls_code = ls_code.left(li_pos);
        }
        else
        {
            ls_code = ls_code.mid(li_pos + 1);
        }

        li_pos = ls_code.indexOf("\r");
    }

    ls_code = ls_code.trimmed();

    li_pos = ls_code.indexOf(" ");

    if (li_pos >= 0)
    {
        m_sSampleNo = ls_code.left(li_pos);
        m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");

        ls_code = ls_code.mid(li_pos + 1).trimmed() + " ";
        li_pos = ls_code.indexOf(" ");

        while (li_pos >= 0)
        {
            ls_result = ls_code.left(li_pos);
            li_i++;

            if (li_i > m_slItems.size())
            {
                break;
            }

            sendResult(m_slItems.at(li_i - 1),ls_result);
        }
    }

    if (m_sData.indexOf("\n") >= 0)
    {
        redecode();
    }
}

void W_Hc9886::loadConfig()
{
    BaseWindow::loadConfig();

    m_sItems = readSetting("HC9886/items","K,NA,CL,iCa,Ca,PH,TCO2,AG").toString();
    m_slItems = m_sItems.split(",");
}
