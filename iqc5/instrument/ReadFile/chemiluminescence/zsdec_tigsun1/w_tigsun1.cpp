#include "w_tigsun1.h"
#include "tigsun1_setup.h"

W_Tigsun1::W_Tigsun1(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-TIGSUN1");
}

W_Tigsun1::~W_Tigsun1()
{

}

void W_Tigsun1::decode(QString data)
{
    QString ls_date;
    QString ls_result;
    QString ls_data;
    QStringList lsl_line;
    QStringList lsl_unit;

    ls_data = data;
    lsl_line = ls_data.split("\r\n");

    for (int i = 0; i < lsl_line.size(); i++)
    {
        lsl_unit = lsl_line.at(i).split(",");

        if (lsl_unit.size() >= 5)
        {
            ls_date = lsl_unit.at(0).trimmed();

            if (ls_date.left(1) == QString(QChar(STX)))
            {
                ls_date = ls_data.mid(1);
            }

            getSampleResultTime(ls_date);

            m_sSampleNo = lsl_unit.at(2).trimmed();

            ls_result = lsl_unit.at(4).trimmed();
            if (ls_result.right(1) == QString(QChar(ETX)))
            {
                ls_result = ls_result.left(ls_result.length() - 1);
            }

            sendResult(lsl_unit.at(3).trimmed(),ls_result);
        }
    }
}

void W_Tigsun1::slt_timeout()
{
    QString filePath = readSetting("TIGSUN1/datafile","").toString();

    QFile file(filePath);

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

        readWriteLock.lockForRead();
        QString fileData =  in.readAll();
        file.close();
        readWriteLock.unlock();

        if (QFile::remove(filePath))
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

void W_Tigsun1::on_action_DecodeSetup_triggered()
{
    this->show();
    Tigsun1_Setup *setup = new Tigsun1_Setup(this);
    setup->exec();
}
