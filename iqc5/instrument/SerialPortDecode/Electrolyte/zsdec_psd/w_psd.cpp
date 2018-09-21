#include "w_psd.h"

W_Psd::W_Psd(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-PSD");
}

W_Psd::~W_Psd()
{

}

void W_Psd::decode(QString data)
{
    m_sData += data;

    QString ls_code;
    QString ls_item;
    QString ls_result;
    QString ls_date;
    QString ls_time;
    QStringList lsl_unit;

    qint32 li_etx;
    qint32 li_pos;

    li_etx = m_sData.indexOf("\r\n");

    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 2);

    ls_code = ls_code.trimmed();
    li_pos = ls_code.indexOf(" ");

    if (li_pos >= 0)
    {
        ls_date = ls_code.left(li_pos);
        ls_code = ls_code.mid(li_pos + 1);
        li_pos = ls_code.indexOf(" ");

        if (li_pos >= 0)
        {
            ls_time = ls_code.left(li_pos);
            ls_code = ls_code.mid(li_pos + 1);
            m_sSampleDate = QDate::fromString(ls_date).toString("yyyy-MM-dd");

            li_pos = ls_code.indexOf(" ");

            if (li_pos >= 0)
            {
                m_sSampleNo = ls_code.left(li_pos);
                ls_code = ls_code.mid(li_pos + 1);
                lsl_unit = ls_code.split("=");

                for(int i = 0; i < lsl_unit.size(); i++)
                {
                    lsl_unit[i] = lsl_unit[i].trimmed();

                    if (i == 0)
                    {
                        ls_item = lsl_unit[0];
                    }
                    else
                    {
                        li_pos = lsl_unit.at(i).indexOf(" ");

                        if (li_pos >= 0)
                        {
                            ls_result = lsl_unit.at(i).left(li_pos);
                            sendResult(ls_item,ls_result);
                            ls_item = lsl_unit.at(i).mid(li_pos + 1).trimmed();
                        }
                        else
                        {
                            ls_result = lsl_unit.at(i);
                            sendResult(ls_item,ls_result);
                            ls_item = lsl_unit.at(i);
                        }
                    }
                }
            }
        }
    }


    if (m_sData.indexOf("\r\n") >= 0)
    {
        redecode();
    }
}
