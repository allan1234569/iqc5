#include "w_ireader.h"

W_Ireader::W_Ireader(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("快速读卡-IREADER");
}

W_Ireader::~W_Ireader()
{

}

void W_Ireader::decode(QString data)
{
    QString ls_code;
    QString ls_itemno;
    QString ls_result;
    qint32 li_etx;
    qint32 li_stx;
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;

    m_sData += data;
    li_etx = m_sData.indexOf(QString(QChar(ETX)));

    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + 1);
    li_stx = ls_code.indexOf(QString(QChar(STX)));

    ls_code = ls_code.mid(li_stx + 1);
    ls_result = ls_code.mid(0,6);
    li_year = ls_result.left(2).toInt();
    li_month = ls_result.mid(2,2).toInt();
    li_day = ls_result.mid(4,2).toInt();

    m_sSampleDate = getSampleDate(li_year,li_month,li_day);

//    //时间
//    ls_result = ls_code.mid(6,6);
//    ls_result = ls_result.left(2) + ":" + ls_result.mid(2,2) + ":" + ls_result.mid(4,2);

    m_sSampleNo = ls_code.mid(20,4);
    ls_itemno = ls_code.mid(12,8).trimmed();
    ls_result = ls_code.mid(24,8).trimmed();
    sendResult(ls_itemno,ls_result);

    if (m_sData.indexOf(QString(QChar(ETX))) >= 0)
    {
        redecode();
    }
}
