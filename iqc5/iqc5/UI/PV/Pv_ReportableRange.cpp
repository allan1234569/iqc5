#include "Pv_ReportableRange.h"
#include "ui_Pv_ReportableRange.h"
#include "MainWindow.h"
#include <QDebug>
#include <QDesktopWidget>

Pv_ReportableRange::Pv_ReportableRange(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pv_ReportableRange)
{
    ui->setupUi(this);
    setWindowTitle(tr("可报告范围实验"));
    showTable();
//    setFixedSize(QApplication::desktop()->width(),QApplication::desktop()->height());//设置屏幕大小
}

void Pv_ReportableRange::showTable()
{
    //初始化试剂表格
    ui->RI_Reagen_TableWidget->setColumnCount(3);
    ui->RI_Reagen_TableWidget->setRowCount(11);

    //设置行高
    for(int i = 0; i < 11; i++)
    {
        ui->RI_Reagen_TableWidget->setRowHeight(i,38);
    }
    //设置列宽

    ui->RI_Reagen_TableWidget->setColumnWidth(0,215);
    ui->RI_Reagen_TableWidget->setColumnWidth(1,215);
    ui->RI_Reagen_TableWidget->setColumnWidth(2,215);

    ui->RI_Reagen_TableWidget->horizontalHeader()->setVisible(false);
    ui->RI_Reagen_TableWidget->verticalHeader()->setVisible(false);

    for(int i = 1; i < 11; i++)
    {
        for(int j = 1; j < 3; j++)
        {
            ui->RI_Reagen_TableWidget->setItem(i,j,new QTableWidgetItem());
            ui->RI_Reagen_TableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }

    QLabel *label_1 = new QLabel(tr("试剂"));
    label_1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Reagen_TableWidget->setCellWidget(0,0,label_1);

    QLabel *label_2 = new QLabel(tr("批号"));
    label_2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Reagen_TableWidget->setCellWidget(0,1,label_2);

    QLabel *label_3 = new QLabel(tr("有效期"));
    label_3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Reagen_TableWidget->setCellWidget(0,2,label_3);

    QStringList list;
    list << tr("校准品") << tr("质控品") << tr("试剂盒") << tr("触发液") << tr("预触发液") << tr("洗涤缓冲液") << tr("RV") << tr("校验稀释液") << tr("多检验人工稀释液") << tr("MasterCheck");
    for(int i = 0; i < 10; i++)
    {
        QLabel *label = new QLabel(list.at(i));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->RI_Reagen_TableWidget->setCellWidget(i+1,0,label);
    }

    //初始化数据记录表格
    ui->RI_Date_TableWidget->setColumnCount(6);
    ui->RI_Date_TableWidget->setRowCount(7);

    ui->RI_Date_TableWidget->horizontalHeader()->setVisible(false);
    ui->RI_Date_TableWidget->verticalHeader()->setVisible(false);

    for(int i =  0; i < 6; i++)
    {
        ui->RI_Date_TableWidget->setColumnWidth(i,107);
    }
    for(int i = 0; i <  7; i++)
    {
        ui->RI_Date_TableWidget->setRowHeight(i,59);
    }

    ui->RI_Date_TableWidget->setSpan(0,0,2,1);
    ui->RI_Date_TableWidget->setSpan(0,1,2,1);
    ui->RI_Date_TableWidget->setSpan(0,2,2,1);
    ui->RI_Date_TableWidget->setSpan(0,5,2,1);

    ui->RI_Date_TableWidget->setCellWidget(0,0,new QLabel());

    QLabel *label1 = new QLabel(tr("1"));
    label1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(2,0,label1);

    QLabel *label2 = new QLabel(tr("2"));
    label2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(3,0,label2);

    QLabel *label3 = new QLabel(tr("4"));
    label3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(4,0,label3);

    QLabel *label4 = new QLabel(tr("4"));
    label4->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(5,0,label4);

    QLabel *label5 = new QLabel(tr("4"));
    label5->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(6,0,label5);

    QLabel *label6 = new QLabel(tr("MasterCheck值"));
    label6->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(0,1,label6);

    QLabel *label7 = new QLabel(tr("预期值"));
    label7->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(0,2,label7);

    QLabel *label8 = new QLabel(tr("公差下限 "));
    label8->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(0,3,label8);

    QLabel *label9 = new QLabel(tr("公差上限"));
    label9->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(0,4,label9);

    QLabel *label10 = new QLabel(tr("平均检验值"));
    label10->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(0,5,label10);

    QLabel *label11 = new QLabel(tr("-%"));
    label11->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(1,3,label11);

    QLabel *label12 = new QLabel(tr("+%"));
    label12->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(1,4,label12);

    QLabel *label13 = new QLabel(tr("水平0"));
    label13->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(2,1,label13);

    QLabel *label14 = new QLabel(tr("水平2"));
    label14->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(3,1,label14);

    QLabel *label15 = new QLabel(tr("水平3"));
    label15->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(4,1,label15);

    QLabel *label16 = new QLabel(tr("水平4"));
    label16->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(5,1,label16);

    QLabel *label17 = new QLabel(tr("水平5"));
    label17->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->RI_Date_TableWidget->setCellWidget(6,1,label17);

    for(int i = 2; i < 7; i ++)
    {
        for(int j = 2; j < 6; j++)
        {
            ui->RI_Date_TableWidget->setItem(i,j,new QTableWidgetItem());
            ui->RI_Date_TableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }

}

Pv_ReportableRange::~Pv_ReportableRange()
{
    delete ui;
}

void Pv_ReportableRange::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}
