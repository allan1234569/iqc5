#include "ManageGroup.h"
#include "ui_ManageGroup.h"
#include "Model/Group.h"
#include "Service/GroupService.h"
#include "UI/EditGroup.h"
#include <QDebug>
#include <QMessageBox>
#include "Model/Category.h"
#include "Service/HospitalService.h"

ManageGroup::ManageGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageGroup)
{
    ui->setupUi(this);

    //初始化医院下拉框
    HospitalService *hospitalService = new HospitalService();
    QVector<Hospital> hospitals = hospitalService->GetAll("");
    ui->inputHospital->clear();
    Hospital hospital;
    foreach(hospital, hospitals)
    {
        ui->inputHospital->addItem(hospital.hospitalName, hospital.hospitalId);
    }
    ui->inputHospital->setCurrentIndex(0);

    this->ShowAllData();
}

ManageGroup::~ManageGroup()
{
    delete ui;
}

void ManageGroup::ShowAllData()
{
    ShowAllData(ui->inputHospital->itemData(ui->inputHospital->currentIndex()).toInt(), "");
}

void ManageGroup::ShowAllData(int hospitalId, QString name)
{
    GroupService service;
    model = service.GetAll(hospitalId, 0, 0, name);

    ui->table->setColumnCount(6);
    ui->table->setRowCount(model.count());
    QStringList headers;
    headers << tr("医院") << tr("科")<< tr("室")<< tr("组")<< tr("编辑")<< tr("删除");
    ui->table->setHorizontalHeaderLabels(headers);
    int count=model.count();
    for(int i=0;i<count;i++)
    {
        //ui->table->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(model[i].Id)));
        ui->table->setItem(i, 0, new QTableWidgetItem(model[i].hospitalName));
        ui->table->setItem(i, 1, new QTableWidgetItem(model[i].sectionName));
        ui->table->setItem(i, 2, new QTableWidgetItem(model[i].officeName));
        ui->table->setItem(i, 3, new QTableWidgetItem(model[i].groupName));

        QPushButton *editButton=new QPushButton(tr("编辑"));
        editButton->setToolTip(QString("%1").arg(model[i].groupId));
        connect(editButton,SIGNAL(clicked()),this,SLOT(OnBtnTableEditClicked()));
        ui->table->setCellWidget(i,4,editButton);

        QPushButton *deleteButton=new QPushButton(tr("删除"));
        deleteButton->setToolTip(QString("%1").arg(model[i].groupId));
        connect(deleteButton,SIGNAL(clicked()),this,SLOT(OnBtnTableDeleteClicked()));
        ui->table->setCellWidget(i,5,deleteButton);
    }
    ui->table->resizeRowsToContents();
}

void ManageGroup::OnBtnTableEditClicked()
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

    EditGroup *form = new EditGroup(this);
    form->SetModel(pbt->toolTip().toInt());
    form->show();
}

void ManageGroup::OnBtnTableDeleteClicked()
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

    GroupService *service = new GroupService();
    service->DeleteById(pbt->toolTip().toInt());
    ShowAllData();
}

void ManageGroup::on_btnCancel_clicked()
{
    this->close();
}

void ManageGroup::on_btnAdd_clicked()
{
    EditGroup *form = new EditGroup(this);
    form->show();
}

void ManageGroup::on_btnSearch_clicked()
{

    ShowAllData();
}

void ManageGroup::on_inputHospital_currentIndexChanged(int index)
{

}
