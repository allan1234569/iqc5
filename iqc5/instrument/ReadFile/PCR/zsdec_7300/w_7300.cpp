#include "w_7300.h"
#include "common.h"

W_7300::W_7300(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle(tr("PCR_7300"));
    setFileSuffix("*.csv");
    setFileType(BaseWindow::CSV);
    loadConfig();
    init();
}

W_7300::~W_7300()
{

}

void W_7300::loadConfig()
{
    BaseWindow::loadConfig();

    if (m_db.open())
    {
        QStringList itemsList = m_db.getItems();
        initItemCombox(itemsList);
        m_db.close();
    }

    m_nResultIndex = readSetting("7300/resultidx",7).toInt();
    m_nWellIndex = readSetting("7300/wellidx",1).toInt();
    m_nsampleNoIndex = readSetting("7300/samplenoidx").toInt();
}

int W_7300::file_decode(const QString &filepath)
{
    QStringList lsl_list;
    QString ls_line;

    QFile file(filepath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return -1;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
    while(!in.atEnd())
    {
        ls_line = in.readLine();
        if (!ls_line.isEmpty() && !ls_line.trimmed().isEmpty())
        {
            lsl_list.insert(lsl_list.size(),ls_line);
        }
    }

    file.close();

    QString ls_ln;
    QStringList lsl_unit;
    bool lb_start = false;
    QString ls_posno;
    int li_row;
    int li_col;

    int li_curRow;

    QString ls_sampleno;
    QString ls_result;


    for(int i = 0; i < lsl_list.size(); i++)
    {
        ls_ln = lsl_list.at(i).trimmed();

        if (ls_ln.isEmpty())
        {

            continue;
        }

        lsl_unit = ls_ln.split(",");

        if (m_nWellIndex <= lsl_unit.size())
        {
            ls_posno = lsl_unit.at(m_nWellIndex-1).toUpper().trimmed();
            if (!lb_start)
            {
                if (ls_posno == "WELL")
                {
                    lb_start  = true;
                }
            }
            else
            {
               li_row = ls_posno.left(1).toInt() - QString(QChar('A')).toInt() + 1;
               li_col = ls_posno.mid(1).toInt();

               if (li_row > 0  && li_row <= 8)
               {
                   if (li_col > 0  && li_col <= 12)
                   {
                        if (m_nResultIndex <= lsl_unit.size())
                        {
                            ls_result = lsl_unit.at(m_nResultIndex-1).trimmed();
                        }

                        if (m_nsampleNoIndex > 0)
                        {
                            ls_sampleno = lsl_unit.at(m_nsampleNoIndex-1).trimmed();

                        }

                        if (ls_result.isEmpty())
                        {
                            ls_result = m_sEmptyResult;
                        }

                        li_curRow = insertRow();
                        setItemValue(li_curRow,0,ls_sampleno);
                        setItemValue(li_curRow,1,ls_result);
                        setItemValue(li_curRow,2,tr("未入库"));

                   }
               }
            }
        }
    }

    setResultHeader(1);
}

void W_7300::set_TableWidgetHeader()
{
    m_slHeaders << tr("样本号") << tr("结果") << tr("状态");
    ui->Result_TableWidget->clear();
    ui->Result_TableWidget->setColumnCount(m_slHeaders.size());
    ui->Result_TableWidget->setHorizontalHeaderLabels(m_slHeaders);
}

void W_7300::on_Import_PushButton_clicked()
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
        ls_itemNo   = ui->ItemCode_ComboBox->currentText();

        m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");

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
