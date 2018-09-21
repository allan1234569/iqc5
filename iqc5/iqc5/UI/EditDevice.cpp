#include "EditDevice.h"
#include "ui_EditDevice.h"
#include "Service/BrandService.h"
#include "Service/ModelService.h"
#include "Service/DeviceService.h"
#include "UI/ManageDevice.h"
#include <QMessageBox>
#include <QDebug>

EditDevice::EditDevice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDevice)
{
    ui->setupUi(this);

    //初始化品牌下拉框
    BrandService *brandService; brandService = new BrandService();
    ModelService *modelService; modelService = new ModelService();
    QVector<Brand> brands = brandService->GetBrands("");
    ui->inputBrand->clear();

    foreach(Brand brand, brands)
    {
        ui->inputBrand->addItem(brand.BrandName, brand.BrandId);
    }
    ui->inputBrand->setCurrentIndex(0);

    //初始化型号下拉框
    QString firstBrandId = ui->inputBrand->itemData(0).toString();
    QVector<Model> models = modelService->GetByBrandId(firstBrandId);

    ui->inputModel->clear();
    foreach(Model model, models)
    {
        ui->inputModel->addItem(model.ModelName, model.ModelId);
    }
    ui->inputModel->setCurrentIndex(0);

    deviceId = "";

    ui->inputBrand->setEditable(true);
    ui->inputModel->setEditable(true);

}

void EditDevice::SetModel(QString id)
{
    if(id != 0)
    {
        DeviceService service;
        deviceId = id;
        this->setWindowTitle("修改");
        Device device =service.GetById(id);

        for(int i=0;i<ui->inputBrand->count();i++)
        {
            if(QString::compare(ui->inputBrand->itemData(i).toString(), device.BrandId)==0)
            {
                ui->inputBrand->setCurrentIndex(i);
                on_inputBrand_currentIndexChanged(i);
                break;
            }
        }
        for(int i=0;i<ui->inputModel->count();i++)
        {
            if(QString::compare(ui->inputModel->itemData(i).toString(), device.ModelId)==0)
            {
                ui->inputModel->setCurrentIndex(i);
                break;
            }
        }

        ui->inputName->setText(device.DeviceName);
        ui->inputcode->setText(device.code);
        ui->inputsn->setText(device.sn);
        ui->inputsteelseal->setText(device.steelseal);
        ui->inputassetscode->setText(device.assetscode);
        ui->inputinstalldate->setText(device.installdate);
        ui->inputinstallplace->setText(device.installplace);
        ui->inputstopdate->setText(device.stopdate);
        ui->inputmemo->setText(device.memo);
    }
}

EditDevice::~EditDevice()
{
    delete ui;
}

void EditDevice::on_btnCancel_clicked()
{
    this->close();
}

void EditDevice::on_btnOK_clicked()
{
    if(ui->inputBrand->currentText() == "")
    {
        QMessageBox::information(this, tr("信息") ,tr("品牌不能为空"));
        return;
    }
    if(ui->inputModel->currentText() == "")
    {
        QMessageBox::information(this, tr("信息") ,tr("型号不能为空"));
        return;
    }
    if(ui->inputName->text() == "")
    {
        QMessageBox::information(this, tr("信息") ,tr("仪器名称不能为空"));
        return;
    }
    if(ui->inputinstallplace->text() == "")
    {
        QMessageBox::information(this, tr("信息") ,tr("安装地点不能为空"));
        return;
    }
    Device m;
    m.DeviceId = deviceId;
    m.DeviceName = ui->inputName->text();

    BrandService brandService;
    if(brandService.GetBrands(ui->inputBrand->currentText()).count()>0)
    {
        m.BrandId = ui->inputBrand->itemData(ui->inputBrand->currentIndex()).toString();

    }
    else
    {
        Brand brand;
        brand.BrandName = ui->inputBrand->currentText();
        m.BrandId = brandService.Insert(brand);
    }
    ModelService modelService;
    if(modelService.GetModels(ui->inputModel->currentText()).count()>0)
    {
        m.ModelId = ui->inputModel->itemData(ui->inputModel->currentIndex()).toString();

    }
    else
    {
        Model model;
        model.ModelName = ui->inputModel->currentText();
        model.BrandId = m.BrandId;
        m.ModelId = modelService.Insert(model);
    }

    m.code = ui->inputcode->text();
    m.sn = ui->inputsn->text();
    m.steelseal = ui->inputsteelseal->text();
    m.assetscode = ui->inputassetscode->text();
    m.installdate = ui->inputinstalldate->text();
    m.installplace = ui->inputinstallplace->text();
    m.stopdate = ui->inputstopdate->text();
    m.memo = ui->inputmemo->text();

    DeviceService service;
    if(deviceId == "")
    {
        service.Insert(m);
    }
    else
    {
        service.Update(m);
    }
    ManageDevice * f = qobject_cast<ManageDevice *>(this->parent());
    if(f!=NULL)
    {
        f->ShowAllData();
    }
    this->close();
}

void EditDevice::on_inputBrand_currentIndexChanged(int index)
{
    //初始化型号下拉框
    ModelService *modelService;modelService = new ModelService();

    QString brandId = ui->inputBrand->itemData(index).toString();
    QVector<Model> models = modelService->GetByBrandId(brandId);

    ui->inputModel->clear();
    foreach(Model model, models)
    {
        ui->inputModel->addItem(model.ModelName, model.ModelId);
    }
}
void EditDevice::SetName(QString name)
{
    ui->inputName->setText(name);
}
