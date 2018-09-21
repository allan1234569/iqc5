

#include "ManageReagentTestType.h"
#include "ui_ManageReagentTestType.h"
#include "Model/Reagent.h"
#include "Service/ReagentService.h"
#include "Service/CategoryService.h"
#include "Service/TestTypeService.h"
#include "UI/ManageReagent.h"
#include <QDebug>
#include <QMessageBox>
#include "MainWindow.h"

ManageReagentTestType::ManageReagentTestType(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageReagentTestType)
{
    ui->setupUi(this);

     InitTree();
     //InitTestTypeTree();
}


void ManageReagentTestType::InitTree()
{
    ReagentService *service;service = new ReagentService();
    QString keyword = ui->inputKeyword->text();

    ui->treeWidget->clear();

    QVector<Reagent> models = service->GetReagents("","", keyword, "","",0);

    if(models.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<models[0].ManufacturerName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[0].ReagentName);
        pItem->setToolTip(0, QString("%1").arg(models[0].ReagentId));
        ca->addChild(pItem);

        for(int i=1;i<models.count();i++)
        {
            if(QString::compare(models[i].ManufacturerName, models[i-1].ManufacturerName) != 0)
            {
                ca = new QTreeWidgetItem(QStringList()<<models[i].ManufacturerName);
                ui->treeWidget->addTopLevelItem(ca);
            }

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[i].ReagentName);
            pItem->setToolTip(0, QString("%1").arg(models[i].ReagentId));
            ca->addChild(pItem);
        }
    }
    ui->treeWidget->expandAll();

}

void ManageReagentTestType::InitTestTypeTree()
{
    QString keyTestType = ui->input2->text();
    TestTypeService *service;service = new TestTypeService();

    ui->treeWidget_2->clear();

    QVector<TestType> models = service->GetTestTypesWithReagentChecked(ui->treeWidget->currentItem()->toolTip(0), keyTestType);

    if(models.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<models[0].SubjectName);
        ui->treeWidget_2->addTopLevelItem(ca);
        QTreeWidgetItem* ca2 = new QTreeWidgetItem(QStringList()<<models[0].CategoryName);
        ca->addChild(ca2);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[0].TestTypeCode);
        pItem->setToolTip(0, QString("%1").arg(models[0].TestTypeId));
        if(models[0].flag ==1)
        {
            pItem->setCheckState(0,Qt::Checked);
        }
        else
        {
            pItem->setCheckState(0,Qt::Unchecked);
        }
        ca2->addChild(pItem);

        for(int i=1;i<models.count();i++)
        {
            if(QString::compare(models[i].SubjectName, models[i-1].SubjectName) != 0)
            {
                ca = new QTreeWidgetItem(QStringList()<<models[i].SubjectName);
                ui->treeWidget_2->addTopLevelItem(ca);
            }

            if(QString::compare(models[i].CategoryName, models[i-1].CategoryName) != 0)
            {
                ca2 = new QTreeWidgetItem(QStringList()<<models[i].CategoryName);
                ca->addChild(ca2);
            }

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[i].TestTypeCode);
            pItem->setToolTip(0, QString("%1").arg(models[i].TestTypeId));
            if(models[i].flag >=1)
            {
                pItem->setCheckState(0,Qt::Checked);
            }
            else
            {
                pItem->setCheckState(0,Qt::Unchecked);
            }

            ca2->addChild(pItem);
        }

    }
    ui->treeWidget_2->expandAll();

}

void ManageReagentTestType::Save()
{
    Reagent m;
    m.ReagentId=ui->treeWidget->currentItem()->toolTip(0);
    QTreeWidgetItemIterator it(ui->treeWidget_2);
    while (*it)
    {
        QTreeWidgetItem* item = *it;
        if(item->checkState(0) == Qt::Checked)
        {
            TestType t;
            t.TestTypeId =item->toolTip(0);
            m.types.append(t);
        }

        ++it;
    }


    ReagentService service;
    service.UpdateTestType(m);

    QMessageBox::information(this, tr("信息"),tr("保存成功"));
    //((ManageReagent *)(this->parent()))->ShowAllData();
    //this->close();
}

ManageReagentTestType::~ManageReagentTestType()
{
    delete ui;
}

void ManageReagentTestType::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item->childCount() == 0)
    {
        this->InitTestTypeTree();
    }
}

void ManageReagentTestType::on_btnSave_clicked()
{
    Save();
}

void ManageReagentTestType::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}

void ManageReagentTestType::on_input2_textChanged(const QString &arg1)
{
    InitTestTypeTree();
}
