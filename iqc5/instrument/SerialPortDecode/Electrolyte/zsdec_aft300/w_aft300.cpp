#include "w_aft300.h"

W_AFT300::W_AFT300(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电解质-AFT300");
}

W_AFT300::~W_AFT300()
{

}

void W_AFT300::decode(QString data)
{
    m_sData += data;

    QString ls_code;
    quint32 li_seq;
    quint32 li_sampleno;
    QString ls_result;

    QString ls_start;
    ls_start.resize(5);

    ls_start.insert(3,dateToByteString(QDate::currentDate().toString("dd")));
    ls_start.insert(4,dateToByteString(QDate::currentDate().toString("MM")));
    ls_start.insert(5,dateToByteString(QDate::currentDate().toString("yy")));

    while(m_sData.size() > 31)
    {
        if (m_sData.mid(0,5) == ls_start)
        {
            ls_code = m_sData.mid(0,32);
            m_sData = m_sData.mid(32);

            m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");
            m_sSampleResultDateTime = m_sSampleDate + " " + hex(ls_code.mid(5,1)) + hex(ls_code.mid(6,1));

            li_seq = getAsc(ls_code.mid(7,1)) * 256;
            li_seq += getAsc(ls_code.mid(8,1));

            li_sampleno = getAsc(ls_code.mid(30,1)) *256;
            li_sampleno += getAsc(ls_code.mid(31,1));

            if (li_sampleno > 0)
            {
                m_sSampleNo = QString::number(li_sampleno);
            }
            else
            {
                m_sSampleNo = QString::number(li_seq);
            }

            ls_result = QString::number(getAsc(ls_code.mid(10,1)) +  getAsc(ls_code.mid(11,1)) / 256);
            sendResult("K",ls_result);

            ls_result = QString::number(getAsc(ls_code.mid(13,1)) +  getAsc(ls_code.mid(14,1)) / 256);
            sendResult("NA",ls_result);

            ls_result = QString::number(getAsc(ls_code.mid(16,1)) +  getAsc(ls_code.mid(17,1)) / 256);
            sendResult("CL",ls_result);

            ls_result = QString::number(getAsc(ls_code.mid(19,1)) +  getAsc(ls_code.mid(20,1)) / 256);
            if (ls_result.toInt() != 0)
            {
                sendResult("CA",ls_result);
            }

            ls_result = QString::number(getAsc(ls_code.mid(22,1)) +  getAsc(ls_code.mid(23,1)) / 256);
            if (ls_result.toInt() != 0)
            {
                sendResult("PH",ls_result);
            }

            ls_result = QString::number(getAsc(ls_code.mid(25,1)) +  getAsc(ls_code.mid(26,1)) / 256);
            if (ls_result.toInt() != 0)
            {
                sendResult("nCA",ls_result);
            }

            if (m_sData.size() > 31)
            {
                redecode();
            }
        }
        else
        {
           m_sData = m_sData.mid(1);
        }
    }
}
