#include "w_byr744.h"

W_Byr744::W_Byr744(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-BYR744");
}

W_Byr744::~W_Byr744()
{

}

void W_Byr744::decode(QString data)
{
    m_sData += data;

    QString ls_code;
    QString ls_item;
    QString ls_result;
    qint32 li_etx;
    qint32 li_pos;

    li_etx = m_sData.indexOf("\r");

    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx).trimmed();
    m_sData = m_sData.mid(li_etx + 1);

    if (ls_code.left(1) == "-")
    {
        li_pos = ls_code.indexOf("#");

        if (li_pos < 0)
        {
            goto label_0;
        }

        m_sSampleNo = ls_code.mid(li_pos + 1).trimmed();
    }
    else
    {
        ls_item = ls_code.left(2).toUpper();

        if ((ls_item == "NA") || (ls_item == "CL"))
        {
        }
        else
        {
            if (ls_item.left(1) == "K")
            {
               ls_item = "K";
            }
            else
            {
                goto label_0;
            }
        }

        li_pos = ls_code.indexOf(" ");

        if (li_pos >= 0)
        {
            ls_result = ls_code.mid(li_pos + 1);
            li_pos = ls_result.indexOf(" ");

            if (li_pos < 0)
            {
                li_pos = ls_result.toLower().indexOf("mmol/l");
            }

            if (li_pos >= 0)
            {
                ls_result = ls_result.left(li_pos);
            }

            m_sSampleResultDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            sendResult(ls_item,ls_result);
        }

    }

    label_0:

    if (m_sData.indexOf("\r") >= 0)
    {
        redecode();
    }

}
