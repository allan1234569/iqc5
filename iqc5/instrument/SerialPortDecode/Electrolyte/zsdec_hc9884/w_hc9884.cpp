#include "w_hc9884.h"

W_Hc9884::W_Hc9884(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-HC9884");

    loadConfig();
}

W_Hc9884::~W_Hc9884()
{

}

void W_Hc9884::decode(QString data)
{
    qint32 li_etx;
    qint32 li_pos;
    qint32 li_i = 0;
    QString ls_code;
    QString ls_result;
    QString ls_etx;

    ls_etx = QString("\r") + " " +QString(QChar(LF));

    li_etx = m_sData.indexOf(ls_etx);

    if (li_etx < 0)
    {
        return;
    }

    m_sData += data;
    ls_code = m_sData.left(li_etx).trimmed();
    m_sData = m_sData.mid(li_etx + 3);
    li_pos = ls_code.indexOf(" ");

    if (li_pos >= 0)
    {
        m_sSampleNo = ls_code.left(li_pos);
        m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");
        ls_code = ls_code.mid(li_pos + 1) + " ";

        li_pos = ls_code.indexOf(" ");

        while (li_pos >= 0)
        {
            li_i++;
            ls_result = ls_code.left(li_pos);

            if (li_i > m_slItems.size())
            {
                break;
            }
            sendResult(m_slItems.at(li_i - 1),ls_result);
            ls_code = ls_code.left( li_pos);
            li_pos = ls_code.indexOf(" ");
        }
    }

    if (m_sData.indexOf("\r\n") >= 0)  //待测试
    {
        redecode();
    }
}

void W_Hc9884::loadConfig()
{
    BaseWindow::loadConfig();

    m_sItems = readSetting("HC9884/items","K,NA,CL,TCO2,AG").toString();
    m_slItems = m_sItems.split(",");

}
