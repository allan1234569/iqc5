#include "w_fluocycle.h"

W_Fluocycle::W_Fluocycle(QWidget *parent)
    : BaseWindow(parent)
{
}

W_Fluocycle::~W_Fluocycle()
{

}

int W_Fluocycle::decode(const QString &data)
{
    if (!m_db.open())
    {
        return -1;
    }

    f_loadConfig();

    QStringList lsl_line;
    QStringList lsl_unit;
    QString ls_head;
    unsigned int li_ok;

    QString ls_item;
    QString ls_result;
    QString ls_date;

    QString ls_str;
    QString ls_data;

    lsl_line = data.split("\n");

    for(int i = 0; i < lsl_line.size(); i++)
    {
        lsl_unit = lsl_line.at(i).split(";");
        if (lsl_unit.size() >= 5)
        {
            li_ok = 0;

            for(int j = 0; j < lsl_unit.size(); j++)
            {
                ls_str = lsl_unit.at(j);
                if (ls_str.indexOf("=") > 0)
                {
                    ls_head = ls_str.left(ls_str.indexOf("=")).toUpper();
                    ls_data = ls_str.mid(ls_str.indexOf("=") + 1).trimmed();

                    if (ls_head == "TESTDATE")
                    {
                        ls_data.replace(" ","");
                        ls_data.replace("年","-");
                        ls_data.replace("月","-");
                        ls_data.replace("日","");
//                        if (QDate::fromString(ls_data,"yyyy-MM-dd").isValid())
//                        {
                            ls_date = ls_data;
                            m_sSampleDate = ls_date;
                            li_ok++;
//                        }
                    }
                    else if (ls_head == "SAMPLEID")
                    {
                        m_sSampleNo = ls_data;
                        li_ok++;
                    }
                    else if (ls_head == "TESTCODE")
                    {
                        ls_item = ls_data;
                        li_ok++;
                    }
                    else if (ls_head == "RESULT")
                    {
                        ls_result = ls_data;
                        li_ok++;
                    }
                }
            }

            if (li_ok < 4)
            {
            }
            else
            {
                int ret = sendResult(ls_item,ls_result);

                if (ret == 0)
                {
                    QFile::remove(m_sFileName);
                }
            }
        }
    }

    return 0;
}
