#include "ManageDevice.h"
#include "ui_ManageDevice.h"
#include "Model/Device.h"
#include "Service/DeviceService.h"
#include "UI/EditDevice.h"
#include <QDebug>
#include <QMessageBox>
#include "Model/Category.h"
#include "Service/BrandService.h"
#include "Service/ModelService.h"
#include "MainWindow.h"

ManageDevice::ManageDevice(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageDevice)
{
    ui->setupUi(this);


    QString keyword = ui->inputKeyword->text();
    SearchTree(keyword);

}

void ManageDevice::SearchTree(QString name)
{
    DeviceService *service;service = new DeviceService();

    ui->treeWidget->clear();

    QVector<Device> devices =  service->GetAll("","",name,0);

    if(devices.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<devices[0].BrandName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* ca2 = new QTreeWidgetItem(QStringList()<<devices[0].ModelName);
        ca->addChild(ca2);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<devices[0].DeviceName);
        pItem->setToolTip(0, QString("%1").arg(devices[0].DeviceId));
        ca2->addChild(pItem);

        for(int i=1;i<devices.count();i++)
        {
            if(QString::compare(devices[i].BrandName, devices[i-1].BrandName) != 0)
            {
                ca = new QTreeWidgetItem(QStringList()<<devices[i].BrandName);
                ui->treeWidget->addTopLevelItem(ca);
            }

            if(QString::compare(devices[i].ModelName, devices[i-1].ModelName) != 0)
            {
                ca2 = new QTreeWidgetItem(QStringList()<<devices[i].ModelName);
                ca->addChild(ca2);
            }

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<devices[i].DeviceName);
            pItem->setToolTip(0, QString("%1").arg(devices[i].DeviceId));
            ca2->addChild(pItem);
        }

    }
    ui->treeWidget->expandAll();

    //this->ShowAllData();
}

ManageDevice::~ManageDevice()
{
    delete ui;
}

void ManageDevice::ShowAllData()
{
    if (ui->treeWidget->currentItem() != NULL)
    {
        ShowAllData(ui->treeWidget->currentItem()->toolTip(0), ui->inputKeyword->text());
    }
    else
    {
        ShowAllData("", ui->inputKeyword->text());
    }

}

void ManageDevice::ShowAllData(QString modelId, QString name)
{
    DeviceService service;
    model = service.GetAll("", modelId, name,0);

    ui->table->setColumnCount(6);
    ui->table->setRowCount(model.count());
    QStringList headers;
    headers << tr("名称")<<tr("型号")<<tr("品牌")<<tr("条形码")<< tr("编辑")<< tr("删除");
    ui->table->setHorizontalHeaderLabels(headers);
    int count=model.count();
    for(int i=0;i<count;i++)
    {
        //ui->table->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(model[i].Id)));
        ui->table->setItem(i, 0, new QTableWidgetItem(model[i].DeviceName));
        ui->table->setItem(i, 1, new QTableWidgetItem(model[i].ModelName));
        ui->table->setItem(i, 2, new QTableWidgetItem(model[i].BrandName));
        ui->table->setItem(i, 3, new QTableWidgetItem(model[i].sn));

        QPushButton *editButton=new QPushButton(tr("编辑"));
        editButton->setToolTip(QString("%1").arg(model[i].DeviceId));
        connect(editButton,SIGNAL(clicked()),this,SLOT(OnBtnTableEditClicked()));
        ui->table->setCellWidget(i,4,editButton);

        QPushButton *deleteButton=new QPushButton(tr("删除"));
        deleteButton->setToolTip(QString("%1").arg(model[i].DeviceId));
        connect(deleteButton,SIGNAL(clicked()),this,SLOT(OnBtnTableDeleteClicked()));
        ui->table->setCellWidget(i,5,deleteButton);
    }
    ui->table->resizeRowsToContents();
}

void ManageDevice::OnBtnTableEditClicked()
{
    QPushButton *pbt = dynamic_cast<QPushButton*>(this->sender());
    if(pbt == 0)
        return;
    int x = pbt->frameGeometry().x();
    int y = pbt->frameGeometry().y();
    QModelIndex index = ui->table->indexAt(QPoint(x,y));
    int row = index.row();
    if(row == -1)
        return;

    EditDevice *form = new EditDevice(this);
    form->SetModel(pbt->toolTip());
    form->show();
}

void ManageDevice::OnBtnTableDeleteClicked()
{
    QPushButton *pbt = dynamic_cast<QPushButton*>(this->sender());
    if(pbt == 0)
        return;
    int x = pbt->frameGeometry().x();
    int y = pbt->frameGeometry().y();
    QModelIndex index = ui->table->indexAt(QPoint(x,y));
    int row = index.row();
    if(row == -1)
        return;

    DeviceService *service = new DeviceService();
    service->DeleteById(pbt->toolTip());
    ShowAllData();
}

void ManageDevice::on_btnAdd_clicked()
{
    EditDevice *form = new EditDevice(this);
    form->show();
}

void ManageDevice::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    //this->ShowAllData();
}

void ManageDevice::on_inputKeyword_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    this->SearchTree(ui->inputKeyword->text());
}

void ManageDevice::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    this->ShowAllData();
}

void ManageDevice::showEvent(QShowEvent *)
{
    QString keyword = ui->inputKeyword->text();
    SearchTree(keyword);
}

void ManageDevice::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}
