#include "w_rpc744.h"

W_Rpc744::W_Rpc744(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-RPC744");
}

W_Rpc744::~W_Rpc744()
{

}

void W_Rpc744::decode(QString data)
{
    m_sData += data;

    qint32 li_etx;
    qint32 li_pos;
    QString ls_code;
    QString ls_etx;
    QString ls_item;
    QString ls_result;
    QStringList lsl_ln;

    ls_etx.fill('\r',6);

    li_etx = m_sData.indexOf(ls_etx);

    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 6);

    m_sSampleNo = "";

    lsl_ln = ls_code.split("\r");

    for(int i = 0; i < lsl_ln.size(); i++)
    {
        ls_result = lsl_ln.at(i);
        li_pos = ls_result.indexOf("#");

        if (li_pos >= 0)
        {
            if (ls_result.indexOf("------") >= 0)
            {
                m_sSampleNo = ls_result.mid(li_pos + 1);
            }

            li_pos = ls_result.indexOf("ID#");

            if (li_pos >= 0)
            {
                ls_result = ls_result.mid(li_pos + 3).trimmed();

                if (ls_result.toInt() > 0)
                {
                    m_sSampleNo = ls_result;
                }
            }
        }

        if (m_sSampleNo != "")
        {
            li_pos = ls_result.indexOf(" ");

            if (li_pos >= 0)
            {
                ls_item = ls_result.left(li_pos).toUpper();
                ls_result = ls_result.mid(li_pos + 1);
                ls_item = ls_item.left(ls_item.length() - 1);

                if ((ls_item == "K") || (ls_item == "NA") || (ls_item == "CL"))
                {
                    li_pos = ls_result.toUpper().indexOf("MMOL/L");

                    if (li_pos >= 0)
                    {
                        ls_result = ls_result.left(li_pos);
                    }

                    ls_result = ls_result.replace(" ","");
                    sendResult(ls_item,ls_result);
                }
            }
        }
    }

    if (m_sData.indexOf(ls_etx) >= 0)
    {
        redecode();
    }
}
