#include "w_a2000.h"

W_A2000::W_A2000(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle("zsdec_a2000");

    resetUi();

    setFileSuffix("*.csv");
    setFileType(BaseWindow::CSV);

    loadConfig();

    m_bOuter_Command = false;

    init();
}

W_A2000::~W_A2000()
{

}

void W_A2000::resetUi()
{
//    ui->date_Label->setText("样本日期");
//    ui->item_Label->setText("样本范围");

//    QRegExpValidator *validator = new QRegExpValidator(QRegExp("\\d+"),this);
//    sampleMin_LineEdit = new QLineEdit(ui->centralWidget);
//    sampleMin_LineEdit->setValidator(validator);
//    sampleMin_LineEdit->setFixedWidth(80);

//    sampleMax_LineEdit = new QLineEdit(ui->centralWidget);
//    sampleMax_LineEdit->setValidator(validator);
//    sampleMax_LineEdit->setFixedWidth(80);
//    line_Label = new QLabel("--",ui->centralWidget);

//    TestType_Label = new QLabel("项目类型",ui->centralWidget);
//    TestType_Combox = new QComboBox(ui->centralWidget);
//    TestType_Combox->setFixedWidth(80);
//    TestType_Combox->addItem(tr("所有项目"));
//    TestType_Combox->setEditable(true);

//    ui->item_HorizontalLayout->takeAt(3);
//    ui->item_HorizontalLayout->insertWidget(3,sampleMin_LineEdit);
//    ui->item_HorizontalLayout->insertWidget(4,line_Label);
//    ui->item_HorizontalLayout->insertWidget(5,sampleMax_LineEdit);
//    ui->item_HorizontalLayout->insertWidget(6,TestType_Label);
//    ui->item_HorizontalLayout->insertWidget(7,TestType_Combox);


//    ui->Refresh_PushButton->setFixedWidth(70);
//    ui->Import_PushButton->setFixedWidth(70);

    ui->projectConfig_Label->setVisible(false);
    ui->projectConfig_LineEdit->setVisible(false);
    ui->Allocation_PushButton->setVisible(false);
    ui->autoAllocation_CheckBox->setVisible(false);

    ui->Refresh_PushButton->setVisible(false);
    ui->ItemCode_ComboBox->setVisible(false);

//    ui->date_Label->setVisible(false);
//    ui->SampleDate_DateEdit->setVisible(false);
    //    ui->date_Label->setVisible(false);
    ui->item_Label->setVisible(false);
    ui->nextSample_Label->setVisible(false);
    ui->nextSampleNo_Label->setVisible(false);

    ui->main_VerticalLayout->removeItem(ui->sample_horizontalLayout);
}

void W_A2000::set_TableWidgetHeader()
{
//    m_slHeaders   << tr("样本号") << tr("项目名称") << tr("浓度水平") << tr("质控品") << tr("项目类型") << tr("结果") << tr("日期") << tr("状态");


//    ui->Result_TableWidget->setColumnCount(m_slHeaders.size());
//    ui->Result_TableWidget->setHorizontalHeaderLabels(m_slHeaders);
}

void W_A2000::file_decode(const QString as_file, const QString as_path)
{
    QString ls_line;
    QString ls_date;
    QString ls_id;
    QString ls_sample;
    QString ls_item;
    QString ls_result;
    QString ls_start;
    QStringList lsl_unit;
    qint32 li_pos;
    qint32 li_CurRow;

    QString filename;

    if(!as_path.endsWith("/"))
    {
        filename = as_path + "/" + as_file;
    }
    else
    {
        filename = as_path + as_file;
    }
    QFile file(filename);
    if (!file.open(QFile::ReadOnly))
    {
        return;
    }

    GetId(as_file);

    m_ItemTables.clear();
    QFile f(QDir::toNativeSeparators(g_sItemTables_file));

    if(!f.exists())
    {
        f.open(QFile::ReadWrite | QFile::Truncate);
        f.close();
    }

    if (f.open(QFile::ReadOnly))
    {
        QTextStream in(&f);
        in.setCodec(QTextCodec::codecForName("system"));
        while(!in.atEnd())
        {
            m_ItemTables.push_back(in.readLine());
        }

        f.close();
    }

    ls_start = "A2000_LisData";
    ls_date = as_file.left(as_file.indexOf("."));
    li_pos = ls_date.indexOf(ls_start);
    ls_date = ls_date.mid(li_pos + ls_start.length());
    ls_date = ls_date.left(8);
    ls_date = QDate::fromString(ls_date,"yyyyMMdd").toString("yyyy-MM-dd");
    m_sSampleDate = ls_date;


    int i = 0;
    QTextStream in(&file);
    in.setCodec(QTextCodec::codecForName("system"));
    while(!in.atEnd())
    {
        ls_line = in.readLine(1024);

        lsl_unit = ls_line.split(",");
        ls_id = lsl_unit[m_nIdIndex - 1].trimmed();
        ls_sample = lsl_unit[m_nSampleIndex - 1].trimmed();
        m_sSampleNo = ls_sample;
        ls_item = lsl_unit[m_nItemIndex - 1].trimmed();
        ls_result = lsl_unit[m_nResultIndex -1].trimmed();

        if(m_ItemTables.size() <= 0)
        {

        }
        else
        {
            QStringList lsl_itemUnit;

            for(int i = 0; i < m_ItemTables.size(); i++)
            {

                lsl_itemUnit = m_ItemTables[i].split("\t");
                if(lsl_itemUnit.count() >= 3)
                {

                    if(lsl_itemUnit[0] == m_sSampleNo && lsl_itemUnit[1] == ls_item)
                    {
                        li_CurRow = insertRow();
                        setItemValue(li_CurRow,0,ls_id);
                        setItemValue(li_CurRow,1,m_sSampleNo);          //样本号
                        setItemValue(li_CurRow,2,lsl_itemUnit[1]);      //项目名称
                        setItemValue(li_CurRow,3,lsl_itemUnit[2]);      //浓度水平
                        setItemValue(li_CurRow,4,ls_result);            //结果
                        setItemValue(li_CurRow,5,ls_date);              //日期
                        if(!IdMap.contains(ls_id + "," + ls_date))
                        {
                            setItemValue(li_CurRow,6,"未入库");
                        }
                        else
                        {
                            setItemValue(li_CurRow,6,"已入库");
                        }
                    }
                }
            }
        }
    }

    ui->Result_TableWidget->sortItems(0,Qt::AscendingOrder);
}

void W_A2000::excel_file_decode(const QString as_filepath)
{

}

void W_A2000::GetId(QString filename)
{
    IdMap.clear();
    QString ls_line;
    QStringList lsl_unit;

    QRegularExpression reg("(\\d{4}\\d{2}\\d{2})");
    QRegularExpressionMatch match = reg.match(filename);

    if(match.hasMatch())
    {
        QString date = match.captured(1);
        date = QDate::fromString(date,"yyyyMMdd").toString("yyyy-MM-dd");
        QString resultPath = QDir::currentPath() + "/result/" + date + ".csv";
        QFile file(resultPath);
        if(file.open(QFile::ReadOnly))
        {
            QTextStream in(&file);
            in.setCodec("UTF-8");
            while(!in.atEnd())
            {
                ls_line = in.readLine();
                lsl_unit = ls_line.split(",");
                if(lsl_unit.size() >= 6)
                {
                    IdMap.append(lsl_unit.at(0) + "," + lsl_unit.at(5));
                }
            }

            file.close();
        }
    }
}

void W_A2000::on_Import_PushButton_clicked()
{
    QString ls_id;
    QString ls_sampleNo;
    QString ls_projectName;
    QString ls_result;
    QString ls_date;
    QString ls_createDate;
    QString ls_state;
    int li_densityId;
    int li_sampleNo;

    ls_createDate = ui->SampleDate_DateEdit->text();

    if (!m_db.open())
    {
        return;
    }

    int li_rowCnt = getRowCount();
    int li_cnt = 0;
    for(int row = 0; row < li_rowCnt; row++)
    {
        ls_state = getItemValue(row,6);
        if(ls_state.compare("已入库") == 0)
        {
            continue;
        }

        ls_id = getItemValue(row,0);
        ls_projectName = getItemValue(row,2);
        li_densityId = getItemValue(row,3).mid(1).toInt();
        ls_result   = getItemValue(row,4);
        ls_date = getItemValue(row,5);

        int ret = sendResult(ls_id, ls_projectName, ls_result, li_densityId, ls_date, ls_createDate);

        if (ret == 0)
        {
            li_cnt++;
            setItemValue(row, 6, tr("已入库"));
        }
        else if (ret == 2)
        {
            break;
        }
    }

    m_db.close();

    if(!m_bOuter_Command)
    {
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
}


void W_A2000::loadConfig()
{
    BaseWindow::loadConfig();

    m_nSampleIndex = readSetting("A2000/sampleidx",3).toInt();
    m_nItemIndex = readSetting("A2000/itemidx",6).toInt();
    m_nResultIndex =readSetting("A2000/resultidx",9).toInt();
    m_nIdIndex = readSetting("A2000/id",2).toInt();
}

bool W_A2000::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    MSG* msg = reinterpret_cast<MSG*>(message);
    if(msg->message==WM_COPYDATA)
    {
        m_bOuter_Command = true;
        COPYDATASTRUCT* data = reinterpret_cast<COPYDATASTRUCT*>(msg->lParam);
        QString txt = static_cast<char*>(data->lpData);
        if(txt == "COMMAND_IMPORT")
        {
            for(int i = 0;i < ui->listWidget->count(); i++)
            {
                QString date = QDate::currentDate().toString("yyyyMMdd");


                if(ui->listWidget->item(i)->text().contains(date))
                {
                    file_decode(ui->listWidget->item(i)->text(), ui->FilePath_LineEdit->text());
                    on_Import_PushButton_clicked();
                }
            }
        }

        m_bOuter_Command = false;
        return true;
    }

    return false;

    //	return nativeEvent(eventType,message,result);
}
