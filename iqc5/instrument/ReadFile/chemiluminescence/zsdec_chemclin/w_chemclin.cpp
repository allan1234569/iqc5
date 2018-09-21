#include "w_chemclin.h"

#include "axml_dec.h"

W_Chemclin::W_Chemclin(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-CHEMCLIN");
    setFileSuffix("*.res");
    setFileType(BaseWindow::RES);
    init();
}

W_Chemclin::~W_Chemclin()
{

}

void W_Chemclin::set_TableWidgetHeader()
{
    m_slHeaders << tr("项目") << tr("样本号") << tr("结果") << tr("日期") << tr("状态");
    ui->Result_TableWidget->clear();
    ui->Result_TableWidget->setColumnCount(m_slHeaders.size());
    ui->Result_TableWidget->setHorizontalHeaderLabels(m_slHeaders);
}

void W_Chemclin::file_decode(const QString as_file, const QString as_path)
{
    QString filepath;
    if (as_path.right(1) != "/")
    {
        filepath = as_path + "/" + as_file;
    }
    else
    {
        filepath = as_path + as_file;
    }

    AXml_dec xml_dec(filepath); //设置路径
    xml_dec.parser();   //开始解析


    int li_curRow;

    QString item;
    ui->ItemCode_ComboBox->clear();

    for(int i = 0; i <xml_dec.count(); i++)
    {
        li_curRow = insertRow();
        item = xml_dec.getItems().at(i);
        if (ui->ItemCode_ComboBox->findText(item) == -1)
        {
            ui->ItemCode_ComboBox->addItem(item);
        }
        setItemValue(li_curRow,0,xml_dec.getItems().at(i)); //项目
        setItemValue(li_curRow,1,xml_dec.getSampleNos().at(i)); //样本号
        setItemValue(li_curRow,2,xml_dec.getResults().at(i)); //结果
        setItemValue(li_curRow,3,xml_dec.getSampleDates().at(i)); //日期
        setItemValue(li_curRow,4,"未入库"); //状态
        setResultHeader(2);
    }
}

void W_Chemclin::excel_file_decode(const QString as_filepath)
{

}

void W_Chemclin::on_Import_PushButton_clicked()
{
    QString ls_sampleNo;
    QString ls_itemNo;
    QString ls_result;
    QString ls_date;
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
        ls_date     = getItemValue(row,3);
        m_sSampleDate = ls_date;

        int ret = sendResult(ls_itemNo,ls_result);

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
