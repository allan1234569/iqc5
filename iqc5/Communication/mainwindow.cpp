#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "res.h"
#include <QProcess>
#include <QDir>
#include <aprocess.h>
#include <QDate>
#include <QFile>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFocusEvent>
#include <QFileDialog>
#include "aboutdialog.h"
#include <QCoreApplication>
#include <QEvent>

#ifdef Q_OS_WIN
    #include <windows.h>

#pragma comment(lib,"user32.lib")

#elif Q_OS_UNIX

#endif



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_nwWidget = NULL;
    m_spWidget = NULL;

    f_exit = false;

    init();

    m_systemTranIcon = new QSystemTrayIcon(this);

    creatTrayIcon();
    showTryaIcon();

    f_log("通信程序已启动");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_spWidget;
    delete m_nwWidget;

    delete m_systemTranIcon;
    delete m_tray_Menu;
    delete m_action_Show;
    delete m_action_Setup;
    delete m_action_Data;
    delete m_action_ComLog;
    delete m_action_Exit;
}

void MainWindow::init()
{
    QWidget *widget = this->centralWidget();
    if (widget != NULL)
    {
        delete widget;
        widget = NULL;
    }

    if (g_eType == NET)
    {
        m_Mode = "网络通信";
        m_nwWidget = new ANetWorker;
        this->setCentralWidget(m_nwWidget);

        this->setFixedSize(m_nwWidget->width(),m_nwWidget->height()+40);

        connect(m_nwWidget,SIGNAL(sig_displayTrayIcon(bool)),this,SLOT(slt_displayTrayIcon(bool)));
        connect(m_nwWidget,SIGNAL(sig_curStatus(QString,QString)),this,SLOT(slt_showCurrentStatus(QString,QString)));

    }
    else if(g_eType == COM)
    {
        m_Mode = "串口通信";
        m_spWidget = new ASerialPort;
        connect(m_spWidget,SIGNAL(sig_displayTrayIcon(bool)),this,SLOT(slt_displayTrayIcon(bool)));
        connect(m_spWidget,SIGNAL(sig_curStatus(QString,QString)),this,SLOT(slt_showCurrentStatus(QString,QString)));
        this->setCentralWidget(m_spWidget);
        this->setFixedSize(m_spWidget->width(),m_spWidget->height());
    }
    else
    {
        QMessageBox::warning(this,
                             QString("警告"),
                             QString("未知的通信方式，程序将关闭")
                             );
        f_log("未知的通信方式，程序启动失败");
        exit(0);
        //TODO
    }
}

void MainWindow::creatTrayIcon()
{
    m_tray_Menu = new QMenu;

    //初始化
    m_action_Show = new QAction("显示(S)",this);
    m_action_Setup = new QAction("设置",this);
    m_action_Data = new QAction("查看数据",this);
    m_action_ComLog = new QAction("查看通信日志",this);
    m_action_Exit = new QAction("退出",this);

    m_tray_Menu->addAction(m_action_Show);
    m_tray_Menu->addAction(m_action_Setup);
    m_tray_Menu->addAction(m_action_Data);
    m_tray_Menu->addAction(m_action_ComLog);
    m_tray_Menu->addAction(m_action_Exit);

    connect(m_action_Show,SIGNAL(triggered()),this,SLOT(slt_show()));
    connect(m_action_Setup,SIGNAL(triggered()),this,SLOT(on_action_Setup_triggered()));
    connect(m_action_Data,SIGNAL(triggered()),this,SLOT(on_action_Data_triggered()));
    connect(m_action_ComLog,SIGNAL(triggered()),this,SLOT(on_action_ComLog_triggered()));
    connect(m_action_Exit,SIGNAL(triggered()),this,SLOT(on_action_Exit_triggered()));
}

void MainWindow::showTryaIcon()
{
    //放在托盘提示信息、托盘图标

    QString toolTipStr = QString("通信程序\n"
                                 "通信仪器：%1\n"
                                 "通信方式：%2\n")
            .arg(g_sDestInst.isEmpty()?QString("未知仪器"):g_sDestInst)
            .arg(m_Mode);
    m_systemTranIcon ->setToolTip(toolTipStr);
    m_systemTranIcon ->setIcon(QIcon("://pics/computers_256px.png"));
    m_systemTranIcon->setContextMenu(m_tray_Menu);
    //点击托盘执行的事件
//    connect(m_systemTranIcon , SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));
    connect(m_systemTranIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(slt_showTrayIcon(QSystemTrayIcon::ActivationReason)));

    //显示托盘
    m_systemTranIcon->show();
    //托盘显示提示信息
    m_systemTranIcon->showMessage(QString("提示"), QString("通信程序已启动"));
}

void MainWindow::slt_show()
{
    this->show();
}

void MainWindow::slt_displayTrayIcon(bool flag)
{

    if (flag)
    {
        m_systemTranIcon->setIcon(QIcon("://pics/computers_256px.png"));
    }
    else
    {
        m_systemTranIcon->setIcon(QIcon(""));
    }
}

void MainWindow::slt_showCurrentStatus(const QString &msg, const QString source)
{
     m_systemTranIcon ->setIcon(QIcon(source));
     QString toolTipStr = QString("通信程序\n"
                                  "通信仪器：%1\n"
                                  "通信方式：%2\n"
                                  "%3")
             .arg(g_sDestInst.isEmpty()?QString("未知仪器"):g_sDestInst)
             .arg(m_Mode)
             .arg(msg);
     m_systemTranIcon->setToolTip(toolTipStr);
}

void MainWindow::slt_showTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::DoubleClick:
        this->show();
        break;
    default:
        break;
    }
}

void MainWindow::restartApplication()
{
    QCoreApplication::quit();
    QProcess::startDetached(QCoreApplication::applicationFilePath(),QStringList());
}

void MainWindow::on_action_Exit_triggered()
{
    f_exit = true;
    this->close();
}

void MainWindow::on_action_Setup_triggered()
{
    AProcess *process = new AProcess;
//    connect(process,SIGNAL(finished()),this,SLOT(slt_restartApplication()));
    process->setProgram("communication_setup.exe");
    process->start();
}

void MainWindow::on_action_ResultPath_triggered()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                      QString("请选择结果存放路径"),
                                      QString("./row"));

    g_sRawDataDir = path;
}

void MainWindow::on_action_Data_triggered()
{
    QDate date;
    QString logfilePath = g_sRawDataDir + "\/" + date.currentDate().toString("yyyyMMdd").append(".txt");


    QFile file(logfilePath);
    if (!file.exists())
    {
        QMessageBox::warning(this,
                             "提示",
                             QString("没有找到文件") + logfilePath
                             );
        return;
    }

    AProcess *process = new AProcess;
    QString program = "notepad.exe " + logfilePath;
    process->setProgram(program);
    process->start();
}

void MainWindow::on_action_ComLog_triggered()
{
    AProcess *process = new AProcess;

    QFile file(g_sFileLog);
    if (!file.exists())
    {
        QMessageBox::warning(this,
                             "提示",
                             QString("没有找到文件").append(g_sFileLog)
                             );
    }

    QString parements = QString("notepad.exe ").append(g_sFileLog);
    process->setProgram(parements);
    process->start();
}

void MainWindow::on_action_Clear_triggered()
{
    switch (g_eType) {
    case COM:
        if (m_spWidget != NULL)
        {
            m_spWidget->clear_display();
        }
        break;
    case NET:
        if (m_nwWidget != NULL)
        {
            m_nwWidget->clear_display();
        }
        break;
    default:
        break;
    }
}

void MainWindow::on_action_About_triggered()
{
    AboutDialog dialog;/* = new AboutDialog(this);*/
    dialog.exec();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
//    QMessageBox msg(QMessageBox::Warning,"退出","退出将导致无法接收串口数据，是否确定要退出？");
//    msg.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
//    msg.setButtonText(QMessageBox::Ok,QString("是"));
//    msg.setButtonText(QMessageBox::Cancel,QString("否"));

//    int ret = msg.exec ();

//    switch (ret) {
//    case QMessageBox::Ok:
//        f_exit = true;
//        break;
//    case QMessageBox::Cancel:
//        f_exit = false;
//    default:
//        break;
//    }


    if (!f_exit)
    {
        this->hide();
        event->ignore();
    }
    else
    {
        event->accept();
        f_log("通信程序退出\n");
    }

}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG *msg = static_cast<MSG*>(message);
    if (msg->message == WM_COPYDATA)
    {
//        COPYDATASTRUCT * p = reinterpret_cast<COPYDATASTRUCT*>(msg->lParam);  //此句报错
        restartApplication();

    }
    return QMainWindow::nativeEvent(eventType,message,result);
}

