#include "w_wiacalc.h"

W_Wiacalc::W_Wiacalc(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-WIACALC");
    setFileSuffix("*.A");
    setFileType(BaseWindow::TXT);

    loadConfig();

    init();

    m_bIsDual = false;

}

W_Wiacalc::~W_Wiacalc()
{

}

qint32 W_Wiacalc::getPos(QString as_str)
{
    qint32 li_i;
    qint32 li_pos;

    li_pos = as_str.indexOf(m_sSampleId);

    if (li_pos < 0)
    {
        return -1;
    }

    for (li_i = li_pos - 1; li_i >= 0; li_i--)
    {
        if (as_str.mid(li_i,1) < " ")
        {
            break;
        }
    }

    m_nSampleNoPos = li_i + 1;
    m_nSampleNoTransLen = li_pos + m_sSampleId.length() - (m_nSampleNoPos - 1);
    li_pos = as_str.indexOf(m_sResult);

    if (li_pos < 0)
    {
        return -1;
    }

    for (li_i = li_pos - 1; li_i >= 0; li_i--)
    {
        if (as_str.mid(li_i,1) < " ")
        {
            break;
        }
    }

    m_nResultPos = li_i + 1;
    m_nResultLen = li_pos + m_sResult.length() - (m_nResultPos - 1);

    return 0;

}

void W_Wiacalc::set_TableWidgetHeader()
{
    m_slHeaders << tr("样本号") << tr("结果") << tr("状态");
    ui->Result_TableWidget->clear();
    ui->Result_TableWidget->setColumnCount(m_slHeaders.size());
    ui->Result_TableWidget->setHorizontalHeaderLabels(m_slHeaders);
}

void W_Wiacalc::file_decode(const QString as_file, const QString as_path)
{
    QString ls_data;
    QString ls_result;
    QString ls_r1;
    QString ls_r2;
    QStringList lsl_array;
    qint32 li_i;
    qint32 li_file;
    qint32 li_curRow;

    QString filename = as_path + as_file;

    QFile file(filename);

    if (!file.open(QFile::ReadOnly))
    {
        return;
    }

    ls_data = QString::fromUtf8(file.readAll().data());
    li_file = as_file.indexOf(".");
    if (li_file >= 0)
    {
        m_sItem = as_file.left(li_file);
    }
    else
    {
        m_sItem = as_file;
    }

    lsl_array = ls_data.split("\r\n");

    if (lsl_array.size() < 1)
    {
        return;
    }

    m_bIsDual = false;

    for (li_i = 0; li_i < lsl_array.size(); li_i++)
    {
        if (lsl_array.at(li_i).left(4) == " SEQ")
        {
            if (getPos(lsl_array.at(li_i)) < 0)
            {
                return;
            }

            break;
        }
    }

    if (li_i >= lsl_array.size())
    {
        return;
    }

    for (li_i = li_i + 1; li_i < lsl_array.size(); li_i++)
    {
        if (m_bIsDual)
        {
            m_sSampleNo = lsl_array.at(li_i).left(8).trimmed();

            if (m_sSampleNo.toLong() < 0)
            {
                continue;
            }

            ls_r1 = lsl_array.at(li_i).mid(17,11).trimmed();
            ls_r2 = lsl_array.at(li_i).mid(37,10).trimmed();

            if (ls_r1.trimmed().toUpper() == "OUT")
            {
                ls_r1 = m_sOut;
            }

            if (ls_r2.trimmed().toUpper() == "OUT")
            {
                ls_r2 = m_sOut;
            }

            ls_result = QString("%1%2,%3%4")
                    .arg(" ",10 - ls_r1.length())
                    .arg(ls_r1)
                    .arg(" ", 10 - ls_r2.length())
                    .arg(ls_r2);
        }
        else
        {
            m_sSampleNo = lsl_array.at(li_i).mid(m_nSampleNoPos - 1, m_nSampleNoLen).trimmed();

            if (m_sSampleNo.isEmpty())
            {
                continue;
            }

            ls_result = lsl_array.at(li_i).mid(m_nResultPos - 1, m_nResultLen).trimmed();

            if (ls_result.trimmed().toUpper() == "OUT")
            {
                ls_result = m_sOut;
            }
        }

        li_curRow = insertRow();
        setItemValue(li_curRow,0,m_sSampleNo);
        setItemValue(li_curRow,1,ls_result);
        setItemValue(li_curRow,2,"未入库");

    }
}

void W_Wiacalc::excel_file_decode(const QString as_filepath)
{

}

void W_Wiacalc::loadConfig()
{
    BaseWindow::loadConfig();

    m_sSampleId = readSetting("WIACALC/sampleid","PAT").toString();
    m_sResult = readSetting("WIACALC/srcresult","PAT").toString();
    m_sOut = readSetting("WIACALC/out","PAT").toString();
}

void W_Wiacalc::on_Import_PushButton_clicked()
{
    QString ls_r1;
    QString ls_r2;
    QString ls_sampleNo;
    QString ls_itemNo;
    QString ls_result;
    QString ls_date;
    qint32 li_pos;
    qint32 li_sampleNo;

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

        m_sSampleDate = ui->SampleDate_DateEdit->text();

        if (!m_sSampleNo.isEmpty())
        {
            ls_result   = getItemValue(row,1);
            int ret;
            if (m_bIsDual)
            {
                li_pos = ls_result.indexOf(",");

                ls_r1 = ls_result.left(li_pos).trimmed();
                ls_r2 = ls_r1.mid(li_pos + 1).trimmed();
                ret = sendResult("FPSA",ls_r1);
                ret = sendResult("PSA",ls_r2);
            }
            else
            {
                ret = sendResult(m_sItem,ls_result);
            }



            if (ret == 0)
            {
                li_cnt++;

                li_sampleNo = ls_sampleNo.toInt();
                m_nMaxSampleNo = qMax(m_nMaxSampleNo,li_sampleNo);
                setItemValue(row,4,tr("已入库"));
            }
            else if (ret == 2)
            {
                break;
            }
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
