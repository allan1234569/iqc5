#include "adecodebase.h"
#include <QDateTime>
#include <QFile>
#include <QRegularExpression>

ADecodeBase::ADecodeBase()
{
}

int ADecodeBase::CutAstmCheckSum(QString &as_data) const
{
    int li_pos =  -1;
    int li_replaced = 0;

    li_pos = as_data.indexOf(char(2));

    while (li_pos >= 0)
    {
        as_data = as_data.replace(li_pos,1,"");
        li_replaced++;
        li_pos = as_data.indexOf(char(2));
    }

    li_pos = as_data.indexOf(char(23));

    while (li_pos >= 0)
    {
        if (as_data.mid(li_pos,5).length() == 5)
        {
            as_data = as_data.replace(li_pos,5,"");
            li_replaced++;
            li_pos = as_data.indexOf(char(23));
        }
        else
        {
            return li_replaced;
        }
    }

    li_pos = as_data.indexOf(char(3));

    while (li_pos >= 0)
    {
        if (as_data.mid(li_pos,5).length() == 5)
        {
            as_data = as_data.replace(li_pos,5,"");
            li_replaced++;
            li_pos = as_data.indexOf(char(3));
        }
        else
        {
            return li_replaced;
        }
    }

    return li_replaced;
}

QString ADecodeBase::CutZeroChar(QString as_data) const
{
    QByteArray ba = as_data.toLatin1();
    QByteArray lb_bit;
    QByteArray lb_ret;
    char lc_zero = char(0);
    int li_len = 0;
    li_len = ba.length();

    for(int i = 0; i < li_len; i++)
    {
        lb_bit = ba.mid(i,1);
        if (int(lb_bit.data()) != int(lc_zero))
        {
            lb_ret += lb_bit;
        }
    }

    return QString(lb_ret);



    return "";
}

int ADecodeBase::DivSampleNos(QString as_str, QString &as_ret) const
{
    int ll_pos = 0;
    int ll_pos1 = 0;
    QString ls_start;
    QString ls_end;
    int li_start = 0;
    int li_end = 0;
    int li_ret = 0;

    QString ls_str;

//    if (as_str.isEmpty() || as_str.trimmed().isEmpty())
//    {
//        return 0;
//    }

//    as_str = as_str.trimmed() + ",";
//    as_str = replace(as_str,"，",",");
//    as_str = replace(as_str,"－","-");

//    ll_pos = as_str.indexOf(",");

//    while (ll_pos >= 0)
//    {
//        ls_str = as_str.left(ll_pos - 1).trimmed();
//        as_str = as_str.mid(ll_pos + 1);
//        ll_pos = as_str.indexOf(",");

//        if (ls_str != "")
//        {
//            ll_pos1 = ls_str.indexOf("-");

//            if (ll_pos1 >= 0)
//            {
//                ls_start = ls_str.left(ll_pos1 - 1);
//                if (!IsDigitStr(ls_start))
//                {
//                    continue;
//                }

//                ls_end = ls_str.mid(ll_pos1 + 1);
//                if (!IsDigitStr(ls_end))
//                {
//                    continue;
//                }

//                li_start = ls_start.toInt();
//                li_end = ls_end.toInt();

//                for(int i = li_start; i < li_end; i++)
//                {
//                    li_ret++;
//                    as_ret.insert(li_ret,QString::number(i));   //不太确定
//                }
//            }
//            else
//            {
//                li_ret++;
//                as_ret.insert(li_ret,ls_str);   //不太确定
//            }
//        }
//    }

    return li_ret;
}

bool ADecodeBase::IsDigitStr(QString as_src) const
{
    QRegularExpression reg("\\d+.{0,1}\\d+");
    QRegularExpressionMatch match = reg.match(as_src);
    if (match.hasMatch())
    {
        return true;
    }
    else
    {
       return false;
    }
}

int ADecodeBase::GetBlankArray(QString as_str, QStringList &asl_list) const
{
    int li_pos = 0;
    int li_i = 0;

    while(as_str.length() > 0)
    {
        as_str = as_str.trimmed();
        li_pos = as_str.indexOf(" ");

        if (li_pos > 0)
        {
            asl_list.insert(li_i, as_str.left(li_pos -1));
            li_i++;
            as_str = as_str.mid(li_pos + 1);

        }
        else
        {
            if (as_str.length() > 0)
            {
                asl_list.insert(li_i, as_str);
                li_i++;
                return li_i;
            }
        }
    }
    return li_i;
}

int ADecodeBase::GetAscii(QByteArray ab_data) const
{
    QString ls_bit;
    ls_bit = ab_data.mid(1,1);

    if (ls_bit.length() > 0)
    {
        return int(ls_bit.toLatin1().data());
    }
    else
    {
        return 0;
    }
}

QString ADecodeBase::GetResult(QString as_result) const
{
    double ld_ret = 0;
    int li_e = 0;
    if (IsDigitStr(as_result))
    {
        ld_ret = as_result.toDouble();
        if (ld_ret == 0)
        {
            return "0,00";
        }

        while (ld_ret > 10)
        {
            ld_ret /= 10;
            li_e++;
        }

        while (ld_ret < 1)
        {
            ld_ret *= 10;
            li_e--;
        }

        as_result = QString("%1").arg(ld_ret) + "E";

        if (li_e == 0)
        {
            as_result.remove("E");
            return as_result;
        }
        else if (li_e > 0)
        {
            as_result += "+";
        }
        else
        {
            as_result += QString("%1").arg(li_e,2,10,QChar('0'));
        }
    }

    return as_result;
}

QString ADecodeBase::GetField(QString as_str, QString as_cut, quint32 as_index) const
{
    int li_pos = 0;
    int li_len = 0;
    int li_ret = 0;

    if (as_str.isNull() || as_str.trimmed().isEmpty())
    {
        return "";
    }

    li_len = as_cut.length();

    if (li_len <= 0)
    {
        return "";
    }

    if (as_str.right(li_len) != as_cut)
    {
        as_str += as_cut;
    }

    li_pos = as_str.indexOf(as_cut);

    while(li_pos > 0)
    {
        li_ret++;

        if (li_ret == as_index)
        {
            return as_str.left(li_pos - 1);
        }

        as_str = as_str.mid(li_pos,li_len);
        li_pos = as_str.indexOf(as_cut);

    }

    return "";
}

QString ADecodeBase::GetFileContent(QString as_file) const
{
    QFile file(as_file);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return "";
    }

    QByteArray ba = file.readAll();
    file.close();

    return ba;
}

QString ADecodeBase::GetLine(QString as_str, int as_lineNumber) const
{
    QString crlf = "\r\n";
    int li_pos1 = 0;
    int li_pos2 = 0;

    int li_count = 0;
    QString ls_data;

    if (as_str.isNull() | as_lineNumber <= 0)
    {
        return "";
    }

    if (as_str.right(2) != crlf)
    {
        as_str += crlf;
    }

    li_pos1 = 1;
    li_pos2 = as_str.indexOf(crlf);

    while (li_pos2 > 0)
    {
        li_count++;
        if (li_count == as_lineNumber)
        {
            return as_str.mid(li_pos1, li_pos2 - li_pos1);
        }

        li_pos1 = li_pos2 + 2;
        li_pos2 = as_str.indexOf(crlf,li_pos1);
    }

    return "";
}

int ADecodeBase::GetMonth(QString as_month) const
{
    if (as_month.toUpper() == "JAN")
    {
        return 1;
    }
    else if (as_month.toUpper() == "FEB")
    {
        return 2;
    }
    else if (as_month.toUpper() == "MAR")
    {
        return 3;
    }
    else if (as_month.toUpper() == "APR")
    {
        return 4;
    }
    else if (as_month.toUpper() == "MAY")
    {
        return 5;
    }
    else if (as_month.toUpper() == "JUN")
    {
        return 6;
    }
    else if (as_month.toUpper() == "JUL")
    {
        return 7;
    }
    else if (as_month.toUpper() == "AUG")
    {
        return 8;
    }
    else if (as_month.toUpper() == "SEP")
    {
        return 9;
    }
    else if (as_month.toUpper() == "OCT")
    {
        return 10;
    }
    else if (as_month.toUpper() == "NOV")
    {
        return 11;
    }
    else if (as_month.toUpper() == "DEC")
    {
        return 12;
    }
    else
    {
        return 0;
    }
}

int ADecodeBase::GetSeg(QString &as_data, QString as_stx, QString as_etx, QString &as_ret)
{
    int li_stx;
    int li_etx;

    if(as_stx.isEmpty())
    {
        return -1;
    }

    li_stx = as_data.indexOf(as_stx);

    if (li_stx < 0)
    {
        return -2;
    }

    li_etx = as_data.indexOf(as_etx, li_stx + as_stx.length());

    if (li_etx >= 0)
    {
        as_ret = as_data.mid(li_stx + as_stx.length(), li_etx - li_stx - as_stx.length());
        return 0;
    }
    else
    {
        as_ret = as_data.mid(li_stx + as_stx.length());
        return 1;
    }
}

int ADecodeBase::GetSeg(QString as_str, QStringList &asl_list)
{
    int li_pos = 0;
    int li_ret = 0;

    if (as_str.isNull() || as_str.trimmed().isEmpty())
    {
        return 0;
    }

    as_str = as_str.trimmed();

    li_pos = as_str.indexOf(" ");

    while (li_pos >= 0)
    {
        asl_list.insert(li_ret, as_str.left(li_pos - 1));
        as_str = as_str.mid(li_pos + 1);
        li_ret++;

        li_pos = as_str.indexOf(" ");
    }

    asl_list.insert(li_ret, as_str);
    li_ret++;

    return li_ret;
}

int ADecodeBase::HexToDec(QString as_hexStr) const
{

}

int ADecodeBase::PutArrayBlank(QString as_str, QStringList &asl_list)
{
    int li_pos = 0;
    int li_count = 0;


    if (as_str.isEmpty())
    {
        return 0;
    }

    as_str = as_str.trimmed();
    li_pos = as_str.indexOf(" ");

    while (li_pos > 0)
    {
        li_count++;
        asl_list.insert(li_count-1, as_str.left(li_pos - 1));
        as_str = as_str.mid(li_pos + 1).trimmed();
        li_pos = as_str.indexOf(" ");
    }

    if (!as_str.isEmpty())
    {
        li_count++;
        asl_list.insert(li_count-1, as_str);
    }

    return li_count;
}

int ADecodeBase::PutStrToArray(QString as_str, int ai_step, QStringList &asl_list)
{
    int li_count = 0;

    if (ai_step > 0)
    {
        li_count = as_str.length();
        if (li_count > ai_step)
        {
            if ((li_count%ai_step) > 0)
            {
                li_count = li_count/ai_step + 1;
            }
            else
            {
                li_count = li_count/ai_step;
            }

            for(int index = 0; index < li_count; index++)
            {
                asl_list.insert(index, as_str.mid(index*ai_step, ai_step));
            }

            return li_count;
        }
        else
        {
            asl_list.insert(0,as_str);
            return 1;
        }
    }
    else
    {
        asl_list.insert(0,as_str);
        return 1;
    }
}

int ADecodeBase::PutStrToArray(QString as_str, QString as_cut, QStringList &asl_list)
{
    int li_len = 0;
    int li_pos = 0;
    int li_ret = 0;

    if (as_str.isNull() || as_str.trimmed().isEmpty())
    {
        return 0;
    }

    li_len = as_cut.length();

    if (li_len <= 0)
    {
        return 0;
    }

    if (as_str.right(li_len) != as_cut)
    {
        as_str += as_cut;
    }

    if (as_cut == " ")
    {
        as_str = as_str.trimmed() + " ";
    }

    li_pos = as_str.indexOf(as_cut);

    while (li_pos > 0)
    {
        asl_list.insert(li_ret, as_str.left(li_pos - 1));
        li_ret++;
        as_str = as_str.mid(li_pos + li_len);

        if (as_cut == " ")
        {
            as_str = as_str.trimmed() + " ";
        }

        li_pos = as_str.indexOf(as_cut);
    }

    return li_ret;
}

QString ADecodeBase::Replace(QString as_str, const char *ac_before, const char *ac_after)
{
    if (as_str.isNull() || ac_before == NULL || ac_after == NULL || ac_before == "" || ac_after == "")
    {
        return as_str;
    }

    int ll_beforeLen = strlen(ac_before);
    int ll_afterLen = strlen(ac_after);

    int ll_pos = as_str.indexOf(ac_before);

    while(ll_pos >= 0)
    {
        as_str = as_str.replace(ll_pos,ll_beforeLen,ac_after);
        ll_pos = as_str.indexOf(ac_before,ll_pos+ll_afterLen);
    }

    return as_str;
}


char *ADecodeBase::ReplaceZeroChar(const char *ac_str)
{
    int li_len = 0;
    QByteArray lb_ret;

    if (ac_str == NULL)
    {
        return "";
    }

    QByteArray ba(ac_str);
    li_len = ba.length();

    for(int i = 0; i < li_len; i++)
    {
        if (ba.at(i) == char(0))
        {
            lb_ret += char(1);
        }
        else
        {
            lb_ret += ba.at(i);
        }
    }

    return lb_ret.data();
}

char *ADecodeBase::ReplaceZeroChar(const char *ac_str, int ai_char)
{
    int li_len = 0;
    QByteArray lb_ret;

    if (ai_char < 1 || ai_char > 255)
    {
        ai_char = 32;
    }

    QByteArray ba = ac_str;
    li_len = ba.length();

    for(int i = 0; i < li_len; i++)
    {
        if (ba.at(i) == char(0))
        {
            lb_ret += char(ai_char);
        }
        else
        {
            lb_ret += ba.at(i);
        }
    }

    return lb_ret.data();
}

QString ADecodeBase::TransEResult(QString as_result) const
{
    int li_pos = 0;
    QString ls_head;

    li_pos = as_result.indexOf("E");

    if (li_pos > 0)
    {
        ls_head = as_result.left(li_pos - 1);
        if (IsDigitStr(ls_head))
        {
            as_result = QString::number(ls_head.toDouble(),10,1) + "#" + as_result.mid(li_pos);
        }
    }

    return as_result;
}

QString ADecodeBase::TransNResult(QString as_result) const
{
    QString ls_ret;
    QString ls_bit;
    QString ls_result = as_result;

    while (ls_result.length() > 0)
    {
        ls_bit = ls_result.left(1);
        if (ls_bit == "0" ||
            ls_bit == "1" ||
            ls_bit == "2" ||
            ls_bit == "3" ||
            ls_bit == "4" ||
            ls_bit == "5" ||
            ls_bit == "6" ||
            ls_bit == "7" ||
            ls_bit == "8" ||
            ls_bit == "9" ||
            ls_bit == "-" ||
            ls_bit == "+" ||
            ls_bit == "."
            )
        {
            ls_ret += ls_bit;
        }

        ls_result= ls_result.mid(1);
    }

    return ls_ret;
}

QString ADecodeBase::TransUrineResult(QString as_result) const
{
    QString ls_ret;
    QString ls_bit;

    QString ls_result = as_result;

    while (ls_result.length() > 0)
    {
        ls_bit = ls_result.left(1);

        if (ls_bit == "." ||
            ls_bit == "+" ||
            ls_bit == "-" ||
            ls_bit == ">" ||
            ls_bit == "=" ||
            ls_bit == "<"
            )
        {
            ls_ret += ls_bit;
        }
        else
        {
            if (ls_bit >= "0" && ls_bit <= "9")
            {
                ls_ret += ls_bit;
            }
        }

        ls_result = ls_result.mid(1);
    }

    return ls_ret;
}
