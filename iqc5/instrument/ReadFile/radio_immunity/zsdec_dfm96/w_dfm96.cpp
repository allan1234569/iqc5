#include "w_dfm96.h"

W_Dfm96::W_Dfm96(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("放免仪-DFM96");
    setFileSuffix("*.*");
    m_bNewMode = false;
    loadConfig();
    init();
}


W_Dfm96::~W_Dfm96()
{

}

void W_Dfm96::set_TableWidgetHeader()
{
    m_slHeaders << tr("样本号") << tr("项目") << tr("结果") << tr("状态");
    ui->Result_TableWidget->clear();
    ui->Result_TableWidget->setColumnCount(m_slHeaders.size());
    ui->Result_TableWidget->setHorizontalHeaderLabels(m_slHeaders);
}

int W_Dfm96::file_decode(const QString &as_file, const QString as_path)
{
    QString ls_item;
    QString ls_result;
    QString ls_data;
    QString ls_str;
    QStringList lsl_line;
    int li_pos;
    int li_num;
    int li_ret;
    int li_curRow;


    li_pos = as_file.trimmed().indexOf(".");
    ls_item = as_file.left(li_pos);

    ls_data = getContent(m_sFilePath);

    if (m_bNewMode)
    {
        file_decode_new(as_file, as_path);
    }

    if(ls_data.isEmpty())
    {
        return 0;
    }



    li_pos = ls_data.indexOf("****");

    if(li_pos >= 0)
    {
        ls_data = ls_data.mid(li_pos);

        while ((ls_data.length() > 29))
        {
            ls_result = ls_data.mid(22,8);
            li_curRow = insertRow();
            setItemValue(li_curRow,0,"");
            setItemValue(li_curRow,1,ls_item);
            setItemValue(li_curRow,2,ls_result);
            setItemValue(li_curRow,3,tr("未入库"));
            ls_data = ls_data.mid(30);
        }

        return 0;
    }

    ls_data = getContent(m_sFilePath);
    li_pos = ls_data.indexOf("***");

    if (li_pos  < 0)
    {
        return 0;
    }

    while (li_pos > 0)
    {
        ls_data = ls_data.mid(li_pos + 3);
        li_pos = ls_data.indexOf("***");
    }

    lsl_line = ls_data.split("\n");
    for(int i = 0; i < lsl_line.size(); i++)
    {
        ls_result = lsl_line.at(i).mid(6,8).trimmed();
        if (ls_result.length() >= 5)
        {
            li_curRow = insertRow();
            setItemValue(li_curRow,0,"");
            setItemValue(li_curRow,1,ls_item);
            setItemValue(li_curRow,2,ls_result);
            setItemValue(li_curRow,3,tr("未入库"));
        }
    }
}

void W_Dfm96::file_decode_new(const QString &as_file, const QString as_path)
{
    QString ls_result;
    QString ls_item;
    QString ls_key;
    const QString ls_file = as_file + as_path;
    int li_pos;
    int li_count;
    int li_curRow;

    li_pos = as_file.indexOf(".");
    ls_item = as_file.left(li_pos).trimmed();

    QSettings *setting = new QSettings(ls_file,QSettings::IniFormat);
    setting->setIniCodec("UTF-8");

    li_count = setting->value("样本管数/个数",0).toInt();

    for (int i = 0; i < li_count; i++)
    {
        ls_key = QString("样品管/%1样品浓度").arg(i);
        ls_result = setting->value(ls_key.toStdString().data()).toString();
        li_curRow = insertRow();
        setItemValue(li_curRow,0,"");
        setItemValue(li_curRow,0,ls_item);
        setItemValue(li_curRow,0,ls_result);
        setItemValue(li_curRow,0,tr("未入库"));
    }

}

void W_Dfm96::loadConfig()
{
    BaseWindow::loadConfig();

    m_bNewMode = readSetting("DFM96/newmode",0).toBool();
}

void W_Dfm96::on_Import_PushButton_clicked()
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
