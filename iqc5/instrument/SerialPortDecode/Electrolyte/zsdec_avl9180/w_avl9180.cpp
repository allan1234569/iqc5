#include "w_avl9180.h"

W_Avl9180::W_Avl9180(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-AFT9180");
}

W_Avl9180::~W_Avl9180()
{

}

void W_Avl9180::decode(QString data)
{
    m_sData += data;

    QString ls_code;
    QString ls_item;
    QString ls_result;
    QStringList lsl_line;
    qint32 li_etx;
    qint32 li_pos;

    li_etx = m_sData.indexOf(QChar(ETX));

    if (li_etx < 0)
    {
        return ;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 1);
    m_sSampleNo = "";

    lsl_line = ls_code.split("\n");

    for (int i = 0; i <lsl_line.size(); i++)
    {
        ls_code = lsl_line.at(i).trimmed();
        li_pos = ls_code.indexOf("Sample No.");

        if (li_pos >= 0)
        {
            m_sSampleNo = ls_code.mid(li_pos + 10);
            m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");
            m_sSampleResultDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        }
        else
        {
            ls_item = ls_code.left(2).trimmed().toUpper();

            if ((ls_item == "K") || (ls_item == "NA") || (ls_item == "CL"))
            {
                li_pos = ls_code.indexOf("=");

                if (li_pos >= 0)
                {
                    ls_result = ls_code.mid(li_pos + 1);
                    li_pos = ls_result.indexOf(" ");
                    ls_result = ls_result.left(li_pos);
                    sendResult(ls_item,ls_result);
                }
            }
        }
    }

    if (m_sData.indexOf(QChar(ETX)) >= 0)
    {
        redecode();
    }
}
