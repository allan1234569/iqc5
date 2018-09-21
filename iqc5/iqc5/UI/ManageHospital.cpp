#include "ManageHospital.h"
#include "ui_ManageHospital.h"
#include "Model/Hospital.h"
#include "Service/HospitalService.h"
#include "UI/EditHospital.h"
#include <QDebug>
#include <QMessageBox>
#include "Model/Category.h"
#include "Service/CategoryService.h"

ManageHospital::ManageHospital(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageHospital)
{
    ui->setupUi(this);

    this->ShowAllData();
}

ManageHospital::~ManageHospital()
{
    delete ui;
}

void ManageHospital::ShowAllData()
{
    ShowAllData(ui->txtName->text());
}

void ManageHospital::ShowAllData(QString name)
{
    HospitalService service;
    model = service.GetAll(name);

    ui->table->setColumnCount(3);
    ui->table->setRowCount(model.count());
    QStringList headers;
    headers << tr("医院名称") << tr("编辑")<< tr("删除");
    ui->table->setHorizontalHeaderLabels(headers);
    int count=model.count();
    for(int i=0;i<count;i++)
    {
        ui->table->setItem(i, 0, new QTableWidgetItem(model[i].hospitalName));

        QPushButton *editButton=new QPushButton(tr("编辑"));
        editButton->setToolTip(QString("%1").arg(model[i].hospitalId));
        connect(editButton,SIGNAL(clicked()),this,SLOT(OnBtnTableEditClicked()));
        ui->table->setCellWidget(i,1,editButton);

        QPushButton *deleteButton=new QPushButton(tr("删除"));
        deleteButton->setToolTip(QString("%1").arg(model[i].hospitalId));
        connect(deleteButton,SIGNAL(clicked()),this,SLOT(OnBtnTableDeleteClicked()));
        ui->table->setCellWidget(i,2,deleteButton);
    }
    ui->table->resizeRowsToContents();
}

void ManageHospital::OnBtnTableEditClicked()
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

    EditHospital *form = new EditHospital(this);
    form->SetModel(pbt->toolTip().toInt());
    form->show();
}

void ManageHospital::OnBtnTableDeleteClicked()
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

    HospitalService *service = new HospitalService();
    service->DeleteById(pbt->toolTip().toInt());
    ShowAllData();
}

void ManageHospital::on_btnCancel_clicked()
{
    this->close();
}

void ManageHospital::on_btnAdd_clicked()
{
    EditHospital *form = new EditHospital(this);
    form->show();
}

void ManageHospital::on_btnSearch_clicked()
{

    ShowAllData();
}
