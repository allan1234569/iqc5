#include "ManageMaterialTestType.h"
#include "ui_ManageMaterialTestType.h"
#include "Model/Material.h"
#include "Service/MaterialService.h"
#include "Service/CategoryService.h"
#include "Service/TestTypeService.h"
#include "UI/ManageMaterial.h"
#include <QDebug>
#include <QMessageBox>
#include "MainWindow.h"

ManageMaterialTestType::ManageMaterialTestType(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageMaterialTestType)
{
    ui->setupUi(this);

     InitTree();
     //InitTestTypeTree();
}


void ManageMaterialTestType::InitTree()
{
    MaterialService *service;service = new MaterialService();
    QString keyword = ui->inputKeyword->text();

    ui->treeWidget->clear();

    QVector<Material> models = service->GetMaterials("","", keyword, "","",0);

    if(models.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<models[0].ManufacturerName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[0].MaterialName);
        pItem->setToolTip(0, QString("%1").arg(models[0].MaterialId));
        ca->addChild(pItem);

        for(int i=1;i<models.count();i++)
        {
            if(QString::compare(models[i].ManufacturerName, models[i-1].ManufacturerName) != 0)
            {
                ca = new QTreeWidgetItem(QStringList()<<models[i].ManufacturerName);
                ui->treeWidget->addTopLevelItem(ca);
            }

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[i].MaterialName);
            pItem->setToolTip(0, QString("%1").arg(models[i].MaterialId));
            ca->addChild(pItem);
        }
    }
    ui->treeWidget->expandAll();

}

void ManageMaterialTestType::InitTestTypeTree()
{
    TestTypeService *service;service = new TestTypeService();

    ui->treeWidget_2->clear();

    QVector<TestType> models = service->GetTestTypesWithMaterialChecked(ui->treeWidget->currentItem()->toolTip(0));

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

void ManageMaterialTestType::Save()
{
    Material m;
    m.MaterialId=ui->treeWidget->currentItem()->toolTip(0);
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


    MaterialService service;
    service.UpdateTestType(m);

    QMessageBox::information(this, tr("信息"),tr("保存成功"));
    //((ManageMaterial *)(this->parent()))->ShowAllData();
    //this->close();
}

ManageMaterialTestType::~ManageMaterialTestType()
{
    delete ui;
}

void ManageMaterialTestType::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item->childCount() == 0)
    {
        this->InitTestTypeTree();
    }
}

void ManageMaterialTestType::on_btnSave_clicked()
{
    Save();
}

void ManageMaterialTestType::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}
