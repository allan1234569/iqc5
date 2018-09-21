#include "w_rapid.h"
#include "w_rapid_setup.h"

W_Rapid::W_Rapid(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("过敏原-RAPID");

    loadConfig();
}

W_Rapid::~W_Rapid()
{

}

void W_Rapid::decode(QString data)
{
    qint32 li_year;
    qint32 li_month;
    qint32 li_day;
    qint32 li_pos;
    QString ls_data;
    QString ls_sampledate;
    QString ls_result;
    QString ls_line;
    QString ls_item;
    QString ls_key;
    QStringList lsl_unit;

    QSettings setting(m_sResultFile,QSettings::IniFormat);

    ls_sampledate = setting.value("HEADER/DATE","").toString();

    li_pos = ls_sampledate.indexOf("-");

    if (li_pos >= 0)
    {
        li_year = ls_sampledate.left(li_pos).toInt();
        ls_sampledate = ls_sampledate.mid(li_pos + 1);
        li_pos = ls_sampledate.indexOf("-");

        if (li_pos >= 0)
        {
            li_month = ls_sampledate.left(li_pos).toInt();
            ls_sampledate = ls_sampledate.mid(li_pos + 1).toInt();
            li_day = ls_sampledate.toInt();

            m_sSampleDate = QDate(li_year,li_month,li_day).toString("yyyy-MM-dd");
        }
    }

    ls_data = data;

    ls_key = QString("%1/%2").arg(m_sSampleNoSeg).arg(m_sSampleNoKey);
    m_sSampleNo = setting.value(ls_key.toStdString().data(),"").toString();


    li_pos = ls_data.indexOf(QString("\n[LINES]"));

    if (li_pos >= 0)
    {
        ls_result = ls_data.mid(li_pos + 9);
        li_pos = ls_result.indexOf("\n");

        while(li_pos >= 0)
        {
            ls_line = ls_result.left(li_pos);
            ls_result = ls_result.mid(li_pos + 2).trimmed();
            lsl_unit = ls_line.split(";");

            if (lsl_unit.size() >= 5)
            {
                ls_item = lsl_unit.at(0).trimmed();
                ls_result = lsl_unit.at(4).trimmed();
                sendResult(ls_item,ls_result);
            }
        }
    }
}

void W_Rapid::loadConfig()
{
    m_sSampleNoSeg = readSetting("RAPID/samplenoseg","PATIENT").toString();

    m_sSampleNoKey = readSetting("RAPID/samplenokey","SAMPLE-ID").toString();

    m_sResultFile = readSetting("resultfile","").toString();
    m_sResultFile += QString("/%1.txt").arg(QDate::currentDate().toString("yyyyMMdd"));
}

void W_Rapid::on_action_DecodeSetup_triggered()
{
    this->show();
    W_Rapid_Setup *setupDialog = new W_Rapid_Setup;
    setupDialog->exec();
}

void W_Rapid::slt_timeout()
{


    QFile file(m_sResultFile);

    if (!file.exists())
    {
        return;
    }

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {

    }
    else
    {
        QTextStream in(&file);
        //            in.setCodec("UTF-8");

        QString fileData =  in.readAll();
        file.close();

        if (QFile::remove(m_sResultFile))
        {
            if (!fileData.isEmpty())
            {
                if (m_db.isOpened())
                {
                    m_Timer->stop();
                    decode(fileData);
                    m_Timer->start();
                }
                else
                {
                    if (m_db.open())
                    {
                        m_Timer->stop();
                        decode(fileData);
                        m_Timer->start();
                    }
                }

            }
        }
    }
}
