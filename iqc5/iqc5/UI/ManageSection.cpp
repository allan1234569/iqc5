#include "ManageSection.h"
#include "ui_ManageSection.h"
#include "Model/Section.h"
#include "Service/SectionService.h"
#include "UI/EditSection.h"
#include <QDebug>
#include <QMessageBox>
#include "Model/Hospital.h"
#include "Service/HospitalService.h"

ManageSection::ManageSection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageSection)
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

ManageSection::~ManageSection()
{
    delete ui;
}

void ManageSection::ShowAllData()
{
    ShowAllData(ui->inputHospital->itemData(ui->inputHospital->currentIndex()).toInt(),"");
}

void ManageSection::ShowAllData(int hospitalId, QString name)
{
    SectionService service;
    model = service.GetAll(hospitalId, name);

    ui->table->setColumnCount(4);
    ui->table->setRowCount(model.count());
    QStringList headers;
    headers << tr("医院") << tr("科室")<< tr("编辑")<< tr("删除");
    ui->table->setHorizontalHeaderLabels(headers);
    int count=model.count();
    for(int i=0;i<count;i++)
    {
        //ui->table->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(model[i].Id)));
        ui->table->setItem(i, 0, new QTableWidgetItem(model[i].hospitalName));
        ui->table->setItem(i, 1, new QTableWidgetItem(model[i].sectionName));

        QPushButton *editButton=new QPushButton(tr("编辑"));
        editButton->setToolTip(QString("%1").arg(model[i].sectionId));
        connect(editButton,SIGNAL(clicked()),this,SLOT(OnBtnTableEditClicked()));
        ui->table->setCellWidget(i,2,editButton);

        QPushButton *deleteButton=new QPushButton(tr("删除"));
        deleteButton->setToolTip(QString("%1").arg(model[i].sectionId));
        connect(deleteButton,SIGNAL(clicked()),this,SLOT(OnBtnTableDeleteClicked()));
        ui->table->setCellWidget(i,3,deleteButton);
    }
    ui->table->resizeRowsToContents();
}

void ManageSection::OnBtnTableEditClicked()
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

    EditSection *form = new EditSection(this);
    form->SetModel(pbt->toolTip().toInt());
    form->show();
}

void ManageSection::OnBtnTableDeleteClicked()
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

    SectionService *service = new SectionService();
    service->DeleteById(pbt->toolTip().toInt());
    ShowAllData();
}

void ManageSection::on_btnCancel_clicked()
{
    this->close();
}

void ManageSection::on_btnAdd_clicked()
{
    EditSection *form = new EditSection(this);
    form->show();
}

void ManageSection::on_btnSearch_clicked()
{

    ShowAllData();
}

void ManageSection::on_inputHospital_currentIndexChanged(int index)
{

}
