#include "widget.h"
#include "ui_widget.h"
#include <QProcess>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QUuid>
#include <QSqlQuery>
#include <QFile>
#include <QGuiApplication>
#include <QCloseEvent>
#include "parserthread.h"
#include "global.h"
#include <QThread>

extern QSettings *settings;
//extern QSqlDatabase db;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    dialog = new SetupDialog(this);
    connect(dialog,SIGNAL(on_exit()),this,SLOT(close()));
    initSystemTray();
    GetConfigInfo();

//    db.setDatabaseName("mytest.db");
//    db.open();

    m_bConnected = false;
    client = new ClientSocket(this);
    client->connectToHost(hostAddress,hostPort);
    connect(client, SIGNAL(connected()), this, SLOT(OnConnected()));
    connect(client, SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
    while(!m_bConnected)
    {
        client->connectToHost(hostAddress,hostPort);
        client->waitForConnected();
        QThread::sleep(5);
    }
    timer = new QTimer(this);
    timer->start(timerInterval);
    connect(timer,SIGNAL(timeout()),this,SLOT(GetData()));

}



void Widget::initSystemTray()
{
    createAction();
    setTrayIcon();
    translateActions();

    QIcon icon = QIcon("://images/analysis_1.png");
    setWindowIcon(icon);
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("BNProspec Parser");
    trayIcon->setContextMenu(menu);
    QString titlec=tr("Hello");
    QString textc=QString("BNProspec Parser已启动!");
    trayIcon->show();
    trayIcon->showMessage(titlec,textc,QSystemTrayIcon::Information,5000);
}

void Widget::createAction()
{
    menu = new QMenu(this);

    action_setup = new QAction(this);
    action_quit = new QAction(this);

    menu->addAction(action_setup);
    menu->addAction(action_quit);

    connect(action_quit,SIGNAL(triggered()),this,SLOT(close()));
//    connect(action_setup,SIGNAL(triggered()),this,SLOT(showConfigureForm()));
}

void Widget::setTrayIcon()
{
    action_setup->setIcon(QIcon("://images/setup.png"));
    action_quit->setIcon(QIcon("://images/setup.png"));
}

void Widget::translateActions()
{
    action_setup->setText(tr("设置"));
    action_quit->setText(tr("退出"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::GetConfigInfo()
{
    QString ipAdress = settings->value(QString("SERVER/ip")).toString();
    QString portNo = settings->value(QString("SERVER/port")).toString();
    device.DeviceName = settings->value(QString("DEVICE/DeviceName")).toString();
    device.ModelName = settings->value(QString("DEVICE/ModelName")).toString();
    device.BrandName = settings->value(QString("DEVICE/BrandName")).toString();

    device.DeviceId = settings->value(QString("DEVICE/DeviceId")).toString();
    device.ModelId = settings->value(QString("DEVICE/ModelId")).toString();
    device.BrandId = settings->value(QString("DEVICE/BrandId")).toString();

    timerInterval = settings->value(QString("SETUP/TIMER")).toString().toInt();
    hostAddress.setAddress(ipAdress);
    hostPort = portNo.toShort();

    if(ipAdress.isEmpty() || portNo.isEmpty() || device.DeviceId.isEmpty() || device.ModelId.isEmpty() || device.BrandId.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("仪器信息配置不正确，请配置后重新启动应用程序");
        msgBox.setInformativeText("是否要配置?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Yes:
            dialog->exec();
            break;
//        case QMessageBox::No:
//            // Don't Save was clicked
//            break;
//        default:
//            // should never be reached
//            break;
        }
    }
}

void Widget::parser(const QString &content)
{
    QString dataTime, sampleId, testTypeCode;
    if(content.contains(QRegularExpression("<STX>\\dR")))
    {
        QStringList list = split(content,QRegularExpression("<CR><ETX>[0-9a-zA-Z]<CR><LF>"));
        foreach (QString str, list) {
            QStringList tempList = split(str,QRegularExpression("\\n"));
            foreach (QString line, tempList) {
                if( line.contains(QRegularExpression("<STX>\\dH")) )
                {
                    QRegularExpression regH("\\|\\d+<CR>");
                    QRegularExpressionMatch rm = regH.match(line);
                    if(rm.hasMatch())
                    {
                       dataTime = rm.capturedTexts().at(0);
                       dataTime.remove("|");
                       dataTime.remove("<CR>");
                    }
                }
                else if( line.contains(QRegularExpression("<STX>\\dO")) )//解析样本号
                {
                    QRegularExpression regO("O\\|(\\d)+\\|(\\d+)\\|\\d+\\|\\^+\\d+\\^+(\\w+)\\^+\\d+");
                    QRegularExpressionMatch rm = regO.match(line);
                    if(rm.hasMatch())
                    {
                        rm.capturedTexts().at(1);//子项目编号
                        sampleId = rm.capturedTexts().at(2);//样本号
                        testTypeCode = rm.capturedTexts().at(3);//检测项目
                    }
                }
                else if( line.contains(QRegularExpression("<STX>\\dR")) )
                {/*4R|1|^^^1^IgG^400^^F|15.2|g/l|7 TO 16 g/l|||F||||20140217102804<CR><ETX>9C<CR><LF>*/
                    QRegularExpression regR("R\\|\\d+\\|\\^+\\d+\\^+(\\w+)\\^+\\d+\\^+\\w+\\|+(\\d+.\\d+)");
                    QRegularExpressionMatch rm = regR.match(line);
                    if(rm.hasMatch())
                    {
                        QString testType = rm.capturedTexts().at(1);
                        QString value = rm.capturedTexts().at(2);
                        if(testType == testTypeCode)
                        {
                            MyProject *pro = new MyProject;
                            pro->sampleId = sampleId;
                            pro->testTypeCode = testTypeCode;
                            pro->Value = value.toDouble();
                            pro->DataTime = dataTime;
                            ProjectVec.push_back(pro);

                            testTypeCode.clear();
                            sampleId.clear();
                        }
                    }
                }
            }
        }
    }
}

QStringList Widget::split(const QString &desStr, const QRegularExpression &re, QString::SplitBehavior behavior) const
{
    return desStr.split(re,behavior);
}

QByteArray Widget::convertToJson()
{
    QJsonDocument jsonDocment;
    QJsonArray jsonArray;
    for(int i = 0; i < ProjectVec.size(); i++ )
    {
        MyProject *pro = ProjectVec.at(i);
        QJsonObject jsonObject;
        jsonObject.insert("sampleId",pro->sampleId);
        jsonObject.insert("testTypeCode",pro->testTypeCode);
        jsonObject.insert("value",QString::number(pro->Value));
        jsonObject.insert("dataTime",pro->DataTime);
        jsonObject.insert("deviceName",device.DeviceName);
        jsonObject.insert("modelName",device.ModelName);
        jsonObject.insert("brandName",device.BrandName);
        jsonObject.insert("deviceId",device.DeviceId);
        jsonObject.insert("modelId",device.ModelId);
        jsonObject.insert("brandId",device.BrandId);
        jsonArray.insert(i,jsonObject);
    }
    jsonDocment.setArray(jsonArray);
    QByteArray jsonData;
    if( !jsonDocment.isEmpty() )
    {
        jsonData= jsonDocment.toJson();
    }

    return jsonData;
}

bool Widget::SendMessage(QByteArray message)
{
    qDebug() << message;
//    client->abort();
//    client->connectToHost(QString("127.0.0.1"),10000);

//    qDebug() <<  client->error();
    if( -1 == client->sendMessage(message) )
    {
        return false;
    }
//    client->disconnectFromHost();

    return true;
}

void Widget::closeEvent(QCloseEvent *event)
{
    QGuiApplication::setQuitOnLastWindowClosed(true);
    event->accept();
}

void Widget::GetData()
{
    QString path = dir.currentPath();
    path += "/datalock.txt";
    QFile file(path);
    if( !file.open(QIODevice::ReadWrite) )
    {
        return;
    }

    QString content;
    content.append(file.readAll());
    file.close();


    ProjectVec.clear();
    QStringList list = content.split("<EOT>\r\n<ENQ>");
    QByteArray parserdStr;
    foreach (QString str, list) {
        parser(str);
    }
    parserdStr =  convertToJson();
    parserdStr.prepend("#<DataStart ");
    parserdStr.append(" DataEnd>#");
    if( SendMessage(parserdStr) )
    {
        file.open(QIODevice::Truncate);
        file.close();
        file.open(QIODevice::WriteOnly);
        file.write("");
        file.close();
    }
}

void Widget::OnConnected()
{
     m_bConnected = true;
}

void Widget::OnDisconnected()
{
    qDebug() << __LINE__;
    m_bConnected = false;
    while(!m_bConnected)
    {
        client->connectToHost(hostAddress,hostPort);
        client->waitForConnected();
        QThread::sleep(5);
    }
}
