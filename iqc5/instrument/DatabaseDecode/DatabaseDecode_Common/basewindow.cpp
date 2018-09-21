#include "basewindow.h"
#include "ui_basewindow.h"
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

#include "aprocess.h"
#include "asetupdialog.h"

BaseWindow::BaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaseWindow)
{

    ui->setupUi(this);

    loadConfig();

    createActions();

    showTrayIcon();

    m_bCanClose = false;
    m_nSampleNo = 1;
    cnt = 0;

    m_Timer = new QTimer(this);
    connect(m_Timer,SIGNAL(timeout()),
            this,SLOT(slt_timeout()));
    double tempTimer = readSetting("timer","0.5").toDouble();
    tempTimer = tempTimer * 1000;

    m_Timer->setInterval(tempTimer);
    m_Timer->start();

    ui->Original_TableWidget->horizontalHeader()->setHighlightSections(false);
    ui->After_TableWidget->horizontalHeader()->setHighlightSections(false);

    connect(ui->SampleDate_DateEdit,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(slt_setQuery()));
}

BaseWindow::~BaseWindow()
{
    delete ui;
    m_accessDB.closeDB();
}


void BaseWindow::init()
{
    loadConfig();

    //本地数据库初始化
    m_accessDB.m_sDriver = driver;
    m_accessDB.m_sDbName = databasePath;
    m_accessDB.m_sIdName = "DS";
    m_accessDB.m_sUid = uid;
    m_accessDB.m_sPassword = password;
    if (!m_accessDB.openDB())
    {
        QMessageBox msgBox;
        msgBox.setText("本地数据库连接失败,请检查配置");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setButtonText(QMessageBox::Ok,QString("是"));
        msgBox.setButtonText(QMessageBox::Cancel,QString("否"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    m_accessDB.newQuery();

    ///界面初始化
    QString tempStr;
    int tempNum;

    ui->DbFilePath_LineEdit->setText(databasePath);

    tempStr = readSetting("autoin","").toString();
    if (tempStr.isEmpty())
    {
        writeSetting("autoin",1);
        tempNum = readSetting("autoin",1).toInt();
    }
    else
    {
        tempNum = tempStr.toInt();
    }

    if (tempNum == 0)
    {
        ui->AutoIn_CheckBox->setChecked(false);
    }
    else if (tempNum == 1)
    {
        ui->AutoIn_CheckBox->setChecked(true);
    }

    ui->SampleDate_DateEdit->setDate(QDate::currentDate());
}

void BaseWindow::setDatabaseFilePath(const QString path)
{
    ui->DbFilePath_LineEdit->setText(path);
}

void BaseWindow::updateOriginalTableWidget(QSqlQuery *query, QStringList &fields)
{
    int recordCount = 0;

    int rowCount = ui->Original_TableWidget->rowCount();

    while(query->next())
    {
           recordCount++;
    }

    if (recordCount <= 0)
    {
        return;
    }

    if (recordCount > rowCount)
    {
        QString field;
        int row = rowCount;
        query->seek(rowCount-1);
        while(query->next())
        {
            ui->Original_TableWidget->insertRow(row);
            for(int i = 0; i < fields.count(); i++)
            {
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setTextAlignment(Qt::AlignHCenter);
                ui->Original_TableWidget->setItem(row,i,item);

                field = query->value(fields.at(i)).toString();

                ui->Original_TableWidget->item(row,i)->setText(field);
            }

            row++;
        }
    }
    else
    {
        return;
    }

    ui->Original_TableWidget->scrollToBottom();
}

void BaseWindow::updateAfterTableWidget(int row)
{
    ui->After_TableWidget->insertRow(row);
    int column = ui->After_TableWidget->columnCount();
    for(int i = 0; i < column; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignHCenter);
        ui->After_TableWidget->setItem(row,i,item);
        ui->After_TableWidget->item(row,i)->setText(
                    ui->Original_TableWidget->item(row,i)->text()
                    );
    }

    ui->After_TableWidget->scrollToBottom();
}

void BaseWindow::clearAllData(QTableWidget *widget)
{
    for(int i = widget->rowCount()-1; i >= 0; i--)
    {
        widget->removeRow(i);
    }
}

void BaseWindow::loadConfig()
{
    f_loadConfig();
    m_sInstr = readSetting("INSTR/devicename","").toString();
    m_sLabNumber = readSetting("LABORATORY/labno","").toString();
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
    m_sSampleDate = ui->SampleDate_DateEdit->text();
    slt_setQuery();

    decode();

    int original_rowCount = ui->Original_TableWidget->rowCount();

    int put_rowCount = ui->After_TableWidget->rowCount();

    if (original_rowCount > put_rowCount)
    {
        if(ui->AutoIn_CheckBox->isChecked())    //自动入库
        {
            on_Import_PushButton_clicked();
        }
        else
        {
            return;
        }
    }
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

int BaseWindow::decode(const QString &data)
{

}

void BaseWindow::redecode()
{
    bool lb_continue = true;
    int li_count = 0;
    int li_ret;

    QString msg;

    if (m_nRedecodeCnt > 50)
    {
        return ;
    }



    while (lb_continue)
    {
        li_ret = decode();
        if (li_ret == 0)
        {
            li_count++;

            m_nRedecodeCnt++;

            if (m_nRedecodeCnt > 0)
            {
                m_nRedecodeCnt--;
            }

            lb_continue = true;
        }
        else
        {
            lb_continue = false;
        }
    }

    if (li_count <= 0)
    {
        if (li_ret == -1)
        {
            msg = tr("数据库打开失败，没有数据被处理");
        }
        else if (li_ret == 1)
        {
            msg = tr("没有找到有效数据块，停止处理，请稍后再试");
        }
    }
    else
    {
        if(li_ret == -1)
        {
            msg = tr("已处理%1组数据,此时数据库打开失败数据无法提交").arg(li_count);
        }
        else if(li_ret == 1)
        {
            msg = tr("成功处理%1组数据").arg(li_count);
        }

    }

    m_sysTrayIcon->showMessage(tr("提示"),msg,QSystemTrayIcon::Information,50000);

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

void BaseWindow::addResult(QString as_sampleNo, QString as_value, QString as_itemCode)
{

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
    ljo_jsonObject.insert("lab",m_sLabNumber);
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

    readWriteLock.lockForRead();
    QString fileData = QString::fromLocal8Bit(file.readAll());
    file.close();
    readWriteLock.unlock();

    return fileData;
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

    connect(m_sysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(slt_showTrayIcon(QSystemTrayIcon::ActivationReason)));
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


void BaseWindow::on_Select_PushButton_clicked()
{

}

void BaseWindow::on_Import_PushButton_clicked()
{
    m_Timer->stop();

    if (!m_db.open())
    {
        return;
    }

    if(ui->AutoIn_CheckBox->isChecked())
    {
        int original_rowCount = ui->Original_TableWidget->rowCount();

        int put_rowCount = ui->After_TableWidget->rowCount();

        QString ls_sampleNo;
        QString ls_itemNo;
        QString ls_result;
        QString ls_time;

        if (original_rowCount > put_rowCount)
        {
            bool lb_close = false;
            int row = put_rowCount;
            for(int i = row; i < original_rowCount ;i++)
            {
                ls_sampleNo = ui->Original_TableWidget->item(i,0)->text();
                ls_itemNo   = ui->Original_TableWidget->item(i,1)->text();
                ls_result   = ui->Original_TableWidget->item(i,2)->text();
                ls_time     = ui->Original_TableWidget->item(i,3)->text();

                int ret = m_db.sendResult(ls_sampleNo,ls_itemNo,ls_result,m_sInstr,m_sLabNumber,ls_time);
                if (ret == 0)
                {
                    updateAfterTableWidget(i);
                }
                else if(ret == 2)
                {
                    lb_close = true;
                    break;
                }
            }

            if (lb_close)
            {
                ui->AutoIn_CheckBox->setChecked(false);
            }
        }
    }
    else
    {
        int rowIndex = ui->Original_TableWidget->currentRow();
    }

    m_db.close();
    m_Timer->start();
}

void BaseWindow::on_AutoIn_CheckBox_clicked(bool checked)
{
    if (checked)
    {
        writeSetting("autoin",1);
    }
    else
    {
        writeSetting("autoin",0);
    }
}

void BaseWindow::on_SampleDate_DateEdit_dateChanged(const QDate &date)
{
    m_sSampleDate = date.toString("yyyy-MM-dd");
    clearAllData(ui->Original_TableWidget);
    slt_setQuery();
}

