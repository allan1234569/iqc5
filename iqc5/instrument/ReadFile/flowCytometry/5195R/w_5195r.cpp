#include "w_5195r.h"

W_5195R::W_5195R(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("流式细胞-5195-R");

    loadConfig();

    init();

    writeSetting("5195-R/hwhw","CD10+, 1000");
}

W_5195R::~W_5195R()
{

}

void W_5195R::set_TableWidgetHeader()
{
    m_slHeaders << tr("项目") << tr("样本号") << tr("结果") << tr("状态");
    ui->Result_TableWidget->clear();
    ui->Result_TableWidget->setColumnCount(m_slHeaders.size());
    ui->Result_TableWidget->setHorizontalHeaderLabels(m_slHeaders);
}

void W_5195R::file_decode(const QString as_file, const QString as_path)
{
    qint32 li_index;
    qint32 li_curRow;
    QString ls_data;
    QStringList lsl_line;
    QStringList lsl_unit;
    QString filename;

    filename = as_path + as_file;
    QFile file(filename);
    if (!file.open(QFile::ReadOnly))
    {
        return;
    }

    ls_data = QString::fromUtf8(file.readAll().data());
    file.close();

    lsl_line = ls_data.split(QString(QChar(CR)));


    for (int i = 1; i < lsl_line.size(); i++)
    {
        lsl_unit = lsl_line.at(i).split("\t");

        if (m_nSampleNoIndex <= lsl_unit.size())
        {
            m_sSampleNo = lsl_unit.at(m_nSampleNoIndex - 1);
            for (int j = 0; j < m_nItemCnt; j++)
            {
                li_index = m_nlItemIndex[j];

                if (li_index > 0)
                {
                    if (li_index <= lsl_unit.size())
                    {
                        li_curRow = insertRow();
                        setItemValue(li_curRow,0,m_slItemName[j]);      //项目
                        setItemValue(li_curRow,1,m_sSampleNo);          //样本号
                        setItemValue(li_curRow,2,lsl_unit[li_index - 1]);   //结果
                        setItemValue(li_curRow,3,"未入库");
                    }
                }
            }
        }
    }
}

void W_5195R::excel_file_decode(const QString as_filepath)
{

}

void W_5195R::loadConfig()
{
    QString ls_str;
    QString ls_key;
    QStringList lsl_data;

    BaseWindow::loadConfig();

    m_nSampleNoIndex = readSetting("5195-R/samplenoindex",7).toInt();
    m_sFileType = readSetting("5195-R/filetype","*.exp").toString();

    qDebug() << readSetting("5195-R/item1","").toString();

    setFileType(BaseWindow::EXP);
    setFileSuffix(m_sFileType);

    m_nItemCnt = 0;

    int i = 0;
    while(1)
    {
        i++;
        ls_key = QString("5195-R/item%1").arg(i);
        ls_str = readSetting(ls_key.toStdString().data(),"").toString();

        lsl_data = ls_str.split(",");
        if (lsl_data.size() < 2)
        {
            break;
        }

        m_slItemName.insert(i -1,lsl_data.at(0));
        m_nlItemIndex.insert(i - 1, lsl_data.at(1).toInt());
        m_nItemCnt  = i;
    }
}

void W_5195R::on_Import_PushButton_clicked()
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
        ls_date     = ui->SampleDate_DateEdit->text();
        m_sSampleDate = ls_date;

        int ret = sendResult(ls_itemNo,ls_result);

        if (ret == 0)
        {
            li_cnt++;

            li_sampleNo = ls_sampleNo.toInt();
            m_nMaxSampleNo = qMax(m_nMaxSampleNo,li_sampleNo);
            setItemValue(row,3,tr("已入库"));
            ui->Result_TableWidget->scrollToItem(ui->Result_TableWidget->item(row,3));
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
