#include "w_qs8005.h"

W_Qs8005::W_Qs8005(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("酶免仪-QS8005");
}

W_Qs8005::~W_Qs8005()
{

}

void W_Qs8005::decode(QString data)
{
    QString ls_code;
    QString ls_itemno;
    QString ls_result;
    QString ls_sampleno;
    QStringList lsl_ln;
    qint32 li_stx;
    qint32 li_etx;
    qint32 li_pos;

    m_sData += data;
    li_etx = m_sData.indexOf(QString(QChar(ETX)));

    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 1);
    li_stx = ls_code.indexOf(QString(QChar(STX)));

    while (li_stx >= 0)
    {
        ls_code = ls_code.mid(li_stx + 1);
        li_stx = ls_code.indexOf(QString(QChar(STX)));
    }

    lsl_ln = ls_code.split("\r\n");

    if (lsl_ln.size() >= 4)
    {
        ls_sampleno = lsl_ln[1].trimmed();
        m_sSampleNo = ls_sampleno.mid(8);

        getSampleResultTime(lsl_ln[2].trimmed().left(16));

        for (int i = 3; i < lsl_ln.size(); i++)
        {
            ls_result = lsl_ln[i].trimmed();
            li_pos = ls_result.indexOf(" ");

            if (li_pos >= 0)
            {
                ls_itemno = ls_result.left(li_pos);
                ls_result = ls_result.mid(li_pos + 1).trimmed();

                if (!ls_result.isEmpty())
                {
                    sendResult(ls_itemno,ls_result);
                }
            }
        }
    }

    if (m_sData.indexOf(QString(QChar(ETX))) >= 0)
    {
        redecode();
    }
}
