#include "Pv_Precision.h"
#include "ui_Pv_Precision.h"
#include <QVector>
#include <QHeaderView>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopWidget>
#include <QToolTip>
#include "MainWindow.h"

//Service
#include "DeviceService.h"
#include "ReagentBatchService.h"
#include "MaterialBatchService.h"
#include "MaterialService.h"
#include "TestTypeService.h"

#include <QFile>
#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <math.h>

#include "Common/Round.h"
#include "Pv_TextBrowser.h"

#include <QPrinter>
#include <QPagedPaintDevice>
#include <QTextBlock>
#include <QFileDialog>

#include "ChiSquare.h"

#include "UI/ShowToolTip.h"
#include "UI/TipBox.h"
#include "QRegExp"

#include "UI/PV/cmsgToolTip.h"

Pv_Precision::Pv_Precision(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pv_Precision)
{
    ui->setupUi(this);   
    double T = GetChiSquare(27.4,1);
    Init();
}

void Pv_Precision::Init()
{
    setWindowTitle(tr("精密度验证"));

    listWidget = NULL;
    lineEdit = NULL;
    browser = NULL;
    count = 0;
    timeId = 0;
    page = 0;
    ep5Html = "";
    westgardHtml = "";
    ep15Html = "";
    defaultStyle = "QLineEdit{border-width:1px;border-style:inherit;border-color:white;background-color:rgb(246, 250, 250);}"
                    " QLineEdit:hover{background-color:white;color:black}";
    warningStyle = "QLineEdit{border-width: 1px;border-style: solid;border-color: rgb(255, 0, 0);background-color:rgb(246, 250, 250);}"
                   " QLineEdit:hover{background-color:white;color:white}";
    dateEditStyle = "QDateEdit{border-width:1px;border-style:inherit;border-color:white;background-color:rgb(246, 250, 250);}"
                    "QLineEdit:hover{background-color:white;color:black}";
    setStyle("All",defaultStyle,dateEditStyle,true);

    ui->ep5_date->setDate(QDate::currentDate());
    ui->ep5_CalculateDate->setDate(QDate::currentDate());
    ui->ep5_approvalDate->setDate(QDate::currentDate());

    ui->Westgard_date->setDate(QDate::currentDate());
    ui->Westgard_CalculateDate->setDate(QDate::currentDate());
    ui->Westgard_ApprovalDate->setDate(QDate::currentDate());

    ui->ep15_date->setDate(QDate::currentDate());
    ui->ep15_CalculateDate->setDate(QDate::currentDate());
    ui->ep15_ApprovalDate->setDate(QDate::currentDate());


    ui->ep5_LevelComboBox->addItem(tr("L1"));
    ui->ep5_LevelComboBox->addItem(tr("L2"));
    ui->ep5_LevelComboBox->addItem(tr("L3"));

    showEp5();
    showEp15();
    showWestgard();

    on_ep5_L2_clicked();
    on_Westgard_L2_clicked();
    on_ep15_L2_clicked();

    westgardLevel = TWO;

    //显示示例
    show_ep5_samples();
    show_ep15_samples();
    show_westgard_samples();



//    setFixedSize(QApplication::desktop()->width(),QApplication::desktop()->height());//设置固定大小
    connect(ui->ep5_LevelComboBox,SIGNAL(currentIndexChanged(int)),
            ui->ep5_StackedWidget,SLOT(setCurrentIndex(int)));
    connect(ui->ep5_tableWidget,SIGNAL(itemPressed(QTableWidgetItem*)),
            this,SLOT(SlotItemClicked(QTableWidgetItem*)));
    connect(ui->ep5_StackedWidget,SIGNAL(currentChanged(int)),
            ui->ep5_LevelComboBox,SLOT(setCurrentIndex(int)));
}

void Pv_Precision::show_ep5_samples()
{
    //第一张表
    for(int i = 1; i <= 20; i++)
    {
        for(int j = 2; j <= 5; j++)
        {
            ui->ep5_tableWidget->item(i,j)->setText(QString::number(Random(230,250)));
        }
    }

    //第二张表
    for(int i = 1; i <= 20; i++)
    {
        for(int j = 2; j <= 5; j++)
        {
            ui->ep5_tableWidget_2->item(i,j)->setText(QString::number(Random(230,250)));
        }
    }

    //第三张表
    for(int i = 1; i <= 20; i++)
    {
        for(int j = 2; j <= 5; j++)
        {
            ui->ep5_tableWidget_3->item(i,j)->setText(QString::number(Random(230,250)));
        }
    }
}

void Pv_Precision::show_westgard_samples()
{
    int column = 0;
    if(westgardLevel == TWO)
    {
        column = 4;
    }
    else if(westgardLevel == THREE)
    {
        column = 5;
    }

    for(int i = 2; i <=21; i++)
    {
        for(int j = 2; j <= column-1; j++)
        {
            ui->Westgard_tableWidget->item(i,j)->setText(QString::number(Random(220,270)));
            ui->Westgard_tableWidget->item(i,j+column)->setText(QString::number(Random(220,270)));
        }
    }
}

void Pv_Precision::show_ep15_samples()
{

    if(ep15Level == TWO)
    {
        for(int i = 2; i <= 4; i++)
        {
            for(int j = 2; j <=6; j++)
            {
                ui->ep15_tableWidget->item(i,j)->setText(QString::number(Random(220,270)));
                ui->ep15_tableWidget->item(i+4,j)->setText(QString::number(Random(220,270)));
            }
        }

    }

    else if(ep15Level == THREE)
    {
        for(int i = 2; i <= 4; i++)
        {
            for(int j = 2; j <=6; j++)
            {
                ui->ep15_tableWidget->item(i,j)->setText(QString::number(Random(220,270)));
                ui->ep15_tableWidget->item(i+4,j)->setText(QString::number(Random(220,270)));
                   ui->ep15_tableWidget->item(i+8,j)->setText(QString::number(Random(220,270)));
            }
        }
    }

}


void Pv_Precision::showEp5()
{
    showEp5Table(ui->ep5_tableWidget);
    showEp5Table(ui->ep5_tableWidget_2);
    showEp5Table(ui->ep5_tableWidget_3);
}

void Pv_Precision::showEp5Table(QTableWidget *widget)
{
    widget->setColumnCount(8);
    widget->setRowCount(21);

    widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //隐藏头表
    widget->verticalHeader()->setVisible(false);
    widget->horizontalHeader()->setVisible(false);
    //合并单元格
    widget->setSpan(0,2,1,2);
    widget->setSpan(0,4,1,2);
    widget->setSpan(0,10,1,2);
    widget->setSpan(0,12,1,2);

    for(int row = 0; row < 21; row++)
    {
        for(int column = 0; column < 8; column++ )
        {
            widget->setItem(row,column,new QTableWidgetItem());
            widget->item(row,column)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }

    //添加列表头
    QStringList list;
    list << tr("天数") << tr("日期") << tr("运行1结果") << tr("") << tr("运行2结果") << tr("") << tr("运行1平均值") << tr("运行2平均值");
    QString str;
    for(int i = 0; i < 8; i++)
    {
        widget->setColumnWidth(i,162);//设置列宽

        if( i == 3 || i == 5 )
            continue;
        str = list.at(i);
        QLabel *label = new QLabel(str);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        widget->setCellWidget(0,i,label);
    }

    //添加行表头
    for(int i = 1; i <= 20; i++)
    {
        QLabel *label = new QLabel(QString::number(i));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        widget->setCellWidget(i,0,label);

        widget->setCellWidget(i,1,new QLabel());
        widget->setCellWidget(i,6,new QLabel());
        widget->setCellWidget(i,7,new QLabel());

        widget->setRowHeight(i,29);//设置行高
    }
}

void Pv_Precision::showEp15()
{
    ui->ep15_tableWidget->setColumnCount(7);
    ui->ep15_tableWidget->setRowCount(9);

    ui->ep15_tableWidget->horizontalHeader()->setVisible(false);
    ui->ep15_tableWidget->verticalHeader()->setVisible(false);

    ui->ep15_tableWidget->setSpan(1,0,4,1);
    ui->ep15_tableWidget->setSpan(5,0,4,1);
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            ui->ep15_tableWidget->setItem(i,j,new QTableWidgetItem());
            ui->ep15_tableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }

    QStringList rowList,columnList;
    columnList << tr("浓度水平") << tr("项目") << tr("第1批") << tr("第2批") << tr("第3批") << tr("第4批") << tr("第5批");

    rowList << tr("日期/操作人员")
               << tr("第一次测量结果：x1") << tr("第二次测量结果:x2") << tr("第三次测量结果:x3");

    QLabel *LevelLabel = new QLabel(tr("L1"));
    LevelLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->ep15_tableWidget->setCellWidget(1,0,LevelLabel);

    LevelLabel = new QLabel(tr("L2"));
    LevelLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->ep15_tableWidget->setCellWidget(5,0,LevelLabel);

    for(int i = 0; i < 4; i++)
    {
        QLabel *label = new QLabel(rowList.at(i));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->ep15_tableWidget->setCellWidget(i+1,1,label);

        label = new QLabel(rowList.at(i));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->ep15_tableWidget->setCellWidget(i+5,1,label);

    }
    for(int i = 0; i < 7; i++)
    {
        QLabel *label = new QLabel(columnList.at(i));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->ep15_tableWidget->setCellWidget(0,i,label);

        ui->ep15_tableWidget->setColumnWidth(i,185);    //设置列宽
    }
    ui->ep15_tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->ep15_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Pv_Precision::showWestgard()
{
    ui->Westgard_tableWidget->setColumnCount(8);
    ui->Westgard_tableWidget->setRowCount(22);

    ui->Westgard_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Westgard_tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //隐藏头表
    ui->Westgard_tableWidget->verticalHeader()->setVisible(false);
    ui->Westgard_tableWidget->horizontalHeader()->setVisible(false);
    //合并单元格
    ui->Westgard_tableWidget->setSpan(0,0,1,4);
    ui->Westgard_tableWidget->setSpan(0,4,1,4);


    for(int row = 2; row < 22; row++)
    {
        for(int column = 0; column < 8; column++ )
        {
            ui->Westgard_tableWidget->setItem(row,column,new QTableWidgetItem());
            ui->Westgard_tableWidget->item(row,column)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }

    QStringList list;
    list << tr("次数") << tr("日期") << tr("质控水平1") << tr("质控水平2")
         << tr("天数") << tr("日期") << tr("质控水平1") << tr("质控水平2");
    int count = 0;
    QLabel *label = new QLabel("批内");
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->Westgard_tableWidget->setCellWidget(0,0,label);
    label = new QLabel("批间");
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->Westgard_tableWidget->setCellWidget(0,4,label);
    for(int i = 0; i < 8; i++)
    {
        QLabel *label = new QLabel(list.at(i));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->Westgard_tableWidget->setCellWidget(1,i,label);

        ui->Westgard_tableWidget->setColumnWidth(i,162);//设置列宽
        ui->Westgard_tableWidget->setColumnWidth(i+4,162);

    }

    //添加列表头
    for(int i = 1; i <= 20; i++)
    {
        //天数和次数
        QLabel *label = new QLabel(QString::number(i));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->Westgard_tableWidget->setCellWidget(i+1,0,label);

        label = new QLabel(QString::number(i));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->Westgard_tableWidget->setCellWidget(i+1,4,label);

        //日期
        label = new QLabel;
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->Westgard_tableWidget->setCellWidget(i+1,1,label);

        label = new QLabel;
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->Westgard_tableWidget->setCellWidget(i+1,5,label);
    }
}

void Pv_Precision::getOutliersIndex(QMap< int, QMap<QString,QString> > level1Map, QMap< int, QMap<QString,QString> > level2Map,QVector< Axis<int> > &vec)
{
    vec.clear();
    Axis<int> index;
    for(int i = 1; i <= 20; i++)
    {
        if(level1Map.contains(i))
        {
            if( level1Map[i].contains("Result1") )
            {
                index.set(i,2);
                vec.push_back(index);
            }
            if(  level1Map[i].contains("Result2")  )
            {

                index.set(i,3);
                vec.push_back(index);
            }
        }


        if(level2Map.contains(i))
        {
            if( level2Map[i].contains("Result1") )
            {

                index.set(i,4);
                vec.push_back(index);
            }
            if( level2Map[i].contains("Result2") )
            {

                index.set(i,5);
                vec.push_back(index);
            }
        }
    }
}

QString Pv_Precision::toString(double val)
{
    return (val==0)?tr(""):QString::number(val);
}

QString Pv_Precision::GenerateReport(TYPE type)
{
    QString html;
    switch (type) {
    case EP5:
        html = GenerateEp5Html();
        break;
    case EP15:
        html = GenerateEp15Html();
        break;
    case WESTGARD:
        html = GenerateEpWeatgardHtml();
        break;
    default:
        break;
    }
    return html;
}

QString Pv_Precision::readFile(QString &filename)
{
    QString html;
    QFile file(filename);
    if( !file.open(QIODevice::ReadOnly) )
    {
//        QMessageBox msg;
//        msg.setText(tr("文件丢失"));
//        msg.exec();
    }
    QTextStream in(&file);
    html = in.readAll();
    file.close();
    return html;
}

QString Pv_Precision::htmlString(QString replaceStr, int length)
{
    QString str;
    int len = replaceStr.length();
    str = QString("<span lang=EN-US"
            " style=\'font-size:14.0pt;font-family:宋体;mso-ascii-theme-font:minor-fareast;"
            " mso-fareast-theme-font:minor-fareast;mso-hansi-theme-font:minor-fareast;"
            " mso-bidi-font-family:Arial\'>%1<\/span> "
                  ).arg(replaceStr);
    if(length <= len)
    {
        return str;
    }

    QString spaceStr = " <span lang=EN-US style=\'font-size:12.0pt;font-family:\"Arial\",\"sans-serif\"\'><span style='mso-spacerun:yes'></span></span> ";
    for(int i = 0; i < length-len; i++)
    {
        spaceStr.insert(spaceStr.indexOf("yes'>")+5,"&nbsp;");
    }
    return str+spaceStr;

}

Pv_Precision::~Pv_Precision()
{
    delete ui;
    delete listWidget;
    delete lineEdit;
    delete browser;
}

void Pv_Precision::on_ep5_BtnExperimentalRequirements_clicked()
{
    QString filename(".//doc//Precision_Ep5.htm");
    showExperimentalRequirements(filename);
}

void Pv_Precision::on_ep5_BtnCommit_clicked()
{

    bool fPass = check(tr("ep5"),tr("Calculate")) && Check_EP5_tables(ep5Level);
    if(fPass)
    {
        if(ep5Level == TWO)
        {
            Commit_Ep5_Table1();
            Commit_Ep5_Table2();
        }
        else if(ep5Level == THREE)
        {
            Commit_Ep5_Table1();
            Commit_Ep5_Table2();
            Commit_Ep5_Table3();
        }
        ep5Html = GenerateReport(Pv_Precision::EP5);
    }
}

void Pv_Precision::on_ep5_BtnOutputReport_clicked()
{
    if(ep5Html.isEmpty())
    {
        QMessageBox msg;
        msg.setText(tr("您尚未提交数据，请提交数据后再次尝试"));
        msg.exec();
    }
    else
    {
        QFileDialog dialog;
        QString filename = dialog.getSaveFileName(this,
                                                  tr("输出报告"), "./", tr("PDF Files (*.pdf);;Mirrosoft Word 文档 (*.doc, *.docx)"));
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filename);

        QTextDocument doc;
        doc.setHtml(ep5Html);
        doc.print(&printer);
        QTextBlock it = doc.end();
    }
}

void Pv_Precision::on_ep5_L2_clicked()
{
    ep5Level = TWO;
    setStyle("ep5",defaultStyle,dateEditStyle);
//    ui->ep5_L1_Label->setVisible(true);
//    ui->ep5_L1_LineEdit->setVisible(true);
//    ui->ep5_L2_Label->setVisible(true);
//    ui->ep5_L2_LineEdit->setVisible(true);
//    ui->ep5_L3_Label->setVisible(false);
//    ui->ep5_L3_LineEdit->setVisible(false);
    ui->ep5_LevelComboBox->setVisible(true);
    if(ui->ep5_LevelComboBox->count() == 3)
    {
        ui->ep5_LevelComboBox->removeItem(2);
    }
    ui->ep5_StackedWidget->setCurrentIndex(0);
    ui->ep5_LevelComboBox->setCurrentIndex(0);

    //预期
    ui->ep5_Cv_Except_Label_L1->setVisible(true);
    ui->ep5_Iner_Cv_Expect_L1->setVisible(true);
    ui->ep5_Cv_Expect_L1->setVisible(true);

    ui->ep5_Cv_Except_Label_L2->setVisible(true);
    ui->ep5_Iner_Cv_Expect_L2->setVisible(true);
    ui->ep5_Cv_Expect_L2->setVisible(true);

    ui->ep5_Cv_Except_Label_L3->setVisible(false);
    ui->ep5_Iner_Cv_Expect_L3->setVisible(false);
    ui->ep5_Cv_Expect_L3->setVisible(false);

    //计算
    ui->ep5_CV_Calculate_Label_L1->setVisible(true);
    ui->ep5_Iner_Cv_Calculate_L1->setVisible(true);
    ui->ep5_Cv_Calculate_L1->setVisible(true);

    ui->ep5_CV_Calculate_Label_L2->setVisible(true);
    ui->ep5_Iner_Cv_Calculate_L2->setVisible(true);
    ui->ep5_Cv_Calculate_L2->setVisible(true);

    ui->ep5_CV_Calculate_Label_L3->setVisible(false);
    ui->ep5_Iner_Cv_Calculate_L3->setVisible(false);
    ui->ep5_Cv_Calculate_L3->setVisible(false);

}

void Pv_Precision::on_ep5_L3_clicked()
{
    ep5Level = THREE;
    setStyle("ep5",defaultStyle,dateEditStyle);
//    ui->ep5_L1_Label->setVisible(true);
//    ui->ep5_L1_LineEdit->setVisible(true);
//    ui->ep5_L3_Label->setVisible(true);
//    ui->ep5_L3_LineEdit->setVisible(true);
//    ui->ep5_L2_Label->setVisible(true);
//    ui->ep5_L2_LineEdit->setVisible(true);

    if(ui->ep5_LevelComboBox->count() == 2)
    {
        ui->ep5_LevelComboBox->addItem(tr("L3"));
    }
    ui->ep5_StackedWidget->setCurrentIndex(0);
    ui->ep5_LevelComboBox->setCurrentIndex(0);
    ui->ep5_LevelComboBox->setVisible(true);

    //预期
    ui->ep5_Cv_Except_Label_L1->setVisible(true);
    ui->ep5_Iner_Cv_Expect_L1->setVisible(true);
    ui->ep5_Cv_Expect_L1->setVisible(true);

    ui->ep5_Cv_Except_Label_L2->setVisible(true);
    ui->ep5_Iner_Cv_Expect_L2->setVisible(true);
    ui->ep5_Cv_Expect_L2->setVisible(true);

    ui->ep5_Cv_Except_Label_L3->setVisible(true);
    ui->ep5_Iner_Cv_Expect_L3->setVisible(true);
    ui->ep5_Cv_Expect_L3->setVisible(true);

    //计算
    ui->ep5_CV_Calculate_Label_L1->setVisible(true);
    ui->ep5_Iner_Cv_Calculate_L1->setVisible(true);
    ui->ep5_Cv_Calculate_L1->setVisible(true);

    ui->ep5_CV_Calculate_Label_L2->setVisible(true);
    ui->ep5_Iner_Cv_Calculate_L2->setVisible(true);
    ui->ep5_Cv_Calculate_L2->setVisible(true);

    ui->ep5_CV_Calculate_Label_L3->setVisible(true);
    ui->ep5_Iner_Cv_Calculate_L3->setVisible(true);
    ui->ep5_Cv_Calculate_L3->setVisible(true);

}

void Pv_Precision::on_Westgard_BtnExperimentalRequirements_clicked()
{
    QString filename = ".//doc//Precision_Westgard.htm";
    showExperimentalRequirements(filename);
}

void Pv_Precision::on_Westgard_BtnCommit_clicked()
{
    bool fPass = true;
    int column = 0;
    if(westgardLevel == TWO)
    {
        column = 4;
    }
    else if(westgardLevel == THREE)
    {
        column = 5;
    }
    for(int i = 2; i < 22; i++)
    {
        for(int j = 2; j <= column-1; j++)
        {
            if( ui->Westgard_tableWidget->item(i,j)->text().isEmpty() )
            {
                fPass = false;
            }
        }
    }

    indexMap mMap1;//批内
    indexMap mMap2;//批间

    fPass = check(tr("Westgard"),tr("Calculate")) && fPass;

    if(!fPass)
    {

    }
    else
    {
        if(westgardLevel == TWO)
        {
            for(int i = 1; i <= 20; i++)
            {
                mMap1[i][tr("L1")] = ui->Westgard_tableWidget->item(i+1,2)->text().toDouble();
                mMap1[i][tr("L2")] = ui->Westgard_tableWidget->item(i+1,3)->text().toDouble();

                mMap2[i][tr("L1")] = ui->Westgard_tableWidget->item(i+1,6)->text().toDouble();
                mMap2[i][tr("L2")] = ui->Westgard_tableWidget->item(i+1,7)->text().toDouble();
            }
        }
        else if(westgardLevel == THREE)
        {
            for(int i = 1; i <= 20; i++)
            {
                mMap1[i][tr("L1")] = ui->Westgard_tableWidget->item(i+1,2)->text().toDouble();
                mMap1[i][tr("L2")] = ui->Westgard_tableWidget->item(i+1,3)->text().toDouble();
                mMap1[i][tr("L3")] = ui->Westgard_tableWidget->item(i+1,4)->text().toDouble();

                mMap2[i][tr("L1")] = ui->Westgard_tableWidget->item(i+1,7)->text().toDouble();
                mMap2[i][tr("L2")] = ui->Westgard_tableWidget->item(i+1,8)->text().toDouble();
                mMap2[i][tr("L3")] = ui->Westgard_tableWidget->item(i+1,9)->text().toDouble();
            }
        }
        westgardInbatch.Set(mMap1);
        westgardBatchs.Set(mMap2);

        if(westgardLevel == TWO)
        {
            //批内
            ui->Westgard_Calculate_L1_Iner_Cv->setText(QString::number(westgardInbatch.GetSr(PrecisionWestgard::L1),'f',2) + "%");
            ui->Westgard_Calculate_L2_Iner_Cv->setText(QString::number(westgardInbatch.GetSr(PrecisionWestgard::L2),'f',2) + "%");

            //批间
            ui->Westgard_Calculate_L1_Cv->setText(QString::number(westgardBatchs.GetSr(PrecisionWestgard::L1),'f',2) + "%");
            ui->Westgard_Calculate_L2_Cv->setText(QString::number(westgardBatchs.GetSr(PrecisionWestgard::L2),'f',2) + "%");
        }
        else if(westgardLevel == THREE)
        {
            //批内
            ui->Westgard_Calculate_L1_Iner_Cv->setText(QString::number(westgardInbatch.GetSr(PrecisionWestgard::L1),'f',2) + "%");
            ui->Westgard_Calculate_L2_Iner_Cv->setText(QString::number(westgardInbatch.GetSr(PrecisionWestgard::L2),'f',2) + "%");
            ui->Westgard_Calculate_L3_Iner_Cv->setText(QString::number(westgardInbatch.GetSr(PrecisionWestgard::L3),'f',2) + "%");

            //批间
            ui->Westgard_Calculate_L1_Cv->setText(QString::number(westgardBatchs.GetSr(PrecisionWestgard::L1),'f',2) + "%");
            ui->Westgard_Calculate_L2_Cv->setText(QString::number(westgardBatchs.GetSr(PrecisionWestgard::L2),'f',2) + "%");
            ui->Westgard_Calculate_L3_Cv->setText(QString::number(westgardBatchs.GetSr(PrecisionWestgard::L3),'f',2) + "%");
        }

        westgardHtml = GenerateReport(Pv_Precision::WESTGARD);
    }
}

void Pv_Precision::on_Westgard_BtnOutputReport_clicked()
{
    if(westgardHtml.isEmpty())
    {
        QMessageBox msg;
        msg.setText(tr("您尚未提交数据，请提交数据后再次尝试"));
        msg.exec();
    }
    else
    {
        QFileDialog dialog;
        QString filename = dialog.getSaveFileName(this,
                                                  tr("输出报告"), "./", tr("PDF Files (*.pdf);;Mirrosoft Word 文档 (*.doc, *.docx)"));
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filename);

        QTextDocument doc;
        doc.setHtml(westgardHtml);
        doc.print(&printer);
        QTextBlock it = doc.end();
    }
}

void Pv_Precision::on_Westgard_L2_clicked()
{
    if(westgardLevel == THREE)
    {
        westgardLevel = TWO;
        Westgard_RemoveColumns();
    }
    setStyle("Westgard",defaultStyle,dateEditStyle);
    ui->Westgard_ConcentrationLevel1->setVisible(true);
    ui->Westgard_ConcentrationLevel2->setVisible(true);
    ui->Westgard_ConcentrationLevel3->setVisible(false);
    ui->Westgard_L3_Label->setVisible(false);


    //预期
    ui->Westgard_Except_L1->setVisible(true);
    ui->Westgard_Except_L1_Cv->setVisible(true);
    ui->Westgard_Except_L1_Iner_Cv->setVisible(true);

    ui->Westgard_Except_L2->setVisible(true);
    ui->Westgard_Except_L2_Cv->setVisible(true);
    ui->Westgard_Except_L2_Iner_Cv->setVisible(true);

    ui->Westgard_Except_L3->setVisible(false);
    ui->Westgard_Except_L3_Cv->setVisible(false);
    ui->Westgard_Except_L3_Iner_Cv->setVisible(false);

    //计算
    ui->Westgard_Calculate_L1->setVisible(true);
    ui->Westgard_Calculate_L1_Cv->setVisible(true);
    ui->Westgard_Calculate_L1_Iner_Cv->setVisible(true);

    ui->Westgard_Calculate_L2->setVisible(true);
    ui->Westgard_Calculate_L2_Cv->setVisible(true);
    ui->Westgard_Calculate_L2_Iner_Cv->setVisible(true);

    ui->Westgard_Calculate_L3->setVisible(false);
    ui->Westgard_Calculate_L3_Cv->setVisible(false);
    ui->Westgard_Calculate_L3_Iner_Cv->setVisible(false);
}

void Pv_Precision::on_Westgard_L3_clicked()
{
    if(westgardLevel == TWO)
    {
        westgardLevel = THREE;
        Westgard_AddColumns("质控水平3");
    }
    setStyle("Westgard",defaultStyle,dateEditStyle);
    ui->Westgard_ConcentrationLevel1->setVisible(true);
    ui->Westgard_ConcentrationLevel2->setVisible(true);
    ui->Westgard_ConcentrationLevel3->setVisible(true);
    ui->Westgard_L3_Label->setVisible(true);


    //预期
    ui->Westgard_Except_L1->setVisible(true);
    ui->Westgard_Except_L1_Cv->setVisible(true);
    ui->Westgard_Except_L1_Iner_Cv->setVisible(true);

    ui->Westgard_Except_L2->setVisible(true);
    ui->Westgard_Except_L2_Cv->setVisible(true);
    ui->Westgard_Except_L2_Iner_Cv->setVisible(true);

    ui->Westgard_Except_L3->setVisible(true);
    ui->Westgard_Except_L3_Cv->setVisible(true);
    ui->Westgard_Except_L3_Iner_Cv->setVisible(true);

    //计算
    ui->Westgard_Calculate_L1->setVisible(true);
    ui->Westgard_Calculate_L1_Cv->setVisible(true);
    ui->Westgard_Calculate_L1_Iner_Cv->setVisible(true);

    ui->Westgard_Calculate_L2->setVisible(true);
    ui->Westgard_Calculate_L2_Cv->setVisible(true);
    ui->Westgard_Calculate_L2_Iner_Cv->setVisible(true);

    ui->Westgard_Calculate_L3->setVisible(true);
    ui->Westgard_Calculate_L3_Cv->setVisible(true);
    ui->Westgard_Calculate_L3_Iner_Cv->setVisible(true);
}

void Pv_Precision::on_ep15_BtnExperimentalRequirements_clicked()
{
    QString filename = ".//doc//Precision_Ep15.htm";
    showExperimentalRequirements(filename);
}

void Pv_Precision::on_ep15_BtnCommit_clicked()
{
    bool fPass = true;
    if(ep15Level == TWO)
    {
        for(int i = 2; i <= 4; i++)
        {
            for(int j = 2; j <= 6; j++)
            {
                if( ui->ep15_tableWidget->item(i,j)->text().isNull()  ||
                        ui->ep15_tableWidget->item(i+4,j)->text().isNull())

                    fPass = false;
            }
        }
    }
    else if(ep15Level == THREE)
    {
        for(int i = 2; i <= 4; i++)
        {
            for(int j = 2; j <= 6; j++)
            {
                if(     ui->ep15_tableWidget->item(i,j)->text().isNull() ||
                        ui->ep15_tableWidget->item(i+4,j)->text().isNull() ||
                        ui->ep15_tableWidget->item(i+8,j)->text().isNull() )

                    fPass = false;
            }
        }
    }

    fPass = check(tr("ep15"),tr("Calculate")) && fPass;

    if( !fPass )
    {
    }
    else
    {
        if(ep15Level == TWO)
        {
            Commit_Ep15_L1();
            Commit_Ep15_L2();
        }
        else if(ep15Level == THREE)
        {
            Commit_Ep15_L1();
            Commit_Ep15_L2();
            Commit_Ep15_L3();
        }
        ep15Html = GenerateReport(Pv_Precision::EP15);
    }

}

void Pv_Precision::on_ep15_BtnOutputReport_clicked()
{
    if(ep15Html.isEmpty())
    {
        QMessageBox msg;
        msg.setText(tr("您尚未提交数据，请提交数据后再次尝试"));
        msg.exec();
    }
    else
    {
        QFileDialog dialog;
        QString filename = dialog.getSaveFileName(this,
                                                  tr("输出报告"), "./", tr("PDF Files (*.pdf);;Mirrosoft Word 文档 (*.doc, *.docx)"));
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filename);

        QTextDocument doc;
        doc.setHtml(ep15Html);
        doc.print(&printer);
        QTextBlock it = doc.end();
    }
}

void Pv_Precision::on_ep15_L2_clicked()
{
    ep15Level = TWO;

    if(ui->ep15_tableWidget->rowCount() > 9)    //表格增加
        ep15_RemoveRows(ui->ep15_tableWidget);

    setStyle("ep15",defaultStyle,dateEditStyle);
    ui->ep15_Concentration_L1->setVisible(true);
    ui->ep15_Concentration_L2->setVisible(true);
    ui->ep15_Concentration_L3->setVisible(false);
    ui->ep15_L3_Label->setVisible(false);

    //预期
    ui->ep15_Except_L1->setVisible(true);
    ui->ep15_Except_L1_Cv->setVisible(true);
    ui->ep15_Except_L1_Iner_Cv->setVisible(true);

    ui->ep15_Except_L2->setVisible(true);
    ui->ep15_Except_L2_Cv->setVisible(true);
    ui->ep15_Except_L2_Iner_Cv->setVisible(true);

    ui->ep15_Except_L3->setVisible(false);
    ui->ep15_Except_L3_Cv->setVisible(false);
    ui->ep15_Except_L3_Iner_Cv->setVisible(false);

    //计算
    ui->ep15_Calculate_L1->setVisible(true);
    ui->ep15_Calculate_L1_Cv->setVisible(true);
    ui->ep15_Calculate_L1_Iner_Cv->setVisible(true);

    ui->ep15_Calculate_L2->setVisible(true);
    ui->ep15_Calculate_L2_Cv->setVisible(true);
    ui->ep15_Calculate_L2_Iner_Cv->setVisible(true);

    ui->ep15_Calculate_L3->setVisible(false);
    ui->ep15_Calculate_L3_Cv->setVisible(false);
    ui->ep15_Calculate_L3_Iner_Cv->setVisible(false);
}

void Pv_Precision::on_ep15_L3_clicked()
{
    ep15Level = THREE;

    if(ui->ep15_tableWidget->rowCount() <= 9)               //表格减少
        ep15_AddRows(ui->ep15_tableWidget,QString("L3"));

    setStyle("ep15",defaultStyle,dateEditStyle);
    ui->ep15_Concentration_L1->setVisible(true);
    ui->ep15_Concentration_L2->setVisible(true);
    ui->ep15_Concentration_L3->setVisible(true);
    ui->ep15_L3_Label->setVisible(true);

    //预期
    ui->ep15_Except_L1->setVisible(true);
    ui->ep15_Except_L1_Cv->setVisible(true);
    ui->ep15_Except_L1_Iner_Cv->setVisible(true);

    ui->ep15_Except_L2->setVisible(true);
    ui->ep15_Except_L2_Cv->setVisible(true);
    ui->ep15_Except_L2_Iner_Cv->setVisible(true);

    ui->ep15_Except_L3->setVisible(true);
    ui->ep15_Except_L3_Cv->setVisible(true);
    ui->ep15_Except_L3_Iner_Cv->setVisible(true);


    //计算
    ui->ep15_Calculate_L1->setVisible(true);
    ui->ep15_Calculate_L1_Cv->setVisible(true);
    ui->ep15_Calculate_L1_Iner_Cv->setVisible(true);

    ui->ep15_Calculate_L2->setVisible(true);
    ui->ep15_Calculate_L2_Cv->setVisible(true);
    ui->ep15_Calculate_L2_Iner_Cv->setVisible(true);

    ui->ep15_Calculate_L3->setVisible(true);
    ui->ep15_Calculate_L3_Cv->setVisible(true);
    ui->ep15_Calculate_L3_Iner_Cv->setVisible(true);
}

void Pv_Precision::on_ep5_instrument_textChanged(const QString str)
{
    ui->ep5_instrument->setStyleSheet(defaultStyle);
    lineEdit = ui->ep5_instrument;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    DeviceService deviceServer;
    QVector<Device> d = deviceServer.GetAll("", "", str, 0);
    for(int i = 0; i < d.count(); i++)
    {
        QListWidgetItem *it;it = new QListWidgetItem();
        it->setText(d[i].DeviceName);
        it->setToolTip(d[i].DeviceName);
        listWidget->addItem(it);
    }
    listWidget->setVisible(true);
}

void Pv_Precision::on_listWidget_clicked(const QModelIndex)
{
    if(listWidget != NULL)
    {
        if(listWidget->currentItem() != NULL)
        {
            QString s = listWidget->currentItem()->text();
            lineEdit->setFocus();
            lineEdit->setText(s);
        }
        listWidget->setVisible(false);
    }
}

void Pv_Precision::showExperimentalRequirements(QString &filename)
{
    if(browser != NULL)
    {
        browser->setVisible(false);
        browser = NULL;
    }
    QString html = readFile(filename);//得到HTML
    browser = new Pv_TextBrowser;
    browser->setHtml(html);
    browser->show();
}

void Pv_Precision::_textChanged(QString str)
{
    const QMetaObject *smeta = sender()->metaObject();
    if(QString(smeta->className()) == "QLineEdit")
    {
        QObject *obj = sender();
        QLineEdit *lineEdit = (QLineEdit*)obj;
        lineEdit->setStyleSheet(defaultStyle);
    }
}

void Pv_Precision::SlotItemClicked(QTableWidgetItem *item)
{
    if (qApp->mouseButtons() == Qt::LeftButton)
    {
        return;
    }

    if (qApp->mouseButtons() == Qt::RightButton)
    {
        ShowMenu();
    }
}

void Pv_Precision::on_ep5_sample_textChanged(const QString str)
{
    ui->ep5_sample->setStyleSheet(defaultStyle);
    lineEdit = ui->ep5_sample;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    MaterialService server;
    QVector<Material> material = server.GetMaterials("","",str,"","","","",0);
    for(int i = 0; i < material.count(); i++)
    {
        QListWidgetItem *it;it = new QListWidgetItem();
        it->setText(material[i].MaterialName);
        it->setToolTip(material[i].MaterialName);
        listWidget->addItem(it);
    }
    listWidget->setVisible(true);
}

void Pv_Precision::on_ep5_ReagenBatchNo_textChanged(const QString str)
{
    ui->ep5_ReagenBatchNo->setStyleSheet(defaultStyle);
    lineEdit = ui->ep5_ReagenBatchNo;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    ReagentBatchService server;
    QVector<ReagentBatch> reagent = server.GetReagentBatchs("",str);
    for(int i = 0; i < reagent.count(); i++)
    {
        QListWidgetItem *it;it = new QListWidgetItem();
        it->setText(reagent[i].BatchNo);
        it->setToolTip(reagent[i].BatchNo);
        listWidget->addItem(it);
    }

    listWidget->setVisible(true);
}

void Pv_Precision::on_ep5_CPBatchNo_textChanged(const QString str)
{
    ui->ep5_CPBatchNo->setStyleSheet(defaultStyle);
}

//void Pv_Precision::on_ep5_CPBatchNo_textChanged(const QString str)
//{
//    lineEdit = ui->ep5_CPBatchNo;
//    if(listWidget != NULL)
//    {
//        listWidget->setVisible(false);
//    }
//    listWidget = new QListWidget(this);
//    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
//    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
//    listWidget->clear();


//    MaterialBatchService server;
//    QVector<MaterialBatch> material = server.GetMaterialBatchs("",ui->ep5_CPBatchNo->text());
//    for(int i = 0; i < material.count(); i++)
//    {
//        QListWidgetItem *it;it = new QListWidgetItem();
//        it->setText(material[i].BatchNo);
//        it->setToolTip(material[i].BatchNo);
//        listWidget->addItem(it);
//    }

//    listWidget->setVisible(true);
//}


void Pv_Precision::on_ep5_Analyte_textChanged(const QString str)
{
    ui->ep5_Analyte->setStyleSheet(defaultStyle);
    lineEdit = ui->ep5_Analyte;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    TestTypeService server;
    QVector<TestType> type = server.GetTestTypes("","",str);
    for(int i = 0; i < type.count(); i++)
    {
        QListWidgetItem *it;it = new QListWidgetItem();
        it->setText(type[i].TestTypeName);
        it->setToolTip(type[i].TestTypeName);
        listWidget->addItem(it);
    }

    listWidget->setVisible(true);
}

//void Pv_Precision::on_ep5_validationConcentration_textChanged(const QString str)
//{
//    ui->ep5_validationConcentration->setStyleSheet("");
//}

//void Pv_Precision::on_ep5_validationConcentration_2_textChanged(const QString str)
//{
//    ui->ep5_validationConcentration_2->setStyleSheet("");
//}

//void Pv_Precision::on_ep5_validationConcentration_3_textChanged(const QString str)
//{
//    ui->ep5_validationConcentration_3->setStyleSheet("");
//}

//void Pv_Precision::on_ep5_ClaimConcentration_textChanged(const QString str)
//{
//    ui->ep5_ClaimConcentration->setStyleSheet("");
//}

//void Pv_Precision::on_ep5_ClaimConcentration_2_textChanged(const QString str)
//{
//    ui->ep5_ClaimConcentration_2->setStyleSheet("");
//}

//void Pv_Precision::on_ep5_ClaimConcentration_3_textChanged(const QString str)
//{
//    ui->ep5_ClaimConcentration_3->setStyleSheet("");
//}

//void Pv_Precision::on_ep5_ClaimSd_textChanged(const QString str)
//{
//    ui->ep5_ClaimSd->setStyleSheet("");
//}

//void Pv_Precision::on_ep5_ClaimSd_2_textChanged(const QString str)
//{
//    ui->ep5_ClaimSd_2->setStyleSheet("");
//}

//void Pv_Precision::on_ep5_ClaimSd_3_textChanged(const QString str)
//{
//    ui->ep5_ClaimSd_3->setStyleSheet("");
//}

//void Pv_Precision::on_ep5_ClaimTotalSd_textChanged(const QString str)
//{
//    ui->ep5_ClaimTotalSd->setStyleSheet("");
//}

//void Pv_Precision::on_ep5_ClaimTotalSd_2_textChanged(const QString str)
//{
//    ui->ep5_ClaimTotalSd_2->setStyleSheet("");
//}

//void Pv_Precision::on_ep5_ClaimTotalSd_3_textChanged(const QString str)
//{
//    ui->ep5_ClaimTotalSd_3->setStyleSheet("");
//}

//void Pv_Precision::on_ep5_Auditor_textChanged(const QString str)
//{
//    ui->ep5_Auditor->setStyleSheet("");
//}

//void Pv_Precision::on_ep5_Technicina_textChanged(const QString str)
//{
//    ui->ep5_Technicina->setStyleSheet("");
//}

void Pv_Precision::on_Westgard_Instrument_textChanged(const QString str)
{
    ui->Westgard_Instrument->setStyleSheet("");
    lineEdit = ui->Westgard_Instrument;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    DeviceService deviceServer;
    QVector<Device> d = deviceServer.GetAll("", "", str, 0);
    for(int i = 0; i < d.count(); i++)
    {
        QListWidgetItem *it;it = new QListWidgetItem();
        it->setText(d[i].DeviceName);
        it->setToolTip(d[i].DeviceName);
        listWidget->addItem(it);
    }
    listWidget->setVisible(true);
}

void Pv_Precision::on_Westgard_Sample_textChanged(const QString str)
{
    ui->Westgard_Sample->setStyleSheet("");
    lineEdit = ui->Westgard_Sample;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    MaterialService server;
    QVector<Material> material = server.GetMaterials();
    for(int i = 0; i < material.count(); i++)
    {
        QListWidgetItem *it;it = new QListWidgetItem();
        it->setText(material[i].MaterialName);
        it->setToolTip(material[i].MaterialName);
        listWidget->addItem(it);
    }
    listWidget->setVisible(true);
}

void Pv_Precision::on_Westgard_ReagenBatchNo_textChanged(const QString str)
{
    ui->Westgard_ReagenBatchNo->setStyleSheet("");
    lineEdit = ui->Westgard_ReagenBatchNo;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    ReagentBatchService server;
    QVector<ReagentBatch> reagent = server.GetReagentBatchs("",str);
    for(int i = 0; i < reagent.count(); i++)
    {
        QListWidgetItem *it;it = new QListWidgetItem();
        it->setText(reagent[i].BatchNo);
        it->setToolTip(reagent[i].BatchNo);
        listWidget->addItem(it);
    }

    listWidget->setVisible(true);
}

void Pv_Precision::on_Westgard_CPBatchNo_textChanged(const QString str)
{
    ui->Westgard_CPBatchNo->setStyleSheet("");
}

//void Pv_Precision::on_Westgard_CPBatchNo_textChanged(const QString str)
//{
//    lineEdit = ui->Westgard_CPBatchNo;
//    if(listWidget != NULL)
//    {
//        listWidget->setVisible(false);
//    }
//    listWidget = new QListWidget(this);
//    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
//    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
//    listWidget->clear();


//    MaterialBatchService server;
//    QVector<MaterialBatch> material = server.GetMaterialBatchs("",str);
//    for(int i = 0; i < material.count(); i++)
//    {
//        QListWidgetItem *it;it = new QListWidgetItem();
//        it->setText(material[i].BatchNo);
//        it->setToolTip(material[i].BatchNo);
//        listWidget->addItem(it);
//    }

//    listWidget->setVisible(true);
//}

void Pv_Precision::on_Westgard_Analyte_textChanged(const QString str)
{
    ui->Westgard_Analyte->setStyleSheet("");
    lineEdit = ui->Westgard_Analyte;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();


    TestTypeService server;
    QVector<TestType> type = server.GetTestTypes();
    for(int i = 0; i < type.count(); i++)
    {
        QListWidgetItem *it;it = new QListWidgetItem();
        it->setText(type[i].TestTypeName);
        it->setToolTip(type[i].TestTypeName);
        listWidget->addItem(it);
    }

    listWidget->setVisible(true);
}

void Pv_Precision::Westgard_AddColumns(QString label)
{
    ui->Westgard_tableWidget->insertColumn(ui->Westgard_tableWidget->columnCount()/2);
    ui->Westgard_tableWidget->insertColumn(ui->Westgard_tableWidget->columnCount());

    ui->Westgard_tableWidget->setSpan(0,0,1,5);
    ui->Westgard_tableWidget->setSpan(0,5,1,5);

    QLabel *itemLabel = new QLabel(label);
    itemLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->Westgard_tableWidget->setCellWidget(1,ui->Westgard_tableWidget->columnCount()/2-1,itemLabel);

    itemLabel = new QLabel(label);
    itemLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->Westgard_tableWidget->setCellWidget(1,ui->Westgard_tableWidget->columnCount()-1,itemLabel);

    for(int i = 0; i < 5; i++)
    {
        ui->Westgard_tableWidget->setColumnWidth(i,130);//设置列宽
        ui->Westgard_tableWidget->setColumnWidth(i+5,130);
    }
    for(int i = 2; i < 22; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->Westgard_tableWidget->setItem(i,ui->Westgard_tableWidget->columnCount()/2-1,item);

        item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->Westgard_tableWidget->setItem(i,ui->Westgard_tableWidget->columnCount()-1,item);
    }
}

void Pv_Precision::Westgard_RemoveColumns()
{
    ui->Westgard_tableWidget->removeColumn(ui->Westgard_tableWidget->columnCount()/2-1);
    ui->Westgard_tableWidget->removeColumn(ui->Westgard_tableWidget->columnCount()-1);
    for(int i = 0; i < 4; i++)
    {
        ui->Westgard_tableWidget->setColumnWidth(i,162);//设置列宽
        ui->Westgard_tableWidget->setColumnWidth(i+4,162);
    }
}

void Pv_Precision::on_ep15_Instrument_textChanged(const QString str)
{
    ui->ep15_Instrument->setStyleSheet("");
    lineEdit = ui->ep15_Instrument;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    DeviceService deviceServer;
    QVector<Device> d = deviceServer.GetAll("", "", str, 0);
    for(int i = 0; i < d.count(); i++)
    {
        QListWidgetItem *it;it = new QListWidgetItem();
        it->setText(d[i].DeviceName);
        it->setToolTip(d[i].DeviceName);
        listWidget->addItem(it);
    }
    listWidget->setVisible(true);
}

void Pv_Precision::on_ep15_ReagenBatchNo_textChanged(const QString str)
{
    ui->ep15_ReagenBatchNo->setStyleSheet("");
    lineEdit = ui->ep15_ReagenBatchNo;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    ReagentBatchService server;
    QVector<ReagentBatch> reagent = server.GetReagentBatchs("",str);
    for(int i = 0; i < reagent.count(); i++)
    {
        QListWidgetItem *it;it = new QListWidgetItem();
        it->setText(reagent[i].BatchNo);
        it->setToolTip(reagent[i].BatchNo);
        listWidget->addItem(it);
    }

    listWidget->setVisible(true);
}

void Pv_Precision::on_ep15_CPBatchNo_textChanged(const QString str)
{
    ui->ep15_CPBatchNo->setStyleSheet("");
}

//void Pv_Precision::on_ep15_CPBatchNo_textChanged(const QString str)
//{
//    lineEdit = ui->ep15_CPBatchNo;
//    if(listWidget != NULL)
//    {
//        listWidget->setVisible(false);
//    }
//    listWidget = new QListWidget(this);
//    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
//    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
//    listWidget->clear();

//    MaterialBatchService server;
//    QVector<MaterialBatch> material = server.GetMaterialBatchs("", str);
//    for(int i = 0; i < material.count(); i++)
//    {
//        QListWidgetItem *it;it = new QListWidgetItem();
//        it->setText(material[i].BatchNo);
//        it->setToolTip(material[i].BatchNo);
//        listWidget->addItem(it);
//    }

//    listWidget->setVisible(true);
//}

void Pv_Precision::on_ep15_AnalysisProgram_textChanged(const QString str)
{
    ui->ep15_AnalysisProgram->setStyleSheet("");
    lineEdit = ui->ep15_AnalysisProgram;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+13,lineEdit->geometry().y()+52,lineEdit->geometry().width(),120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();


    TestTypeService server;
    QVector<TestType> type = server.GetTestTypes("", "",str);
    for(int i = 0; i < type.count(); i++)
    {
        QListWidgetItem *it;it = new QListWidgetItem();
        it->setText(type[i].TestTypeName);
        it->setToolTip(type[i].TestTypeName);
        listWidget->addItem(it);
    }

    listWidget->setVisible(true);
}

void Pv_Precision::ep15_AddRows(QTableWidget *tableWidget,QString label)
{
    tableWidget->setRowCount(tableWidget->rowCount()+4);
    tableWidget->setSpan(tableWidget->rowCount()-4,0,4,1);
    QLabel *itemLabel = new QLabel(label);
    itemLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    tableWidget->setCellWidget(tableWidget->rowCount()-4,0,itemLabel);
    QStringList rowList;
    rowList << tr("日期/操作人员")
               << tr("第一次测量结果：x1") << tr("第二次测量结果:x2") << tr("第三次测量结果:x3");
    int row = tableWidget->rowCount()-4;



    for(int i = 0; i < 4; i++)
    {
        QLabel *label = new QLabel(rowList.at(i));
        label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tableWidget->setCellWidget(row,1,label);
        for(int j = 2; j < 7; j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->ep15_tableWidget->setItem(row,j,item);
        }

        row++;
    }


}

void Pv_Precision::ep15_RemoveRows(QTableWidget *tableWidget)
{
    int row = tableWidget->rowCount();
    for(int i = 0; i < 4; i++)
    {
        tableWidget->removeRow(row-1);
        row--;
    }
}

void Pv_Precision::keyPressEvent(QKeyEvent *keyevent)
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

void Pv_Precision::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}

void Pv_Precision::mousePressEvent(QMouseEvent *event)
{
    if(listWidget != NULL && event->button() == Qt::LeftButton)
    {
        listWidget->setVisible(false);
    }
}

void Pv_Precision::timerEvent(QTimerEvent *event)
{
    count--;
    if(count <= 0)
        killTimer(timeId);

    if(count%2 != 0)
    {
//        foreach (Axis<int> axis, outliersAxisVec) {
//           ui->ep5_tableWidget->item(axis.x,axis.y)->setBackgroundColor(QColor("white"));
//        }
    }
    else
    {
//        foreach (Axis<int> axis, outliersAxisVec) {
//           ui->ep5_tableWidget->item(axis.x,axis.y)->setBackgroundColor(QColor("red"));
//        }
    }
}

void Pv_Precision::contextMenuEvent(QContextMenuEvent *e)
{
//    QMenu *menu = new QMenu();
//    menu->addSeparator();
//    menu->addSeparator();
//    menu->addAction(Act_Maxsize);
//    menu->addSeparator();
//    menu->addSeparator();
//    menu->addAction(Act_Normal);
//    menu->addSeparator();
//    menu->addSeparator();
//    menu->exec(e->globalPos());
//    delete menu;
}

QString Pv_Precision::GenerateEp5Html()
{
    QString html = "";
    if(ep5Level == TWO)
    {
        QString filename = ".//doc//Precision_Ep5_Report_Template2.htm";
        html = readFile(filename);

        bool res1 = ep5Level1Html(html);
        bool res2 = ep5Level2Html(html);
        if(res1 && res2)
        {
            html.replace("#CONC#",tr("两个浓度的验证值均小于制造商声明值，精密度的性能可以接受。"));
        }
        else
        {
            QString str = "";
            if( !res1 )
            {
                str.append("浓度水平1的验证值均大于产家声明值，");
            }
            else
            {
                str.append("浓度水平1的验证值均小于产家声明值，");
            }

            if( !res2 )
            {
                str.append("浓度水平2的验证值均大于制造商声明值，");
            }
            else
            {
                str.append("浓度水平2的验证值均小于制造商声明值，");
            }
            str.append("精密度的性能不在要求的界限内，不能被接受。");
            html.replace("#CONC#",str);
        }
    }

    else if(ep5Level == THREE)
    {
        QString filename = ".//doc//Precision_Ep5_Report_Template3.htm";
        html = readFile(filename);

        bool res1 = ep5Level1Html(html);
        bool res2 = ep5Level2Html(html);
        bool res3 = ep5Level3Html(html);

        if(res1 && res2 && res3)
        {
            html.replace("#CONC#",tr("三个浓度的验证值均小于制造商声明值，精密度的性能可以接受。"));
        }
        else
        {
            QString str = "";
            if( !res1 )
            {
                str.append("浓度水平1的验证值均大于制造商声明值，");
            }
            else
            {
                str.append("浓度水平1的验证值均小于产家声明值，");
            }

            if( !res2 )
            {
                str.append("浓度水平2的验证值均大于制造商声明值，");
            }
            else
            {
                str.append("浓度水平2的验证值均小于制造商声明值，");
            }

            if( !res3 )
            {
                str.append("浓度水平3的验证值均大于制造商声明值，");
            }
            else
            {
                str.append("浓度水平3的验证值均小于制造商声明值，");
            }
            str.append("精密度的性能不在要求的界限内，不能被接受。");
            html.replace("#CONC#",str);
        }
    }

    html.replace("#DT#",htmlString(ui->ep5_date->text(),24));
    html.replace("#PJ#",htmlString(ui->ep5_Analyte->text()));
    html.replace("#AT#",htmlString(ui->ep5_instrument->text(),24));
    html.replace("#DI#",htmlString(ui->ep5_Analyte->text()));
    html.replace("#RB#",htmlString(ui->ep5_ReagenBatchNo->text(),24));
    html.replace("#CB#",htmlString(ui->ep5_sample->text()));
    html.replace("#QB#",htmlString(ui->ep5_Analyte->text(),24));
    html.replace("#SC#",htmlString(ui->ep5_Analyte->text()));

    html.replace("#TC#",htmlString(ui->ep5_Technicina->text(),24));
    html.replace("#ADT#",htmlString(ui->ep5_Auditor->text(),24));
    html.replace("#DTT#",ui->ep5_CalculateDate->text());
    html.replace("#DTA#",ui->ep5_approvalDate->text());

    return html;
}

bool Pv_Precision::ep5Level1Html(QString &html)
{
    for(int i = 1; i <= 20; i++)
    {
        for(int j = 1; j <= 11; j++)
        {
            if(j == 1 || j >= 6 && j <= 7)//日期，批均值
            {
                QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,j));
                html.replace(QString("#%1_%2#").arg(i).arg(j),QString("%1").arg(label->text()));
            }
            if( j >= 2 && j <= 5)
            {
                html.replace(QString("#%1_%2#").arg(i).arg(j),QString("%1").arg(ui->ep5_tableWidget->item(i,j)->text()));
            }

            if(j == 8)
            {
                QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,6));
                double a = label->text().toDouble();
                label = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,7));
                double b = label->text().toDouble();
                double res = (a+b)/2;
                html.replace(QString("#%1_%2#").arg(i).arg(j),QString::number(res,'f',2));
            }
            if(j == 9)
            {
                double a = ui->ep5_tableWidget->item(i,2)->text().toDouble();
                double b = ui->ep5_tableWidget->item(i,3)->text().toDouble();
                double res = (a-b)*(a-b);
                html.replace(QString("#%1_%2#").arg(i).arg(j),QString::number(res));
            }
            if(j == 10)
            {
                double a = ui->ep5_tableWidget->item(i,4)->text().toDouble();
                double b = ui->ep5_tableWidget->item(i,5)->text().toDouble();
                double res = (a-b)*(a-b);
                html.replace(QString("#%1_%2#").arg(i).arg(j),QString::number(res,'f',2));
            }
            if(j == 11)
            {
                QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,6));
                double a = label->text().toDouble();
                label = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,7));
                double b = label->text().toDouble();
                double res = (a-b)*(a-b);
                html.replace(QString("#%1_%2#").arg(i).arg(j),QString::number(res,'f',2));
            }
        }
    }

    ///批内精密度
    html.replace("#UCL#",ui->ep5_validationConcentration_L1->text());
    html.replace("#CCL#",ui->ep5_ClaimConcentration_L1->text());
    double dof = precision1.getR();
    html.replace("#DOF#",QString::number(dof));//自由度，待定
    double sd = precision1.GetSd();
    html.replace("#USD#",QString::number(sd,'f',2));
    html.replace("#UVSD#",QString::number(sd*sd,'f',2));
    double pcsd = ui->ep5_ClaimSd_L1->text().toDouble();//待定
    html.replace("#PCSD#",QString::number(pcsd,'f',2));//制造商声明的标准差，待定
    html.replace("#VSD#",QString::number(pcsd*pcsd,'f',2));//制造商声明的方差，待定
    double ucr = (sd/(pcsd*pcsd))*dof;
    html.replace("#UCR#",QString::number(ucr,'f',2));
    double chiSquare = GetChiSquare((double)dof,5);
    html.replace("#CS#",QString::number(chiSquare));//卡方值
    if(ucr > chiSquare)
    {
        html.replace("#CR#",QString("<span>&radic;</span>"));
        html.replace("#CA#",QString(""));
    }
    else
    {
        html.replace("#CR#",QString(""));
        html.replace("#CA#",QString("<span>&radic;</span>"));
    }

    ///方法/仪器精密度
    html.replace("#DUCL#",ui->ep5_validationConcentration_L1->text());
    html.replace("#DCCL#",ui->ep5_ClaimConcentration_L1->text());//浓度值，未知
    double ddof = precision1.GetT();
    html.replace("#DDOF#",QString::number(ddof));//自由度，待定
    double dsd = precision1.GetSt();
    html.replace("#DUSD#",QString::number(dsd,'f',2));
    html.replace("#DUVSD#",QString::number(dsd*dsd,'f',2));
    double dpcsd = ui->ep5_ClaimTotalSd_L1->text().toDouble();
    html.replace("#DPCSD#",QString::number(dpcsd,'f',2));//制造商声明的标准差，待定
    html.replace("#DVSD#",QString::number(dpcsd*dpcsd,'f',2));//制造商声明的方差，待定
    double duct = (dsd/(dpcsd*dpcsd))*ddof;
    html.replace("#DUCT#",QString::number(duct));
    double DchiSquare = GetChiSquare((double)ddof,5);
        html.replace("#DCS#",QString::number(DchiSquare));//卡方值
    if(duct > DchiSquare)
    {
        html.replace("#DCR#",QString("<span>&radic;</span>"));
        html.replace("#DCA#",QString(""));
        return false;
    }
    else
    {
        html.replace("#DCR#",QString(""));
        html.replace("#DCA#",QString("<span>&radic;</span>"));
        return true;
    }
}

bool Pv_Precision::ep5Level2Html(QString &html)
{
    for(int i = 1; i <= 20; i++)
    {
        for(int j = 1; j <= 11; j++)
        {
            if(j == 1 || j >= 6 && j <= 7)//日期，批均值
            {
                QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget_2->cellWidget(i,j));
                html.replace(QString("#2@%1_%2#").arg(i).arg(j),QString("%1").arg(label->text()));
            }
            if( j >= 2 && j <= 5)
            {
                html.replace(QString("#2@%1_%2#").arg(i).arg(j),QString("%1").arg(ui->ep5_tableWidget_2->item(i,j)->text()));
            }

            if(j == 8)
            {
                QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget_2->cellWidget(i,6));
                double a = label->text().toDouble();
                label = qobject_cast<QLabel*>(ui->ep5_tableWidget_2->cellWidget(i,7));
                double b = label->text().toDouble();
                double res = (a+b)/2;
                html.replace(QString("#2@%1_%2#").arg(i).arg(j),QString::number(res,'f',2));
            }
            if(j == 9)
            {
                double a = ui->ep5_tableWidget_2->item(i,2)->text().toDouble();
                double b = ui->ep5_tableWidget_2->item(i,3)->text().toDouble();
                double res = (a-b)*(a-b);
                html.replace(QString("#2@%1_%2#").arg(i).arg(j),QString::number(res));
            }
            if(j == 10)
            {
                double a = ui->ep5_tableWidget_2->item(i,4)->text().toDouble();
                double b = ui->ep5_tableWidget_2->item(i,5)->text().toDouble();
                double res = (a-b)*(a-b);
                html.replace(QString("#2@%1_%2#").arg(i).arg(j),QString::number(res,'f',2));
            }
            if(j == 11)
            {
                QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget_2->cellWidget(i,6));
                double a = label->text().toDouble();
                label = qobject_cast<QLabel*>(ui->ep5_tableWidget_2->cellWidget(i,7));
                double b = label->text().toDouble();
                double res = (a-b)*(a-b);
                html.replace(QString("#2@%1_%2#").arg(i).arg(j),QString::number(res,'f',2));
            }
        }
    }

    html.replace("#2@UCL#",ui->ep5_validationConcentration_L2->text());   //待定
    html.replace("#2@CCL#",ui->ep5_ClaimConcentration_L2->text());
    int dof = precision2.getR();
    html.replace("#2@DOF#",QString::number(dof));//自由度，待定
    double sd = precision2.GetSd();
    html.replace("#2@USD#",QString::number(sd,'f',2));
    html.replace("#2@UVSD#",QString::number(sd*sd,'f',2));
    double pcsd = ui->ep5_ClaimSd_L2->text().toDouble();
    html.replace("#2@PCSD#",QString::number(pcsd,'f',2));//制造商声明的标准差，待定
    html.replace("#2@VSD#",QString::number(pcsd*pcsd,'f',2));//制造商声明的方差，待定
    double ucr = (sd/(pcsd*pcsd))*dof;
    html.replace("#2@UCR#",QString::number(ucr));
    double chiSquare = GetChiSquare((double)dof,5);
        html.replace("#2@CS#",QString::number(chiSquare));//卡方值
    if(ucr > chiSquare)
    {
        html.replace("#2@CR#",QString("<span>&radic;</span>"));
        html.replace("#2@CA#",QString(""));
    }
    else
    {
        html.replace("#2@CR#",QString(""));
        html.replace("#2@CA#",QString("<span>&radic;</span>"));
    }

    ///方法/仪器精密度
    html.replace("#2@DUCL#",ui->ep5_validationConcentration_L2->text());   //待定
    html.replace("#2@DCCL#",ui->ep5_ClaimConcentration_L2->text());//浓度值，未知
    int ddof = precision2.GetT();
    html.replace("#2@DDOF#",QString::number(ddof));//自由度，待定
    double dsd = precision2.GetSt();
    html.replace("#2@DUSD#",QString::number(dsd,'f',2));
    html.replace("#2@DUVSD#",QString::number(dsd*dsd,'f',2));
    double dpcsd = ui->ep5_ClaimTotalSd_L2->text().toDouble();
    html.replace("#2@DPCSD#",QString::number(dpcsd,'f',2));//制造商声明的标准差，待定
    html.replace("#2@DVSD#",QString::number(dpcsd*dpcsd,'f',2));//制造商声明的方差，待定
    double duct = (dsd/(dpcsd*dpcsd))*ddof;
    html.replace("#2@DUCT#",QString::number(duct));
    double DchiSquare = GetChiSquare((double)ddof,5);
    html.replace("#2@DCS#",QString::number(DchiSquare));//卡方值
    if(duct > DchiSquare)
    {
        html.replace("#2@DCR#",QString("<span>&radic;</span>"));
        html.replace("#2@DCA#",QString(""));
        return false;
    }
    else
    {
        html.replace("#2@DCR#",QString(""));
        html.replace("#2@DCA#",QString("<span>&radic;</span>"));
        return true;
    }
}

bool Pv_Precision::ep5Level3Html(QString &html)
{
    for(int i = 1; i <= 20; i++)
    {
        for(int j = 1; j <= 11; j++)
        {
            if(j == 1 || j >= 6 && j <= 7)//日期，批均值
            {
                QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget_3->cellWidget(i,j));
                html.replace(QString("#3@%1_%2#").arg(i).arg(j),QString("%1").arg(label->text()));
            }
            if( j >= 2 && j <= 5)
            {
                html.replace(QString("#3@%1_%2#").arg(i).arg(j),QString("%1").arg(ui->ep5_tableWidget_3->item(i,j)->text()));
            }

            if(j == 8)
            {
                QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget_3->cellWidget(i,6));
                double a = label->text().toDouble();
                label = qobject_cast<QLabel*>(ui->ep5_tableWidget_3->cellWidget(i,7));
                double b = label->text().toDouble();
                double res = (a+b)/2;
                html.replace(QString("#3@%1_%2#").arg(i).arg(j),QString::number(res,'f',2));
            }
            if(j == 9)
            {
                double a = ui->ep5_tableWidget_3->item(i,2)->text().toDouble();
                double b = ui->ep5_tableWidget_3->item(i,3)->text().toDouble();
                double res = (a-b)*(a-b);
                html.replace(QString("#3@%1_%2#").arg(i).arg(j),QString::number(res));
            }
            if(j == 10)
            {
                double a = ui->ep5_tableWidget_3->item(i,4)->text().toDouble();
                double b = ui->ep5_tableWidget_3->item(i,5)->text().toDouble();
                double res = (a-b)*(a-b);
                html.replace(QString("#3@%1_%2#").arg(i).arg(j),QString::number(res,'f',2));
            }
            if(j == 11)
            {
                QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget_3->cellWidget(i,6));
                double a = label->text().toDouble();
                label = qobject_cast<QLabel*>(ui->ep5_tableWidget_3->cellWidget(i,7));
                double b = label->text().toDouble();
                double res = (a-b)*(a-b);
                html.replace(QString("#3@%1_%2#").arg(i).arg(j),QString::number(res,'f',2));
            }
        }
    }


    ///批内精密度
    html.replace("#3@UCL#",ui->ep5_validationConcentration_L3->text());
    html.replace("#3@CCL#",ui->ep5_ClaimConcentration_L3->text());
    int dof = precision3.getR();
    html.replace("#3@DOF#",QString::number(dof));
    double sd = precision3.GetSd();
    html.replace("#3@USD#",QString::number(sd,'f',2));
    html.replace("#3@UVSD#",QString::number(sd*sd,'f',2));
    double pcsd = ui->ep5_ClaimSd_L3->text().toDouble();
    html.replace("#3@PCSD#",QString::number(pcsd,'f',2));//制造商声明的标准差，待定
    html.replace("#3@VSD#",QString::number(pcsd*pcsd,'f',2));//制造商声明的方差，待定
    double ucr = (sd/(pcsd*pcsd))*dof;
    html.replace("#3@UCR#",QString::number(ucr));
    double chiSquare = GetChiSquare((double)dof,5);
    html.replace("#3@CS#",QString::number(chiSquare));//卡方值
    if(ucr > chiSquare)
    {
        html.replace("#3@CR#",QString("<span>&radic;</span>"));
        html.replace("#3@CA#",QString(""));
    }
    else
    {
        html.replace("#3@CR#",QString(""));
        html.replace("#3@CA#",QString("<span>&radic;</span>"));
    }

    ///方法/仪器精密度
    html.replace("#3@DUCL#",ui->ep5_validationConcentration_L3->text());
    html.replace("#3@DCCL#",ui->ep5_ClaimConcentration_L3->text());
    int ddof = precision3.GetT();
    html.replace("#3@DDOF#",QString::number(ddof));
    double dsd = precision3.GetSt();
    html.replace("#3@DUSD#",QString::number(dsd,'f',2));
    html.replace("#3@DUVSD#",QString::number(dsd*dsd,'f',2));
    double dpcsd = ui->ep5_ClaimTotalSd_L3->text().toDouble();
    html.replace("#3@DPCSD#",QString::number(dpcsd,'f',2));//制造商声明的标准差，待定
    html.replace("#3@DVSD#",QString::number(dpcsd*dpcsd,'f',2));//制造商声明的方差，待定
    double duct = (dsd/(dpcsd*dpcsd))*ddof;
    html.replace("#3@DUCT#",QString::number(duct));
    double DchiSquare = GetChiSquare((double)dof,5);//卡方值
        html.replace("#3@DCS#",QString::number(DchiSquare));
    if(duct > DchiSquare)
    {
        html.replace("#3@DCR#",QString("<span>&radic;</span>"));
        html.replace("#3@DCA#",QString(""));
        return false;
    }
    else
    {
        html.replace("#3@DCR#",QString(""));
        html.replace("#3@DCA#",QString("<span>&radic;</span>"));
        return true;
    }
}

QString Pv_Precision::GenerateEp15Html()
{
    QString html = "";
    QString filename = "";
    QString str="",str1="",str2="",str3="";
    if(ep15Level == TWO)
    {
        filename = QString(".//doc//Precision_Ep15_Report_Template.htm");
        html = readFile(filename);


        for(int i = 1; i <= 3; i++)
        {
            for(int j = 1; j <= 5; j++)
            {
                html.replace(QString("#L1@%1_%2#").arg(i).arg(j),ui->ep15_tableWidget->item(i+1,j+1)->text());
                html.replace(QString("#L2@%1_%2#").arg(i).arg(j),ui->ep15_tableWidget->item(i+5,j+1)->text());
            }
        }
    }

    else if(ep15Level == THREE)
    {
        filename = QString(".//doc//Precision_Ep15_Report_Template1.htm");
        html = readFile(filename);

        for(int i = 1; i <= 3; i++)
        {
            for(int j = 1; j <= 5; j++)
            {
                html.replace(QString("#L1@%1_%2#").arg(i).arg(j),ui->ep15_tableWidget->item(i+1,j+1)->text());
                html.replace(QString("#L2@%1_%2#").arg(i).arg(j),ui->ep15_tableWidget->item(i+5,j+1)->text());
                html.replace(QString("#L3@%1_%2#").arg(i).arg(j),ui->ep15_tableWidget->item(i+9,j+1)->text());
            }
        }
        html.replace("#L3EI#",htmlString(ui->ep15_Except_L3_Iner_Cv->text()));
        html.replace("#L3CI#",htmlString(ui->ep15_Calculate_L3_Iner_Cv->text()));
        html.replace("#L3E#",htmlString(ui->ep15_Except_L3_Cv->text()));
        html.replace("#L3C#",htmlString(ui->ep15_Calculate_L3_Cv->text()));
        html.replace("#L3#",htmlString(ui->ep15_Concentration_L3->text()));

        {//L3
            if(ui->ep15_Calculate_L3_Iner_Cv->text().toDouble()  < ui->ep15_Except_L3_Iner_Cv->text().toDouble())
            {
                str3 = QString("<span>计算值Sr &lt; 厂家声称值&delta;r，表明厂家声称的精密度可靠。</span>");
            }
            else
            {
                if(ui->ep15_Calculate_L3_Cv->text().toDouble() <= ui->ep15_Except_L3_Cv->text().toDouble())
                {
                    str3 = QString("<span>计算值Sr &gt; 厂家声称值&delta;r，但计算值S1 &lt; 厂家声明称值&delta;1，厂家声称的精密度可靠。</span>");
                }
                else
                {
                    double T = ep15Precision3.GetT(LEVEL3);
                    double C = GetChiSquare(T,5);
                    double value = ui->ep15_Except_L3_Cv->text().toDouble()*sqrt(C)/sqrt(T);
                    if(ui->ep15_Calculate_L3_Cv->text().toDouble() < value)
                    {
                        str = QString("<span>计算值Sr &gt; 厂家声明称值&delta;r，但计算值S1 &lt; 验证值，厂家声称的精密度可靠。</span>");
                    }
                    else
                    {
                        str3 = QString("<span>计算值Sr &gt; 厂家声称值&delta;r,并且计算值S1 &gt; 验证值,厂家声称的精密度不可靠。</span>");
                    }
                }
            }
            str3.prepend("水平3：");
            str3.append("\n");
        }
    }

    {//L1
        if(ui->ep15_Calculate_L1_Iner_Cv->text().toDouble()  < ui->ep15_Except_L1_Iner_Cv->text().toDouble())
        {
            str1 = QString("<span>计算值Sr &lt; 厂家声称值&delta;r，表明厂家声称的精密度可靠。</span>");
        }
        else
        {
            if(ui->ep15_Calculate_L1_Cv->text().toDouble() <= ui->ep15_Except_L1_Cv->text().toDouble())
            {
                str1 = QString("<span>计算值Sr &gt; 厂家声称值&delta;r，但计算值S1 &lt; 厂家声明称值&delta;1，厂家声称的精密度可靠。</span>");
            }
            else
            {
                double T = ep15Precision1.GetT(LEVEL1);
                double C = GetChiSquare(T,5);
                double value = ui->ep15_Except_L1_Cv->text().toDouble()*sqrt(C)/sqrt(T);
                if(ui->ep15_Calculate_L1_Cv->text().toDouble() < value)
                {
                    str1 = QString("<span>计算值Sr &gt; 厂家声明称值&delta;r，但计算值S1 &lt; 验证值，厂家声称的精密度可靠。</span>");
                }
                else
                {
                    str1 = QString("<span>计算值Sr &gt; 厂家声称值&delta;r,并且计算值S1 &gt; 验证值,厂家声称的精密度不可靠。</span>");
                }
            }
        }
        str1.prepend("水平1：");
        str1.append("\n");
    }
    {//L2
        if(ui->ep15_Calculate_L2_Iner_Cv->text().toDouble()  < ui->ep15_Except_L2_Iner_Cv->text().toDouble())
        {
            str2 = QString("计算值Sr &lt; 厂家声称值&delta;r，表明厂家声称的精密度可靠。</span>");
        }
        else
        {
            if(ui->ep15_Calculate_L2_Cv->text().toDouble() <= ui->ep15_Except_L2_Cv->text().toDouble())
            {
                str2 = QString("<span>计算值Sr &lt; 厂家声称值&delta;r，但计算值S1 &lt; 厂家声明称值&delta;1，厂家声称的精密度可靠。</span>");
            }
            else
            {
                double T = ep15Precision2.GetT(LEVEL2);
                double C = GetChiSquare(T,5);
                double value = ui->ep15_Except_L2_Cv->text().toDouble()*sqrt(C)/sqrt(T);
                if(ui->ep15_Calculate_L2_Cv->text().toDouble() < value)
                {
                    str2 = QString("<span>计算值Sr &gt; 厂家声明称值&delta;r，但计算值S1 &lt; 验证值，厂家声称的精密度可靠。</span>");
                }
                else
                {
                    str2 = QString("<span>计算值Sr &gt; 厂家声称值&delta;r,并且计算值S1 &gt; 验证值,厂家声称的精密度不可靠。</span>");
                }
            }
        }
        str2.prepend("水平2：");
        str2.append("\n");
    }

    html.replace("#L1EI#",htmlString(ui->ep15_Except_L1_Iner_Cv->text()));
    html.replace("#L1E#",htmlString(ui->ep15_Except_L1_Cv->text()));
    html.replace("#L1CI#",htmlString(ui->ep15_Calculate_L1_Iner_Cv->text()));
    html.replace("#L1C#",htmlString(ui->ep15_Calculate_L1_Cv->text()));

    html.replace("#L2EI#",htmlString(ui->ep15_Except_L2_Iner_Cv->text()));
    html.replace("#L2CI#",htmlString(ui->ep15_Calculate_L2_Iner_Cv->text()));
    html.replace("#L2E#",htmlString(ui->ep15_Except_L2_Cv->text()));
    html.replace("#L2C#",htmlString(ui->ep15_Calculate_L2_Cv->text()));

    html.replace("#DT#",htmlString(ui->ep15_date->text()));
    html.replace("#PJ#",htmlString(ui->ep15_AnalysisProgram->text()));
    html.replace("#AT#",htmlString(ui->ep15_Instrument->text()));
//                html.replace("#DI#",htmlString(ui->ep15_Analyte->text()));        //设备标识
    html.replace("#RB#",htmlString(ui->ep15_ReagenBatchNo->text()));
    html.replace("#CB#",htmlString(ui->ep15_CPBatchNo->text()));
//        html.replace("#QB#",htmlString(ui->ep15_Analyte->text()));          //质控品批号
    html.replace("#L1#",htmlString(ui->ep15_Concentration_L1->text()));
    html.replace("#L2#",htmlString(ui->ep15_Concentration_L2->text()));


    str = str1 + str2 + str3;
    html.replace("#CONC#",str);
    html.replace("#TC#",ui->ep15_Technicina->text());
    html.replace("#ADT#",ui->ep15_Auditor->text());
    html.replace("#DTT#",ui->ep15_CalculateDate->text());
    html.replace("#DTA#",ui->ep15_ApprovalDate->text());

    return html;
}

QString Pv_Precision::GenerateEpWeatgardHtml()
{
    QString filename = "";
    int column = 0;
    if(westgardLevel == TWO)
    {
        column = 4;
        filename = ".//doc//Precision_Westgard_Report_Template.htm";
    }
    else if(westgardLevel == THREE)
    {
        column = 5;
        filename = ".//doc//Precision_Westgard_Report_Template2.htm";
    }
    QString html = readFile(filename);

    html.replace("#DT#",htmlString(ui->Westgard_date->text()));
    html.replace("#PJ#",htmlString(ui->Westgard_Analyte->text()));
    html.replace("#AT#",htmlString(ui->Westgard_Instrument->text()));
    html.replace("#DI#",htmlString(ui->Westgard_Analyte->text()));
    html.replace("#RB#",htmlString(ui->Westgard_ReagenBatchNo->text()));
    html.replace("#CB#",htmlString(ui->Westgard_Sample->text()));
    html.replace("#QB#",htmlString(ui->Westgard_Analyte->text()));
    html.replace("#SC#",htmlString(ui->Westgard_Analyte->text()));
    html.replace("#L1#",htmlString(ui->Westgard_ConcentrationLevel1->text()));
    html.replace("#L2#",htmlString(ui->Westgard_ConcentrationLevel2->text()));

    html.replace("#L1EI#",ui->Westgard_Except_L1_Iner_Cv->text());
    html.replace("#L1E#",ui->Westgard_Except_L1_Cv->text());
    html.replace("#L1CI#",ui->Westgard_Calculate_L1_Iner_Cv->text());
    html.replace("#L1C#",ui->Westgard_Calculate_L1_Cv->text());

    html.replace("#L2EI#",ui->Westgard_Except_L2_Iner_Cv->text());
    html.replace("#L2E#",ui->Westgard_Except_L2_Cv->text());
    html.replace("#L2CI#",ui->Westgard_Calculate_L2_Iner_Cv->text());
    html.replace("#L2C#",ui->Westgard_Calculate_L2_Cv->text());
    if(westgardLevel == THREE)
    {
        html.replace("#L3#",htmlString(ui->Westgard_ConcentrationLevel3->text()));
        html.replace("#L3EI#",ui->Westgard_Except_L3_Iner_Cv->text());
        html.replace("#L3E#",ui->Westgard_Except_L3_Cv->text());
        html.replace("#L3CI#",ui->Westgard_Calculate_L3_Iner_Cv->text());
        html.replace("#L3C#",ui->Westgard_Calculate_L3_Cv->text());
    }
        for(int i = 1; i <= 20; i++)
        {
            for(int j = 1; j <= column-1; j++)
            {
                if(j == 1)
                {
                    html.replace(QString("#%1_%2#").arg(i).arg(j),qobject_cast<QLabel*>(ui->Westgard_tableWidget->cellWidget(i+1,j))->text());
                    html.replace(QString("#%1_%2#").arg(i).arg(j+column),qobject_cast<QLabel*>(ui->Westgard_tableWidget->cellWidget(i+1,j+column))->text());
                }
                else
                {
                    html.replace(QString("#%1_%2#").arg(i).arg(j),ui->Westgard_tableWidget->item(i+1,j)->text());
                    html.replace(QString("#%1_%2#").arg(i).arg(j+column),ui->Westgard_tableWidget->item(i+1,j+column)->text());
                }
            }
        }

    html.replace("#CONC#",QString(""));

    html.replace("#TC#",ui->Westgard_Technicina->text());
    html.replace("#ADT#",ui->Westgard_Auditor->text());
    html.replace("#DTT#",ui->Westgard_CalculateDate->text());
    html.replace("#DTA#",ui->Westgard_ApprovalDate->text());

    return html;
}

bool Pv_Precision::Check_EP5_tables(LEVEL level)
{
    bool fPass = true;

    //检查数据是否完整
    if(level == TWO)
    {
        fPass = Check_EP5_table_ByName(ui->ep5_tableWidget,0) &&
                Check_EP5_table_ByName(ui->ep5_tableWidget_2,1);
//        for(int i = 1; i < ui->ep5_tableWidget->rowCount(); i++)
//        {
//            for(int j = 2; j <= 5; j++)
//            {
//                if(ui->ep5_tableWidget->item(i,j)->text().isEmpty())
//                {
//                    fEmpty = true;
//                }
//            }
//        }

//        for(int i = 1; i < ui->ep5_tableWidget_2->rowCount(); i++)
//        {
//            for(int j = 2; j <= 5; j++)
//            {
//                if(ui->ep5_tableWidget_2->item(i,j)->text().isEmpty())
//                {
//                    fEmpty = true;
//                }
//            }
//        }
//        if(fEmpty && count != 1)
//        {
//            page = 1;
//        }
    }
    else if(level == THREE)
    {
        fPass = Check_EP5_table_ByName(ui->ep5_tableWidget,0) &&
                Check_EP5_table_ByName(ui->ep5_tableWidget_2,1) &&
                Check_EP5_table_ByName(ui->ep5_tableWidget_3,2);

//        for(int i = 1; i < ui->ep5_tableWidget->rowCount(); i++)
//        {
//            for(int j = 2; j <= 5; j++)
//            {
//                if(ui->ep5_tableWidget->item(i,j)->text().isEmpty())
//                {
//                    fEmpty = true;
//                }
//            }
//        }
//        for(int i = 1; i < ui->ep5_tableWidget_2->rowCount(); i++)
//        {
//            for(int j = 2; j <= 5; j++)
//            {
//                if(ui->ep5_tableWidget_2->item(i,j)->text().isEmpty())
//                {
//                    fEmpty = true;
//                }
//            }
//        }

//        //表3
//        for(int i = 1; i < ui->ep5_tableWidget_3->rowCount(); i++)
//        {
//            for(int j = 2; j <= 5; j++)
//            {
//                if(ui->ep5_tableWidget_3->item(i,j)->text().isEmpty())
//                {
//                    fEmpty = true;
//                }
//            }
//        }
    }

    if(!fPass)   //不计算结果
    {
        QMessageBox msg;
        msg.setText(tr("无法提交数据，请完成数据录入"));

        msg.exec();
    }

    return fPass;
}

bool Pv_Precision::Check_EP5_table_ByName(QTableWidget *widget, int tableIndex)
{
    bool fPass = true;
    for(int i = 1; i < widget->rowCount(); i++)
    {
        for(int j = 2; j <= 5; j++)
        {
            if(widget->item(i,j)->text().isEmpty())
            {
                fPass = false;
            }
        }
    }

    if(tableIndex == 0)
    {
        page = 0;
    }
    else if(tableIndex == 1)
    {
        if(ep5Level == TWO)
        {
            if(fPass)
            {
                page = 0;
            }
            else
            {
                page = 1;
            }
        }
        else if(ep5Level == THREE)
        {
            if(!fPass)
                page = 1;
        }
    }
    else if(tableIndex == 2)
    {
        if(!fPass)
        {
            page = 2;
        }
    }

    ui->ep5_StackedWidget->setCurrentIndex(page);
    return fPass;
}

void Pv_Precision::Commit_Ep5_Table1()
{
    //获取数据
    indexMap record1Map;
    indexMap record2Map;

    for(int i = 1; i <= 20; i++)
    {
        record1Map[i][tr("Result1")] = ui->ep5_tableWidget->item(i,2)->text().toDouble();
        record1Map[i][tr("Result2")] = ui->ep5_tableWidget->item(i,3)->text().toDouble();

        record2Map[i][tr("Result1")] = ui->ep5_tableWidget->item(i,4)->text().toDouble();
        record2Map[i][tr("Result2")] = ui->ep5_tableWidget->item(i,5)->text().toDouble();
    }

    precision1.Set(record1Map,record2Map);//初始化
    QMap<int, double> aver1 = precision1.GetAverages(LEVEL1);
    QMap<int,double> aver2 = precision1.GetAverages(LEVEL2);
    precision1.checkOutliers();  //检测查离群值
    if(precision1.fOutliers) //判断是否有离群值
    {
        getOutliersIndex(precision1.outliers1,precision1.outliers2,outliersAxisVec1);//获取离群值坐标
        QMessageBox msgBox(QMessageBox::Warning,tr("警告"),tr("检测出有离群值,是否清除该离群值并重新统计？"),QMessageBox::Yes | QMessageBox::No);
        //            QPushButton *ButtonYES = msgBox.addButton(tr("是"),QMessageBox::AcceptRole);
        //            QPushButton *ButtonNO = msgBox.addButton(tr("否"),QMessageBox::AcceptRole);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes) //清除离群值
        {
            foreach (Axis<int> axis, outliersAxisVec1)
            {
                for(int i = 1; i <= 7; i++)
                {
                    ui->ep5_tableWidget->item(axis.x,i)->setText("");
                    if(i == 1 )
                    {
                        QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(axis.x,i));
                        label->setText("");
                    }
                }
                for(int i = 1; i <= 20; i++)
                {
                    QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,6));
                    label->setText("");

                    label = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,7));
                    label->setText("");
                }
                ui->ep5_Iner_Cv_Calculate_L1->setText("");
                ui->ep5_Cv_Calculate_L1->setText("");
            }
            precision1.fOutliers = false; //清除离群值标志
            return;
        }
        else if(ret == QMessageBox::No) //不计算直接返回
        {
            precision1.fOutliers = false; //清除离群值标志
            return;
        }
    }

    for(int i = 1; i < ui->ep5_tableWidget->rowCount(); i++)//设置平均值
    {
        //设置run1的平均值
        QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,6));
        label->setText(QString::number(aver1.value(i)));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //            QLabel *label3 = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,14));
        //            label3->setText(QString::number(aver1.value(i+10)));
        //            label3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        //设置run2的平均值
        QLabel *label2 = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,7));
        label2->setText(QString::number(aver2.value(i)));
        label2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //            QLabel *label4 = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,15));
        //            label4->setText(QString::number(aver2.value(i+10)));
        //            label4->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    double cv = precision1.GetSd()*100/precision1.GetTotalAverage();
    ui->ep5_Iner_Cv_Calculate_L1->setText(QString::number(cv,'f',2)+"%");   //设置精密度的值并保留小数点后两位

    double ccv = precision1.GetSt()*100/precision1.GetTotalAverage();
    ui->ep5_Cv_Calculate_L1->setText(QString::number(ccv,'f',2)+"%");
}

void Pv_Precision::Commit_Ep5_Table2()
{
    //获取数据
    indexMap record1Map;
    indexMap record2Map;

    for(int i = 1; i <= 20; i++)
    {
        record1Map[i][tr("Result1")] = ui->ep5_tableWidget_2->item(i,2)->text().toDouble();
        record1Map[i][tr("Result2")] = ui->ep5_tableWidget_2->item(i,3)->text().toDouble();

        record2Map[i][tr("Result1")] = ui->ep5_tableWidget_2->item(i,4)->text().toDouble();
        record2Map[i][tr("Result2")] = ui->ep5_tableWidget_2->item(i,5)->text().toDouble();
    }

    precision2.Set(record1Map,record2Map);//初始化
    QMap<int, double> aver1 = precision2.GetAverages(LEVEL1);
    QMap<int,double> aver2 = precision2.GetAverages(LEVEL2);
    precision2.checkOutliers();  //检测查离群值
    if(precision2.fOutliers) //判断是否有离群值
    {
        getOutliersIndex(precision2.outliers1,precision2.outliers2,outliersAxisVec2);//获取离群值坐标
        QMessageBox msgBox(QMessageBox::Warning,tr("警告"),tr("检测出有离群值,是否清除该离群值并重新统计？"),QMessageBox::Yes | QMessageBox::No);
        //            QPushButton *ButtonYES = msgBox.addButton(tr("是"),QMessageBox::AcceptRole);
        //            QPushButton *ButtonNO = msgBox.addButton(tr("否"),QMessageBox::AcceptRole);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes) //清除离群值
        {
            foreach (Axis<int> axis, outliersAxisVec2)
            {
                for(int i = 1; i <= 7; i++)
                {
                    ui->ep5_tableWidget_2->item(axis.x,i)->setText("");
                    if(i == 1 )
                    {
                        QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget_2->cellWidget(axis.x,i));
                        label->setText("");
                    }
                }
                for(int i = 1; i <= 20; i++)
                {
                    QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget_2->cellWidget(i,6));
                    label->setText("");

                    label = qobject_cast<QLabel*>(ui->ep5_tableWidget_2->cellWidget(i,7));
                    label->setText("");
                }
                ui->ep5_Cv_Calculate_L2->setText("");
                ui->ep5_Iner_Cv_Calculate_L2->setText("");
            }
            precision2.fOutliers = false; //清除离群值标志
            return;
        }
        else if(ret == QMessageBox::No) //不计算直接返回
        {
            precision2.fOutliers = false; //清除离群值标志
            return;
        }
    }

    for(int i = 1; i < ui->ep5_tableWidget_2->rowCount(); i++)//设置平均值
    {
        //设置run1的平均值
        QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget_2->cellWidget(i,6));
        label->setText(QString::number(aver1.value(i)));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //            QLabel *label3 = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,14));
        //            label3->setText(QString::number(aver1.value(i+10)));
        //            label3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        //设置run2的平均值
        QLabel *label2 = qobject_cast<QLabel*>(ui->ep5_tableWidget_2->cellWidget(i,7));
        label2->setText(QString::number(aver2.value(i)));
        label2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //            QLabel *label4 = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,15));
        //            label4->setText(QString::number(aver2.value(i+10)));
        //            label4->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    double cv = precision2.GetSd()*100/precision2.GetTotalAverage();
    ui->ep5_Iner_Cv_Calculate_L2->setText(QString::number(cv,'f',2)+"%");   //设置精密度的值并保留小数点后两位

    double ccv = precision2.GetSt()*100/precision2.GetTotalAverage();
    ui->ep5_Cv_Calculate_L2->setText(QString::number(ccv,'f',2)+"%");
}

void Pv_Precision::Commit_Ep5_Table3()
{
    //获取数据
    indexMap record1Map;
    indexMap record2Map;

    for(int i = 1; i <= 20; i++)
    {
        record1Map[i][tr("Result1")] = ui->ep5_tableWidget_3->item(i,2)->text().toDouble();
        record1Map[i][tr("Result2")] = ui->ep5_tableWidget_3->item(i,3)->text().toDouble();

        record2Map[i][tr("Result1")] = ui->ep5_tableWidget_3->item(i,4)->text().toDouble();
        record2Map[i][tr("Result2")] = ui->ep5_tableWidget_3->item(i,5)->text().toDouble();
    }

    precision3.Set(record1Map,record2Map);//初始化
    QMap<int, double> aver1 = precision3.GetAverages(LEVEL1);
    QMap<int,double> aver2 = precision3.GetAverages(LEVEL2);
    precision3.checkOutliers();  //检测查离群值
    if(precision3.fOutliers) //判断是否有离群值
    {
        getOutliersIndex(precision3.outliers1,precision3.outliers2,outliersAxisVec3);//获取离群值坐标
        QMessageBox msgBox(QMessageBox::Warning,tr("警告"),tr("检测出有离群值,是否清除该离群值并重新统计？"),QMessageBox::Yes | QMessageBox::No);
        //            QPushButton *ButtonYES = msgBox.addButton(tr("是"),QMessageBox::AcceptRole);
        //            QPushButton *ButtonNO = msgBox.addButton(tr("否"),QMessageBox::AcceptRole);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes) //清除离群值
        {
            foreach (Axis<int> axis, outliersAxisVec3)
            {
                for(int i = 1; i <= 7; i++)
                {
                    ui->ep5_tableWidget_3->item(axis.x,i)->setText("");
                    if(i == 1 )
                    {
                        QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget_3->cellWidget(axis.x,i));
                        label->setText("");
                    }
                }
                for(int i = 1; i <= 20; i++)
                {
                    QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget_3->cellWidget(i,6));
                    label->setText("");

                    label = qobject_cast<QLabel*>(ui->ep5_tableWidget_3->cellWidget(i,7));
                    label->setText("");
                }
                ui->ep5_Iner_Cv_Calculate_L3->setText("");
                ui->ep5_Cv_Calculate_L3->setText("");
            }
            precision3.fOutliers = false; //清除离群值标志
            return;
        }
        else if(ret == QMessageBox::No) //不计算直接返回
        {
            precision3.fOutliers = false; //清除离群值标志
            return;
        }
    }

    for(int i = 1; i < ui->ep5_tableWidget_3->rowCount(); i++)//设置平均值
    {
        //设置run1的平均值
        QLabel *label = qobject_cast<QLabel*>(ui->ep5_tableWidget_3->cellWidget(i,6));
        label->setText(QString::number(aver1.value(i)));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //            QLabel *label3 = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,14));
        //            label3->setText(QString::number(aver1.value(i+10)));
        //            label3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        //设置run2的平均值
        QLabel *label2 = qobject_cast<QLabel*>(ui->ep5_tableWidget_3->cellWidget(i,7));
        label2->setText(QString::number(aver2.value(i)));
        label2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //            QLabel *label4 = qobject_cast<QLabel*>(ui->ep5_tableWidget->cellWidget(i,15));
        //            label4->setText(QString::number(aver2.value(i+10)));
        //            label4->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    double cv = precision3.GetSd()*100/precision3.GetTotalAverage();
    ui->ep5_Iner_Cv_Calculate_L3->setText(QString::number(cv,'f',2)+"%");   //设置精密度的值并保留小数点后两位

    double ccv = precision3.GetSt()*100/precision3.GetTotalAverage();
    ui->ep5_Cv_Calculate_L3->setText(QString::number(ccv,'f',2)+"%");
}

void Pv_Precision::Commit_Ep15_L1()
{
    RCS_Map map;
    for(int i = 2; i <= 4; i++)
    {
        for(int j = 2; j <= 6; j++)
        {
            map[QString("x%1").arg(i-1)][QString("batch%1").arg(j-1)] = ui->ep15_tableWidget->item(i,j)->text().toDouble();
        }
    }
    ep15Precision1.Set(map,LEVEL1);

    ui->ep15_Calculate_L1_Iner_Cv->setText(QString::number(ep15Precision1.GetSr(LEVEL1),'f',2));
    ui->ep15_Calculate_L1_Cv->setText(QString::number(ep15Precision1.GetSrr(LEVEL1),'f',2));
}

void Pv_Precision::Commit_Ep15_L2()
{
    RCS_Map map;
    for(int i = 5; i <= 8; i++)
    {
        for(int j = 2; j <= 6; j++)
        {
            map[QString("x%1").arg(i-4)][QString("batch%1").arg(j-1)] = ui->ep15_tableWidget->item(i,j)->text().toDouble();
        }
    }
    ep15Precision2.Set(map,LEVEL2);

    ui->ep15_Calculate_L2_Iner_Cv->setText(QString::number(ep15Precision2.GetSr(LEVEL2),'f',2));
    ui->ep15_Calculate_L2_Cv->setText(QString::number(ep15Precision2.GetSrr(LEVEL2),'f',2));
}

void Pv_Precision::Commit_Ep15_L3()
{
    RCS_Map map;
    for(int i = 9; i <= 12; i++)
    {
        for(int j = 2; j <= 6; j++)
        {
            map[QString("x%1").arg(i-8)][QString("batch%1").arg(j-1)] = ui->ep15_tableWidget->item(i,j)->text().toDouble();
        }
    }
    ep15Precision3.Set(map,LEVEL3);
    ui->ep15_Calculate_L3_Iner_Cv->setText(QString::number(ep15Precision3.GetSr(LEVEL3),'f',2));
    ui->ep15_Calculate_L3_Cv->setText(QString::number(ep15Precision3.GetSrr(LEVEL3),'f',2));
}

bool Pv_Precision::check(QString prefix, QString filter)
{
    bool fPass = true;
    QList<QLineEdit*> list = findChildren<QLineEdit*>();

    if(filter.isEmpty())
        filter = "@@@@@";

    if(prefix == "ep5")
    {
        if(ep5Level == TWO)
        {
            foreach (QLineEdit *lineEdit, list) {
                if(lineEdit->objectName().contains(prefix) && !lineEdit->objectName().contains(filter) && !lineEdit->objectName().contains("_L3") && lineEdit->text().isEmpty())
                {
                    lineEdit->setStyleSheet(warningStyle);
                    fPass = false;
                }
            }
        }
        else
        {
            foreach (QLineEdit *lineEdit, list) {
                if(lineEdit->objectName().contains(prefix) && !lineEdit->objectName().contains(filter) && lineEdit->text().isEmpty())
                {
                    lineEdit->setStyleSheet(warningStyle);
                    fPass = false;
                }
            }
        }
    }
    else if(prefix == "Westgard")
    {
        if(westgardLevel == TWO)
        {
            foreach (QLineEdit *lineEdit, list) {
                if(lineEdit->objectName().contains(prefix) && !lineEdit->objectName().contains(filter) && !lineEdit->objectName().contains("_L3") && lineEdit->text().isEmpty())
                {
                    lineEdit->setStyleSheet(warningStyle);
                    fPass = false;
                }
            }
        }
        else
        {
            foreach (QLineEdit *lineEdit, list) {
                if(lineEdit->objectName().contains(prefix) && !lineEdit->objectName().contains(filter) && lineEdit->text().isEmpty())
                {
                    lineEdit->setStyleSheet(warningStyle);
                    fPass = false;
                }
            }
        }
    }
    else if(prefix == "ep15")
    {
        if(ep15Level == TWO)
        {
            foreach (QLineEdit *lineEdit, list) {
                if(lineEdit->objectName().contains(prefix) && !lineEdit->objectName().contains(filter) && !lineEdit->objectName().contains("_L3") && lineEdit->text().isEmpty())
                {
                    lineEdit->setStyleSheet(warningStyle);
                    fPass = false;
                }
            }
        }
        else
        {
            foreach (QLineEdit *lineEdit, list) {
                if(lineEdit->objectName().contains(prefix) && !lineEdit->objectName().contains(filter) && lineEdit->text().isEmpty())
                {
                    lineEdit->setStyleSheet(warningStyle);
                    fPass = false;
                }
            }
        }
    }

    return fPass;
}

void Pv_Precision::setStyle(const QString method, const QString &lineEditStyle, const QString &dateEditStyle, bool fConnent)
{
    //设置CSS样式
    QList<QLineEdit*> list = findChildren<QLineEdit*>();
    QList<QDateEdit*> dList = findChildren<QDateEdit*>();
    if( method.contains("All") || method.contains(""))
    {
        foreach (QDateEdit* dateEdit, dList) {
           dateEdit->setStyleSheet(dateEditStyle);
        }
        foreach (QLineEdit *lineEdit, list) {
            lineEdit->setStyleSheet(lineEditStyle);
            if(fConnent)
            {
                connect(lineEdit,SIGNAL(textChanged(QString)),this,SLOT(_textChanged(QString)));
            }
        }
    }
    else
    {

        foreach (QDateEdit* dateEdit, dList) {
            QString obj_name = dateEdit->objectName();
            if( obj_name.contains(method) )
                dateEdit->setStyleSheet(dateEditStyle);
        }
        foreach (QLineEdit *lineEdit, list) {
            QString obj_name = lineEdit->objectName();
            if( obj_name.contains(method) )
            {
                lineEdit->setStyleSheet(lineEditStyle);
                if(fConnent)
                {
                    connect(lineEdit,SIGNAL(textChanged(QString)),this,SLOT(_textChanged(QString)));
                }
            }
        }
    }
}

void Pv_Precision::ShowMenu()
{
    QPoint pos;
    QMenu menu(ui->ep5_tableWidget);
    QIcon myIcon("://images/add.gif");
    QAction *copyAction = menu.addAction(myIcon,tr("复制"));
    QAction *cutAction = menu.addAction(myIcon,tr("剪切"));
    QAction *pasteAction = menu.addAction(myIcon,tr("粘贴"));
    QAction *clearAction = menu.addAction(myIcon,tr("清空"));

    menu.exec(QCursor::pos());
}

void Pv_Precision::showWarning(QString text)
{
    QMessageBox* box = new QMessageBox;
    QTimer::singleShot(5000, box, SLOT(close()));
    QApplication::beep();
    box->setWindowTitle(tr("警告"));
    box->setIcon(QMessageBox::Warning);
    box->setText(text);
    box->addButton(tr("是(&Y)"), QMessageBox::YesRole);
    box->show();
}

void Pv_Precision::showInformation(QString text)
{
    QMessageBox* box = new QMessageBox;
    QTimer::singleShot(5000, box, SLOT(close()));

    box->setWindowTitle(tr(""));
    box->setIcon(QMessageBox::Information);
    box->setText(text);
    box->addButton(tr("是(&Y)"), QMessageBox::YesRole);
    box->show();
}
