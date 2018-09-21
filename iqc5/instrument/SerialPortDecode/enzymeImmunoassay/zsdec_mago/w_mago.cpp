#include "w_mago.h"

W_Mago::W_Mago(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("酶免仪-MAGO");
}

W_Mago::~W_Mago()
{

}

QString W_Mago::getItemNo(QString as_item)
{
    QString ls_item;
    QString ls_bit;

    as_item = as_item.toUpper();

    for (int i = 0; i < as_item.length(); i++)
    {
        ls_bit = as_item.mid(i, 1);

        if ((ls_bit >= "A") && (ls_bit <= "Z"))
        {
            ls_item = ls_item + ls_bit;
        }
    }

    return ls_item;
}

QString W_Mago::getResult(QString as_result)
{
    qint32 li_pos;

    li_pos = as_result.indexOf(QString(QChar(STX)));

    if (li_pos >= 0)
    {
        as_result = as_result.left(li_pos);
    }

    li_pos = as_result.indexOf("/");

    if (li_pos >= 0)
    {
        as_result = as_result.mid(li_pos + 1);
    }

    as_result = as_result.trimmed().toUpper();

    if ((as_result == "POSITIVE") || (as_result == "NEGATIVE") || (as_result == "WEAKPOSITIVE"))
    {
        as_result = "";
    }

    return as_result.trimmed();
}

void W_Mago::decode(QString data)
{
    QString ls_data;
    QString ls_code;
    QString ls_itemno;
    QString ls_val;
    QString ls_result;
    QString ls_stx;
    QString ls_etx;
    QStringList lsl_line;
    qint32 li_etx;
    qint32 li_stx;
    qint32 li_i;
    qint32 li_cnt;
    qint32 li_pos;

    m_sData += data;

    ls_etx = QString(QChar(STX)) + "</PACK>" + QString(QChar(ETX));
    ls_stx = QString(QChar(STX)) + "<PACK>" + QString(QChar(ETX));
    li_etx = m_sData.indexOf(ls_etx);

    if (li_etx < 0)
    {
        return;
    }

    ls_code = m_sData.left(li_etx);
    m_sData = m_sData.mid(li_etx + ls_etx.length());


    lsl_line = ls_code.split(ls_stx);

    for (int i = 0; i < lsl_line.size(); i++)
    {
        li_stx = lsl_line.at(i).indexOf(QString(QChar(STX)));

        if (li_stx > 0)
        {
            if (lsl_line.at(i).left(2) == "Q?")
            {
                lsl_line[i] = lsl_line[i].mid(2);
                li_pos = lsl_line[i].indexOf(QString(QChar(ETX)));

                if (li_pos > 0)
                {
                    lsl_line[i] = lsl_line[i].left(li_pos);
                }

                m_sSampleNo = lsl_line[i];
            }
            else if (lsl_line.at(i).left(2) == "t!")
            {
                lsl_line[i] = lsl_line[i].mid(2);
                li_pos = lsl_line[i].indexOf(QString(QChar(ETX)));

                ls_itemno = getItemNo(lsl_line[i].left(li_pos));

                if (!ls_itemno.isEmpty())
                {
                    ls_result = lsl_line[i].mid(li_pos + 1);
                    li_pos = ls_result.indexOf(QString(QChar(STX)) + "v!");

                    if (li_pos >= 0)
                    {
                        ls_result = ls_result.mid(li_pos + 3);
                        li_pos = ls_result.indexOf(QString(QChar(ETX)));

                        if (li_pos >= 0)
                        {
                            ls_val = ls_result.left(li_pos);
//                            ls_result = ls_result.mid(li_pos + 1);
//                            li_pos = ls_result.indexOf(QString(QChar(STX)) + "i!");

//                            if (li_pos >= 0)
//                            {
//                                ls_result = getResult(ls_result.mid(li_pos + 3));
//                            }
//                            else
//                            {
//                                ls_result = "";
//                            }
                        }
                        else
                        {
                            ls_val = ls_result;
                            ls_result = "";
                        }

                        ls_result = ls_val; //只要定量结果

//                        if (m_sResultFlag == "1") //数值结果
//                        {
//                            if (ls_val != "")
//                            {
//                                ls_result = ls_val;
//                            }
//                        }
//                        else if (m_sResultFlag == "2")   // 定性结果
//                        {
//                            if (ls_result == "")
//                            {
//                                ls_result = ls_val;
//                            }
//                        }
//                        else if (m_sResultFlag == "4")    //定性+定量
//                        {
//                            ls_result = (ls_result + " " + ls_val).trimmed();
//                        }
//                        else  //定量+定性
//                        {
//                            ls_result = (ls_val + " " + ls_result).trimmed();
//                        }

                        m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");
                        if (!ls_result.isEmpty())
                        {
                            sendResult(ls_itemno,ls_result);
                        }
                    }
                }
            }
        }
    }

    if (m_sData.indexOf(ls_etx) >= 0)
    {
        redecode();
    }
}
