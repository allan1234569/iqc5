#include "ManageOffice.h"
#include "ui_ManageOffice.h"
#include "Model/Office.h"
#include "Service/OfficeService.h"
#include "UI/EditOffice.h"
#include <QDebug>
#include <QMessageBox>
#include "Model/Hospital.h"
#include "Service/HospitalService.h"
#include "Service/SectionService.h"

ManageOffice::ManageOffice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageOffice)
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

ManageOffice::~ManageOffice()
{
    delete ui;
}

void ManageOffice::ShowAllData()
{
    ShowAllData(ui->inputHospital->itemData(ui->inputHospital->currentIndex()).toInt(), "");
}

void ManageOffice::ShowAllData(int hospitalId, QString name)
{
    OfficeService service;
    model = service.GetAll(hospitalId, 0, name);

    ui->table->setColumnCount(5);
    ui->table->setRowCount(model.count());
    QStringList headers;
    headers << tr("医院") << tr("科室")<< tr("室") << tr("编辑")<< tr("删除");
    ui->table->setHorizontalHeaderLabels(headers);
    int count=model.count();
    for(int i=0;i<count;i++)
    {
        //ui->table->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(model[i].Id)));
        ui->table->setItem(i, 0, new QTableWidgetItem(model[i].hospitalName));
        ui->table->setItem(i, 1, new QTableWidgetItem(model[i].sectionName));
        ui->table->setItem(i, 2, new QTableWidgetItem(model[i].officeName));

        QPushButton *editButton=new QPushButton(tr("编辑"));
        editButton->setToolTip(QString("%1").arg(model[i].officeId));
        connect(editButton,SIGNAL(clicked()),this,SLOT(OnBtnTableEditClicked()));
        ui->table->setCellWidget(i,3,editButton);

        QPushButton *deleteButton=new QPushButton(tr("删除"));
        deleteButton->setToolTip(QString("%1").arg(model[i].officeId));
        connect(deleteButton,SIGNAL(clicked()),this,SLOT(OnBtnTableDeleteClicked()));
        ui->table->setCellWidget(i,4,deleteButton);
    }
    ui->table->resizeRowsToContents();
}

void ManageOffice::OnBtnTableEditClicked()
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

    EditOffice *form = new EditOffice(this);
    form->SetModel(pbt->toolTip().toInt());
    form->show();
}

void ManageOffice::OnBtnTableDeleteClicked()
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

    OfficeService *service = new OfficeService();
    service->DeleteById(pbt->toolTip().toInt());
    ShowAllData();
}

void ManageOffice::on_btnCancel_clicked()
{
    this->close();
}

void ManageOffice::on_btnAdd_clicked()
{
    EditOffice *form = new EditOffice(this);
    form->show();
}

void ManageOffice::on_btnSearch_clicked()
{

    ShowAllData();
}

void ManageOffice::on_inputHospital_currentIndexChanged(int index)
{

}
