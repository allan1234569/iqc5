 #include "Pv_Accruacy.h"
#include "ui_Pv_Accruacy.h"
#include "Pv_AccuracyPlot.h"
#include "MainWindow.h"
#include "formula.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QTextDocument>
#include <QTextBlock>
#include <QTextStream>

#include "Common/Axis.h"
#include "Common/Round.h"

#include <QAxWidget>
#include <QAxObject>

Pv_Accruacy::Pv_Accruacy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pv_Accruacy)
{
    lineEdit = NULL;
    listWidget = NULL;
    excursionChart = NULL;
    browser = NULL;

    ui->setupUi(this);
    Init();
    showEp9Table();
    showEp15Table();
//    setFixedSize(QApplication::desktop()->width(),QApplication::desktop()->height());//设置屏幕大小
}

void Pv_Accruacy::Init()
{
    setWindowTitle(tr("正确度实验"));
    ui->comboBox->addItem(tr("使用患者样本"));
    ui->comboBox->addItem(tr("使用参考物质"));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));

    ui->ep9_CalculateDate->setDate(QDate::currentDate());
    ui->ep9_ApprovalDate->setDate(QDate::currentDate());

    ui->ep15_CalculateDate->setDate(QDate::currentDate());
    ui->ep15_ApprovalDate->setDate(QDate::currentDate());

    ui->ep15_CalculateDate_2->setDate(QDate::currentDate());
    ui->ep15_ApprovalDate_2->setDate(QDate::currentDate());
}

void Pv_Accruacy::showEp9Table()
{
    ui->ep9_tableWidget->setColumnCount(12);
    ui->ep9_tableWidget->setRowCount(42);

    ui->ep9_tableWidget->horizontalHeader()->setVisible(false);
    ui->ep9_tableWidget->verticalHeader()->setVisible(false);

    ui->ep9_tableWidget->setSpan(0,0,2,1);
    ui->ep9_tableWidget->setSpan(0,1,2,1);
    ui->ep9_tableWidget->setSpan(0,2,1,4);
    ui->ep9_tableWidget->setSpan(0,6,2,1);
    ui->ep9_tableWidget->setSpan(0,7,2,1);
    ui->ep9_tableWidget->setSpan(0,8,1,4);

    for(int i = 0; i < 42; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            QTableWidgetItem *it;it = new QTableWidgetItem();
            it->setTextColor(QColor("#ffff99"));
            ui->ep9_tableWidget->setItem(i,j,it);
            ui->ep9_tableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->ep9_tableWidget->setColumnWidth(j,108);
        }
    }

   QLabel *ep9_label1 = new QLabel(tr("样本编号"));
   ep9_label1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(0,0,ep9_label1);

   QLabel *ep9_label2 = new QLabel(tr("SID"));
   ep9_label2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(0,1,ep9_label2);

   QLabel *ep9_label3 = new QLabel(tr("实验方法"));
   ep9_label3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(0,2,ep9_label3);

   QLabel *ep9_label4 = new QLabel(tr("x1"));
   ep9_label4->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(1,2,ep9_label4);

   QLabel *ep9_label5 = new QLabel(tr("x2"));
   ep9_label5->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(1,3,ep9_label5);

   QLabel *ep9_label6 = new QLabel(tr("均值"));
   ep9_label6->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(1,4,ep9_label6);

   QLabel *ep9_label7 = new QLabel(tr("差值"));
   ep9_label7->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(1,5,ep9_label7);
   ///
   /// \brief ep9_label8
   ///
   QLabel *ep9_label8 = new QLabel(tr("样本编号"));
   ep9_label8->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(0,6,ep9_label8);

   QLabel *ep9_label9 = new QLabel(tr("SID"));
   ep9_label9->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(0,7,ep9_label9);

   QLabel *ep9_label10 = new QLabel(tr("实验方法"));
   ep9_label10->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(0,8,ep9_label10);

   QLabel *ep9_label11 = new QLabel(tr("x1"));
   ep9_label11->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(1,8,ep9_label11);

   QLabel *ep9_label12 = new QLabel(tr("x2"));
   ep9_label12->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(1,9,ep9_label12);


   QLabel *ep9_label13 = new QLabel(tr("均值"));
   ep9_label13->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(1,10,ep9_label13);


   QLabel *ep9_label14 = new QLabel(tr("差值"));
   ep9_label14->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->ep9_tableWidget->setCellWidget(1,11,ep9_label14);


    for(int i = 0; i < 40; i++)//初始化列表头
    {
       QLabel *label = new QLabel(QString::number(i+1));
       label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
       ui->ep9_tableWidget->setCellWidget(i+2,0,label);

       QLabel *label1 = new QLabel(QString::number(i+1));
       label1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
       ui->ep9_tableWidget->setCellWidget(i+2,6,label1);
    }

}

void Pv_Accruacy::showEp15Table()
{
//    //初始化使用患者样本的界面
//    ui->ep15_tableWidget->setColumnCount(10);
//    ui->ep15_tableWidget->setRowCount(11);

//    ui->ep15_tableWidget->horizontalHeader()->setVisible(false);
//    ui->ep15_tableWidget->verticalHeader()->setVisible(false);

//    for(int i = 0; i < 11; i++)
//    {
//        for(int j = 0; j < 10; j++)
//        {
//            QTableWidgetItem *it;it = new QTableWidgetItem();
//            ui->ep15_tableWidget->setItem(i,j,it);
//            ui->ep15_tableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//            ui->ep15_tableWidget->setColumnWidth(j,130);
//            ui->ep15_tableWidget->setRowHeight(i,33);
//        }
//    }

//    for(int i = 1; i <= 10; i++)
//    {
//        QLabel *label = new QLabel(QString::number(i));
//        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//        ui->ep15_tableWidget->setCellWidget(i,0,label);

//        QLabel *label1 = new QLabel(QString::number(i+10));
//        label1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//        ui->ep15_tableWidget->setCellWidget(i,5,label1);
//    }

//    QLabel *ep15_label1 = new QLabel(tr("样本编号"));
//    ep15_label1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    ui->ep15_tableWidget->setCellWidget(0,0,ep15_label1);

//    QLabel *ep15_label3 = new QLabel(tr("实验方法结果"));
//    ep15_label3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    ui->ep15_tableWidget->setCellWidget(0,1,ep15_label3);

//    QLabel *ep15_label4 = new QLabel(tr("比较方法结果"));
//    ep15_label4->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    ui->ep15_tableWidget->setCellWidget(0,2,ep15_label4);

//    QLabel *ep15_label5 = new QLabel(tr("Yi-Xi"));
//    ep15_label5->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    ui->ep15_tableWidget->setCellWidget(0,3,ep15_label5);

//    QLabel *ep15_label6 = new QLabel(tr("Yi-Xi-B"));
//    ep15_label6->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    ui->ep15_tableWidget->setCellWidget(0,4,ep15_label6);

//    QLabel *ep15_label7 = new QLabel(tr("样本编号"));
//    ep15_label7->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    ui->ep15_tableWidget->setCellWidget(0,5,ep15_label7);

//    QLabel *ep15_label9 = new QLabel(tr("实验方法结果"));
//    ep15_label9->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    ui->ep15_tableWidget->setCellWidget(0,6,ep15_label9);

//    QLabel *ep15_label10 = new QLabel(tr("比较方法结果"));
//    ep15_label10->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    ui->ep15_tableWidget->setCellWidget(0,7,ep15_label10);

//    QLabel *ep15_label11 = new QLabel(tr("Yi-Xi"));
//    ep15_label11->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    ui->ep15_tableWidget->setCellWidget(0,8,ep15_label11);

//    QLabel *ep15_label12 = new QLabel(tr("Yi-Xi-B"));
//    ep15_label12->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    ui->ep15_tableWidget->setCellWidget(0,9,ep15_label12);


    //初始化使用患者样本的界面
    ui->ep15_tableWidget->horizontalHeader()->setVisible(false);
    ui->ep15_tableWidget->verticalHeader()->setVisible(false);

    ui->ep15_tableWidget->setColumnCount(8);
    ui->ep15_tableWidget->setRowCount(22);

    ui->ep15_tableWidget->setSpan(21,0,1,2);

    QLabel* label = new QLabel(tr("合计"));
    label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->ep15_tableWidget->setCellWidget(21,0,label);

    for(int i = 1; i < 22; i++)
    {
        ui->ep15_tableWidget->setItem(i,0,new QTableWidgetItem());
        ui->ep15_tableWidget->item(i,0)->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        ui->ep15_tableWidget->setItem(i,1,new QTableWidgetItem());
        ui->ep15_tableWidget->item(i,1)->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

        for(int j = 2; j < 8; j++)
        {
            QLabel *label = new QLabel();
            label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            ui->ep15_tableWidget->setCellWidget(i,j,label);
        }
    }

    ui->ep15_tableWidget->setCellWidget(0,0,new QLabel(tr("实验方法R<sub>i</sub>")));
    ui->ep15_tableWidget->setCellWidget(0,1,new QLabel(tr("比较方法R<sub>c</sub>")));
    ui->ep15_tableWidget->setCellWidget(0,2,new QLabel(tr("b<sub>i</sub>")));
    ui->ep15_tableWidget->setCellWidget(0,3,new QLabel(tr("b<sub>i</sub>-<span style=\"TEXT-DECORATION: overline\">b</span>")));
    ui->ep15_tableWidget->setCellWidget(0,4,new QLabel(tr("(b<sub>i</sub>-<span style=\"TEXT-DECORATION: overline\">b</span>)<sup>2</sup>")));
    ui->ep15_tableWidget->setCellWidget(0,5,new QLabel(tr("b<sub>irel</sub>")));
    ui->ep15_tableWidget->setCellWidget(0,6,new QLabel(tr("b<sub>irel</sub>-<span style=\"TEXT-DECORATION: overline\">b</span><sub>irel</sub>")));
    ui->ep15_tableWidget->setCellWidget(0,7,new QLabel(tr("(b<sub>irel</sub>-<span style=\"TEXT-DECORATION: overline\">b</span><sub>irel</sub>)<sup>2</sup>")));

    for(int i = 0; i < 8; i++)
    {
        QLabel *label = qobject_cast<QLabel*>(ui->ep15_tableWidget->cellWidget(0,i));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setFont(QFont());
        ui->ep15_tableWidget->setColumnWidth(i,160);
    }


    //初始化使用参考物质的界面
    ui->ep15_tableWidget2->horizontalHeader()->setVisible(false);
    ui->ep15_tableWidget2->verticalHeader()->setVisible(false);

    ui->ep15_tableWidget2->setColumnCount(6);
    ui->ep15_tableWidget2->setRowCount(11);

    for(int i = 0; i < 6; i++)
    {
        ui->ep15_tableWidget2->setColumnWidth(i,214);
    }

    ui->ep15_tableWidget2->setSpan(0,0,1,2);
    ui->ep15_tableWidget2->setSpan(1,0,2,1);
    ui->ep15_tableWidget2->setSpan(3,0,2,1);
    ui->ep15_tableWidget2->setSpan(5,0,2,1);
    ui->ep15_tableWidget2->setSpan(7,0,2,1);
    ui->ep15_tableWidget2->setSpan(9,0,2,1);

    //行表头
    QLabel *label1 = new QLabel(tr("项目"));
    label1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->ep15_tableWidget2->setCellWidget(0,0,label1);

    QLabel *label2 = new QLabel(tr("测量结果"));
    label2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->ep15_tableWidget2->setCellWidget(0,2,label2);

    QLabel *label3 = new QLabel("x<sub>i</sub>-<span style=\"TEXT-DECORATION: overline\">x</span>");
    label3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->ep15_tableWidget2->setCellWidget(0,3,label3);


    QLabel *label4 = new QLabel(tr("(x<sub>i</sub>-<span style=\"TEXT-DECORATION: overline\">x</span>)<sup>2</sup>"));
    label4->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->ep15_tableWidget2->setCellWidget(0,4,label4);

    QLabel *label5 = new QLabel(tr("日期/操作者"));
    label5->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->ep15_tableWidget2->setCellWidget(0,5,label5);

    QStringList listHead,list;
    listHead << tr("第一批") << tr("第二批") << tr("第三批") << tr("第四批") << tr("第五批");
    list << tr("第一次（x<sub>1</sub>）") << tr("第二次（x<sub>2</sub>）") << tr("第一次（x<sub>3</sub>）")
         << tr("第二次（x<sub>4</sub>）") << tr("第一次（x<sub>5</sub>）") << tr("第二次（x<sub>6</sub>）")
         << tr("第一次（x<sub>7</sub>）") << tr("第二次（x<sub>8</sub>）") << tr("第一次（x<sub>9</sub>）")
         << tr("第二次（x<sub>10</sub>）");

    int count = 0;
    //列表头
    for(int i = 1; i <= 10; i++)
    {
        QLabel *label = new QLabel(list.at(i-1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->ep15_tableWidget2->setCellWidget(i,1,label);

        if(i%2 == 1)
        {
            QLabel *rowLabel1 = new QLabel(listHead.at(count));
            rowLabel1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->ep15_tableWidget2->setCellWidget(i,0,rowLabel1);
            count++;
        }
        for(int j = 2; j <= 5; j++)
        {
            ui->ep15_tableWidget2->setItem(i,j,new QTableWidgetItem());
            ui->ep15_tableWidget2->item(i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }

    show_reference_samples();//显示示例
    show_patient_samples();
}

void Pv_Accruacy::show_patient_samples()
{
    QStringList list0,list1;

    list0 << tr("1") << tr("22") << tr("44") << tr("66") <<tr("88")  << tr("101") <<tr("123")  << tr("145") <<tr("167")  <<tr("182")  <<tr("196")  << tr("221") << tr("243") << tr("265") << tr("277") << tr("298") << tr("324") << tr("343") << tr("358") << tr("378");
    list1 << tr("1") << tr("20") << tr("40") << tr("60") << tr("80") << tr("100")<< tr("120") << tr("140") << tr("160") << tr("180") << tr("200") << tr("220") << tr("240") << tr("260") << tr("280") << tr("300") << tr("320") << tr("340") << tr("360") << tr("380");
    for(int i = 1; i <= 20; i++)
    {
        ui->ep15_tableWidget->item(i,0)->setText(list0.at(i-1));
        ui->ep15_tableWidget->item(i,1)->setText(list1.at(i-1));
    }
}

void Pv_Accruacy::show_reference_samples()
{
    for(int i = 0; i < 10; i++)
    {
        ui->ep15_tableWidget2->item(i+1,2)->setText(QString::number(Random(150,200)));
    }
}

Pv_Accruacy::~Pv_Accruacy()
{
    delete ui;
    delete lineEdit;
    delete listWidget;
    delete excursionChart;
    delete browser;
}

void Pv_Accruacy::on_ep9_BtnPlot_clicked()
{
    Pv_AccuracyPlot *window = new Pv_AccuracyPlot(this);
    window->showMaximized();
}

void Pv_Accruacy::on_ep15_BtnCommit_clicked()
{
    bool fNull = false;
    for(int i = 1; i <= 20; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if( ui->ep15_tableWidget->item(i,j)->text().isNull() )
                fNull = true;
        }
    }
    if( fNull )
    {

    }
    else
    {
        data_Map mData;
        for(int i = 1; i <= 20; i++)
        {
            mData[i]["Ri"] = ui->ep15_tableWidget->item(i,0)->text().toDouble();
            mData[i]["Rc"] = ui->ep15_tableWidget->item(i,1)->text().toDouble();
        }

        accruacyPatient.Set(mData);
        accruacyPatient.GetBi();
        accruacyPatient.GetBirel();

        for(int i = 1; i <= 20; i++)
        {
            QLabel *label = qobject_cast<QLabel*>(ui->ep15_tableWidget->cellWidget(i,2));
            label->setText(QString::number(accruacyPatient.mBi[i],'f',2));

            QLabel *label1 = qobject_cast<QLabel*>(ui->ep15_tableWidget->cellWidget(i,3));
            label1->setText(QString::number(label->text().toDouble()-accruacyPatient.averageBi,'f',2));

            QLabel *label2 = qobject_cast<QLabel*>(ui->ep15_tableWidget->cellWidget(i,4));
            label2->setText(QString::number(label1->text().toDouble() * label1->text().toDouble(),'f',2));

            //
            QLabel *label3 = qobject_cast<QLabel*>(ui->ep15_tableWidget->cellWidget(i,5));
            label3->setText(QString::number(accruacyPatient.mBirel[i],'f',2));

            QLabel *label4 = qobject_cast<QLabel*>(ui->ep15_tableWidget->cellWidget(i,6));
            label4->setText(QString::number(label3->text().toDouble()-accruacyPatient.averageBirel,'f',2));

            QLabel *label5 = qobject_cast<QLabel*>(ui->ep15_tableWidget->cellWidget(i,7));
            label5->setText(QString::number(label4->text().toDouble() * label4->text().toDouble(),'f',2));



        }
    }
}

void Pv_Accruacy::on_ep15_BtnCommit_2_clicked()
{
    bool fNull = false;
    for(int i = 1; i <= 10; i++)
    {
        if( ui->ep15_tableWidget2->item(i,2)->text().isNull() )
            fNull = true;
    }
    if( fNull )
    {

    }
    else
    {
        QMap<int, double> dataMap;
        for(int i = 1; i <= 10; i++)
        {
            dataMap.insert(i,ui->ep15_tableWidget2->item(i,2)->text().toDouble());
        }
        Accruacy_ReferenceMaterial accruacy;
        float average = GetAverage(dataMap);
        for(int i = 1; i <= 10; i++)
        {
            ui->ep15_tableWidget2->item(i,3)->setText(QString::number(ui->ep15_tableWidget2->item(i,2)->text().toFloat() - average));
            ui->ep15_tableWidget2->item(i,4)->setText(QString::number(ui->ep15_tableWidget2->item(i,3)->text().toFloat() * ui->ep15_tableWidget2->item(i,3)->text().toFloat()));
        }
    }
}

void Pv_Accruacy::on_ep15_BtnExcursionChart_clicked()
{
    QVector< Axis<double> > axisVec;
    for(int i = 1; i <= 20; i++)//获取表中的数据，为绘制坐标图准备
    {
        Axis<double> axis;
        double x = ui->ep15_tableWidget->item(i,1)->text().toDouble();
        QLabel *label = qobject_cast<QLabel*>(ui->ep15_tableWidget->cellWidget(i,2));
        double y = label->text().toDouble();
        axis.set(x,y);
        axisVec.push_back(axis);
    }

    if(Pv_ExcursionChart::isOpen)
    {
        excursionChart->setVisible(false);
    }
    excursionChart = new Pv_ExcursionChart();
    excursionChart->Set(accruacyPatient.averageBi,axisVec);
    excursionChart->show();
}

void Pv_Accruacy::on_ep15_BtnPrint_clicked()
{

//    QPrinter printer(QPrinter::HighResolution);//初始化打印机，设置为高分辨率
//    QPrintDialog printDlg(this);
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("printer.pdf");

    QFile file(".//Precision_Ep5_Report_Template.htm");
    if(!file.open(QIODevice::ReadOnly))
    {

    }
    QString html;
    QTextStream in(&file);
    html = in.readAll();
    file.close();
    html.replace("#date#",QDateTime::currentDateTime().toString());
    QTextDocument doc;
    doc.setHtml(html);
    doc.print(&printer);
    QTextBlock it = doc.end();
}

void Pv_Accruacy::on_ep9_BtnExperimentalRequirements_clicked()
{
    QString filename = ".//doc//Accruacy_Ep9.htm";
    showExperimentalRequirements(filename);
}

void Pv_Accruacy::on_ep15_BtnExperimentalRequirements_clicked()
{
    QString filename = ".//doc//Accruacy_Ep15_Patient.htm";
    showExperimentalRequirements(filename);
}

void Pv_Accruacy::on_ep15_BtnExperimentalRequirements_2_clicked()
{
    QString filename = ".//doc//Accruacy_Ep15_Reference.htm";
    showExperimentalRequirements(filename);
}

void Pv_Accruacy::on_ep9_InstrumentX_textChanged()
{
    lineEdit = ui->ep9_InstrumentX;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

//    DeviceService deviceServer;
//    QVector<Device> d = deviceServer.GetAll("", "", "",0);
//    for(int i = 0; i < d.count(); i++)
//    {
//        QListWidgetItem *it;it = new QListWidgetItem();
//        it->setText(d[i].DeviceName);
//        it->setToolTip(d[i].DeviceName);
//        listWidget->addItem(it);
//    }
    listWidget->setVisible(true);
}

void Pv_Accruacy::on_ep9_InstrumentY_textChanged()
{
    lineEdit = ui->ep9_InstrumentY;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

//    DeviceService deviceServer;
//    QVector<Device> d = deviceServer.GetAll("", "", "",0);
//    for(int i = 0; i < d.count(); i++)
//    {
//        QListWidgetItem *it;it = new QListWidgetItem();
//        it->setText(d[i].DeviceName);
//        it->setToolTip(d[i].DeviceName);
//        listWidget->addItem(it);
//    }
    listWidget->setVisible(true);
}

void Pv_Accruacy::on_ep9_XMethod_textChanged()
{

}

void Pv_Accruacy::on_ep9_YMethod_textChanged()
{

}

void Pv_Accruacy::on_ep15_Device_textChanged()
{

}

void Pv_Accruacy::on_ep15_analysisProgram_textChanged()
{

}

void Pv_Accruacy::on_ep15_ReagenBatch_textChanged(const QString &arg1)
{
//    lineEdit = ui->ep15_InstrumentX;
//    if(listWidget != NULL)
//    {
//        listWidget->setVisible(false);
//    }
//    listWidget = new QListWidget(this);
//    listWidget->setGeometry(lineEdit->geometry().x()+22,lineEdit->geometry().y()+87,lineEdit->geometry().width(),120);
//    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
//    listWidget->clear();

//    DeviceService deviceServer;
//    QVector<Device> d = deviceServer.GetAll("", "", "",0);
//    for(int i = 0; i < d.count(); i++)
//    {
//        QListWidgetItem *it;it = new QListWidgetItem();
//        it->setText(d[i].DeviceName);
//        it->setToolTip(d[i].DeviceName);
//        listWidget->addItem(it);
//    }
//    listWidget->setVisible(true);
}

void Pv_Accruacy::on_ep15_CalibratorBatch_textChanged()
{
//    lineEdit = ui->ep15_InstrumentY;
//    if(listWidget != NULL)
//    {
//        listWidget->setVisible(false);
//    }
//    listWidget = new QListWidget(this);
//    listWidget->setGeometry(lineEdit->geometry().x()+22,lineEdit->geometry().y()+87,lineEdit->geometry().width(),120);
//    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
//    listWidget->clear();

//    DeviceService deviceServer;
//    QVector<Device> d = deviceServer.GetAll("", "", "",0);
//    for(int i = 0; i < d.count(); i++)
//    {
//        QListWidgetItem *it;it = new QListWidgetItem();
//        it->setText(d[i].DeviceName);
//        it->setToolTip(d[i].DeviceName);
//        listWidget->addItem(it);
//    }
    listWidget->setVisible(true);
}

void Pv_Accruacy::on_ep15_Device_2_textChanged()
{

}

void Pv_Accruacy::on_ep15_analysisProgram_2_textChanged()
{

}

void Pv_Accruacy::on_ep15_ReagenBatch_2_textChanged()
{
    lineEdit = ui->ep15_ReagenBatch_2;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+22,lineEdit->geometry().y()+87,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

//    DeviceService deviceServer;
//    QVector<Device> d = deviceServer.GetAll("", "", "",0);
//    for(int i = 0; i < d.count(); i++)
//    {
//        QListWidgetItem *it;it = new QListWidgetItem();
//        it->setText(d[i].DeviceName);
//        it->setToolTip(d[i].DeviceName);
//        listWidget->addItem(it);
//    }
    listWidget->setVisible(true);
}

void Pv_Accruacy::on_ep15_CalibratorBatch_2_textChanged()
{

}

void Pv_Accruacy::on_ep15_Concentration_2_textChanged()
{

}

void Pv_Accruacy::showExperimentalRequirements(QString &filename)
{
    if(browser != NULL)
    {
        browser->setVisible(false);
        browser = NULL;
    }

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {

    }
    QTextStream in(&file);
    QString html = in.readAll();
    file.close();
    browser = new Pv_TextBrowser;
    browser->setHtml(html);
    browser->show();
}

void Pv_Accruacy::keyPressEvent(QKeyEvent *keyevent)
{
    if(keyevent->key() == Qt::Key_Escape)
    {
        if(listWidget != NULL)
        {
            listWidget->setVisible(false);
        }
    }

    if((listWidget == NULL || listWidget->count() == 0))
        return;

    int iIndex = listWidget->currentRow();
    if(keyevent->key() == Qt::Key_Up)
    {
        iIndex--;
        if(iIndex < 0) iIndex = 0;
        QListWidgetItem *pItem = listWidget->item(iIndex);
        listWidget->setCurrentItem(pItem);

    }
    else if (keyevent->key() == Qt::Key_Down)
    {
        iIndex++;
        if(iIndex >= listWidget->count()) iIndex = listWidget->count() - 1;
        QListWidgetItem *pItem = listWidget->item(iIndex);
        listWidget->setCurrentItem(pItem);
    }
    else if (keyevent->key() == Qt::Key_Enter || keyevent->key() == Qt::Key_Return)
    {
        if(listWidget != NULL)
        {
            if(listWidget->currentItem() != NULL)
            {
                QString s = listWidget->currentItem()->text();
                lineEdit->setText(s);
            }
            listWidget->setVisible(false);
        }
    }
}

void Pv_Accruacy::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}

void Pv_Accruacy::mousePressEvent(QMouseEvent *event)
{
    if(listWidget != NULL && event->button() == Qt::LeftButton)
    {
        listWidget->setVisible(false);
    }
}
