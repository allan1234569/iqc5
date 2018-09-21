#include "w_dsi903.h"

W_Dsi903::W_Dsi903(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-DSI903");
}

W_Dsi903::~W_Dsi903()
{

}

void W_Dsi903::decode(QString data)
{
    m_sData += data;

    QString ls_code;
    qint32 li_pos;

    li_pos = m_sData.indexOf(QChar(SUB));

    if (li_pos < 0)
    {
        return;
    }

    m_sSampleResultDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    ls_code = m_sData.left(li_pos);
    m_sData = m_sData.mid(li_pos + 1);

    m_sSampleNo = ls_code.left(5);
    sendResult("NA",ls_code.mid(6,3));
    sendResult("K",ls_code.mid(10,4));
    sendResult("CL",ls_code.mid(15,3));

    if (m_sData.indexOf(QChar(SUB)) >= 0)
    {
        redecode();
    }
}
