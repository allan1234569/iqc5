#include "d280.h"

D280::D280(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle(tr("d280"));

    init();
}

D280::~D280()
{

}

int D280::decode(const QString &data)
{
    if (!m_accessDB.queryDB(m_queryStr))
    {
        return 1;
    }

    QStringList fields;
    fields << QString("inside_id") << QString("item") << QString("result") << QString("time") << QString("unit");

    updateOriginalTableWidget(m_accessDB.m_query,fields);
}

void D280::slt_setQuery()
{
    qDebug() << m_sSampleDate;
    QString ldt_sampledt = (QDateTime::fromString(m_sSampleDate,"yyyy-MM-dd")).toString("yyyyMMdd");
    if (!ldt_sampledt.isEmpty())
    {
        m_queryStr = QString("SELECT inside_id,item,time,result,unit FROM result_item "
                             "WHERE inside_id like ':%1\%'"
                             "ORDER BY inside_id ASC,time ASC")
                .arg(ldt_sampledt);
    }
    else
    {
        m_queryStr = "";
    }


}

void D280::loadConfig()
{
    BaseWindow::loadConfig();

    driver = readSetting("D280/driver","Microsoft Access Driver (*.mdb, *.accdb)").toString();
    databasePath = readSetting("D280/databasepath","").toString();
    uid = readSetting("D280/uid","").toString();
    password = readSetting("D280/password","").toString();
}

void D280::on_Select_PushButton_clicked()
{
    QString dbFileName = QFileDialog::getOpenFileName(this,
                                                      tr("请选择数据文件"),
                                                      tr("./"),
                                                      tr("DB Files (*.mdb)")
                                                      );

    if (!dbFileName.isEmpty())
    {
        setDatabaseFilePath(dbFileName);
        writeSetting("D280/databasepath",dbFileName);
    }
}
