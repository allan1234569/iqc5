#include "EditSection.h"
#include "ui_EditSection.h"
#include "Service/HospitalService.h"
#include "Service/SectionService.h"
#include "UI/ManageSection.h"
#include <QMessageBox>

EditSection::EditSection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditSection)
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

    sectionId = 0;

}

void EditSection::SetModel(QString id)
{
    if(id != 0)
    {
        SectionService service;
        sectionId = id;
        this->setWindowTitle("修改");
        Section section =service.GetById(id);

        for(int i=0;i<ui->inputHospital->count();i++)
        {
            if(section.hospitalId == ui->inputHospital->itemData(i).toInt())
            {
                ui->inputHospital->setCurrentIndex(i);
                on_inputHospital_currentIndexChanged(i);
                break;
            }
        }

        ui->inputSection->setText(section.sectionName);

    }
}

EditSection::~EditSection()
{
    delete ui;
}

void EditSection::on_btnCancel_clicked()
{
    this->close();
}

void EditSection::on_btnOK_clicked()
{
    if( ui->inputSection->text() == "")
    {
        QMessageBox::information(this, tr("信息") ,tr("科不能为空"));
        return;
    }

    Section m;
    m.sectionId = sectionId;
    m.hospitalId = ui->inputHospital->itemData(ui->inputHospital->currentIndex()).toInt();
    m.sectionName = ui->inputSection->text();


    SectionService service;
    if(sectionId == 0)
    {
        service.Insert(m);
    }
    else
    {
        service.Update(m);
    }

    ((ManageSection *)(this->parent()))->ShowAllData();
    this->close();
}

void EditSection::on_inputHospital_currentIndexChanged(int index)
{

}
