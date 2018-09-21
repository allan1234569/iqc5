#include "w_mx3000p.h"
#include "common.h"


W_MX3000P::W_MX3000P(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle(tr("PCR_MX3000P"));
    setFileSuffix("*.xls,*.xlsx");
    setFileType(BaseWindow::XLS);
    loadConfig();
    init();
}

W_MX3000P::~W_MX3000P()
{

}

void W_MX3000P::loadConfig()
{
     m_nWellIndex = readSetting("mx3000p/wellidx",1).toInt();
     m_nSampleNoIndex = readSetting("mx3000p/samplenoidx",2).toInt();
     m_nItemIndex  = readSetting("mx3000p/itemidx",3).toInt();
     m_nResultIndex = readSetting("mx3000p/resultidx",7).toInt();
}

void W_MX3000P::excel_file_decode(const QString as_filepath)
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
    int li_row;
    int li_col;
    bool lb_start = false;

    int li_curRowCount = 0;

    if (row_count - row_start <= 0)
    {
        resetTableWidget();
    }

    for(int i = row_start; i <= row_count; i++)
    {
        if (m_nWellIndex > 0 && m_nWellIndex <= column_count)
        {
//            QAxObject *cell = workSheet->querySubObject("Cells(int,int)",i,m_nWellIndex);
//            if (cell == NULL)
//            {
//                continue;
//            }

//            ls_posno = cell->dynamicCall("Value2()").toString().trimmed().toUpper();

            ls_posno = excel.getItemValue(i,m_nWellIndex).trimmed().toUpper();
            if (ls_posno.isEmpty())
            {
                continue;
            }

            if (!lb_start)
            {
                if (ls_posno == "WELL")
                {
                    lb_start = true;
                }
            }
            else
            {
                if (ls_posno.isEmpty())
                {
                    return;
                }

                li_row = ls_posno.left(1).toInt() - QString(QChar('A')).toInt() + 1;
                li_col = ls_posno.mid(1).toInt();

                if (li_row > 0 && li_row <= 8)
                {
                    if (li_col > 0 && li_col <= 12)
                    {
                        if (m_nItemIndex > 0 && m_nItemIndex <= column_count)
                        {
                            ls_item = excel.getItemValue(i,m_nItemIndex);
                        }

                        if (m_nResultIndex > 0 && m_nResultIndex <= column_count)
                        {
                            ls_result = excel.getItemValue(i,m_nResultIndex);
                        }

                        if (m_nSampleNoIndex > 0 && m_nSampleNoIndex <= column_count)
                        {
                            ls_sampleno = excel.getItemValue(i,m_nSampleNoIndex);
                        }

                        li_curRowCount = insertRow();
                        setItemValue(li_curRowCount,0,ls_sampleno);
                        setItemValue(li_curRowCount,1,ls_item);
                        setItemValue(li_curRowCount,2,ls_result);
                        setItemValue(li_curRowCount,3,tr("未入库"));


                    }
                }
            }
        }
    }

    setResultHeader(2);

    excel.close();
}

void W_MX3000P::set_TableWidgetHeader()
{
    m_slHeaders << tr("样本号") << tr("项目") << tr("结果") << tr("状态");
    ui->Result_TableWidget->clear();
    ui->Result_TableWidget->setColumnCount(m_slHeaders.size());
    ui->Result_TableWidget->setHorizontalHeaderLabels(m_slHeaders);
}

void W_MX3000P::on_Import_PushButton_clicked()
{
    QString ls_sampleNo;
    QString ls_itemNo;
    QString ls_result;
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
        ls_itemNo   = getItemValue(row,1);
        ls_result   = getItemValue(row,2);

        m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");

        int ret = sendResult(ls_itemNo,ls_result);
        if (ret == 0)
        {
            li_cnt++;

            li_sampleNo = ls_sampleNo.toInt();
            m_nMaxSampleNo = qMax(m_nMaxSampleNo,li_sampleNo);
            setItemValue(row,3,tr("已入库"));
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
