#include "w_mpc1.h"

W_Mpc1::W_Mpc1(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("化学发光-JETLIA962");

    resetUi();

    loadConfig();

    init();
}

W_Mpc1::~W_Mpc1()
{

}

void W_Mpc1::resetUi()
{
    ui->ItemCode_ComboBox->setVisible(false);
    ui->date_Label->setText("样本日期");
    ui->item_Label->setText("样本范围");

    QRegExpValidator *validator = new QRegExpValidator(QRegExp("\\d+"),this);
    sampleMin_LineEdit = new QLineEdit("0",ui->centralWidget);
    sampleMin_LineEdit->setValidator(validator);

    sampleMax_LineEdit = new QLineEdit("100",ui->centralWidget);
    sampleMax_LineEdit->setValidator(validator);
    line_Label = new QLabel("--",ui->centralWidget);

    ui->item_HorizontalLayout->takeAt(3);
    ui->item_HorizontalLayout->insertWidget(3,sampleMin_LineEdit);
    ui->item_HorizontalLayout->insertWidget(4,line_Label);
    ui->item_HorizontalLayout->insertWidget(5,sampleMax_LineEdit);

    ui->main_VerticalLayout->takeAt(1);
    ui->sample_Label->setVisible(false);
    ui->sampleNo_LineEdit->setVisible(false);
    ui->Allocation_PushButton->setVisible(false);
    ui->autoAllocation_CheckBox->setVisible(false);
    ui->nextSample_Label->setVisible(false);
    ui->nextSampleNo_Label->setVisible(false);

    ui->info_horizontalLayout->takeAt(0);
    ui->result_GroupBox->setVisible(false);
    ui->listWidget->setVisible(false);
    delete ui->listWidget;
    ui->listWidget = NULL;

    ui->Refresh_PushButton->setText("读取文件");
}

void W_Mpc1::set_TableWidgetHeader()
{
    m_slHeaders << tr("项目") << tr("样本号") << tr("结果") << tr("日期") << tr("状态");
    ui->Result_TableWidget->clear();
    ui->Result_TableWidget->setColumnCount(m_slHeaders.size());
    ui->Result_TableWidget->setHorizontalHeaderLabels(m_slHeaders);
}

void W_Mpc1::file_decode(const QString as_file, const QString as_path)
{
    QString filename;
    QString ls_line;
    QString ls_sampleno;
    QString ls_item;
    QString ls_tempitem;
    QString ls_result;
    QString ls_date;
    QString ls_sampleda;
    QString ls_key;
    qint32 li_file;
    qint32 li_i;
    qint32 li_curRow;
    qint32 li_maxSampleno;
    qint32 li_minSampleno;
    char buf[1024];

    filename = as_path + as_file;

    QFile file(filename);

    if (!file.exists())
    {
        showMessage("信息","文件不存在，请选择有效数据");
        return;
    }

    if (!file.open(QFile::ReadOnly))
    {
        showMessage("信息","文件打开错误");
        return;
    }

    ls_date = ui->SampleDate_DateEdit->text();

    li_minSampleno = sampleMin_LineEdit->text().toInt();
    li_maxSampleno = sampleMax_LineEdit->text().toInt();

    while(file.readLine(buf,sizeof(buf)) >= 0)
    {
        ls_line = QString::fromUtf8(buf);
        if (ls_line.length() >= 221)
        {
            if (ls_line.left(3) >= "sam")
            {
                ls_sampleda = ls_line.mid(220,10).trimmed();
                if (ls_sampleda >= ls_date)
                {
                    ls_sampleno = ls_line.mid(4,3).trimmed();
                    li_i = ls_sampleno.toInt();

                    if ((li_minSampleno > 0) && (li_maxSampleno > 0))
                    {
                        if ((li_i < li_minSampleno) || (li_i > li_maxSampleno))
                        {
                            continue;
                        }
                    }
                    else
                    {
                        if (li_minSampleno > 0)
                        {
                            if ( li_i < li_minSampleno)
                            {
                                continue;
                            }
                        }
                        else
                        {
                            if (li_maxSampleno > 0)
                            {
                                if (li_maxSampleno < li_i)
                                {
                                    continue;
                                }
                            }
                        }
                    }

                    ls_item = ls_line.mid(7,50).trimmed();

                    if (ls_item.length() > 20)
                    {
                        ls_key = QString("MPC/%1").arg(ls_item);
                        ls_tempitem = readSetting(ls_key.toStdString().data(),"").toString();
                        if (ls_tempitem.isEmpty())
                        {
                            ls_item = ls_item.right(20);
                            writeSetting(ls_key.toStdString().data(),ls_item);
                        }
                    }

                    ls_result = ls_line.mid(57,15).trimmed();

                    li_curRow = insertRow();
                    setItemValue(li_curRow,0,ls_item);
                    setItemValue(li_curRow,1,ls_sampleno);
                    setItemValue(li_curRow,2,ls_result);
                    setItemValue(li_curRow,3,ls_sampleda);
                    setItemValue(li_curRow,4,"未入库");
                }
            }
        }
    }

    file.close();
    writeSetting("datafile",filename);
}

void W_Mpc1::excel_file_decode(const QString as_filepath)
{

}

void W_Mpc1::on_Select_PushButton_clicked()
{
    QString dirPath = QFileDialog::getOpenFileName(this,
                                                   tr("请选择数据文件"),
                                                   QString("./"),
                                                   QString("*.txt"));
    if (dirPath.isEmpty())
    {
        return;
    }
    ui->FilePath_LineEdit->setText(dirPath);

    writeSetting("datafile",dirPath);
}

void W_Mpc1::on_Import_PushButton_clicked()
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
        ls_itemNo   = getItemValue(row,0);
        ls_sampleNo = getItemValue(row,1);
        m_sSampleNo = ls_sampleNo;

        ls_result   = getItemValue(row,2);
        ls_datetime = getItemValue(row,3);
        m_sSampleDate = ls_datetime;

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

void W_Mpc1::on_Refresh_PushButton_clicked()
{
    QString path = ui->FilePath_LineEdit->text();

    QFile file(path);

    if (file.exists())
    {
        file_decode(path.mid(path.lastIndexOf("/") + 1), path.left(path.lastIndexOf("/") + 1));
    }
    else
    {
        showMessage("提示","文件不存在，请选择有效的数据文件");
    }
}
