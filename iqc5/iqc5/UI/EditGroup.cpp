#include "EditGroup.h"
#include "ui_EditGroup.h"
#include "Service/HospitalService.h"
#include "Service/SectionService.h"
#include "Service/OfficeService.h"
#include "Service/GroupService.h"
#include "UI/ManageGroup.h"
#include "Model/Section.h"
#include <QMessageBox>

EditGroup::EditGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditGroup)
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

    QString firstHospitalId = ui->inputHospital->itemData(0).toString();

    SectionService *sectionService = new SectionService();
    QVector<Section> sections = sectionService->GetAll(firstHospitalId, "");

    ui->inputSection->clear();
    foreach(Section section, sections)
    {
        ui->inputSection->addItem(section.sectionName, section.sectionId);
    }
    ui->inputSection->setCurrentIndex(0);

    QString firstSectionId = ui->inputSection->itemData(0).toString();

    OfficeService *officeServiceService = new OfficeService();
    QVector<Office> offices = officeServiceService->GetAll(firstHospitalId, firstSectionId, "");

    ui->inputOffice->clear();
    foreach(Office office, offices)
    {
        ui->inputOffice->addItem(office.officeName, office.officeId);
    }
    ui->inputOffice->setCurrentIndex(0);

    groupId = 0;

}

void EditGroup::SetModel(QString id)
{
    if(id != 0)
    {
        GroupService service;
        groupId = id;
        this->setWindowTitle("修改");
        Group group =service.GetById(id);

        for(int i=0;i<ui->inputHospital->count();i++)
        {
            if(group.hospitalId== ui->inputHospital->itemData(i).toString())
            {
                ui->inputHospital->setCurrentIndex(i);
                on_inputHospital_currentIndexChanged(i);
                break;
            }
        }

        for(int i=0;i<ui->inputSection->count();i++)
        {
            if(group.sectionId== ui->inputSection->itemData(i).toString())
            {
                ui->inputSection->setCurrentIndex(i);
                on_inputSection_currentIndexChanged(i);
                break;
            }
        }

        for(int i=0;i<ui->inputOffice->count();i++)
        {
            if(group.officeId== ui->inputOffice->itemData(i).toString())
            {
                ui->inputOffice->setCurrentIndex(i);
                break;
            }
        }

        ui->inputGroup->setText(group.groupName);
    }
}

EditGroup::~EditGroup()
{
    delete ui;
}

void EditGroup::on_btnCancel_clicked()
{
    this->close();
}

void EditGroup::on_btnOK_clicked()
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
    if( ui->inputOffice->currentIndex() < 0)
    {
        QMessageBox::information(this, tr("信息") ,tr("室不能为空"));
        return;
    }
    if( ui->inputGroup->text() == "")
    {
        QMessageBox::information(this, tr("信息") ,tr("组不能为空"));
        return;
    }
    Group m;
    m.groupId = groupId;
    m.officeId = ui->inputOffice->itemData(ui->inputOffice->currentIndex()).toString();
    m.groupName = ui->inputGroup->text();

    GroupService service;
    if(groupId == 0)
    {
        service.Insert(m);
    }
    else
    {
        service.Update(m);
    }

    ((ManageGroup *)(this->parent()))->ShowAllData();
    this->close();
}

void EditGroup::on_inputHospital_currentIndexChanged(int index)
{
    //初始化科下拉框
    int hospitalId = ui->inputHospital->itemData(index).toString();

    SectionService *sectionService = new SectionService();
    QVector<Section> sections = sectionService->GetAll(hospitalId, "");

    ui->inputSection->clear();
    foreach(Section section, sections)
    {
        ui->inputSection->addItem(section.sectionName, section.sectionId);
    }
    ui->inputSection->setCurrentIndex(0);


}

void EditGroup::on_inputSection_currentIndexChanged(int index)
{
    //初始化室下拉框
    int sectionId = ui->inputSection->itemData(index).toString();

        OfficeService *officeServiceService = new OfficeService();
        QVector<Office> offices = officeServiceService->GetAll(0, sectionId, "");

        ui->inputOffice->clear();
        foreach(Office office, offices)
        {
            ui->inputOffice->addItem(office.officeName, office.officeId);
        }
        ui->inputOffice->setCurrentIndex(0);


}
