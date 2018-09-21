#include "w_aft500.h"

W_Aft500::W_Aft500(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-AFT500");
}

W_Aft500::~W_Aft500()
{

}

void W_Aft500::decode(QString data)
{
    m_sData += data;

    QString ls_code;
    QString ls_head;
    QString ls_tail;
    int li_pos;


    if (m_sData.length() <= 0)
    {
        return;
    }

    li_pos = m_sData.indexOf(QChar(LF));

    while (li_pos >= 0)
    {
        ls_code = m_sData.left(li_pos).trimmed();
        m_sData = m_sData.mid(li_pos + 1);
        li_pos = ls_code.indexOf(" ");

        if (li_pos >= 0)
        {
            ls_head = ls_code.left(li_pos).trimmed();
            ls_tail = ls_code.mid(li_pos + 1);

            if (isDate(ls_head) && isTime(ls_tail))
            {
                m_sSampleResultDateTime = ls_head + " " + ls_tail;
            }

            goto label_0;
        }

        if (ls_code.indexOf("序列号:") == 0)
        {
            m_sSampleNo = ls_code.mid(7).trimmed();
        }
        else
        {
            if (ls_code.indexOf("样品编号:") == 0)
            {
                if (ls_code.mid(9).trimmed().toInt() > 0)
                {
                    m_sSampleNo = ls_code.mid(9).trimmed();
                }
            }
            else
            {
                li_pos = ls_code.indexOf("=");

                if (li_pos >= 0)
                {
                    ls_head = ls_code.left(li_pos).trimmed();   //项目名
                    ls_tail = ls_code.mid(li_pos).trimmed();
                    li_pos = ls_code.indexOf(" ");

                    if (li_pos >= 0)
                    {
                        ls_tail = ls_tail.left(li_pos);         //结果
                    }

                    sendResult(ls_head,ls_tail);
                }
            }
        }

        label_0:

        li_pos = m_sData.indexOf(QChar(LF));
    }
}
