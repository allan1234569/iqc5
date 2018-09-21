#include "w_seibacom.h"

W_SeibaCom::W_SeibaCom(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电泳仪-SEIBA_COM");
}

W_SeibaCom::~W_SeibaCom()
{

}

void W_SeibaCom::decode(QString data)
{
    m_sData += data;

    int li_etx;
    int li_eot;
    int li_stx;
    int li_i;
    QString ls_code;
    QString ls_patid;
    QString ls_item;
    QString ls_result;
    QString ls_dot;
    QString ls_gr;
    QString ls_flag;

    li_etx = m_sData.indexOf(QString(QChar(STX)));
    li_eot = m_sData.indexOf(QString(QChar(EOT)));

    if (li_etx < 0)
    {
        if (li_eot < 0)
        {
            return;
        }

        li_etx = li_eot;
    }
    else
    {
        if ((li_eot >= 0) && (li_eot > li_etx))
        {
            li_etx = li_eot;
        }
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 1);

    if (ls_code.mid(1,1).toUpper() == "D")
    {
        m_sSampleNo = ls_code.mid(2,4).trimmed();
        ls_patid = ls_code.mid(6,15);

        m_sSampleDate = QDate(ls_code.mid(261,4).toInt(),
                              ls_code.mid(259,2).toInt(),
                              ls_code.mid(257,2).toInt())
                .toString("yyyy-MM-dd");

        int li_cnt = ls_code.mid(265,2).toInt();

        for(int i = 0; i < li_cnt; i++)
        {
            ls_item = ls_code.mid(268 + i * 10 - 1, 10).trimmed();

            if (!ls_item.isEmpty())
            {
                ls_result = ls_code.mid(368 + i * 5 - 1, 5);

                if (isNumber(ls_result))
                {
                    ls_result = QString::number(ls_result.toDouble());
                }

                sendResult(ls_item,ls_result);
            }
        }

        ls_result = ls_code.mid(548, 5);

        if (!ls_result.isEmpty())
        {
            if (isNumber(ls_result))
            {
                ls_result = QString::number(ls_result.toDouble());
            }

            sendResult("A/G",ls_result);
        }
    }

    if ((m_sData.indexOf(QString(QChar(ETX))) >= 0) || (m_sData.indexOf(QString(QChar(EOT))) >= 0))
    {
        redecode();
    }
}
