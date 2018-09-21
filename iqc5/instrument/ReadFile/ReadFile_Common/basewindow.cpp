#include "basewindow.h"
#include <QCloseEvent>
#include <QFileDialog>
#include <QProcess>
#include <QDateTime>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QSqlRecord>
#include <QLabel>
#include <QStatusBar>

#include "common.h"
#include "aprocess.h"
#include "asetupdialog.h"
#include "receivesetupdialog.h"

BaseWindow::BaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaseWindow)
{
    ui->setupUi(this);

    loadConfig();

    m_bCanClose = false;
    m_nResultCnt = 0;
    listWidget = NULL;
    m_bIsReadState = false;

    createActions();

    showTrayIcon();

    m_slItemTypes << Item << LineEdit << LineEdit << ComboBox  << ComboBox << Item << Item << Item;

    m_Timer = new QTimer(this);
    connect(m_Timer,SIGNAL(timeout()),
            this,SLOT(slt_timeout()));
    double tempTimer = readSetting("timer","0.5").toDouble();
    tempTimer = tempTimer * 1000;

    m_Timer->setInterval(tempTimer);
    m_Timer->start();

    ui->Result_TableWidget->horizontalHeader()->setHighlightSections(false);

    ui->SampleDate_DateEdit->setDate(QDate::currentDate());

    ui->projectConfig_LineEdit->setToolTip("格式：样本号,项目名,浓度水平；样本号,项目名,浓度水平");
    QRegExpValidator *validator = new QRegExpValidator(QRegExp("(\\w+,\\w+,\\w+;)+\\w+,\\w+,\\w+"),this);
    ui->projectConfig_LineEdit->setValidator(validator);

    projectDelegate = new TrackDelegate(TrackDelegate::LineEdit, ui->Result_TableWidget);
    densityDelegate = new TrackDelegate(TrackDelegate::Combox, ui->Result_TableWidget);
    densityDelegate->setList(QStringList() << "L1" << "L2" << "L3" << "L4" << "L5" << "L6");

    ui->Result_TableWidget->setItemDelegateForColumn(0,new ReadOnlyDelegate);
    ui->Result_TableWidget->setItemDelegateForColumn(2,projectDelegate);
    ui->Result_TableWidget->setItemDelegateForColumn(3,densityDelegate);
    ui->Result_TableWidget->setItemDelegateForColumn(4,new ReadOnlyDelegate);
    ui->Result_TableWidget->setItemDelegateForColumn(5,new ReadOnlyDelegate);
    ui->Result_TableWidget->setItemDelegateForColumn(6,new ReadOnlyDelegate);

    connect(projectDelegate,SIGNAL(sig_editing(QString)),this,SLOT(slt_Editing(QString)));
    connect(projectDelegate,SIGNAL(sig_editFinished()),this,SLOT(slt_EditFinished()));

    ui->Result_TableWidget->installEventFilter(this);
}

BaseWindow::~BaseWindow()
{
    delete ui;
}


void BaseWindow::init()
{
    ///界面初始化
    QString tempStr;
    int tempNum;

    m_sDataFilePath = readSetting("datafile","").toString();
    ui->FilePath_LineEdit->setText(m_sDataFilePath);

    ///自动刷新
    tempStr = readSetting("autorefresh","").toString();
    if (tempStr.isEmpty())
    {
        writeSetting("autorefresh",1);
        tempNum = readSetting("autorefresh",1).toInt();
    }
    else
    {
        tempNum = tempStr.toInt();
    }

    ///自动分配样本号
    tempStr = readSetting("autoAllocation","").toString();
    if (tempStr.isEmpty())
    {
        writeSetting("autoAllocation",1);
        tempNum = readSetting("autorefresh",1).toInt();
    }
    else
    {
        tempNum = tempStr.toInt();
    }

    if (tempNum == 0)
    {
        ui->autoAllocation_CheckBox->setChecked(false);
        on_autoAllocation_CheckBox_clicked(false);
    }
    else if (tempNum == 1)
    {
        ui->autoAllocation_CheckBox->setChecked(true);
        on_autoAllocation_CheckBox_clicked(true);
    }

    if (readSetting("importmode",0).toInt() == 0)
    {
        on_comboBox_currentIndexChanged(0);
    }
    else
    {
        on_comboBox_currentIndexChanged(1);
    }

    initListWidget();

    if (!ASql::testConnection())
    {
        exit(1);
    }
}

bool BaseWindow::initListWidget()
{
    if (ui->listWidget)
    {
        ui->listWidget->clear();
        QString path = ui->FilePath_LineEdit->text();
        if(path.isEmpty())
        {
            return false;
        }
        QDir dir(ui->FilePath_LineEdit->text());

        if(!dir.exists())
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("警告"));
            msgBox.setText(tr("指定目录不存在"));
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
            msgBox.exec();

            return false;
        }

        QStringList suffixList;
        suffixList = m_sFileSuffix.split(",");
        QStringList list = dir.entryList(suffixList);

        if(list.size() <= 0)
        {
            this->show();
            QMessageBox msgBox;
            msgBox.setWindowTitle(QObject::tr("提示"));
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText(QObject::tr("当前目录未检测到任何文件"));
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setButtonText(QMessageBox::Ok,QObject::tr("确定"));
            msgBox.setFont(QFont("宋体",10));
            msgBox.exec();
            return true;
        }

        for(int i = 0; i < list.count(); i++)
        {
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(list.at(i));
            item->setCheckState(Qt::Unchecked);
            if((item->text() == ".") || (item->text() == ".."))
            {
                continue;
            }
            ui->listWidget->addItem(item);
        }
        return true;
    }
    else
    {
        return false;
    }
}

void BaseWindow::initItemCombox(const QStringList as_list)
{
    ui->ItemCode_ComboBox->addItems(as_list);
}

void BaseWindow::refreshData()
{
    QList<QString> inerList;
    int rowCount;

    for(int row = 0; row < m_dataList.count(); row++)
    {
        inerList = m_dataList.at(row);
        rowCount = ui->Result_TableWidget->rowCount();
        ui->Result_TableWidget->insertRow(rowCount);
        for(int column = 0; column < inerList.count(); column++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(inerList.at(column));
            ui->Result_TableWidget->setItem(rowCount,column,item);
        }
    }
}

void BaseWindow::setFileSuffix(const QString suffix)
{
    m_sFileSuffix = suffix;
    ui->FileSuffix_Label->setText(m_sFileSuffix);
}

void BaseWindow::setFileType(FileType type)
{
    m_eFileType = type;
}

void BaseWindow::showMessage(const QString title, const QString msg)
{
    QMessageBox msgBox;
    msgBox.setGeometry(this->pos().x() + this->width()/2,
                       this->pos().y() + this->height()/2,
                       msgBox.width(),
                       msgBox.height());
    msgBox.setWindowIcon(this->windowIcon());
    msgBox.setWindowTitle(title);
    msgBox.setText(msg);
    msgBox.exec();
}

int BaseWindow::findColumn(QString HeaderItem)
{
    for (int column = 0; column < ui->Result_TableWidget->columnCount(); column++)
    {
        if (ui->Result_TableWidget->horizontalHeaderItem(column)->text().compare(HeaderItem) == 0)
        {
            return column;
        }
    }
}

void BaseWindow::setItemValue(int row, int column, const QString value)
{
    if (column > ui->Result_TableWidget->columnCount())
    {
        return;
    }

    if (ui->Result_TableWidget->item(row,column) != NULL)
    {
        ui->Result_TableWidget->item(row,column)->setText(value);
    }
}

int BaseWindow::getColumn(const QString &columnLabel)
{

    for(int i = 0; i < ui->Result_TableWidget->columnCount(); i++)
    {
        if (ui->Result_TableWidget->horizontalHeaderItem(i)->text() == columnLabel)
        {

            return i;
        }
    }

    return -1;
}

void BaseWindow::setSampleNos(int row, const QString values)
{
    if (row == -1)
    {
        int row = ui->Result_TableWidget->rowCount() -1;
        ui->Result_TableWidget->item(row,0)->setText(values);
    }
    else
    {
        ui->Result_TableWidget->item(row,0)->setText(values);
    }
}

void BaseWindow::ClearTableWidgetContents()
{
    QTableWidget *widget = ui->Result_TableWidget;
    for(int i = widget->rowCount()-1; i >= 0; i--)
    {
        widget->removeRow(i);
    }
}

void BaseWindow::loadConfig()
{
    f_loadConfig();
    m_sInstr = readSetting("INSTR/devicename","").toString();
    m_sInstallPlace = readSetting("INSTR/installplace","").toString();

    m_sWorkDay = readSetting("workday","").toString();

    m_importMode = readSetting("importmode",0).toInt();

    QDate ld_workday = QDate::fromString(m_sWorkDay,"yyyy-MM-dd");
    QDate ld_today = QDate::currentDate();
    if (ld_workday != ld_today)
    {
        m_sWorkDay = ld_today.toString("yyyy-MM-dd");
        writeSetting("workday",m_sWorkDay);
        m_nMaxSampleNo = 1001;
        writeSetting("nextsampleno",m_nMaxSampleNo);
        ui->nextSampleNo_Label->setText(QString::number(m_nMaxSampleNo));
    }
    else
    {
        m_nMaxSampleNo = readSetting("nextsampleno",1001).toInt();
        ui->nextSampleNo_Label->setText(QString::number(m_nMaxSampleNo));
    }

    m_sEmptyResult = readSetting("empytresult","-0.00").toString();

    if (m_db.open())
    {
        QStringList itemsList = m_db.getItems();
        initItemCombox(itemsList);
        m_db.close();
    }

}

void BaseWindow::getSampleResultTime(QString as_data)
{
    QString ls_format;

    ls_format = readSetting("General/sample_data_time_format","yyyy/MM/dd hh:mm:ss").toString();
    m_sSampleResultDateTime = QDateTime::fromString(as_data).toString(ls_format);

    if (m_bUseSysDate)
    {
        m_sSampleResultDateTime = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    }
}

void BaseWindow::slt_show()
{
    m_bCanClose = false;
    this->show();
}

void BaseWindow::slt_showTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::DoubleClick:
        this->show();
        break;
    default:
        break;
    }
}

void BaseWindow::slt_timeout()
{
//    m_sSampleDate = ui->SampleDate_DateEdit->text();
//    slt_setQuery();

//    decode();

//    int original_rowCount = ui->Original_TableWidget->rowCount();

//    int put_rowCount = ui->Result_TableWidget->rowCount();

//    if (original_rowCount > put_rowCount)
//    {
//        if(ui->AutoIn_CheckBox->isChecked())    //自动入库
//        {
//            on_Import_PushButton_clicked();
//        }
//        else
//        {
//            return;
//        }
//    }
}


void BaseWindow::on_action_Exit_triggered()
{
    m_bCanClose = true;
    this->close();
}

void BaseWindow::on_action_DecodeSetup_triggered()
{
    this->show();   //如果主程序不显示出来，dialog关闭时，主程序将会关闭
    ASetupDialog *dialog = new ASetupDialog(this);

    dialog->exec();

}

void BaseWindow::on_action_DecodeLog_triggered()
{

    QFile file(g_sLogFilePath);
    if (!file.exists())
    {
        this->show();
        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("提示"));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(QObject::tr("\n没有发现日志文件（log.txt）"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,QObject::tr("确定"));
        msgBox.setFont(QFont("宋体",10));

        msgBox.exec();
        return;
    }

    QString program = QString("notepad.exe ").append(g_sLogFilePath);
    AProcess *process = new AProcess;
    process->setProgram(program);
    process->start();
}

void BaseWindow::on_action_Help_triggered()
{

}

void BaseWindow::on_action_ReceiveSetup_triggered()
{
    ReceiveSetupDialog *setup = new ReceiveSetupDialog(this);
    setup->exec();
}

void BaseWindow::dealSampleNo(QString &as_sampleNo, bool ab_flag)
{
    int li_i;
    int li_len;
    QString ls_sampleNo;
    QString ls_sampleBit;
    bool lb_foundNotZero = false;

    as_sampleNo = as_sampleNo.trimmed();

    /***
     * 此段暂时保留，未必会用上
     */

    if (m_sSampleNoTrans.compare("L") == 0)
    {
        as_sampleNo = as_sampleNo.left(m_nSampleNoTransLen);
    }
    else if (m_sSampleNoTrans.compare("M") == 0)
    {
        as_sampleNo = as_sampleNo.mid(m_nSampleNoTransLen);
    }
    else if (m_sSampleNoTrans.compare("R") == 0)
    {
        as_sampleNo =as_sampleNo.right(m_nSampleNoTransLen);
    }

    if (m_dec.IsDigitStr(as_sampleNo))
    {
        as_sampleNo = QString::number(as_sampleNo.toInt());
    }
    else
    {
        //TODO
    }
}

int BaseWindow::sendResult(QString as_id , QString as_item, QString as_result, int ai_densityId, QString as_testTime, QString as_CreateTime)
{
    int ret = m_db.sendResult(as_item,as_result,ai_densityId,g_sRegInstr,g_sInstallPlace,as_testTime,as_CreateTime);
    if (0 == ret)
    {
        addResult(as_id,m_sSampleNo,as_item, as_result,QString::number(ai_densityId),as_testTime,as_CreateTime);
        m_nResultCnt++;
    }

    return ret;
}

void BaseWindow::addResult(const QString id, const QString as_sampleNo, const QString as_projectname, const QString as_value, const QString as_densityid, const QString as_resultTime, const QString as_createTime)
{
    QString resultDir = QDir::currentPath().append("/result");
    QDir dir(resultDir);
    if (!dir.exists())
    {
        dir.mkdir(resultDir);
        if (!dir.exists())
        {
            return;
        }
    }


    ///格式：  ID号,样本号,项目名称,结果,浓度水平,测试时间,导入时间,仪器,安装地点
    QString resultStr = QString("%1,%2,%3,%4,%5,%6,%7,%8,%9\r\n")
            .arg(id)
            .arg(as_sampleNo)
            .arg(as_projectname)
            .arg(as_value)
            .arg(as_densityid)
            .arg(as_resultTime)
            .arg(as_createTime)
            .arg(m_sInstr)
           .arg(m_sInstallPlace);

    QString filepath = QDir::currentPath().append("/result/").append(as_resultTime).append(".csv");
    QFile file(filepath);
    if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Append))
    {
        return;
    }

//    if (file.size() == 0)
//    {
//        file.write("样本号,项目名称,项目类型,结果,浓度水平,时间,仪器,实验室编号");
//    }
    file.write(resultStr.toStdString().data());

    file.close();
}

QByteArray BaseWindow::packageToJson(QString as_sampleNo, QString as_value, QString as_itemCode, QString as_deviceName)
{
    QJsonDocument ljd_jsonDocment;
    QJsonArray lja_jsonArray;
    QJsonObject ljo_jsonObject;

    ljo_jsonObject.insert("sampleNo",as_sampleNo);
    ljo_jsonObject.insert("testTypeCode",as_itemCode);
    ljo_jsonObject.insert("value",as_value);
    ljo_jsonObject.insert("dataTime",m_sSampleResultDateTime);
    ljo_jsonObject.insert("deviceName",as_deviceName);
    ljo_jsonObject.insert("installplace",m_sInstallPlace);
    lja_jsonArray.insert(0,ljo_jsonObject);

    ljd_jsonDocment.setArray(lja_jsonArray);

    QByteArray json_data = ljd_jsonDocment.toJson();

    return json_data;
}

QString BaseWindow::getContent(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return "";
    }

//    readWriteLock.lockForRead();
    QString fileData = QString::fromLocal8Bit(file.readAll());
    file.close();
//    readWriteLock.unlock();

    return fileData;
}

int BaseWindow::readExcel(const QString &as_filename)
{
    excel_file_decode(as_filename);
}

quint32 BaseWindow::insertRow()
{
    int row = ui->Result_TableWidget->rowCount();
    ui->Result_TableWidget->insertRow(row);
    for(int i = 0; i < 8; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        ui->Result_TableWidget->setItem(row,i,item);

        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setTextAlignment(Qt::AlignCenter);
        ui->Result_TableWidget->setItem(row,i,item1);

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setTextAlignment(Qt::AlignCenter);
        ui->Result_TableWidget->setItem(row,i,item2);

        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setTextAlignment(Qt::AlignCenter);
        ui->Result_TableWidget->setItem(row,i,item3);

        QTableWidgetItem *item4 = new QTableWidgetItem;
        item4->setTextAlignment(Qt::AlignCenter);
        ui->Result_TableWidget->setItem(row,i,item4);

        QTableWidgetItem *item5 = new QTableWidgetItem;
        item5->setTextAlignment(Qt::AlignCenter);
        ui->Result_TableWidget->setItem(row,i,item5);
    }

    return ui->Result_TableWidget->rowCount() - 1;
}

void BaseWindow::setResultHeader(int column)
{
    QString headerItemStr;
    if (ui->Result_TableWidget->rowCount() == 0)
    {
        headerItemStr = QString("%1").arg(tr("结果"));
    }
    else
    {
        headerItemStr = QString("%1(%2)").arg(tr("结果")).arg(ui->Result_TableWidget->rowCount());
    }

    ui->Result_TableWidget->horizontalHeaderItem(column)->setText(headerItemStr);
}

quint32 BaseWindow::getRowCount()
{
    return ui->Result_TableWidget->rowCount();
}

QString BaseWindow::getItemValue(int row, int column)
{
    return ui->Result_TableWidget->item(row,column)->text();
}

void BaseWindow::decode(QString file)
{
    QString path = ui->FilePath_LineEdit->text();
    QString filename;

    if (file == "")
    {
        filename = ui->listWidget->currentItem()->text();
    }
    else
    {
        filename = file;
    }

    if (path.right(1) != "/")
    {
        path.append("/");
    }

    m_sFilePath = path + filename;
    switch (m_eFileType) {
    case BaseWindow::TXT:
    case BaseWindow::CSV:
    case BaseWindow::RES:
    case BaseWindow::EXP:
        file_decode(filename,path);
        break;
    case BaseWindow::XLS:
        readExcel(m_sFilePath);
        break;

    default:
        break;
    }
}

void BaseWindow::createActions()
{
    m_trayIconmenu = new QMenu();

    m_action_Show = new QAction(QObject::tr("显示"),this);
    m_action_Setup  = new QAction(QObject::tr("配置设置"),this);
    m_action_CheckDecLog = new QAction(QObject::tr("查看解析日志"),this);
    m_action_Help = new QAction(QObject::tr("帮助"),this);
    m_action_Exit = new QAction(QObject::tr("退出"),this);

    m_action_Show->setToolTip(QObject::tr("显示"));
    m_action_Setup->setToolTip(QObject::tr("配置设置"));
    m_action_CheckDecLog->setToolTip(QObject::tr("查看解析日志"));
    m_action_Help->setToolTip(QObject::tr("帮助"));
    m_action_Exit->setToolTip(QObject::tr("退出"));

    connect(m_action_Show,SIGNAL(triggered()),
            this,SLOT(slt_show()));

    connect(m_action_Setup,SIGNAL(triggered()),
            this,SLOT(on_action_DecodeSetup_triggered()));

    connect(m_action_CheckDecLog,SIGNAL(triggered()),
            this,SLOT(on_action_DecodeLog_triggered()));

    connect(m_action_Help,SIGNAL(triggered()),
            this,SLOT(on_action_Help_triggered()));

    connect(m_action_Exit,SIGNAL(triggered()),
            this,SLOT(on_action_Exit_triggered()));

    m_trayIconmenu->addAction(m_action_Show);
    m_trayIconmenu->addAction(m_action_Setup);
    m_trayIconmenu->addAction(m_action_CheckDecLog);
    m_trayIconmenu->addAction(m_action_Help);
    m_trayIconmenu->addAction(m_action_Exit);
}

void BaseWindow::showTrayIcon()
{
    m_sysTrayIcon = new QSystemTrayIcon(this);
    m_sysTrayIcon->setIcon(QIcon("://pics/analysis_128px.png"));
    m_sysTrayIcon->setContextMenu(m_trayIconmenu);
    m_sysTrayIcon->show();    
//    m_sysTrayIcon->setToolTip(QString("已处理：%1条结果").arg(m_nResultCnt));

    connect(m_sysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(slt_showTrayIcon(QSystemTrayIcon::ActivationReason)));
}

void BaseWindow::setFileList(QString filename, bool remove)
{
    bool lb_find = false;
    int i;
    for(i = 0; i < m_fileLists.size(); i++)
    {
        if (m_fileLists.at(i).compare(filename) == 0)
        {
            lb_find = true;
            break;
        }
    }

    if (remove) //移除
    {
        if (lb_find)
        {
             m_fileLists.removeAt(i);
        }
    }
    else    //添加
    {
        if (!lb_find)
        {
            m_fileLists.append(filename);
        }
    }

    qSort(m_fileLists.begin(),m_fileLists.end());
}

void BaseWindow::closeEvent(QCloseEvent *e)
{
    if (m_bCanClose)
    {
        e->accept();
    }
    else
    {
        e->ignore();
        this->hide();
    }
}

void BaseWindow::slt_Editing(const QString &txt)
{
    qint32 table_left = ui->Result_TableWidget->pos().x() + 232;
    qint32 table_top = ui->Result_TableWidget->pos().y() + 115;

    QRect rect = ui->Result_TableWidget->visualItemRect(ui->Result_TableWidget->currentItem());

    if (listWidget != NULL)
    {
        listWidget->setVisible(false);
    }

    listWidget = new QListWidget(this);
    listWidget->clear();

    if (ui->Result_TableWidget->currentColumn() == 1)  //项目名称
    {
        QStringList list = ASql::SearchProjects(txt);
        listWidget->addItems(list);
    }
    else if (ui->Result_TableWidget->currentColumn() == 2) //质控品
    {
        QStringList list = ASql::SearchMaterials(txt);
        listWidget->addItems(list);
    }

    connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(slt_listWidget_Clicked(QListWidgetItem*)));
    connect(listWidget,SIGNAL(itemEntered(QListWidgetItem*)),this,SLOT(slt_listWidget_Clicked(QListWidgetItem*)));

    listWidget->setGeometry(rect.x() + 238,
                           rect.y() + 158,
                           ui->Result_TableWidget->columnWidth(ui->Result_TableWidget->currentColumn()),
                           100);
    listWidget->show();

    b_isEditing = true;
}

void BaseWindow::slt_EditFinished()
{
    b_isEditing = false;
}

void BaseWindow::slt_listWidget_Clicked(QListWidgetItem *item)
{
    if (item == NULL)
    {
        return;
    }

    ui->Result_TableWidget->currentItem()->setText(item->text());
    listWidget->setVisible(false);
}

void BaseWindow::on_Select_PushButton_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this,
                                      tr("请选择文件目录"));
    if (dirPath.isEmpty())
    {
        return;
    }
    ui->FilePath_LineEdit->setText(dirPath);

    if (initListWidget())
    {
        writeSetting("datafile",dirPath);
    }
}

//void BaseWindow::on_Import_PushButton_clicked()
//{
//    QString ls_sampleNo;
//    QString ls_itemNo;
//    QString ls_result;
//    QString ls_datetime;
//    int li_sampleNo;

//    if (!m_db.open())
//    {
//        return;
//    }


//    int li_rowCnt = ui->Result_TableWidget->rowCount();
//    int li_cnt = 0;
//    for(int row = 0; row < li_rowCnt; row++)
//    {
//        ls_sampleNo = ui->Result_TableWidget->item(row,0)->text();
//        ls_result   = ui->Result_TableWidget->item(row,1)->text();
//        ls_itemNo = ui->ItemCode_ComboBox->currentText();
//        ls_datetime     = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

//        int ret = m_db.sendResult(ls_sampleNo,ls_itemNo,ls_result,m_sInstr,m_sLabNumber,ls_datetime);
//        if (ret == 0)
//        {
//            li_cnt++;

//            li_sampleNo = ls_sampleNo.toInt();
//            m_nMaxSampleNo = qMax(m_nMaxSampleNo,li_sampleNo);
//            QLabel *label = qobject_cast<QLabel*>(ui->Result_TableWidget->cellWidget(row,2));
//            label->setText(tr("已入库"));
//            ui->nextSampleNo_Label->setText(QString::number(li_sampleNo+1));

//            addResult(ls_sampleNo,ls_result,ls_itemNo,ls_datetime);
//        }
//        else if (ret == 2)
//        {
//            break;
//        }
//    }

//    m_db.close();

//    writeSetting("nextsampleno",ui->nextSampleNo_Label->text());

//    QMessageBox msgBox;


//    msgBox.setGeometry(this->pos().x() + this->width()/2,
//                       this->pos().y() + this->height()/2,
//                       msgBox.width(),
//                       msgBox.height());
//    msgBox.setWindowIcon(this->windowIcon());
//    msgBox.setWindowTitle(tr("提示"));
//    QString msgStr = QString("%1%2").arg(li_cnt).arg(tr("条记录成功入库"));
//    msgBox.setText(msgStr);
//    msgBox.exec();
//}

void BaseWindow::on_listWidget_itemSelectionChanged()
{
    if (ui->listWidget)
    {
        ClearTableWidgetContents();
        if (ui->listWidget->currentItem() == NULL)
        {
            return;
        }

        decode();
    }
}

void BaseWindow::on_ItemCode_ComboBox_currentTextChanged(const QString &arg1)
{
    writeSetting("lastitem",arg1);
}

void BaseWindow::on_autoAllocation_CheckBox_clicked(bool checked)
{
    ui->projectConfig_LineEdit->setEnabled(!checked);
    if (checked)
    {
        writeSetting("autoAllocation",1);
    }
    else
    {
        writeSetting("autoAllocation",0);
    }

}

void BaseWindow::on_Refresh_PushButton_clicked()
{
    on_listWidget_itemSelectionChanged();
}

void BaseWindow::on_Allocation_PushButton_clicked()
{
    int li_pos;
    int li_pos1;
    int li_start;
    int li_end;
    int li_len;
    QString ls_sampleno;
    int li_cnt = 0;
    int li_tbRowCount = ui->Result_TableWidget->rowCount();
    QStringList lsl_line;
    QStringList lsl_unit;

    int li_sampleColumnIndex;

    li_sampleColumnIndex = findColumn("样本号");


    QString sampleNos = ui->projectConfig_LineEdit->text();
    if (sampleNos.mid(sampleNos.length() - 1,1).compare(";") != 0)
    {
        sampleNos = sampleNos + ";";
    }

    sampleNos = sampleNos.replace("，",",");

    lsl_line = sampleNos.split(";");

    for (int i = 0; i < lsl_line.size(); i++)
    {
        lsl_unit = lsl_line.at(i).split(",");
        if (lsl_unit.size() != 3)
        {
            continue;
        }
        else
        {
            for(int row = 0; row < ui->Result_TableWidget->rowCount(); row++)
            {
                if (ui->Result_TableWidget->item(row,li_sampleColumnIndex)->text() == lsl_unit[0])
                {
                    setItemValue(row,1,lsl_unit[1]); //设置项目名
                    setItemValue(row,2,lsl_unit[2]); //设置浓度水平
                }
            }
        }
    }

}

void BaseWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if (item->checkState() == Qt::Checked)
    {
        setFileList(item->text(), false);
    }
    else
    {
        setFileList(item->text(), true);
    }
}

void BaseWindow::on_comboBox_currentIndexChanged(int index)
{
    writeSetting("importmode",index);
    m_importMode = readSetting("importmode",0).toInt();

    if (index == 0)
    {
        ui->Read_PushButton->setVisible(false);
    }
    else
    {
        ui->Read_PushButton->setVisible(true);
    }

    ClearTableWidgetContents();
}

void BaseWindow::on_Read_PushButton_clicked()
{
    m_bIsReadState = true;
    ClearTableWidgetContents();

    foreach (QString filename, m_fileLists) {
        decode(filename);
    }
    m_bIsReadState = false;
}

void BaseWindow::on_Result_TableWidget_itemSelectionChanged()
{

    if (m_bIsReadState)
    {
        return;
    }

    if (listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
}

bool BaseWindow::eventFilter(QObject *target, QEvent *event)
{
    switch (event->type())
    {
        case QEvent::KeyPress:
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(b_isEditing)
            {
                if (keyEvent->key() == Qt::Key_Down)
                {
                    if (target == ui->Result_TableWidget)
                    {
                        if (ui->Result_TableWidget->currentColumn() == 1)
                        {
                            if (listWidget->count() > 0)
                            {
                                QListWidgetItem *pItem = listWidget->item(0);
                                listWidget->setCurrentItem(pItem);
                                listWidget->setFocus();
                            }
                        }
                    }
                    return true;
                }
                else if(keyEvent->key() == Qt::Key_Up)
                {
                    if (target == ui->Result_TableWidget)
                    {
                        if (ui->Result_TableWidget->currentColumn() == 1)
                        {

                            if (listWidget->count() > 0)
                            {
                                QListWidgetItem *pItem = listWidget->item(listWidget->count() - 1);
                                listWidget->setCurrentItem(pItem);
                                listWidget->setFocus();
                            }
                        }
                    }
                    return true;
                }
            }

            break;
        }

    QObject::eventFilter(target,event);
}

void BaseWindow::keyPressEvent(QKeyEvent *keyevent)
{
    int uKey = keyevent->key();
    Qt::Key key = static_cast<Qt::Key>(uKey);

    if(key == Qt::Key_Escape)
    {
        if(listWidget != NULL)
        {
            listWidget->setVisible(false);
        }
    }
    if((listWidget == NULL || listWidget->count() == 0))
        return;

    int iIndex = listWidget->currentRow();
    if(key == Qt::Key_Up)
    {
        iIndex--;
        if(iIndex < 0) iIndex = 0;
        QListWidgetItem *pItem = listWidget->item(iIndex);
        listWidget->setCurrentItem(pItem);

    }
    else if (key == Qt::Key_Down)
    {
        iIndex++;
        if(iIndex >= listWidget->count()) iIndex = listWidget->count() - 1;
        QListWidgetItem *pItem = listWidget->item(iIndex);
        listWidget->setCurrentItem(pItem);
    }
    else if (key == Qt::Key_Enter || key == Qt::Key_Return)
    {
        if(listWidget != NULL)
        {
            if(listWidget->currentItem() != NULL)
            {
                QString s = listWidget->currentItem()->text();
                ui->Result_TableWidget->setFocus();
                ui->Result_TableWidget->currentItem()->setText(s);
            }
            listWidget->setVisible(false);
        }
    }
}

void BaseWindow::on_Result_TableWidget_itemChanged(QTableWidgetItem *item)
{
//    if(item == NULL)
//    {
//        return;
//    }

//    if(item->column() < 1 || item->column() > 4)
//    {
//        return;
//    }

//    QString testTypeName;
//    if(item->column() == 2)
//    {
//        QStringList list = ASql::SearchTestTypes(item->text());
//        if(list.size() > 0)
//        {
//            testTypeName = list[0];
//        }
//    }

//    int row = item->row();

//    QTableWidgetItem *SampleNoitem = ui->Result_TableWidget->item(row,0);
//    if(SampleNoitem == NULL)
//    {
//        return;
//    }

//    QString value =SampleNoitem->text();

//    for(int i = 0; i < ui->Result_TableWidget->rowCount(); i++)
//    {
//        if( i != row)
//        {
//            if ((ui->Result_TableWidget->item(i,0) != NULL) && (ui->Result_TableWidget->item(i,0)->text() == value))
//            {
//                ui->Result_TableWidget->item(i, item->column())->setText(item->text());
//                if(item->column() == 2)
//                {
//                    ui->Result_TableWidget->item(i, item->column() + 1)->setText(testTypeName);
//                }
//            }
//        }
//    }


}
