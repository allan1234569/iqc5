#include "w_nexgen4.h"

W_Nexgen4::W_Nexgen4(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("酶免仪-Nexgen4");
}

W_Nexgen4::~W_Nexgen4()
{

}

void W_Nexgen4::decode(QString data)
{
    QString ls_code;
    QString ls_item;
    QString ls_result;
    QStringList lsl_unit;
    qint32 li_pos;

    m_sData += data;
    li_pos = m_sData.indexOf("\r\n");

    if (li_pos < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_pos);
    m_sData = m_sData.mid(li_pos + 2);
    li_pos = ls_code.indexOf(QString(QChar(STX)));

    if (li_pos >= 0)
    {
        ls_code = ls_code.mid(li_pos + 2);

        lsl_unit = ls_code.split(";");

        if (lsl_unit.size() >= 3)
        {
            m_sSampleNo = lsl_unit[0].trimmed();
            ls_item = lsl_unit[1].trimmed();
            ls_result = lsl_unit[2].trimmed();
            li_pos = ls_result.indexOf("\r");

            if (li_pos >= 0)
            {
                ls_result = ls_result.left(li_pos).trimmed();
            }

            li_pos = ls_result.indexOf(QString(QChar(ETB)));

            if (li_pos >= 0)
            {
                ls_result = ls_result.left(li_pos).trimmed();
            }

            m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");
            sendResult(ls_item,ls_result);
        }
    }

    if (m_sData.indexOf("\r\n") >= 0)
    {
        redecode();
    }
}
