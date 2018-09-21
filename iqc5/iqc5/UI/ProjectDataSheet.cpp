#include "ProjectDataSheet.h"
#include "ui_ProjectDataSheet.h"

#include <ProjectService.h>
#include <DataSheetService.h>
#include "ExportData.h"

#include <QDebug>


ProjectDataSheet::ProjectDataSheet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectDataSheet)
{
    ui->setupUi(this);

    initProject();

}

ProjectDataSheet::~ProjectDataSheet()
{
    delete ui;
}

void ProjectDataSheet::initProject()
{
    ProjectService *service;
    service = new ProjectService();
    QString keyword = ui->inputKeyword->text();

    ui->treeWidget->clear();

    QVector<Project> projects =  service->SearchProject("","",keyword,"");

    if(projects.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<projects[0].testType.SubjectName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* ca2 = new QTreeWidgetItem(QStringList()<<projects[0].testType.CategoryName);
        ca2->setToolTip(0, projects[0].testType.CategoryId);
        ca->addChild(ca2);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<projects[0].CustomName);
        pItem->setToolTip(0, QString("%1").arg(projects[0].ProjectId));
        ca2->addChild(pItem);

        for(int i=1;i<projects.count();i++)
        {
            if(QString::compare(projects[i].testType.SubjectName, projects[i-1].testType.SubjectName) != 0)
            {
                ca = new QTreeWidgetItem(QStringList()<<projects[i].testType.SubjectName);
                ui->treeWidget->addTopLevelItem(ca);
            }

            if(QString::compare(projects[i].testType.CategoryName, projects[i-1].testType.CategoryName) != 0)
            {
                ca2 = new QTreeWidgetItem(QStringList()<<projects[i].testType.CategoryName);
                ca2->setToolTip(0, projects[i].testType.CategoryId);
                ca->addChild(ca2);
            }

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<projects[i].CustomName);
            pItem->setToolTip(0, QString("%1").arg(projects[i].ProjectId));
            ca2->addChild(pItem);
        }
    }

    ui->treeWidget->expandAll();
}

void ProjectDataSheet::initTableWidget()
{
    ui->tableWidget->clear();

    QStringList headerLabels;
    headerLabels << tr("英文名称") << tr("中文名称") << tr("专业") << tr("亚专业") << tr("浓度") << tr("检测次数") << tr("质控品") << tr("质控品批号") << tr("试剂") << tr("试剂批号") << tr("方法") << tr("仪器") << tr("结果") << tr("日期");
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);

    ui->tableWidget->setRowCount(0);
}

void ProjectDataSheet::showProjectDetail()
{



    initTableWidget();

    ProjectService *service;
    service = new ProjectService();
    if (ui->treeWidget->currentItem() == NULL)
    {
        return;
    }
    QString projectId = ui->treeWidget->currentItem()->toolTip(0);
    currentProject = service->GetById(projectId);

    QVector<DataSheet> allData;
    DataSheetService ds;
    allData = ds.GetDetail(currentProject.ProjectId);
    for (int i = 0; i < allData.size(); i++)
    {
        ui->tableWidget->insertRow(i);
        //中文名
        QTableWidgetItem *item0 = new QTableWidgetItem(allData.at(i).englishName);
        item0->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,0,item0);

        //英文名
        QTableWidgetItem *item1 = new QTableWidgetItem(allData.at(i).chineseName);
        item1->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,1,item1);

        //专业
        QTableWidgetItem *item2 = new QTableWidgetItem(allData.at(i).categoryName);
        item2->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,2,item2);

        //亚专业
        QTableWidgetItem *item3 = new QTableWidgetItem(allData.at(i).subCategoryName);
        item3->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,3,item3);

        //浓度
        QTableWidgetItem *item4 = new QTableWidgetItem(allData.at(i).densityId);
        item4->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,4,item4);

        //检测次数
        QTableWidgetItem *item5 = new QTableWidgetItem(allData.at(i).testNum);
        item5->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,5,item5);

        //质控品
        QTableWidgetItem *item6 = new QTableWidgetItem(allData.at(i).materialName);
        item6->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,6,item6);

        //质控品批号
        QTableWidgetItem *item7 = new QTableWidgetItem(allData.at(i).materialBatchNo);
        item7->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,7,item7);

        //试剂
        QTableWidgetItem *item8 = new QTableWidgetItem(allData.at(i).reagentName);
        item8->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,8,item8);

        //试剂批号
        QTableWidgetItem *item9 = new QTableWidgetItem(allData.at(i).reagentBatchNo);
        item9->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,9,item9);

        //方法
        QTableWidgetItem *item10 = new QTableWidgetItem(allData.at(i).methodName);
        item10->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,10,item10);

        //仪器
        QTableWidgetItem *item11 = new QTableWidgetItem(allData.at(i).deviceName);
        item11->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,11,item11);

        //结果
        QTableWidgetItem *item12 = new QTableWidgetItem(allData.at(i).resultValue);
        item12->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,12,item12);

        //日期
        QTableWidgetItem *item13 = new QTableWidgetItem(allData.at(i).testTime);
        item13->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i,13,item13);
    }
}

void ProjectDataSheet::on_export_Btn_clicked()
{
    ExportData *widget = new ExportData;
    widget->setWindowModality(Qt::ApplicationModal);
    widget->show();
}

void ProjectDataSheet::on_close_Btn_clicked()
{
    this->close();
}

void ProjectDataSheet::on_inputKeyword_textChanged(const QString &arg1)
{
    initProject();
}

void ProjectDataSheet::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    showProjectDetail();
}

void ProjectDataSheet::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    showProjectDetail();
}
