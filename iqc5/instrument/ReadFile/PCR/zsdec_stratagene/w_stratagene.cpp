#include "w_stratagene.h"
#include "common.h"

W_Stratagene::W_Stratagene(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle(tr("CRP_STRATAGENE"));
    loadConfig();
}

W_Stratagene::~W_Stratagene()
{

}

void W_Stratagene::loadConfig()
{
    BaseWindow::loadConfig();

    m_nWellIndex = readSetting("stratagene/wellidx",1).toInt();
    m_nSampleNoIndex = readSetting("stratagene/samplenoidx",2).toInt();
    m_nResultIndex = readSetting("stratagene/resultidx",7).toInt();
}

int W_Stratagene::decode(const QString &data)
{
    f_loadConfig();

    QStringList lsl_line = data.split("\n");
    QStringList lsl_unit;

    QString ls_posno;
    bool lb_start = false;

    QString ls_sampleno;
    QString ls_date;
    QString ls_item;
    QString ls_result;

    for(int i = 0; i < lsl_line.size(); i++)
    {
        if (lsl_line.at(i).trimmed().isEmpty())
        {
            continue;
        }
        else
        {
            lsl_unit = lsl_line.at(i).split("\t");

            if (m_nWellIndex <= lsl_unit.size())
            {
                ls_posno = lsl_unit.at(m_nWellIndex-1).toUpper().trimmed();

                if (!lb_start)
                {
                    if (ls_posno == "WELL")
                    {
                        lb_start = true;
                    }
                }
                else
                {
                    if (m_nSampleNoIndex <= lsl_unit.size())
                    {
                        ls_sampleno = lsl_unit.at(m_nSampleNoIndex-1);

                        ls_date = ls_sampleno.left(8);
                        if (!QDate::fromString(ls_date,"yyyyMMdd").isValid())
                        {
                            continue;
                        }
                        ls_sampleno = ls_sampleno.mid(8);
                        ls_item = ls_sampleno.mid(0,ls_sampleno.length()-3);

                        m_sSampleNo = ls_sampleno.right(ls_sampleno.length() - 3);
                        m_sSampleDate = QDate::fromString(ls_date,"yyyyMMdd").toString("yyyy-MM-dd");

                        if (m_nResultIndex <= lsl_unit.size())
                        {
                            ls_result = lsl_unit.at(m_nResultIndex-1);

                            int ret = sendResult(ls_item,ls_result);
                            if (ret == 0)
                            {
                                QFile::remove(m_sFileName); //删除文件
                            }
                        }
                    }
                }
            }
        }
    }

    m_db.close();

    return 0;
}
