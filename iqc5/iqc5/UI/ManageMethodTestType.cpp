#include "ManageMethodTestType.h"
#include "ui_ManageMethodTestType.h"
#include "Model/Method.h"
#include "Service/MethodService.h"
#include "Service/CategoryService.h"
#include "Service/TestTypeService.h"
#include "UI/ManageMethod.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include "MainWindow.h"

ManageMethodTestType::ManageMethodTestType(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageMethodTestType)
{
    ui->setupUi(this);

     InitTree();
     //InitTestTypeTree();
}


void ManageMethodTestType::InitTree()
{
    MethodService *service;service = new MethodService();

    ui->treeWidget->clear();

    QVector<Method> models =  service->GetMethods("","",ui->inputKeyword->text(),0);

    if(models.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<models[0].SubjectName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* ca2 = new QTreeWidgetItem(QStringList()<<models[0].CategoryName);
        ca->addChild(ca2);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[0].MethodName);
        pItem->setToolTip(0, QString("%1").arg(models[0].MethodId));
        ca2->addChild(pItem);

        for(int i=1;i<models.count();i++)
        {
            if(QString::compare(models[i].SubjectName, models[i-1].SubjectName) != 0)
            {
                ca = new QTreeWidgetItem(QStringList()<<models[i].SubjectName);
                ui->treeWidget->addTopLevelItem(ca);
            }

            if(QString::compare(models[i].CategoryName, models[i-1].CategoryName) != 0)
            {
                ca2 = new QTreeWidgetItem(QStringList()<<models[i].CategoryName);
                ca->addChild(ca2);
            }

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[i].MethodName);
            pItem->setToolTip(0, QString("%1").arg(models[i].MethodId));
            ca2->addChild(pItem);
        }

    }
    ui->treeWidget->expandAll();

}

void ManageMethodTestType::InitTestTypeTree()
{
    TestTypeService *service;service = new TestTypeService();

    ui->treeWidget_2->clear();
    QString methodId = ui->treeWidget->currentItem()->toolTip(0);
    QVector<TestType> models = service->GetTestTypesWithMethodChecked(methodId);
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

void ManageMethodTestType::Save()
{
    Method m;
    m.MethodId=ui->treeWidget->currentItem()->toolTip(0);
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


    MethodService service;
    service.UpdateTestType(m);

    QMessageBox::information(this, tr("信息"),tr("保存成功"));
    //((ManageMethod *)(this->parent()))->ShowAllData();
    //this->close();
}

ManageMethodTestType::~ManageMethodTestType()
{
    delete ui;
}

void ManageMethodTestType::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item->childCount() == 0)
    {
        this->InitTestTypeTree();
    }
}

void ManageMethodTestType::on_btnSave_clicked()
{
    Save();
}

void ManageMethodTestType::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}
