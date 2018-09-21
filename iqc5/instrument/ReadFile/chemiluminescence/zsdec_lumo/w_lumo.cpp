#include "w_lumo.h"

W_Lumo::W_Lumo(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-LUMO");

    setFileSuffix("*.txt");

    setFileType(BaseWindow::TXT);

    loadConfig();

    init();
}

W_Lumo::~W_Lumo()
{

}

void W_Lumo::set_TableWidgetHeader()
{
    m_slHeaders << tr("项目") << tr("样本号") << tr("结果") << tr("状态");
    ui->Result_TableWidget->clear();
    ui->Result_TableWidget->setColumnCount(m_slHeaders.size());
    ui->Result_TableWidget->setHorizontalHeaderLabels(m_slHeaders);
}

void W_Lumo::file_decode(const QString as_file, const QString as_path)
{
    QString ls_data;
    QStringList lsl_line;
    QStringList lsl_unit;
    bool lb_haveresult = false;
    qint32 li_itemidx = -1;
    qint32 li_resultidx = -1;
    qint32 li_curRow;

    QString filename = as_path + as_file;
    QFile file(filename);
    if (!file.open(QFile::ReadOnly))
    {
        return;
    }

    ls_data = QString::fromUtf8(file.readAll());
    file.close();

    lsl_line = ls_data.split("\r\n");

    for (int i = 0; i < lsl_line.size(); i++)
    {
        lsl_unit = lsl_line.at(i).split("\t");

        if (!lb_haveresult)
        {
            if (lsl_unit.at(0).trimmed() == m_sSampleNoLabel)
            {
                for (int j = 0; j < lsl_unit.size(); j++)
                {
                    if (lsl_unit.at(j).trimmed() == m_sItemNoLabel)
                    {
                        li_itemidx = j;
                    }
                    else if (lsl_unit.at(j).trimmed() == m_sResultLabel)
                    {
                        li_resultidx = j;
                    }
                }

                if (li_itemidx == -1)
                {
                    showMessage("提示",QString("找到列：%1，但没有找到列：%2").arg(m_sSampleNoLabel).arg(m_sItemNoLabel));
                    return;
                }

                if (li_resultidx == -1)
                {
                    showMessage("提示",QString("找到列：%1，但没有找到列：%2").arg(m_sSampleNoLabel).arg(m_sResultLabel));
                    return;
                }

                lb_haveresult = true;
            }

            continue;
        }


        if ((lsl_unit.size() >= li_itemidx) && (lsl_unit.size() >= li_resultidx))
        {
            li_curRow = insertRow();
            ls_data = lsl_unit.at(0);
            if (ls_data.length() > 6)
            {
                ls_data.mid(6);
            }

            setItemValue(li_curRow,0,lsl_unit.at(li_itemidx).trimmed());    //项目
            setItemValue(li_curRow,1,ls_data);                              //样本号
            setItemValue(li_curRow,2,lsl_unit.at(li_resultidx).trimmed());  //结果
            setItemValue(li_curRow,3,"未入库");
        }
    }
}

void W_Lumo::excel_file_decode(const QString as_filepath)
{

}

void W_Lumo::loadConfig()
{
    BaseWindow::loadConfig();

    m_sSampleNoLabel = readSetting("LUMO/sampleno_label","样品编号").toString();
    m_sItemNoLabel  = readSetting("LUMO/itemno_label","检测项目").toString();
    m_sResultLabel = readSetting("LUMO/result_label","检测结果").toString();

}

void W_Lumo::on_Import_PushButton_clicked()
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
        ls_itemNo   = getItemValue(row,0);
        ls_sampleNo = getItemValue(row,1);
        m_sSampleNo = ls_sampleNo;

        ls_result   = getItemValue(row,2);
        m_sSampleDate = ui->SampleDate_DateEdit->text();

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
