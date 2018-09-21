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
#include <QTextStream>

#include "aprocess.h"
#include "asetupdialog.h"

BaseWindow::BaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaseWindow)
{
    ui->setupUi(this);

    m_bUseSysDate = false;
    m_bSysIconIsShow = true;

    m_nSampleNo = -1;
    m_sSampleNo = "-1";
    m_nResultCnt = 0;

    createActions();
    showTrayIcon();

    m_Timer = new QTimer(this);
    connect(m_Timer,SIGNAL(timeout()),
            this,SLOT(slt_timeout()));
    m_Timer->setInterval(2000); //设置为2秒
    m_Timer->start();

    m_sysTrayTimer = new QTimer(this);
    m_sysTrayTimer->setInterval(500);
    connect(m_sysTrayTimer,SIGNAL(timeout()),
            this,SLOT(modifyState()));

    m_bCanClose = false;

    m_nHandledSize = 0;

    m_nRedecodeCnt = 0;

    loadConfig();
}

BaseWindow::~BaseWindow()
{
    delete ui;
}

void BaseWindow::showSystemTrayMessage(const QString &msg)
{
    m_sysTrayIcon->showMessage(tr("提示"),
                               tr("仪器配置不正确，请重新配置"),
                               QSystemTrayIcon::Information,
                               3000
                               );
}

void BaseWindow::showSysTrayIcon(bool state)
{
    if (state)
    {
        m_sysTrayIcon->setIcon(QIcon("://pics/analysis_128px.png"));
    }
    else
    {
        m_sysTrayIcon->setIcon(QIcon(""));
    }

    m_sysTrayTimer->stop();
}

void BaseWindow::loadConfig()
{
    int li_temp;

    f_loadConfig();

    li_temp =  readSetting("decodemode",0).toInt();
    if (li_temp == 1)
    {
        m_enumDecodeMode = Log;
        li_temp = 1;
    }
    else
    {
        m_enumDecodeMode = SerialPort;
        li_temp = 0;
    }
    writeSetting("decodemode",li_temp);

}

void BaseWindow::getSampleResultTime(QString as_date)
{
    QString ls_format;

    ls_format = readSetting("DEC/sample_data_time_format","yyyy/MM/dd hh:mm:ss").toString();
    m_sSampleResultDateTime = QDateTime::fromString(as_date,ls_format).toString(ls_format);

    if (m_bUseSysDate)
    {
        m_sSampleResultDateTime = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    }

    if (m_sSampleResultDateTime.isEmpty())
    {
        m_sSampleDate = QDate::currentDate().toString("yyyy-MM-dd");
    }
    else
    {
        m_sSampleDate = QDateTime::fromString(m_sSampleResultDateTime,ls_format).date().toString("yyyy-MM-dd");
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
    QString fileData;

    QString filePath = m_applicationDir.currentPath().append("/raw/").
            append(QDateTime::currentDateTime().toString("yyyyMMdd")).
            append(".txt");
    m_sFileName = filePath;

    QFile file(filePath);

    if (!file.exists())
    {
        return;
    }

    readWriteLock.lockForRead();
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        readWriteLock.unlock();
    }
    else
    {
        QTextStream in(&file);
        //            in.setCodec("UTF-8");


        if (m_enumDecodeMode == Log)
        {
            in.seek(m_nHandledSize);
            fileData = in.read(file.size() - m_nHandledSize);
        }
        else
        {
            fileData =  in.readAll();
        }



        file.close();
        readWriteLock.unlock();

        if (QFile::remove(filePath))
        {
            if (!fileData.isEmpty())
            {
                if (m_db.isOpened())
                {
                    m_Timer->stop();

                    if (decode(fileData) == 0)
                    {
                        m_nHandledSize += fileData.size();
                    }

                    if (fileData.length() > 0)
                    {
                        m_sysTrayTimer->start();
                    }
                    else
                    {
                        showSysTrayIcon(true);
                    }
                    m_Timer->start();
                }
                else
                {
                    if (m_db.open())
                    {
                        m_Timer->stop();

                        if (decode(fileData) == 0)
                        {
                            m_nHandledSize += fileData.size();
                        }

                        if (fileData.length() > 0)
                        {
                            m_sysTrayTimer->start();
                        }
                        else
                        {
                            showSysTrayIcon(true);
                        }
                        m_Timer->start();
                    }
                }

            }
        }



    }
}

void BaseWindow::on_action_ReadFile_triggered()
{
    this->show();
    QString filePath = QFileDialog::getOpenFileName(this,
                                 QObject::tr("请选择原始数据文件"),
                                 QObject::tr("./"),
                                 QObject::tr("*.txt")
                                 );

    if (filePath.isEmpty())
    {
        return;
    }

    //TODO  已经获取到文件路径，打开他并解析
    QString fileData = getContent(filePath);
    if (fileData.isEmpty())
    {
        return;
    }

    if (!fileData.isEmpty())
    {

        m_Timer->stop();
        if (m_db.open())
        {
            decode(fileData);
        }
        m_Timer->start();
    }
}

void BaseWindow::on_action_ReHandle_triggered()
{
    QString filePath = m_applicationDir.currentPath().append("/raw/").
                                            append(QDateTime::currentDateTime().toString("yyyyMMdd")).
                                                   append(".txt");
    QFile file(filePath);
    if (!file.exists())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("未发现今日数据"));
        msgBox.exec();
        return;
    }

    //TODO 打开文件，重新解析
    QString fileData = getContent(filePath);

    if (fileData.isEmpty())
    {
        return;
    }

    if (!fileData.isEmpty())
    {
        m_Timer->stop();
        if (m_db.open())
        {
            decode(fileData);
        }
        m_Timer->start();
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

void BaseWindow::on_action_OriginalData_triggered()
{    
    QString filePath = m_applicationDir.currentPath().append("/raw/").append(QDateTime::currentDateTime().toString("yyyyMMdd")).append(".txt");

    QFile file(filePath);
    if (!file.exists())
    {
        this->show();
        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("提示"));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(QObject::tr("\n没有发现今日的原始数据./raw/%1").arg(filePath.right(12)));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,QObject::tr("确定"));
        msgBox.setFont(QFont("宋体",10));
        msgBox.exec();
        return;
    }

    QString program = QString("notepad.exe ").append(filePath);
    AProcess *process = new AProcess;
    process->setProgram(program);
    process->start();
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

void BaseWindow::modifyState()
{
    if (m_bSysIconIsShow)
    {
        m_sysTrayIcon->setIcon(QIcon(""));

    }
    else
    {
        m_sysTrayIcon->setIcon(QIcon("://pics/analysis_128px.png"));
    }

    m_bSysIconIsShow = !m_bSysIconIsShow;
}

void BaseWindow::redecode()
{
    decode("");
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

QString BaseWindow::dateToByteString(QString as_str)
{
    qint32 li_asc;
    QString ls_ret;
    ls_ret.resize(1);

    li_asc = as_str.mid(0,1).toInt() * 16 + as_str.mid(1,1).toInt();

    if (li_asc > 0)
    {
        ls_ret = QString(char(li_asc));
    }

    return ls_ret;
}

QString BaseWindow::hex(QString as_str)
{
    QString ls_asc;

    QByteArray lb_hex;
    QString ls_ret;

    ls_asc = as_str.left(1);

    if (ls_asc.toInt() > 0)
    {
        lb_hex.append(ls_asc);
        ls_ret = lb_hex.toHex();
    }
    else
    {
        ls_ret = "00";
    }

    return ls_ret;
}

int BaseWindow::getAsc(QString as_str)
{
    QString ls_bit;
    ls_bit = as_str.mid(0,1);
    if (ls_bit.length() > 0)
    {
        return ls_bit.toInt();
    }

    return 0;
}

int BaseWindow::sendResult(QString as_item, QString as_result)
{
    int ret = m_db.sendResult(m_sSampleNo,as_item,as_result,g_sRegInstr,g_sLabNo,m_sSampleDate);
    if (0 == ret)
    {
        addResult(m_sSampleNo,as_result,as_item,m_sSampleDate);
        m_nResultCnt++;
    }

    return ret;
}

void BaseWindow::addResult( const QString as_sampleNo, const QString as_value, const QString as_itemCode, const QString as_resultTime)
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


    ///格式：  样本号|项目代号|结果|时间|仪器|实验室编号
    QString resultStr = QString("%1|%2|%3|%4|%5|%6\r\n")
            .arg(as_sampleNo)
            .arg(as_itemCode)
            .arg(as_value)
            .arg(as_resultTime)
            .arg(g_sRegInstr)
            .arg(g_sLabNo);

    QString filepath = QDir::currentPath().append("/result/").append(QDate::currentDate().toString("yyyy-MM-dd")).append(".txt");
    QFile file(filepath);
    if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Append))
    {
        return;
    }

    file.write(resultStr.toStdString().data());

    file.close();
}

int BaseWindow::sendItemResult(QString as_code, const QString as_item)
{
    quint64 ll_pos;

    if (as_code.trimmed().isEmpty())
    {
        return 2;
    }

    ll_pos = as_code.indexOf(as_item);

    if (ll_pos < 0)
    {
        return 2;
    }

    as_code = as_code.mid(ll_pos+as_item.length());

    ll_pos = as_code.indexOf(" ");

    if (ll_pos >= 0)
    {
        as_code = as_code.left(ll_pos);
    }

    if (!as_code.isEmpty())
    {
        return sendResult(as_item,as_code);
    }
    else
    {
        return 3;
    }
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
        qDebug() << __LINE__;
        return "";
    }

    readWriteLock.lockForRead();
    QString fileData = QString::fromLocal8Bit(file.readAll());
    file.close();
    readWriteLock.unlock();

    return fileData;
}

QString BaseWindow::getSampleDate(int ai_year, int ai_month, int ai_day)
{
    QString ls_date;

    if (ai_year < 0)
    {
        return QDate::currentDate().toString("yyyy-MM-dd");
    }
    else
    {
        if (ai_year  < 50)
        {
            ai_year += 2000;
        }
        else
        {
            if (ai_year <= 100)
            {
                ai_year += 1900;
            }
            else
            {
                if (ai_year <= 1990)
                {
                    return QDate::currentDate().toString("yyyy-MM-dd");
                }
            }
        }
    }

    ls_date = QDate::fromString(QString("%1%2%3")
                                .arg(QString::number(ai_year))
                                .arg(QString::number(ai_month))
                                .arg(QString::number(ai_day)),
                                "yyyyMMdd")
            .toString("yyyy-MM-dd");

    return ls_date;

}

void BaseWindow::createActions()
{
    m_trayIconmenu = new QMenu();

    m_action_Show = new QAction(QObject::tr("显示"),this);
    m_action_ReadFile = new QAction(QObject::tr("读取文件"),this);
    m_action_ReHandle = new QAction(QObject::tr("重新处理当日数据"),this);
    m_action_Setup  = new QAction(QObject::tr("配置设置"),this);
    m_action_CheckOriginalData = new QAction(QObject::tr("查看原始数据"),this);
    m_action_CheckDecLog = new QAction(QObject::tr("查看解析日志"),this);
    m_action_Help = new QAction(QObject::tr("帮助"),this);
    m_action_Exit = new QAction(QObject::tr("退出"),this);

    m_action_Show->setToolTip(QObject::tr("显示"));
    m_action_ReadFile->setToolTip(QObject::tr("读取文件"));
    m_action_ReHandle->setToolTip(QObject::tr("重新处理当日数据"));
    m_action_Setup->setToolTip(QObject::tr("配置设置"));
    m_action_CheckOriginalData->setToolTip(QObject::tr("查看原始数据"));
    m_action_CheckDecLog->setToolTip(QObject::tr("查看解析日志"));
    m_action_Help->setToolTip(QObject::tr("帮助"));
    m_action_Exit->setToolTip(QObject::tr("退出"));

    connect(m_action_Show,SIGNAL(triggered()),
            this,SLOT(slt_show()));

    connect(m_action_ReadFile,SIGNAL(triggered()),
            this,SLOT(on_action_ReadFile_triggered()));

    connect(m_action_ReHandle,SIGNAL(triggered()),
            this,SLOT(on_action_ReHandle_triggered()));

    connect(m_action_Setup,SIGNAL(triggered()),
            this,SLOT(on_action_DecodeSetup_triggered()));

    connect(m_action_CheckOriginalData,SIGNAL(triggered()),
            this,SLOT(on_action_OriginalData_triggered()));

    connect(m_action_CheckDecLog,SIGNAL(triggered()),
            this,SLOT(on_action_DecodeLog_triggered()));

    connect(m_action_Help,SIGNAL(triggered()),
            this,SLOT(on_action_Help_triggered()));

    connect(m_action_Exit,SIGNAL(triggered()),
            this,SLOT(on_action_Exit_triggered()));

    m_trayIconmenu->addAction(m_action_Show);
    m_trayIconmenu->addAction(m_action_ReadFile);
    m_trayIconmenu->addAction(m_action_ReHandle);
    m_trayIconmenu->addAction(m_action_Setup);
    m_trayIconmenu->addAction(m_action_CheckOriginalData);
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
    m_sysTrayIcon->setToolTip(QString("已处理：%1条结果").arg(m_nResultCnt));

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
