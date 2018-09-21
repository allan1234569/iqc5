#include "EditHospital.h"
#include "ui_EditHospital.h"
#include "Service/CategoryService.h"
#include "Service/HospitalService.h"
#include "UI/ManageHospital.h"
#include <QMessageBox>

EditHospital::EditHospital(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditHospital)
{
    ui->setupUi(this);

    hospitalId = 0;

}

void EditHospital::SetModel(QString id)
{
    if(id != 0)
    {
        HospitalService service;
        hospitalId = id;
        this->setWindowTitle("修改");
        Hospital hospital =service.GetById(id);

        ui->inputHospital->setText(hospital.hospitalName);

    }
}

EditHospital::~EditHospital()
{
    delete ui;
}

void EditHospital::on_btnCancel_clicked()
{
    this->close();
}

void EditHospital::on_btnOK_clicked()
{
    if( ui->inputHospital->text() == "")
    {
        QMessageBox::information(this, tr("信息") ,tr("医院名称不能为空"));
        return;
    }

    Hospital m;
    m.hospitalId = hospitalId;
    m.hospitalName = ui->inputHospital->text();

    HospitalService service;
    if(hospitalId == 0)
    {
        service.Insert(m);
    }
    else
    {
        service.Update(m);
    }

    ((ManageHospital *)(this->parent()))->ShowAllData();
    this->close();
}
