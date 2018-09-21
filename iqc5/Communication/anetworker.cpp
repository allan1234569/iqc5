#include "anetworker.h"
#include "ui_anetworker.h"
#include "res.h"

ANetWorker::ANetWorker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ANetWorker)
{
    ui->setupUi(this);
    this->setFixedSize(635,365);

    m_pServer = NULL;
    m_pClient = NULL;

    QString tempLocalPort, tempHost, tempPort, tempTimerStr;
    readSettings(tempHost,"COMM/REMOTEHOST");
    readSettings(tempPort,"COMM/REMOTEPORT");
    readSettings(tempLocalPort,"COMM/LOCALPORT");
    readSettings(tempTimerStr,"PROTOCOL/TIMER");

    ui->deviceValue_Label->setText(g_sDestInst.isEmpty()?QString("未知仪器"):g_sDestInst);

    m_timerInterval = timeChangeover(tempTimerStr);
    if ( !tempHost.isEmpty() && !tempPort.isEmpty() && tempLocalPort.isEmpty() )    //连接远程主机
    {
        QString tHost = tempHost;
        QString tPort = tempPort;

        m_pClient = new AClient(this);
        m_pClient->init_Client(m_timerInterval);
        connect(m_pClient,SIGNAL(sig_newData(QString)),this,SLOT(slt_showData(QString)));
        connect(m_pClient,SIGNAL(sig_currentStatus(QString,QString)),this,SLOT(slt_showStatus(QString,QString)));
        connect(m_pClient,SIGNAL(sig_displayTrayIcon(bool)),this,SLOT(slt_displayTrayIcon(bool)));

        ui->port_Label->setVisible(false);
        ui->portValue_Label->setVisible(false);
        ui->hostValue_Label->setText(QString("%1:%2").arg(tHost).arg(tPort));


    }
    else if ( !tempHost.isEmpty() && !tempPort.isEmpty() && !tempLocalPort.isEmpty() )    //本地侦听
    {
        if ( !tempLocalPort.isEmpty() )
        {
            QString tPort = tempLocalPort;

            m_pServer = new AServer(this);
            connect(m_pServer,SIGNAL(newConnection()),m_pServer,SLOT(slt_onNewConnection()));
            connect(m_pServer,SIGNAL(sig_newData(QString)),this,SLOT(slt_showData(QString)));
            connect(m_pServer,SIGNAL(sig_currentStatus(QString,QString)),this,SLOT(slt_showStatus(QString,QString)));
            connect(m_pServer,SIGNAL(sig_displayTrayIcon(bool)),this,SLOT(slt_displayTrayIcon(bool)));
            m_pServer->listen(QHostAddress::Any,tPort.toInt()); //监听
            m_pServer->setTimer(m_timerInterval);               //设置一个定时器，定时采集数据

            ui->port_Label->setText("侦听端口：");
            ui->portValue_Label->setText(tPort);

            ui->port_Label->setVisible(true);
            ui->portValue_Label->setVisible(true);
            ui->portValue_Label->setText(tPort);
            ui->hostValue_Label->setText(QString("%1:%2").arg(tempHost).arg(tempPort));


        }
    }
}

ANetWorker::~ANetWorker()
{
    delete ui;
}

void ANetWorker::clear_display()
{
    ui->textBrowser->clear();
}

void ANetWorker::reStart()
{
    m_pServer->close();
    m_pClient->close();
}

void ANetWorker::slt_showData(const QString &value)
{
    QString lastStr = ui->textBrowser->toPlainText();   //之前的内容
    QString data = formatBytes2Visible(value,lastStr);  //格式化
    if (!data.isEmpty())
    {
        ui->textBrowser->append(data);
    }
}

void ANetWorker::slt_showStatus(const QString &msg, const QString &status)
{
    ui->stateValue_Label->clear();
    ui->stateValue_Label->setText(status);
    if (status.compare("未连接") == 0)
    {
        emit sig_curStatus(msg, "://pics/network_offline_256px.png");
    }
    else if(status.compare("已连接") == 0)
    {
        emit sig_curStatus(msg, "://pics/computers_256px.png");
    }
}

void ANetWorker::slt_displayTrayIcon(bool flag)
{
    emit sig_displayTrayIcon(flag);
}

