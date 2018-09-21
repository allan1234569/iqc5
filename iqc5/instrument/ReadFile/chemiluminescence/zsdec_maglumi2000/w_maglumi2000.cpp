#include "w_maglumi2000.h"

#include "maglumi2000_setup.h"

W_Maglumi2000::W_Maglumi2000(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-Maglumi2000");

    loadConfig();
}

W_Maglumi2000::~W_Maglumi2000()
{

}

void W_Maglumi2000::loadConfig()
{
    BaseWindow::loadConfig();

    m_nSampleDateIndex = readSetting("Maglumi2000/sampledateidx",1).toInt();
    m_nSampleNoIndex = readSetting("Maglumi2000/samplenoidx",2).toInt();
    m_nItemIndex = readSetting("Maglumi2000/itemidx",3).toInt();
    m_nResultIndex = readSetting("Maglumi2000/resultidx",5).toInt();
}

void W_Maglumi2000::decode(QString data)
{
    QString ls_data;
    QString ls_item;
    QString ls_result;
    QStringList lsl_unit;
    QStringList lsl_line;
    qint32 li_count;

    m_sData += data;
    ls_data = m_sData;
    m_sData = "";

    m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");

    lsl_line = ls_data.split("\r\n");

    for (int i = 0; i < lsl_line.size(); i++)
    {
        lsl_unit = lsl_line.at(i).split(" ");
        li_count = lsl_unit.size();

        if (    (li_count > m_nSampleDateIndex) &&
                (li_count > m_nSampleNoIndex) &&
                (li_count > m_nItemIndex) &&
                (li_count > m_nResultIndex)
                )
        {
            getSampleResultTime(lsl_unit.at(m_nSampleDateIndex - 1));
            m_sSampleNo = lsl_unit.at(m_nSampleNoIndex - 1);
            ls_item = lsl_unit.at(m_nItemIndex - 1);
            ls_result = lsl_unit.at(m_nResultIndex - 1);

            sendResult(ls_item,ls_result);
        }
    }

}

void W_Maglumi2000::slt_timeout()
{
    QString filePath;
    filePath = readSetting("Maglumi2000/datafile","").toString();

    QFile file(filePath);

    if (!file.exists())
    {
        return;
    }

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    else
    {
        readWriteLock.lockForRead();
        QString fileData =  QString::fromUtf8(file.readAll());
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

void W_Maglumi2000::on_action_DecodeSetup_triggered()
{
    this->show();
    Maglumi2000_Setup *setup = new Maglumi2000_Setup(this);
    setup->exec();
}
