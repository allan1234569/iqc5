/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *widget;
    QStackedWidget *stackedWidget;
    QWidget *page_1;
    QGroupBox *groupBox_11;
    QLabel *label_20;
    QGroupBox *groupBox_12;
    QLabel *label_15;
    QLabel *label_17;
    QLineEdit *lineEdit_DeviceName;
    QLineEdit *lineEdit_InstallPlace;
    QLabel *label_35;
    QLineEdit *lineEdit;
    QWidget *page_2;
    QGroupBox *groupBox_7;
    QRadioButton *radioButton_SerialComm;
    QRadioButton *radioButton_SocketComm;
    QRadioButton *radioButton_Log;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_9;
    QRadioButton *radioButton_Database;
    QLabel *label_22;
    QGroupBox *groupBox_8;
    QLabel *label_21;
    QWidget *page_3;
    QStackedWidget *stackedWidget_2;
    QWidget *page_serialPort;
    QGroupBox *groupBox_3;
    QGroupBox *groupBox_4;
    QLabel *label_23;
    QGroupBox *groupBox;
    QLabel *label_11;
    QLabel *label_14;
    QComboBox *comboBox_DataBits;
    QComboBox *comboBox_BuadRate;
    QLabel *label_12;
    QLabel *label_10;
    QComboBox *comboBox_StopBits;
    QLabel *label_13;
    QComboBox *comboBox_PortName;
    QWidget *widget_6;
    QComboBox *comboBox_Parity;
    QLabel *label_30;
    QComboBox *comboBox;
    QLabel *label_31;
    QLabel *label_32;
    QWidget *page_socket;
    QGroupBox *groupBox_13;
    QLabel *label_34;
    QGroupBox *groupBox_16;
    QGroupBox *groupBox_17;
    QRadioButton *radioButton_Clietnt;
    QRadioButton *radioButton_Server;
    QGroupBox *groupBox_18;
    QRadioButton *radioButton_Tcp;
    QRadioButton *radioButton_Udp;
    QGroupBox *groupBox_19;
    QLineEdit *lineEdit_IpPort;
    QLabel *label_18;
    QLabel *label_19;
    QLineEdit *lineEdit_IpAdress;
    QWidget *page_database;
    QGroupBox *groupBox_20;
    QLabel *label_27;
    QGroupBox *groupBox_21;
    QLineEdit *lineEdit_DataDbPath;
    QPushButton *pushButton_SelectDataDb;
    QLabel *label_26;
    QWidget *page_log;
    QGroupBox *groupBox_5;
    QLabel *label_24;
    QGroupBox *groupBox_6;
    QLabel *label_25;
    QLineEdit *lineEdit_LogPath;
    QPushButton *PushButton_SelectLogPath;
    QWidget *page_4;
    QGroupBox *groupBox_9;
    QLabel *label_33;
    QGroupBox *groupBox_10;
    QGroupBox *groupBox_14;
    QPushButton *pushButton_SelectDbPath;
    QLabel *label_16;
    QLineEdit *lineEdit_ServerDb;
    QRadioButton *radioButton_LocalServer;
    QRadioButton *radioButton_RemoteServer;
    QLabel *label_Port;
    QLabel *label_UserName;
    QLabel *label_Password;
    QLineEdit *lineEdit_Port;
    QLineEdit *lineEdit_UserName;
    QLineEdit *lineEdit_Password;
    QGroupBox *groupBox_15;
    QPushButton *pushButton_browse;
    QRadioButton *radioButton_UseDefaultPath;
    QLineEdit *lineEdit_OnlineIniPath;
    QRadioButton *radioButton_CustomPath;
    QLabel *label_28;
    QLabel *label_29;
    QLineEdit *lineEdit_ParserIniPath;
    QGroupBox *groupBox_2;
    QWidget *widget_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_6;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *toolButton_1;
    QLabel *label_7;
    QWidget *widget_2;
    QPushButton *pushButton_PreStep;
    QPushButton *pushButton_NextStep;
    QPushButton *pushButton_Cancel;
    QPushButton *pushButton_save;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(580, 428);
        widget = new QWidget(Dialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 580, 370));
        stackedWidget = new QStackedWidget(widget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(170, 0, 411, 370));
        stackedWidget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        page_1 = new QWidget();
        page_1->setObjectName(QStringLiteral("page_1"));
        groupBox_11 = new QGroupBox(page_1);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        groupBox_11->setGeometry(QRect(0, 0, 410, 120));
        label_20 = new QLabel(groupBox_11);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 10, 390, 100));
        label_20->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_20->setWordWrap(true);
        label_20->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        groupBox_12 = new QGroupBox(page_1);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        groupBox_12->setGeometry(QRect(0, 120, 410, 250));
        label_15 = new QLabel(groupBox_12);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(30, 100, 60, 20));
        label_17 = new QLabel(groupBox_12);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(30, 50, 60, 20));
        lineEdit_DeviceName = new QLineEdit(groupBox_12);
        lineEdit_DeviceName->setObjectName(QStringLiteral("lineEdit_DeviceName"));
        lineEdit_DeviceName->setGeometry(QRect(100, 100, 181, 20));
        lineEdit_InstallPlace = new QLineEdit(groupBox_12);
        lineEdit_InstallPlace->setObjectName(QStringLiteral("lineEdit_InstallPlace"));
        lineEdit_InstallPlace->setGeometry(QRect(100, 50, 180, 20));
        label_35 = new QLabel(groupBox_12);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(30, 150, 70, 20));
        lineEdit = new QLineEdit(groupBox_12);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(100, 150, 180, 20));
        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        groupBox_7 = new QGroupBox(page_2);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(0, 120, 410, 250));
        radioButton_SerialComm = new QRadioButton(groupBox_7);
        radioButton_SerialComm->setObjectName(QStringLiteral("radioButton_SerialComm"));
        radioButton_SerialComm->setGeometry(QRect(20, 30, 130, 20));
        radioButton_SocketComm = new QRadioButton(groupBox_7);
        radioButton_SocketComm->setObjectName(QStringLiteral("radioButton_SocketComm"));
        radioButton_SocketComm->setGeometry(QRect(20, 80, 130, 20));
        radioButton_Log = new QRadioButton(groupBox_7);
        radioButton_Log->setObjectName(QStringLiteral("radioButton_Log"));
        radioButton_Log->setGeometry(QRect(20, 190, 130, 20));
        label_4 = new QLabel(groupBox_7);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(160, 30, 480, 20));
        label_8 = new QLabel(groupBox_7);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(160, 80, 480, 20));
        label_9 = new QLabel(groupBox_7);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(160, 190, 480, 20));
        radioButton_Database = new QRadioButton(groupBox_7);
        radioButton_Database->setObjectName(QStringLiteral("radioButton_Database"));
        radioButton_Database->setGeometry(QRect(20, 140, 129, 20));
        label_22 = new QLabel(groupBox_7);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(160, 140, 240, 20));
        groupBox_8 = new QGroupBox(page_2);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setGeometry(QRect(0, 0, 410, 120));
        label_21 = new QLabel(groupBox_8);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(10, 10, 390, 100));
        label_21->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_21->setWordWrap(true);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        stackedWidget_2 = new QStackedWidget(page_3);
        stackedWidget_2->setObjectName(QStringLiteral("stackedWidget_2"));
        stackedWidget_2->setGeometry(QRect(0, 0, 430, 370));
        page_serialPort = new QWidget();
        page_serialPort->setObjectName(QStringLiteral("page_serialPort"));
        groupBox_3 = new QGroupBox(page_serialPort);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 0, 410, 370));
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 0, 410, 110));
        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(10, 10, 391, 91));
        label_23->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        groupBox = new QGroupBox(groupBox_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 110, 410, 260));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(30, 60, 54, 20));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(30, 180, 54, 20));
        comboBox_DataBits = new QComboBox(groupBox);
        comboBox_DataBits->setObjectName(QStringLiteral("comboBox_DataBits"));
        comboBox_DataBits->setGeometry(QRect(110, 100, 100, 22));
        comboBox_DataBits->setEditable(true);
        comboBox_BuadRate = new QComboBox(groupBox);
        comboBox_BuadRate->setObjectName(QStringLiteral("comboBox_BuadRate"));
        comboBox_BuadRate->setGeometry(QRect(110, 60, 100, 22));
        comboBox_BuadRate->setEditable(true);
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(30, 100, 54, 20));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(30, 20, 54, 20));
        comboBox_StopBits = new QComboBox(groupBox);
        comboBox_StopBits->setObjectName(QStringLiteral("comboBox_StopBits"));
        comboBox_StopBits->setGeometry(QRect(110, 140, 100, 22));
        comboBox_StopBits->setEditable(true);
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(30, 140, 54, 20));
        comboBox_PortName = new QComboBox(groupBox);
        comboBox_PortName->setObjectName(QStringLiteral("comboBox_PortName"));
        comboBox_PortName->setGeometry(QRect(110, 20, 100, 22));
        comboBox_PortName->setEditable(true);
        widget_6 = new QWidget(groupBox);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setGeometry(QRect(-550, -40, 410, 250));
        comboBox_Parity = new QComboBox(groupBox);
        comboBox_Parity->setObjectName(QStringLiteral("comboBox_Parity"));
        comboBox_Parity->setGeometry(QRect(110, 180, 100, 22));
        comboBox_Parity->setEditable(true);
        label_30 = new QLabel(groupBox);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(30, 220, 90, 20));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(140, 220, 90, 22));
        comboBox->setEditable(true);
        label_31 = new QLabel(groupBox);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(120, 220, 20, 20));
        label_32 = new QLabel(groupBox);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(240, 220, 100, 20));
        stackedWidget_2->addWidget(page_serialPort);
        page_socket = new QWidget();
        page_socket->setObjectName(QStringLiteral("page_socket"));
        groupBox_13 = new QGroupBox(page_socket);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        groupBox_13->setGeometry(QRect(0, 0, 410, 110));
        label_34 = new QLabel(groupBox_13);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(0, 0, 410, 110));
        label_34->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_34->setWordWrap(true);
        groupBox_16 = new QGroupBox(page_socket);
        groupBox_16->setObjectName(QStringLiteral("groupBox_16"));
        groupBox_16->setEnabled(true);
        groupBox_16->setGeometry(QRect(0, 110, 410, 260));
        groupBox_16->setFlat(true);
        groupBox_17 = new QGroupBox(groupBox_16);
        groupBox_17->setObjectName(QStringLiteral("groupBox_17"));
        groupBox_17->setGeometry(QRect(10, 10, 190, 80));
        groupBox_17->setFlat(false);
        radioButton_Clietnt = new QRadioButton(groupBox_17);
        radioButton_Clietnt->setObjectName(QStringLiteral("radioButton_Clietnt"));
        radioButton_Clietnt->setGeometry(QRect(20, 20, 80, 16));
        radioButton_Clietnt->setChecked(true);
        radioButton_Server = new QRadioButton(groupBox_17);
        radioButton_Server->setObjectName(QStringLiteral("radioButton_Server"));
        radioButton_Server->setGeometry(QRect(20, 50, 70, 16));
        groupBox_18 = new QGroupBox(groupBox_16);
        groupBox_18->setObjectName(QStringLiteral("groupBox_18"));
        groupBox_18->setGeometry(QRect(220, 10, 180, 80));
        radioButton_Tcp = new QRadioButton(groupBox_18);
        radioButton_Tcp->setObjectName(QStringLiteral("radioButton_Tcp"));
        radioButton_Tcp->setGeometry(QRect(20, 20, 89, 16));
        radioButton_Tcp->setChecked(true);
        radioButton_Udp = new QRadioButton(groupBox_18);
        radioButton_Udp->setObjectName(QStringLiteral("radioButton_Udp"));
        radioButton_Udp->setGeometry(QRect(20, 50, 89, 16));
        groupBox_19 = new QGroupBox(groupBox_16);
        groupBox_19->setObjectName(QStringLiteral("groupBox_19"));
        groupBox_19->setGeometry(QRect(10, 90, 391, 161));
        lineEdit_IpPort = new QLineEdit(groupBox_19);
        lineEdit_IpPort->setObjectName(QStringLiteral("lineEdit_IpPort"));
        lineEdit_IpPort->setGeometry(QRect(90, 50, 150, 20));
        label_18 = new QLabel(groupBox_19);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(30, 50, 60, 20));
        label_19 = new QLabel(groupBox_19);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(30, 100, 50, 20));
        lineEdit_IpAdress = new QLineEdit(groupBox_19);
        lineEdit_IpAdress->setObjectName(QStringLiteral("lineEdit_IpAdress"));
        lineEdit_IpAdress->setGeometry(QRect(90, 100, 150, 20));
        stackedWidget_2->addWidget(page_socket);
        page_database = new QWidget();
        page_database->setObjectName(QStringLiteral("page_database"));
        groupBox_20 = new QGroupBox(page_database);
        groupBox_20->setObjectName(QStringLiteral("groupBox_20"));
        groupBox_20->setGeometry(QRect(0, 0, 410, 110));
        label_27 = new QLabel(groupBox_20);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(0, 0, 410, 110));
        label_27->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_27->setWordWrap(true);
        groupBox_21 = new QGroupBox(page_database);
        groupBox_21->setObjectName(QStringLiteral("groupBox_21"));
        groupBox_21->setGeometry(QRect(0, 110, 410, 260));
        lineEdit_DataDbPath = new QLineEdit(groupBox_21);
        lineEdit_DataDbPath->setObjectName(QStringLiteral("lineEdit_DataDbPath"));
        lineEdit_DataDbPath->setGeometry(QRect(80, 110, 290, 20));
        pushButton_SelectDataDb = new QPushButton(groupBox_21);
        pushButton_SelectDataDb->setObjectName(QStringLiteral("pushButton_SelectDataDb"));
        pushButton_SelectDataDb->setGeometry(QRect(370, 110, 30, 23));
        label_26 = new QLabel(groupBox_21);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(20, 110, 54, 20));
        stackedWidget_2->addWidget(page_database);
        page_log = new QWidget();
        page_log->setObjectName(QStringLiteral("page_log"));
        groupBox_5 = new QGroupBox(page_log);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(0, 0, 410, 110));
        label_24 = new QLabel(groupBox_5);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(0, 0, 410, 110));
        label_24->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_24->setWordWrap(true);
        groupBox_6 = new QGroupBox(page_log);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(0, 110, 410, 260));
        label_25 = new QLabel(groupBox_6);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(10, 110, 54, 20));
        lineEdit_LogPath = new QLineEdit(groupBox_6);
        lineEdit_LogPath->setObjectName(QStringLiteral("lineEdit_LogPath"));
        lineEdit_LogPath->setGeometry(QRect(70, 110, 300, 20));
        PushButton_SelectLogPath = new QPushButton(groupBox_6);
        PushButton_SelectLogPath->setObjectName(QStringLiteral("PushButton_SelectLogPath"));
        PushButton_SelectLogPath->setGeometry(QRect(370, 110, 30, 23));
        stackedWidget_2->addWidget(page_log);
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        groupBox_9 = new QGroupBox(page_4);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        groupBox_9->setGeometry(QRect(0, 0, 410, 110));
        label_33 = new QLabel(groupBox_9);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(0, 0, 411, 110));
        label_33->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_33->setWordWrap(true);
        groupBox_10 = new QGroupBox(page_4);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        groupBox_10->setGeometry(QRect(0, 110, 410, 260));
        groupBox_14 = new QGroupBox(groupBox_10);
        groupBox_14->setObjectName(QStringLiteral("groupBox_14"));
        groupBox_14->setGeometry(QRect(0, 112, 410, 141));
        pushButton_SelectDbPath = new QPushButton(groupBox_14);
        pushButton_SelectDbPath->setObjectName(QStringLiteral("pushButton_SelectDbPath"));
        pushButton_SelectDbPath->setGeometry(QRect(360, 50, 30, 23));
        label_16 = new QLabel(groupBox_14);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 50, 60, 20));
        lineEdit_ServerDb = new QLineEdit(groupBox_14);
        lineEdit_ServerDb->setObjectName(QStringLiteral("lineEdit_ServerDb"));
        lineEdit_ServerDb->setGeometry(QRect(70, 50, 290, 20));
        radioButton_LocalServer = new QRadioButton(groupBox_14);
        radioButton_LocalServer->setObjectName(QStringLiteral("radioButton_LocalServer"));
        radioButton_LocalServer->setGeometry(QRect(10, 20, 89, 16));
        radioButton_LocalServer->setChecked(true);
        radioButton_RemoteServer = new QRadioButton(groupBox_14);
        radioButton_RemoteServer->setObjectName(QStringLiteral("radioButton_RemoteServer"));
        radioButton_RemoteServer->setGeometry(QRect(130, 20, 89, 16));
        radioButton_RemoteServer->setChecked(false);
        label_Port = new QLabel(groupBox_14);
        label_Port->setObjectName(QStringLiteral("label_Port"));
        label_Port->setGeometry(QRect(10, 80, 60, 20));
        label_UserName = new QLabel(groupBox_14);
        label_UserName->setObjectName(QStringLiteral("label_UserName"));
        label_UserName->setGeometry(QRect(10, 110, 60, 20));
        label_Password = new QLabel(groupBox_14);
        label_Password->setObjectName(QStringLiteral("label_Password"));
        label_Password->setGeometry(QRect(200, 110, 50, 20));
        lineEdit_Port = new QLineEdit(groupBox_14);
        lineEdit_Port->setObjectName(QStringLiteral("lineEdit_Port"));
        lineEdit_Port->setGeometry(QRect(70, 80, 113, 20));
        lineEdit_UserName = new QLineEdit(groupBox_14);
        lineEdit_UserName->setObjectName(QStringLiteral("lineEdit_UserName"));
        lineEdit_UserName->setGeometry(QRect(70, 110, 113, 20));
        lineEdit_Password = new QLineEdit(groupBox_14);
        lineEdit_Password->setObjectName(QStringLiteral("lineEdit_Password"));
        lineEdit_Password->setGeometry(QRect(250, 110, 113, 20));
        groupBox_15 = new QGroupBox(groupBox_10);
        groupBox_15->setObjectName(QStringLiteral("groupBox_15"));
        groupBox_15->setGeometry(QRect(0, 0, 410, 111));
        pushButton_browse = new QPushButton(groupBox_15);
        pushButton_browse->setObjectName(QStringLiteral("pushButton_browse"));
        pushButton_browse->setGeometry(QRect(360, 80, 30, 23));
        radioButton_UseDefaultPath = new QRadioButton(groupBox_15);
        radioButton_UseDefaultPath->setObjectName(QStringLiteral("radioButton_UseDefaultPath"));
        radioButton_UseDefaultPath->setGeometry(QRect(10, 20, 89, 16));
        radioButton_UseDefaultPath->setChecked(true);
        lineEdit_OnlineIniPath = new QLineEdit(groupBox_15);
        lineEdit_OnlineIniPath->setObjectName(QStringLiteral("lineEdit_OnlineIniPath"));
        lineEdit_OnlineIniPath->setGeometry(QRect(110, 50, 241, 20));
        radioButton_CustomPath = new QRadioButton(groupBox_15);
        radioButton_CustomPath->setObjectName(QStringLiteral("radioButton_CustomPath"));
        radioButton_CustomPath->setGeometry(QRect(120, 20, 90, 16));
        label_28 = new QLabel(groupBox_15);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(10, 50, 100, 20));
        label_29 = new QLabel(groupBox_15);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(10, 80, 100, 20));
        lineEdit_ParserIniPath = new QLineEdit(groupBox_15);
        lineEdit_ParserIniPath->setObjectName(QStringLiteral("lineEdit_ParserIniPath"));
        lineEdit_ParserIniPath->setGeometry(QRect(110, 80, 241, 20));
        stackedWidget->addWidget(page_4);
        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 0, 170, 370));
        groupBox_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        widget_3 = new QWidget(groupBox_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(10, 10, 150, 350));
        widget_3->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"border-color: rgb(48, 221, 255);"));
        label = new QLabel(widget_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 60, 80, 20));
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(70, 100, 80, 20));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(70, 140, 80, 20));
        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 50, 60, 20));
        label_6 = new QLabel(widget_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 90, 60, 20));
        toolButton_2 = new QToolButton(widget_3);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setEnabled(false);
        toolButton_2->setGeometry(QRect(10, 60, 50, 20));
        toolButton_2->setAutoRaise(true);
        toolButton_3 = new QToolButton(widget_3);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));
        toolButton_3->setEnabled(false);
        toolButton_3->setGeometry(QRect(10, 100, 50, 20));
        toolButton_3->setAutoRaise(true);
        toolButton_4 = new QToolButton(widget_3);
        toolButton_4->setObjectName(QStringLiteral("toolButton_4"));
        toolButton_4->setEnabled(false);
        toolButton_4->setGeometry(QRect(10, 140, 50, 20));
        toolButton_4->setAutoRaise(true);
        toolButton_1 = new QToolButton(widget_3);
        toolButton_1->setObjectName(QStringLiteral("toolButton_1"));
        toolButton_1->setEnabled(false);
        toolButton_1->setGeometry(QRect(10, 20, 50, 20));
        toolButton_1->setAutoRaise(true);
        label_7 = new QLabel(widget_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(70, 20, 80, 20));
        widget_2 = new QWidget(Dialog);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(0, 370, 580, 60));
        widget_2->setStyleSheet(QStringLiteral("background-color: rgb(223, 223, 223);"));
        pushButton_PreStep = new QPushButton(widget_2);
        pushButton_PreStep->setObjectName(QStringLiteral("pushButton_PreStep"));
        pushButton_PreStep->setGeometry(QRect(20, 20, 75, 23));
        pushButton_PreStep->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pushButton_NextStep = new QPushButton(widget_2);
        pushButton_NextStep->setObjectName(QStringLiteral("pushButton_NextStep"));
        pushButton_NextStep->setGeometry(QRect(410, 20, 75, 23));
        pushButton_NextStep->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pushButton_Cancel = new QPushButton(widget_2);
        pushButton_Cancel->setObjectName(QStringLiteral("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(490, 20, 75, 23));
        pushButton_Cancel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pushButton_save = new QPushButton(widget_2);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setGeometry(QRect(410, 20, 75, 23));
        pushButton_save->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        QWidget::setTabOrder(pushButton_PreStep, pushButton_NextStep);
        QWidget::setTabOrder(pushButton_NextStep, pushButton_Cancel);
        QWidget::setTabOrder(pushButton_Cancel, pushButton_save);
        QWidget::setTabOrder(pushButton_save, toolButton_4);
        QWidget::setTabOrder(toolButton_4, toolButton_1);
        QWidget::setTabOrder(toolButton_1, lineEdit_DeviceName);
        QWidget::setTabOrder(lineEdit_DeviceName, lineEdit_InstallPlace);
        QWidget::setTabOrder(lineEdit_InstallPlace, radioButton_SerialComm);
        QWidget::setTabOrder(radioButton_SerialComm, radioButton_SocketComm);
        QWidget::setTabOrder(radioButton_SocketComm, radioButton_Log);
        QWidget::setTabOrder(radioButton_Log, comboBox_PortName);
        QWidget::setTabOrder(comboBox_PortName, comboBox_BuadRate);
        QWidget::setTabOrder(comboBox_BuadRate, comboBox_DataBits);
        QWidget::setTabOrder(comboBox_DataBits, comboBox_StopBits);
        QWidget::setTabOrder(comboBox_StopBits, radioButton_Clietnt);
        QWidget::setTabOrder(radioButton_Clietnt, radioButton_Server);
        QWidget::setTabOrder(radioButton_Server, radioButton_Tcp);
        QWidget::setTabOrder(radioButton_Tcp, radioButton_Udp);
        QWidget::setTabOrder(radioButton_Udp, lineEdit_IpPort);
        QWidget::setTabOrder(lineEdit_IpPort, lineEdit_IpAdress);
        QWidget::setTabOrder(lineEdit_IpAdress, toolButton_3);
        QWidget::setTabOrder(toolButton_3, toolButton_2);

        retranslateUi(Dialog);

        stackedWidget->setCurrentIndex(3);
        comboBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Application Configuration", 0));
        groupBox_11->setTitle(QString());
        label_20->setText(QApplication::translate("Dialog", "<html><head/><body><p>\351\200\232\350\277\207\344\273\252\345\231\250\345\220\215\347\247\260\345\222\214\345\272\217\345\210\227\345\217\267\357\274\214\350\247\243\346\236\220\347\250\213\345\272\217\345\217\257\344\273\245\350\257\206\345\210\253\345\256\236\351\252\214\345\256\244\345\206\205\347\232\204\344\273\252\345\231\250</p><p>\345\210\207\350\256\260\357\274\232<span style=\" color:#ff0000;\">\345\220\214\344\270\200\345\256\211\350\243\205\345\234\260\347\202\271\344\270\213\347\232\204\344\273\252\345\231\250\345\220\215\347\247\260\344\270\215\345\217\257\351\207\215\345\244\215\357\274\214\345\220\246\345\210\231\345\260\206\344\274\232\345\257\274\350\207\264\346\225\260\346\215\256\345\257\274\345\205\245\345\210\260\345\205\266\344\273\226\345\220\214\345\220\215\344\273\252\345\231\250\344\270\255</span></p></body></html>", 0));
        groupBox_12->setTitle(QString());
        label_15->setText(QApplication::translate("Dialog", "\344\273\252\345\231\250\345\220\215\347\247\260\357\274\232", 0));
        label_17->setText(QApplication::translate("Dialog", "\345\256\211\350\243\205\345\234\260\347\202\271\357\274\232", 0));
        label_35->setText(QApplication::translate("Dialog", "\345\272\217\345\210\227\345\217\267\357\274\232", 0));
        groupBox_7->setTitle(QString());
        radioButton_SerialComm->setText(QApplication::translate("Dialog", "\344\270\262\345\217\243/USB\345\217\243\344\270\262\345\217\243\351\200\232\344\277\241", 0));
        radioButton_SocketComm->setText(QApplication::translate("Dialog", "\347\275\221\347\273\234\351\200\232\344\277\241", 0));
        radioButton_Log->setText(QApplication::translate("Dialog", "\350\256\277\351\227\256\346\227\245\345\277\227", 0));
        label_4->setText(QString());
        label_8->setText(QString());
        label_9->setText(QString());
        radioButton_Database->setText(QApplication::translate("Dialog", "\350\257\273\346\225\260\346\215\256\345\272\223", 0));
        label_22->setText(QString());
        groupBox_8->setTitle(QString());
        label_21->setText(QApplication::translate("Dialog", "<html><head/><body><p>\351\200\232\344\277\241\346\226\271\345\274\217\345\260\206\345\206\263\345\256\232\345\246\202\344\275\225\350\216\267\345\217\226\345\210\260\344\273\252\345\231\250\347\232\204\346\243\200\351\252\214\347\273\223\346\236\234\357\274\214\345\246\202\346\236\234\344\273\252\345\231\250\344\270\273\346\234\272\346\210\226\350\200\205\344\273\252\345\231\250\346\234\254\350\272\253\344\270\216\346\234\254\346\234\272\346\234\211\344\270\262\345\217\243\347\272\277\346\210\226\350\200\205USB\347\272\277\350\277\236\346\216\245\357\274\214\350\257\267\351\200\211\346\213\251\344\270\262\345\217\243/USB\344\270\262\345\217\243\351\200\232\344\277\241\357\274\214\351\202\243\344\271\210\350\275\257\344\273\266\345\260\206\344\274\232\351\200\232\350\277\207\344\270\262\345\217\243\346\235\245\350\216\267\345\217\226\345\210\260\346\243\200\351\252\214\347\273\223\346\236\234\357\274\233\345\246\202\346\236\234\344\273\252\345\231\250\346\210\226\350\200\205\344\273\252\345\231\250\344\270\273"
                        "\346\234\272\344\270\216\346\234\254\346\234\272\347\224\250\346\230\257\347\275\221\347\273\234\347\272\277\350\277\236\357\274\214\350\257\267\351\200\211\346\213\251\347\275\221\347\273\234\351\200\232\344\277\241\357\274\214\351\202\243\344\271\210\350\275\257\344\273\266\345\260\206\344\274\232\351\200\232\350\277\207\347\275\221\347\273\234\347\253\257\345\217\243\350\216\267\345\217\226\345\210\260\346\243\200\351\252\214\347\273\223\346\236\234\357\274\233\345\246\202\346\236\234\346\234\254\346\234\272\344\270\216\344\273\252\345\231\250\346\227\240\351\234\200\351\200\232\344\277\241\347\272\277\357\274\214\345\217\257\344\273\245\347\233\264\346\216\245\350\256\277\351\227\256\346\225\260\346\215\256\345\272\223\346\226\207\344\273\266\357\274\214\350\257\267\351\200\211\346\213\251\350\257\273\345\217\226\346\225\260\346\215\256\345\272\223\357\274\214\351\202\243\344\271\210\350\275\257\344\273\266\350\257\273\345\217\226\346\214\207\345\256\232\347\232\204\346\225\260\346\215\256\345\272\223\346\226"
                        "\207\344\273\266\346\235\245\350\216\267\345\217\226\346\243\200\351\252\214\347\273\223\346\236\234\357\274\233\345\220\246\345\210\231\350\257\267\351\200\211\346\213\251\350\256\277\351\227\256\346\227\245\345\277\227\357\274\214\351\200\232\350\277\207\350\247\243\346\236\220\346\227\245\345\277\227\346\226\207\344\273\266\346\235\245\350\216\267\345\217\226\346\211\200\351\234\200\350\246\201\347\232\204\346\243\200\351\252\214\347\273\223\346\236\234\343\200\202</p></body></html>", 0));
        groupBox_3->setTitle(QString());
        groupBox_4->setTitle(QString());
        label_23->setText(QApplication::translate("Dialog", "<html><head/><body><p>\344\270\213\351\235\242\346\230\257\344\270\262\345\217\243\351\200\232\344\277\241\346\227\266\346\211\200\351\234\200\345\217\202\346\225\260\357\274\214\350\257\267\345\217\202\350\200\203\344\273\252\345\231\250\347\232\204\351\200\232\344\277\241\345\215\217\350\256\256\350\277\233\350\241\214\346\255\243\347\241\256\347\232\204\351\205\215\347\275\256</p></body></html>", 0));
        groupBox->setTitle(QString());
        label_11->setText(QApplication::translate("Dialog", "\346\263\242\347\211\271\347\216\207\357\274\232", 0));
        label_14->setText(QApplication::translate("Dialog", "\346\243\200\351\252\214\344\275\215\357\274\232", 0));
        comboBox_DataBits->clear();
        comboBox_DataBits->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("Dialog", "5", 0)
         << QApplication::translate("Dialog", "6", 0)
         << QApplication::translate("Dialog", "7", 0)
         << QApplication::translate("Dialog", "8", 0)
        );
        comboBox_BuadRate->clear();
        comboBox_BuadRate->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("Dialog", "50", 0)
         << QApplication::translate("Dialog", "75", 0)
         << QApplication::translate("Dialog", "110", 0)
         << QApplication::translate("Dialog", "134", 0)
         << QApplication::translate("Dialog", "150", 0)
         << QApplication::translate("Dialog", "200", 0)
         << QApplication::translate("Dialog", "300", 0)
         << QApplication::translate("Dialog", "600", 0)
         << QApplication::translate("Dialog", "1200", 0)
         << QApplication::translate("Dialog", "1800", 0)
         << QApplication::translate("Dialog", "2400", 0)
         << QApplication::translate("Dialog", "4800", 0)
         << QApplication::translate("Dialog", "9600", 0)
         << QApplication::translate("Dialog", "14400", 0)
         << QApplication::translate("Dialog", "19200", 0)
         << QApplication::translate("Dialog", "38400", 0)
         << QApplication::translate("Dialog", "56000", 0)
         << QApplication::translate("Dialog", "57600", 0)
         << QApplication::translate("Dialog", "76800", 0)
         << QApplication::translate("Dialog", "115200", 0)
         << QApplication::translate("Dialog", "128000", 0)
         << QApplication::translate("Dialog", "256000", 0)
        );
        label_12->setText(QApplication::translate("Dialog", "\346\225\260\346\215\256\344\275\215\357\274\232", 0));
        label_10->setText(QApplication::translate("Dialog", "\347\253\257\345\217\243\345\217\267\357\274\232", 0));
        comboBox_StopBits->clear();
        comboBox_StopBits->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("Dialog", "1", 0)
         << QApplication::translate("Dialog", "1.5", 0)
         << QApplication::translate("Dialog", "2", 0)
        );
        label_13->setText(QApplication::translate("Dialog", "\345\201\234\346\255\242\344\275\215\357\274\232", 0));
        comboBox_PortName->clear();
        comboBox_PortName->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("Dialog", "1", 0)
         << QApplication::translate("Dialog", "2", 0)
         << QApplication::translate("Dialog", "3", 0)
         << QApplication::translate("Dialog", "4", 0)
         << QApplication::translate("Dialog", "5", 0)
         << QApplication::translate("Dialog", "6", 0)
         << QApplication::translate("Dialog", "7", 0)
         << QApplication::translate("Dialog", "8", 0)
         << QApplication::translate("Dialog", "9", 0)
         << QApplication::translate("Dialog", "10", 0)
         << QApplication::translate("Dialog", "11", 0)
         << QApplication::translate("Dialog", "12", 0)
         << QApplication::translate("Dialog", "13", 0)
         << QApplication::translate("Dialog", "14", 0)
         << QApplication::translate("Dialog", "15", 0)
         << QApplication::translate("Dialog", "16", 0)
         << QApplication::translate("Dialog", "17", 0)
         << QApplication::translate("Dialog", "18", 0)
         << QApplication::translate("Dialog", "19", 0)
         << QApplication::translate("Dialog", "20", 0)
         << QApplication::translate("Dialog", "21", 0)
         << QApplication::translate("Dialog", "22", 0)
         << QApplication::translate("Dialog", "23", 0)
         << QApplication::translate("Dialog", "24", 0)
         << QApplication::translate("Dialog", "25", 0)
         << QApplication::translate("Dialog", "26", 0)
         << QApplication::translate("Dialog", "27", 0)
         << QApplication::translate("Dialog", "28", 0)
         << QApplication::translate("Dialog", "29", 0)
         << QApplication::translate("Dialog", "30", 0)
         << QApplication::translate("Dialog", "31", 0)
         << QApplication::translate("Dialog", "32", 0)
         << QApplication::translate("Dialog", "33", 0)
         << QApplication::translate("Dialog", "34", 0)
         << QApplication::translate("Dialog", "35", 0)
         << QApplication::translate("Dialog", "36", 0)
         << QApplication::translate("Dialog", "37", 0)
         << QApplication::translate("Dialog", "38", 0)
         << QApplication::translate("Dialog", "39", 0)
         << QApplication::translate("Dialog", "40", 0)
         << QApplication::translate("Dialog", "41", 0)
         << QApplication::translate("Dialog", "42", 0)
         << QApplication::translate("Dialog", "43", 0)
         << QApplication::translate("Dialog", "44", 0)
         << QApplication::translate("Dialog", "45", 0)
         << QApplication::translate("Dialog", "46", 0)
         << QApplication::translate("Dialog", "47", 0)
         << QApplication::translate("Dialog", "48", 0)
         << QApplication::translate("Dialog", "49", 0)
         << QApplication::translate("Dialog", "50", 0)
         << QApplication::translate("Dialog", "51", 0)
         << QApplication::translate("Dialog", "52", 0)
         << QApplication::translate("Dialog", "53", 0)
         << QApplication::translate("Dialog", "54", 0)
         << QApplication::translate("Dialog", "55", 0)
         << QApplication::translate("Dialog", "56", 0)
         << QApplication::translate("Dialog", "57", 0)
         << QApplication::translate("Dialog", "58", 0)
         << QApplication::translate("Dialog", "59", 0)
         << QApplication::translate("Dialog", "60", 0)
         << QApplication::translate("Dialog", "61", 0)
         << QApplication::translate("Dialog", "62", 0)
         << QApplication::translate("Dialog", "63", 0)
         << QApplication::translate("Dialog", "64", 0)
         << QApplication::translate("Dialog", "65", 0)
         << QApplication::translate("Dialog", "66", 0)
         << QApplication::translate("Dialog", "67", 0)
         << QApplication::translate("Dialog", "68", 0)
         << QApplication::translate("Dialog", "69", 0)
         << QApplication::translate("Dialog", "70", 0)
         << QApplication::translate("Dialog", "71", 0)
         << QApplication::translate("Dialog", "72", 0)
         << QApplication::translate("Dialog", "73", 0)
         << QApplication::translate("Dialog", "74", 0)
         << QApplication::translate("Dialog", "75", 0)
         << QApplication::translate("Dialog", "76", 0)
         << QApplication::translate("Dialog", "77", 0)
         << QApplication::translate("Dialog", "78", 0)
         << QApplication::translate("Dialog", "79", 0)
         << QApplication::translate("Dialog", "80", 0)
         << QApplication::translate("Dialog", "81", 0)
         << QApplication::translate("Dialog", "82", 0)
         << QApplication::translate("Dialog", "83", 0)
         << QApplication::translate("Dialog", "84", 0)
         << QApplication::translate("Dialog", "85", 0)
         << QApplication::translate("Dialog", "86", 0)
         << QApplication::translate("Dialog", "87", 0)
         << QApplication::translate("Dialog", "88", 0)
         << QApplication::translate("Dialog", "89", 0)
         << QApplication::translate("Dialog", "90", 0)
         << QApplication::translate("Dialog", "91", 0)
         << QApplication::translate("Dialog", "92", 0)
         << QApplication::translate("Dialog", "93", 0)
         << QApplication::translate("Dialog", "94", 0)
         << QApplication::translate("Dialog", "95", 0)
         << QApplication::translate("Dialog", "96", 0)
         << QApplication::translate("Dialog", "97", 0)
         << QApplication::translate("Dialog", "98", 0)
         << QApplication::translate("Dialog", "99", 0)
         << QApplication::translate("Dialog", "100", 0)
         << QApplication::translate("Dialog", "101", 0)
         << QApplication::translate("Dialog", "102", 0)
         << QApplication::translate("Dialog", "103", 0)
         << QApplication::translate("Dialog", "104", 0)
         << QApplication::translate("Dialog", "105", 0)
         << QApplication::translate("Dialog", "106", 0)
         << QApplication::translate("Dialog", "107", 0)
         << QApplication::translate("Dialog", "108", 0)
         << QApplication::translate("Dialog", "109", 0)
         << QApplication::translate("Dialog", "110", 0)
         << QApplication::translate("Dialog", "111", 0)
         << QApplication::translate("Dialog", "112", 0)
         << QApplication::translate("Dialog", "113", 0)
         << QApplication::translate("Dialog", "114", 0)
         << QApplication::translate("Dialog", "115", 0)
         << QApplication::translate("Dialog", "116", 0)
         << QApplication::translate("Dialog", "117", 0)
         << QApplication::translate("Dialog", "118", 0)
         << QApplication::translate("Dialog", "119", 0)
         << QApplication::translate("Dialog", "120", 0)
         << QApplication::translate("Dialog", "121", 0)
         << QApplication::translate("Dialog", "122", 0)
         << QApplication::translate("Dialog", "123", 0)
         << QApplication::translate("Dialog", "124", 0)
         << QApplication::translate("Dialog", "125", 0)
         << QApplication::translate("Dialog", "126", 0)
         << QApplication::translate("Dialog", "127", 0)
         << QApplication::translate("Dialog", "128", 0)
         << QApplication::translate("Dialog", "129", 0)
         << QApplication::translate("Dialog", "130", 0)
         << QApplication::translate("Dialog", "131", 0)
         << QApplication::translate("Dialog", "132", 0)
         << QApplication::translate("Dialog", "133", 0)
         << QApplication::translate("Dialog", "134", 0)
         << QApplication::translate("Dialog", "135", 0)
         << QApplication::translate("Dialog", "136", 0)
         << QApplication::translate("Dialog", "137", 0)
         << QApplication::translate("Dialog", "138", 0)
         << QApplication::translate("Dialog", "139", 0)
         << QApplication::translate("Dialog", "140", 0)
         << QApplication::translate("Dialog", "141", 0)
         << QApplication::translate("Dialog", "142", 0)
         << QApplication::translate("Dialog", "143", 0)
         << QApplication::translate("Dialog", "144", 0)
         << QApplication::translate("Dialog", "145", 0)
         << QApplication::translate("Dialog", "146", 0)
         << QApplication::translate("Dialog", "147", 0)
         << QApplication::translate("Dialog", "148", 0)
         << QApplication::translate("Dialog", "150", 0)
         << QApplication::translate("Dialog", "151", 0)
         << QApplication::translate("Dialog", "152", 0)
         << QApplication::translate("Dialog", "153", 0)
         << QApplication::translate("Dialog", "154", 0)
         << QApplication::translate("Dialog", "155", 0)
         << QApplication::translate("Dialog", "156", 0)
         << QApplication::translate("Dialog", "157", 0)
         << QApplication::translate("Dialog", "158", 0)
         << QApplication::translate("Dialog", "159", 0)
         << QApplication::translate("Dialog", "160", 0)
         << QApplication::translate("Dialog", "161", 0)
         << QApplication::translate("Dialog", "162", 0)
         << QApplication::translate("Dialog", "163", 0)
         << QApplication::translate("Dialog", "164", 0)
         << QApplication::translate("Dialog", "165", 0)
         << QApplication::translate("Dialog", "166", 0)
         << QApplication::translate("Dialog", "167", 0)
         << QApplication::translate("Dialog", "168", 0)
         << QApplication::translate("Dialog", "169", 0)
         << QApplication::translate("Dialog", "170", 0)
         << QApplication::translate("Dialog", "171", 0)
         << QApplication::translate("Dialog", "172", 0)
         << QApplication::translate("Dialog", "173", 0)
         << QApplication::translate("Dialog", "174", 0)
         << QApplication::translate("Dialog", "175", 0)
         << QApplication::translate("Dialog", "176", 0)
         << QApplication::translate("Dialog", "177", 0)
         << QApplication::translate("Dialog", "178", 0)
         << QApplication::translate("Dialog", "179", 0)
         << QApplication::translate("Dialog", "180", 0)
         << QApplication::translate("Dialog", "181", 0)
         << QApplication::translate("Dialog", "182", 0)
         << QApplication::translate("Dialog", "183", 0)
         << QApplication::translate("Dialog", "184", 0)
         << QApplication::translate("Dialog", "185", 0)
         << QApplication::translate("Dialog", "186", 0)
         << QApplication::translate("Dialog", "187", 0)
         << QApplication::translate("Dialog", "188", 0)
         << QApplication::translate("Dialog", "189", 0)
         << QApplication::translate("Dialog", "190", 0)
         << QApplication::translate("Dialog", "191", 0)
         << QApplication::translate("Dialog", "192", 0)
         << QApplication::translate("Dialog", "193", 0)
         << QApplication::translate("Dialog", "194", 0)
         << QApplication::translate("Dialog", "195", 0)
         << QApplication::translate("Dialog", "196", 0)
         << QApplication::translate("Dialog", "197", 0)
         << QApplication::translate("Dialog", "198", 0)
         << QApplication::translate("Dialog", "199", 0)
         << QApplication::translate("Dialog", "200", 0)
         << QApplication::translate("Dialog", "201", 0)
         << QApplication::translate("Dialog", "202", 0)
         << QApplication::translate("Dialog", "203", 0)
         << QApplication::translate("Dialog", "204", 0)
         << QApplication::translate("Dialog", "205", 0)
         << QApplication::translate("Dialog", "206", 0)
         << QApplication::translate("Dialog", "207", 0)
         << QApplication::translate("Dialog", "208", 0)
         << QApplication::translate("Dialog", "209", 0)
         << QApplication::translate("Dialog", "210", 0)
         << QApplication::translate("Dialog", "211", 0)
         << QApplication::translate("Dialog", "212", 0)
         << QApplication::translate("Dialog", "213", 0)
         << QApplication::translate("Dialog", "214", 0)
         << QApplication::translate("Dialog", "215", 0)
         << QApplication::translate("Dialog", "216", 0)
         << QApplication::translate("Dialog", "217", 0)
         << QApplication::translate("Dialog", "218", 0)
         << QApplication::translate("Dialog", "219", 0)
         << QApplication::translate("Dialog", "220", 0)
         << QApplication::translate("Dialog", "221", 0)
         << QApplication::translate("Dialog", "222", 0)
         << QApplication::translate("Dialog", "223", 0)
         << QApplication::translate("Dialog", "224", 0)
         << QApplication::translate("Dialog", "225", 0)
         << QApplication::translate("Dialog", "226", 0)
         << QApplication::translate("Dialog", "227", 0)
         << QApplication::translate("Dialog", "228", 0)
         << QApplication::translate("Dialog", "229", 0)
         << QApplication::translate("Dialog", "230", 0)
         << QApplication::translate("Dialog", "231", 0)
         << QApplication::translate("Dialog", "232", 0)
         << QApplication::translate("Dialog", "233", 0)
         << QApplication::translate("Dialog", "234", 0)
         << QApplication::translate("Dialog", "235", 0)
         << QApplication::translate("Dialog", "236", 0)
         << QApplication::translate("Dialog", "237", 0)
         << QApplication::translate("Dialog", "238", 0)
         << QApplication::translate("Dialog", "239", 0)
         << QApplication::translate("Dialog", "240", 0)
         << QApplication::translate("Dialog", "241", 0)
         << QApplication::translate("Dialog", "242", 0)
         << QApplication::translate("Dialog", "243", 0)
         << QApplication::translate("Dialog", "244", 0)
         << QApplication::translate("Dialog", "245", 0)
         << QApplication::translate("Dialog", "246", 0)
         << QApplication::translate("Dialog", "247", 0)
         << QApplication::translate("Dialog", "248", 0)
         << QApplication::translate("Dialog", "249", 0)
         << QApplication::translate("Dialog", "250", 0)
         << QApplication::translate("Dialog", "251", 0)
         << QApplication::translate("Dialog", "252", 0)
         << QApplication::translate("Dialog", "253", 0)
         << QApplication::translate("Dialog", "254", 0)
         << QApplication::translate("Dialog", "255", 0)
        );
        comboBox_Parity->clear();
        comboBox_Parity->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("Dialog", "EVEN", 0)
         << QApplication::translate("Dialog", "ODD", 0)
         << QApplication::translate("Dialog", "SPACE", 0)
         << QApplication::translate("Dialog", "MARK", 0)
        );
        label_30->setText(QApplication::translate("Dialog", " \346\225\260\346\215\256\351\207\207\351\233\206\351\227\264\351\232\224\357\274\232", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "200", 0)
         << QApplication::translate("Dialog", "400", 0)
         << QApplication::translate("Dialog", "500", 0)
         << QApplication::translate("Dialog", "800", 0)
         << QApplication::translate("Dialog", "1000", 0)
         << QApplication::translate("Dialog", "2000", 0)
         << QApplication::translate("Dialog", "5000", 0)
        );
        label_31->setText(QApplication::translate("Dialog", "\346\257\217", 0));
        label_32->setText(QApplication::translate("Dialog", "\346\257\253\347\247\222 \351\207\207\351\233\206\344\270\200\346\254\241\346\225\260\346\215\256", 0));
        groupBox_13->setTitle(QString());
        label_34->setText(QApplication::translate("Dialog", "\350\257\267\346\240\271\346\215\256\345\256\236\351\231\205\346\203\205\345\206\265\346\255\243\347\241\256\351\200\211\346\213\251\351\200\232\344\277\241\346\226\271\345\274\217", 0));
        groupBox_16->setTitle(QString());
        groupBox_17->setTitle(QApplication::translate("Dialog", "\346\234\215\345\212\241\347\253\257/\345\256\242\346\210\267\347\253\257", 0));
        radioButton_Clietnt->setText(QApplication::translate("Dialog", "\345\256\242\346\210\267\347\253\257", 0));
        radioButton_Server->setText(QApplication::translate("Dialog", "\346\234\215\345\212\241\347\253\257", 0));
        groupBox_18->setTitle(QApplication::translate("Dialog", "\345\215\217\350\256\256", 0));
        radioButton_Tcp->setText(QApplication::translate("Dialog", "TCP\345\215\217\350\256\256", 0));
        radioButton_Udp->setText(QApplication::translate("Dialog", "UDP\345\215\217\350\256\256", 0));
        groupBox_19->setTitle(QApplication::translate("Dialog", "\350\257\246\347\273\206\345\217\202\346\225\260", 0));
        label_18->setText(QApplication::translate("Dialog", "\347\253\257\345\217\243\345\217\267\357\274\232", 0));
        label_19->setText(QApplication::translate("Dialog", "IP\345\234\260\345\235\200\357\274\232", 0));
        lineEdit_IpAdress->setText(QString());
        groupBox_20->setTitle(QString());
        label_27->setText(QApplication::translate("Dialog", "\350\257\273\345\217\226\346\225\260\346\215\256\345\272\223\347\232\204\346\226\271\345\274\217\346\230\257\351\200\232\350\277\207\347\233\264\346\216\245\350\257\273\344\273\252\345\231\250\347\232\204\346\234\254\345\234\260\346\225\260\346\215\256\345\272\223\347\232\204\346\225\260\346\215\256\347\232\204\346\226\271\345\274\217\346\235\245\350\216\267\345\217\226\346\225\260\346\215\256\357\274\214\350\257\267\346\255\243\347\241\256\351\200\211\346\213\251\346\225\260\346\215\256\345\272\223\350\267\257\345\276\204", 0));
        groupBox_21->setTitle(QString());
        pushButton_SelectDataDb->setText(QApplication::translate("Dialog", "...", 0));
        label_26->setText(QApplication::translate("Dialog", "\346\225\260\346\215\256\350\267\257\345\276\204\357\274\232", 0));
        groupBox_5->setTitle(QString());
        label_24->setText(QApplication::translate("Dialog", "\350\256\277\351\227\256\346\227\245\345\277\227\347\232\204\346\226\271\345\274\217\346\230\257\351\200\232\350\277\207\350\257\273\345\217\226\344\273\252\345\231\250\344\277\235\345\255\230\345\234\250\346\234\254\345\234\260\347\232\204\346\225\260\346\215\256\346\226\207\344\273\266\346\235\245\350\247\243\346\236\220\345\207\272\347\273\223\346\236\234\357\274\214\350\257\267\346\255\243\347\241\256\351\200\211\346\213\251\345\205\266\350\267\257\345\276\204", 0));
        groupBox_6->setTitle(QString());
        label_25->setText(QApplication::translate("Dialog", "\346\227\245\345\277\227\350\267\257\345\276\204\357\274\232", 0));
        PushButton_SelectLogPath->setText(QApplication::translate("Dialog", "...", 0));
        groupBox_9->setTitle(QString());
        label_33->setText(QApplication::translate("Dialog", "<html><head/><body><p>\351\200\232\344\277\241\347\250\213\345\272\217\351\200\232\350\277\207\350\257\273\345\217\226\351\200\232\344\277\241\347\250\213\345\272\217\351\205\215\347\275\256\346\226\207\344\273\266\346\235\245\350\216\267\345\217\226\347\232\204\351\200\232\344\277\241\346\226\271\345\274\217\357\274\214\350\247\243\346\236\220\347\250\213\345\272\217\351\200\232\350\277\207\350\257\273\345\217\226\350\247\243\346\236\220\347\250\213\345\272\217\351\205\215\347\275\256\346\226\207\344\273\266\343\200\202</p><p>\346\234\215\345\212\241\346\225\260\346\215\256\345\272\223\345\217\257\344\273\245\344\275\277\347\224\250\346\234\254\345\234\260SQLITE\346\225\260\346\215\256\357\274\214\344\271\237\345\217\257\344\275\277\347\224\250MySQL\346\225\260\346\215\256\345\272\223</p></body></html>", 0));
        groupBox_10->setTitle(QString());
        groupBox_14->setTitle(QApplication::translate("Dialog", "\346\234\215\345\212\241\345\231\250\346\225\260\346\215\256\345\272\223", 0));
        pushButton_SelectDbPath->setText(QApplication::translate("Dialog", "...", 0));
        label_16->setText(QApplication::translate("Dialog", "\346\225\260\346\215\256\345\272\223\357\274\232", 0));
        radioButton_LocalServer->setText(QApplication::translate("Dialog", "\346\234\254\345\234\260\346\225\260\346\215\256\345\272\223", 0));
        radioButton_RemoteServer->setText(QApplication::translate("Dialog", "\350\277\234\347\250\213\346\225\260\346\215\256\345\272\223", 0));
        label_Port->setText(QApplication::translate("Dialog", "\347\253\257\345\217\243\345\217\267\357\274\232", 0));
        label_UserName->setText(QApplication::translate("Dialog", "\347\231\273\345\275\225\345\220\215\357\274\232", 0));
        label_Password->setText(QApplication::translate("Dialog", "\345\257\206\347\240\201\357\274\232", 0));
        groupBox_15->setTitle(QApplication::translate("Dialog", "\351\205\215\347\275\256\350\267\257\345\276\204", 0));
        pushButton_browse->setText(QApplication::translate("Dialog", "...", 0));
        radioButton_UseDefaultPath->setText(QApplication::translate("Dialog", "\344\275\277\347\224\250\351\273\230\350\256\244\350\267\257\345\276\204", 0));
        radioButton_CustomPath->setText(QApplication::translate("Dialog", "\350\207\252\345\256\232\344\271\211\350\267\257\345\276\204", 0));
        label_28->setText(QApplication::translate("Dialog", "\351\200\232\344\277\241\347\250\213\345\272\217\351\205\215\347\275\256\350\267\257\345\276\204", 0));
        label_29->setText(QApplication::translate("Dialog", "\350\247\243\346\236\220\347\250\213\345\272\217\351\205\215\347\275\256\350\267\257\345\276\204", 0));
        groupBox_2->setTitle(QString());
        label->setText(QApplication::translate("Dialog", "\351\200\211\346\213\251\351\200\232\344\277\241\346\226\271\345\274\217", 0));
        label_2->setText(QApplication::translate("Dialog", "\350\257\246\346\203\205", 0));
        label_3->setText(QApplication::translate("Dialog", "\346\261\207\346\200\273", 0));
        label_5->setText(QString());
        label_6->setText(QString());
        toolButton_2->setText(QString());
        toolButton_3->setText(QString());
        toolButton_4->setText(QString());
        toolButton_1->setText(QString());
        label_7->setText(QApplication::translate("Dialog", "\344\273\252\345\231\250\350\256\276\347\275\256", 0));
        pushButton_PreStep->setText(QApplication::translate("Dialog", "\344\270\212\344\270\200\346\255\245", 0));
        pushButton_NextStep->setText(QApplication::translate("Dialog", "\344\270\213\344\270\200\346\255\245", 0));
        pushButton_Cancel->setText(QApplication::translate("Dialog", "\345\217\226 \346\266\210", 0));
        pushButton_save->setText(QApplication::translate("Dialog", "\344\277\235 \345\255\230", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
