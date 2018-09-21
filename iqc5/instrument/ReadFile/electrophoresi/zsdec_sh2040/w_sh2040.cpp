#include "w_sh2040.h"
#include "autofile_setup.h"

W_Sh2040::W_Sh2040(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("电泳仪-SH2040");

    loadConfig();
}

W_Sh2040::~W_Sh2040()
{

}

void W_Sh2040::loadConfig()
{
    BaseWindow::loadConfig();

    m_nSampleNoIndex = readSetting("SH2040/samplenoidx",1).toInt();
    m_nItemIndex = readSetting("SH2040/itemidx",1).toInt();
    m_nResultIndex = readSetting("SH2040/resultidx",1).toInt();
    m_sResultFile = readSetting("resultfile","").toString();
    m_sResultFile += QString("/%1.txt").arg(QDate::currentDate().toString("yyyyMMdd"));

}

void W_Sh2040::decode(QString data)
{
    QString ls_code;
    QString ls_line;
    QString ls_result;
    QString ls_item;
    QStringList lsl_ln;

    m_sData = "";
    ls_code = data;
    m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");
    m_sSampleNo = "";

    lsl_ln = ls_code.split("\n");

    for(int i = 0; i < lsl_ln.size(); i++)
    {
        ls_line = lsl_ln.at(i);
        m_sSampleNo = m_dec.GetField(ls_line,",",m_nSampleNoIndex);

        if (!m_sSampleNo.isEmpty())
        {
           ls_item = m_dec.GetField(ls_line,",",m_nSampleNoIndex).trimmed();
           ls_result = m_dec.GetField(ls_line,",",m_nResultIndex).trimmed();

           if (!ls_item.isEmpty() && !ls_result.isEmpty())
           {
               sendResult(ls_item,ls_result);
           }
        }
    }
}

void W_Sh2040::on_action_DecodeSetup_triggered()
{
    this->show();   //如果主程序不显示出来，dialog关闭时，主程序将会关闭
    AutoFile_Setup *dialog = new AutoFile_Setup(this);

    dialog->exec();
}

void W_Sh2040::slt_timeout()
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

        readWriteLock.lockForRead();
        QString fileData =  in.readAll();
        file.close();
        readWriteLock.unlock();

//        if (QFile::remove(filePath))
//        {
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
//        }
    }
}

