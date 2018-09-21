#include "w_bhp9507.h"

W_Bhp9507::W_Bhp9507(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-BHP9507");

    setFileSuffix("*.xls");
    setFileType(BaseWindow::XLS);
    loadConfig();
    init();
}

W_Bhp9507::~W_Bhp9507()
{

}

void W_Bhp9507::file_decode(const QString as_file, const QString as_path)
{

}

void W_Bhp9507::excel_file_decode(const QString as_filepath)
{
   AExcel excel(as_filepath);
   if (!excel.openWorkSheet())
   {
       return;
   }

   int row_start = excel.getRowStart();
   int column_start = excel.getColumnStart();
   int row_count = excel.rowCount();
   int column_count = excel.columnCount();

   QString ls_posno;
   QString ls_result;
   QString ls_sampleno;
   QString ls_item;
   int li_curRowCount = 0;

   resetTableWidget();

   qDebug() << __LINE__;

   for(int i = row_start; i < row_count; i++)
   {
       ls_sampleno = excel.getItemValue(i,m_nSampleNoIndex);
       ls_result = excel.getItemValue(i,m_nResultIndex);

       qDebug() << __LINE__;
       if (ls_sampleno.left(1) == "U")
       {
            ls_sampleno = ls_sampleno.mid(1);
            li_curRowCount = insertRow();
            setItemValue(li_curRowCount,0,ls_sampleno);
            setItemValue(li_curRowCount,1,ls_result);
            setItemValue(li_curRowCount,2,"未入库");
       }
   }

   excel.close();
}

void W_Bhp9507::loadConfig()
{
    BaseWindow::loadConfig();

    m_nSampleNoIndex = readSetting("BHP9507/samplenoidx",1).toInt();
    m_nResultIndex = readSetting("BHP9507/resultidx",2).toInt();
    m_sLastItem = readSetting("BHP9507/lastitem","").toString();

    if (m_sLastItem.isEmpty())
    {
        ui->ItemCode_ComboBox->setCurrentIndex(0);
    }
    else
    {
        ui->ItemCode_ComboBox->setCurrentText(m_sLastItem);
    }
}

void W_Bhp9507::set_TableWidgetHeader()
{
    m_slHeaders << tr("样本号") << tr("结果") << tr("状态");
    ui->Result_TableWidget->clear();
    ui->Result_TableWidget->setColumnCount(m_slHeaders.size());
    ui->Result_TableWidget->setHorizontalHeaderLabels(m_slHeaders);
}

void W_Bhp9507::on_Import_PushButton_clicked()
{
    QString ls_sampleNo;
    QString ls_itemNo;
    QString ls_result;
    QString ls_datetime;
    int li_sampleNo;

    if (!m_db.open())
    {
        return;
    }

    int li_rowCnt = getRowCount();
    int li_cnt = 0;
    for(int row = 0; row < li_rowCnt; row++)
    {
        ls_sampleNo = getItemValue(row,0);
        m_sSampleNo = ls_sampleNo;

        ls_result   = getItemValue(row,1);
        ls_itemNo   = ui->ItemCode_ComboBox->currentIndex();


        ls_datetime     = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        m_sSampleDate = ls_datetime;

        int ret = sendResult(ls_itemNo,ls_result);

        if (ret == 0)
        {
            li_cnt++;

            li_sampleNo = ls_sampleNo.toInt();
            m_nMaxSampleNo = qMax(m_nMaxSampleNo,li_sampleNo);
            setItemValue(row,2,tr("已入库"));
        }
        else if (ret == 2)
        {
            break;
        }
    }

    m_db.close();

    QMessageBox msgBox;
    msgBox.setGeometry(this->pos().x() + this->width()/2,
                       this->pos().y() + this->height()/2,
                       msgBox.width(),
                       msgBox.height());
    msgBox.setWindowIcon(this->windowIcon());
    msgBox.setWindowTitle(tr("提示"));
    QString msgStr = QString("%1%2").arg(li_cnt).arg(tr("条记录成功入库"));
    msgBox.setText(msgStr);
    msgBox.exec();
}
