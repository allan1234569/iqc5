#include "w_da7600.h"
#include "common.h"
#include <QTextStream>

W_DA7600::W_DA7600(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle(tr("PCR_DA7600"));
    setFileSuffix(tr("*.csv"));
    setFileType(BaseWindow::CSV);
    loadConfig();
    init();
}

W_DA7600::~W_DA7600()
{

}

void W_DA7600::loadConfig()
{
    m_nWellIndex = readSetting("DA7600/wellidx",1).toInt();
    m_nResultIndex = readSetting("DA7600/resultidx",7).toInt();
    m_nSampleNoIndex = readSetting("DA7600/samplenoidx",2).toInt();
    m_nTypeIndex = readSetting("DA7600/typeidx",4).toInt();
    m_sIsStartWell = readSetting("DA7600/startwell","TUBE_NUM").toString();
    m_sIsSampleType = readSetting("DA7600/sample_type","UNK").toString();
}

int W_DA7600::file_decode(const QString &as_filepath)
{
    QStringList lsl_list;
    QString ls_line;


    QFile file(as_filepath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return -1;
    }

    QTextStream in(&file);

    while(!in.atEnd())
    {
        ls_line = in.readLine();
        if(!ls_line.trimmed().isEmpty())
        {
            lsl_list.insert(lsl_list.size(),ls_line);
        }
    }

    file.close();

    QString ls_sampleno;
    QString ls_result;
    QString ls_ln;
    QString ls_posno;
    QString ls_type;
    QStringList lsl_unit;
    bool lb_start = false;
    int li_curRow;

    for(int i = 0; i < lsl_list.size(); i++)
    {
        ls_ln = lsl_list.at(i).trimmed();
        lsl_unit = ls_ln.split(",");

        if (m_nWellIndex <= lsl_unit.size())
        {
            ls_posno = lsl_unit.at(m_nWellIndex-1).toUpper().trimmed();
            if (!lb_start)
            {
                if (ls_posno == m_sIsStartWell)
                {
                    lb_start = true;
                }
            }
            else
            {
                if (m_nTypeIndex <= lsl_unit.size())
                {
                    if (m_nResultIndex <= lsl_unit.size())
                    {
                        ls_type = lsl_unit.at(m_nTypeIndex-1).toUpper().trimmed();
                        if (ls_type != m_sIsSampleType)
                        {
                            continue;
                        }
                        else
                        {
                            ls_result = lsl_unit.at(m_nResultIndex-1).trimmed();

                            if (m_nSampleNoIndex > 0)
                            {
                                ls_sampleno = lsl_unit.at(m_nSampleNoIndex-1).trimmed();
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
    }

    setResultHeader(1);
}

void W_DA7600::set_TableWidgetHeader()
{
    m_slHeaders << tr("样本号") << tr("结果") << tr("状态");
    ui->Result_TableWidget->clear();
    ui->Result_TableWidget->setColumnCount(m_slHeaders.size());
    ui->Result_TableWidget->setHorizontalHeaderLabels(m_slHeaders);
}

void W_DA7600::on_Import_PushButton_clicked()
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
