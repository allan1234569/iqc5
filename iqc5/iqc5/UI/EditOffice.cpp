#include "EditOffice.h"
#include "ui_EditOffice.h"
#include "Model/Section.h"
#include "Service/HospitalService.h"
#include "Service/SectionService.h"
#include "Service/OfficeService.h"
#include "UI/ManageOffice.h"
#include <QMessageBox>

EditOffice::EditOffice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditOffice)
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

    SectionService *sectionService = new SectionService();
    int firstHospitalId = ui->inputHospital->itemData(0).toInt();
    QVector<Section> sections = sectionService->GetAll(firstHospitalId, "");

    ui->inputSection->clear();
    foreach(Section section, sections)
    {
        ui->inputSection->addItem(section.sectionName, section.sectionId);
    }
    ui->inputSection->setCurrentIndex(0);

    officeId = 0;

}

void EditOffice::SetModel(QString id)
{
    if(id != 0)
    {
        OfficeService service;
        officeId = id;
        this->setWindowTitle("修改");
        Office office =service.GetById(id);

        for(int i=0;i<ui->inputHospital->count();i++)
        {
            if(office.hospitalId== ui->inputHospital->itemData(i).toInt())
            {
                ui->inputHospital->setCurrentIndex(i);
                on_inputHospital_currentIndexChanged(i);
                break;
            }
        }

        for(int i=0;i<ui->inputSection->count();i++)
        {
            if(office.sectionId== ui->inputSection->itemData(i).toInt())
            {
                ui->inputSection->setCurrentIndex(i);
                break;
            }
        }

        ui->inputOffice->setText(office.officeName);
    }
}

EditOffice::~EditOffice()
{
    delete ui;
}

void EditOffice::on_btnCancel_clicked()
{
    this->close();
}

void EditOffice::on_btnOK_clicked()
{
    if( ui->inputHospital->currentIndex() < 0)
    {
        QMessageBox::information(this, tr("信息") ,tr("医院不能为空"));
        return;
    }
    if( ui->inputSection->currentIndex() < 0)
    {
        QMessageBox::information(this, tr("信息") ,tr("科不能为空"));
        return;
    }
    Office m;
    m.officeId = officeId;
    m.sectionId = ui->inputSection->itemData(ui->inputSection->currentIndex()).toInt();
    m.officeName = ui->inputOffice->text();


    OfficeService service;
    if(officeId == 0)
    {
        service.Insert(m);
    }
    else
    {
        service.Update(m);
    }

    ((ManageOffice *)(this->parent()))->ShowAllData();
    this->close();
}

void EditOffice::on_inputHospital_currentIndexChanged(int index)
{
    //初始化科下拉框
    SectionService *sectionService = new SectionService();

    QString hospitalId = ui->inputHospital->itemData(index).toInt();
    QVector<Section> sections = sectionService->GetAll(hospitalId, "");

    ui->inputSection->clear();
    Section section;
    foreach(section, sections)
    {
        ui->inputSection->addItem(section.sectionName, section.sectionId);
    }
}
