#include "w_fj2008ps.h"

W_Fj2008ps::W_Fj2008ps(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("放免仪-FJ2008PS");
    setFileSuffix("*.*");
    init();
}

W_Fj2008ps::~W_Fj2008ps()
{

}

void W_Fj2008ps::set_TableWidgetHeader()
{
    m_slHeaders << tr("样本号") << tr("项目") << tr("结果") << tr("状态");
    ui->Result_TableWidget->clear();
    ui->Result_TableWidget->setColumnCount(m_slHeaders.size());
    ui->Result_TableWidget->setHorizontalHeaderLabels(m_slHeaders);
}

int W_Fj2008ps::file_decode(const QString &as_file, const QString as_path)
{
    QString ls_item;
    QString ls_data;
    QString ls_result;
    QStringList lsl_line;
    int li_pos;
    int li_start;
    int li_curRow;

    li_pos = as_file.indexOf(".");
    ls_item = as_file.left(li_pos).trimmed();

    ls_data = getContent(m_sFilePath);

    if (ls_data.isEmpty())
    {
        return 0;
    }

    li_start = readSetting("FJ2008PS/startline",8).toInt();

    lsl_line = ls_data.split("\n");

    for(int i = li_start - 1; i < lsl_line.size(); i++)
    {
        li_curRow = insertRow();
        setItemValue(li_curRow,0,"");
        setItemValue(li_curRow,1,ls_item);
        setItemValue(li_curRow,2,lsl_line.at(i).trimmed());
        setItemValue(li_curRow,3,tr("未入库"));
    }
}

void W_Fj2008ps::on_Import_PushButton_clicked()
{
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
        m_sSampleNo = getItemValue(row,0);
        ls_itemNo   = getItemValue(row,1);
        ls_result   = getItemValue(row,2);
        m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");

        int ret = sendResult(ls_itemNo,ls_result);
        if (ret == 0)
        {
            li_cnt++;

            li_sampleNo = m_sSampleNo.toInt();
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
