#include "w_dsi903b.h"

W_Dsi903b::W_Dsi903b(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-DSI903B");

    loadConfig();
}

W_Dsi903b::~W_Dsi903b()
{

}

void W_Dsi903b::decode(QString data)
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

    if (m_nSegLen > 0)
    {
        ls_code = ls_code.right(ls_code.length() + 1 - m_nSegLen);
    }

    m_nSampleNo = ls_code.mid(m_nSampleNoStart-1,m_nSampleNoLen).toInt();

    sendResult("K",ls_code.mid(15,1) + "." + ls_code.mid(16,2));
    sendResult("NA",ls_code.mid(19,3) + "." + ls_code.mid(22,1));
    sendResult("CL",ls_code.mid(24,3) + "." + ls_code.mid(27,1));

    if (m_sData.indexOf(QChar(SUB)) >= 0)
    {
        redecode();
    }
}

void W_Dsi903b::loadConfig()
{
    BaseWindow::loadConfig();

    m_nSegLen = readSetting("DSI903B/seglen",29).toInt();
    m_nSampleNoStart = readSetting("DSI903B/samplenostart",11).toInt();
    m_nSampleNoLen = readSetting("DSI903B/samplenolen",4).toInt();
}
