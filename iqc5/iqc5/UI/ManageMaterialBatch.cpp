#include "ManageMaterialBatch.h"
#include "ui_ManageMaterialBatch.h"
#include "Model/Manufacturer.h"
#include "Model/Material.h"
#include "Service/ManufacturerService.h"
#include "Service/MaterialService.h"
#include "Service/MaterialBatchService.h"
#include "UI/EditMaterial.h"
#include <QDebug>
#include <QDateEdit>
#include <QMessageBox>
#include "MainWindow.h"

ManageMaterialBatch::ManageMaterialBatch(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageMaterialBatch)
{
    ui->setupUi(this);

    ui->btnAdd->setIcon(QIcon("images/add.gif"));
    ui->btnDelete->setIcon(QIcon("images/delete.gif"));

    InitTree();

    ui->table->setColumnCount(4);
    QStringList headers;
    headers << tr("BatchId") << tr("批号")<< tr("有效期")<< tr("启用日期");
    ui->table->setHorizontalHeaderLabels(headers);
    ui->table->setColumnHidden(0, true);

}

void ManageMaterialBatch::InitTree()
{
    ManufacturerService *manufacturerService; manufacturerService = new ManufacturerService();
    MaterialService *materialService; materialService = new MaterialService();
    QString keyword = ui->inputKeyword->text();

    ui->treeWidget->clear();

    QVector<Manufacturer> manufacturers = manufacturerService->GetManufacturers(keyword);

    for(int i=0;i<manufacturers.count();i++)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(QStringList()<<manufacturers[i].ManufacturerName);
        item->setToolTip(0, QString("%1").arg(manufacturers[i].ManufacturerId));
        ui->treeWidget->addTopLevelItem(item);

        QVector<Material> materials = materialService->GetMaterialsByManufacturerId(manufacturers[i].ManufacturerId);

        for(int j=0;j<materials.count();j++)
        {
            QTreeWidgetItem* item2 = new QTreeWidgetItem(QStringList()<<materials[j].MaterialName);
            item2->setToolTip(0, QString("%1").arg(materials[j].MaterialId));

            item->addChild(item2);
        }
    }
    ui->treeWidget->expandAll();
}

void ManageMaterialBatch::ShowAllData()
{

}


void ManageMaterialBatch::OnBtnTableEditClicked()
{

}

void ManageMaterialBatch::OnBtnTableDeleteClicked()
{

}

void ManageMaterialBatch::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    this->ShowAllData();
}

void ManageMaterialBatch::on_pushButton_clicked()
{
    this->ShowAllData();
}

void ManageMaterialBatch::on_inputKeyword_textChanged(const QString &arg1)
{

    InitTree();
}

ManageMaterialBatch::~ManageMaterialBatch()
{
    delete ui;
}

void ManageMaterialBatch::initRow(QTableWidget *table, int row, MaterialBatch *model)
{
    if(table->cellWidget(row,0)==NULL) //ID
    {
        QLineEdit *control = new QLineEdit();
        if(model != NULL)
        {
            control->setText(model->MaterialBatchId);
        }
        table->setCellWidget(row, 0, control);
    }

    if(table->cellWidget(row,1)==NULL) //批号
    {
        QLineEdit *control = new QLineEdit();
        if(model != NULL)
        {
            control->setText(model->BatchNo);
        }
        table->setCellWidget(row, 1, control);
    }
    if(table->item(row,2) == NULL) //有效期
    {
        QDateEdit *control = new QDateEdit();
        control->setCalendarPopup(true);
        if(model != NULL)
        {
            control->setDate(QDate::fromString(model->ValidDate,"yyyy-MM-dd"));
        }
        table->setCellWidget(row, 2, control);
    }
    if(table->item(row,3) == NULL) //启用日期
    {
        QLineEdit *control = new QLineEdit();
        control->setEnabled(false);
        if(model != NULL)
        {
            control->setText(model->StartDate);
        }
        table->setCellWidget(row, 3, control);
    }

}

void ManageMaterialBatch::InitTable()
{
    MaterialBatchService service;
    QVector<MaterialBatch> batchs = service.GetMaterialBatchs(currentMaterialId,"");
    ui->table->setRowCount(batchs.count());
    for(int i=0; i<batchs.count();i++)
    {
        initRow(ui->table, i, &batchs[i]);
    }
}
void ManageMaterialBatch::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item->childCount() == 0)
    {
        currentMaterialId = item->toolTip(0);
        InitTable();
    }
}

void ManageMaterialBatch::on_btnAdd_clicked()
{
    if(QString::compare(currentMaterialId, "") != 0)
    {
        int row = ui->table->rowCount();
        ui->table->setRowCount(row+1);
        initRow(ui->table, row, NULL);
    }
}

void ManageMaterialBatch::on_btnDelete_clicked()
{
    int row = ui->table->rowCount();
    if(row > 0)
    {
        ui->table->setRowCount(row-1);
    }
}

void ManageMaterialBatch::on_btnSave_clicked()
{
    for(int row=0; row<ui->table->rowCount();row++)
    {
        MaterialBatchService service;
        MaterialBatch m;
        m.MaterialId = currentMaterialId;
        m.MaterialBatchId = ((QLineEdit*)ui->table->cellWidget(row,0))->text();
        m.BatchNo = ((QLineEdit*)ui->table->cellWidget(row,1))->text();
        m.ValidDate = ((QDateEdit*)ui->table->cellWidget(row,2))->date().toString("yyyy-MM-dd");
        m.StartDate = ((QLineEdit*)ui->table->cellWidget(row,3))->text();

        if(QString::compare(m.MaterialBatchId, "") == 0)
        {
            service.Insert(m);
        }
        else
        {
            service.Update(m);
        }
    }
    InitTable();
    QMessageBox::information(this, tr("信息") , "保存成功");
}

void ManageMaterialBatch::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}
