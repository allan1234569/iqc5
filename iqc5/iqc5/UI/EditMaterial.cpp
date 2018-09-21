#include "EditMaterial.h"
#include "ui_EditMaterial.h"
#include "Model/Material.h"
#include "Model/Category.h"
#include "Model/TestType.h"
#include "Service/MaterialService.h"
#include "Service/MaterialBatchService.h"
#include "UI/ManageMaterial.h"
#include <QMessageBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QDateEdit>
#include "Service/ManufacturerService.h"

EditMaterial::EditMaterial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMaterial)
{
    ui->setupUi(this);

    ui->btnAdd->setIcon(QIcon("images/add_big.png"));
    ui->btnDelete->setIcon(QIcon("images/delete_big.png"));

    materialId = "";

    //初始化国家下拉框
    ManufacturerService *manufacturerService; manufacturerService = new ManufacturerService();
    QVector<Country> countries = manufacturerService->GetCountries();
    ui->inputCountry->clear();

    foreach(Country country, countries)
    {
        ui->inputCountry->addItem(country.CountryName, country.CountryId);
    }
    ui->inputCountry->setCurrentIndex(0);

    //初始化厂商下拉框
    QVector<Manufacturer> manufacturers = manufacturerService->GetManufacturers("");

    ui->inputManufacturer->clear();
    foreach(Manufacturer manufacturer, manufacturers)
    {
        ui->inputManufacturer->addItem(manufacturer.ManufacturerName, manufacturer.ManufacturerId);
    }
    ui->inputManufacturer->setCurrentIndex(0);
    ui->inputManufacturer->setEditable(true);

    ui->table->setColumnCount(9);
    QStringList headers;
    headers <<""<< tr("包装") << tr("单位") << tr("注册号") << tr("批号")<< tr("失效期")<< tr("启用日期")<<tr("添加")<<tr("删除");
    ui->table->setHorizontalHeaderLabels(headers);

    ui->table->setColumnWidth(1,80);
    ui->table->setColumnWidth(2,80);
    ui->table->setColumnWidth(3,120);
    ui->table->setColumnWidth(4,100);
    ui->table->setColumnWidth(6,100);
    ui->table->setColumnWidth(7,40);
    ui->table->setColumnWidth(8,40);
    ui->table->setColumnHidden(0,true);
    ui->table->setColumnHidden(2,true);

}

EditMaterial::~EditMaterial()
{
    delete ui;
}


void EditMaterial::initRow(QTableWidget *table, int row, MaterialBatch *material)
{
    if(table->item(row,0)==NULL) //ID
    {
        table->setItem(row, 0, new QTableWidgetItem(material->MaterialBatchId));
    }
    if(table->cellWidget(row,1)==NULL) //包装
    {
        QLineEdit *control = new QLineEdit();
        if(material != NULL)
        {
            control->setText(material->package);
        }

        table->setCellWidget(row, 1, control);
    }
    if(table->cellWidget(row,2)==NULL) //单位
    {
        QLineEdit *control = new QLineEdit();
        if(material != NULL)
        {
            control->setText(material->Unit);
        }
        table->setCellWidget(row, 2, control);
    }
    if(table->item(row,3) == NULL) //注册号
    {
        QLineEdit *control = new QLineEdit();
        if(material != NULL)
        {
            control->setText(material->RegisterNo);
        }

        table->setCellWidget(row, 3, control);
    }
    if(table->item(row,4) == NULL)//批号
    {
        QLineEdit *control = new QLineEdit();
        if(material != NULL)
        {
            control->setText(material->BatchNo);
        }

        table->setCellWidget(row, 4, control);
    }
    if(table->item(row,5) == NULL)//有效期
    {
        QDateEdit *control = new QDateEdit();
        control->setCalendarPopup(true);
        if(material != NULL && material->ValidDate != "")
        {
            control->setDate(QDate::fromString(material->ValidDate, "yyyy-MM-dd"));
        }
        else
        {
            control->setDate(QDate::currentDate());
        }
        table->setCellWidget(row, 5, control);
    }
    if(table->item(row,6) == NULL)//启用日期
    {
        QLineEdit *control = new QLineEdit();
        if(material != NULL)
        {
            control->setText(material->StartDate.left(10));
        }

        table->setCellWidget(row, 6, control);
    }

    if(table->item(row,7) == NULL)//添加
    {
        QPushButton *control = new QPushButton();
        control->setIcon(QIcon("images/add.gif"));
        control->setToolTip(QString("%1").arg(row));
        connect(control,SIGNAL(clicked()),this,SLOT(rowAdd()));
        table->setCellWidget(row, 7, control);
    }
    if(table->item(row,8) == NULL)//删除
    {
        QPushButton *control = new QPushButton();
        control->setIcon(QIcon("images/delete.gif"));
        control->setToolTip(QString("%1").arg(row));
        connect(control,SIGNAL(clicked()),this,SLOT(rowDelete()));
        table->setCellWidget(row, 8, control);
    }

    table->installEventFilter(this);//注册事件过滤器
}


//添加项目
void EditMaterial::on_btnAdd_clicked()
{
    int rowCount = ui->table->rowCount();
    int row = rowCount-1;
    ui->table->setRowCount(rowCount+1);
    MaterialBatch m;
    if(rowCount>0)
    {
        m.package=((QLineEdit*)ui->table->cellWidget(row,1))->text();
        m.Unit=((QLineEdit*)ui->table->cellWidget(row,2))->text();
        m.RegisterNo=((QLineEdit*)ui->table->cellWidget(row,3))->text();
        m.BatchNo=((QLineEdit*)ui->table->cellWidget(row,4))->text();
        m.ValidDate=((QDateEdit*)ui->table->cellWidget(row,5))->date().toString("yyyy-MM-dd");
        m.StartDate="";
    }
    initRow(ui->table, rowCount, &m);
}

//删除项目
void EditMaterial::on_btnDelete_clicked()
{
    int row = ui->table->rowCount();
    if(row > 0)
    {
        ui->table->setRowCount(row-1);
    }
}

//在某行下面添加一行
void EditMaterial::rowAdd()
{
    QWidget * fWidget = this->focusWidget();
    QPushButton *cb = qobject_cast<QPushButton *>(fWidget);
    QTableWidget* table  =ui->table;
    for(int i =0;i<table->rowCount();i++)
    {
        if(cb == ((QPushButton*)table->cellWidget(i,7))) //找到该下拉框
        {
            int row = i;
            MaterialBatch m;
            m.package=((QLineEdit*)ui->table->cellWidget(row,1))->text();
            m.Unit=((QLineEdit*)ui->table->cellWidget(row,2))->text();
            m.RegisterNo=((QLineEdit*)ui->table->cellWidget(row,3))->text();
            m.BatchNo=((QLineEdit*)ui->table->cellWidget(row,4))->text();
            m.ValidDate=((QDateEdit*)ui->table->cellWidget(row,5))->date().toString("yyyy-MM-dd");
            m.StartDate="";

            table->insertRow(i+1);
            initRow(ui->table, i+1, &m);

            break;
        }
    }
}
//删除某行
void EditMaterial::rowDelete()
{
    QWidget * fWidget = this->focusWidget();
    QPushButton *cb = qobject_cast<QPushButton *>(fWidget);
    QTableWidget* table  =ui->table;
    for(int i =0;i<table->rowCount();i++)
    {
        if(cb == ((QPushButton*)table->cellWidget(i,8))) //找到该下拉框
        {
            ui->table->removeRow(i);
            break;
        }
    }
}


void EditMaterial::SetModel(QString id)
{
    if(id != 0)
    {
        MaterialService service;
        materialId = id;
        this->setWindowTitle("修改质控品信息");
        Material material =service.GetById(id);
        for(int i=0;i<ui->inputManufacturer->count();i++)
        {
            if(material.ManufacturerId== ui->inputManufacturer->itemData(i).toString())
            {
                ui->inputManufacturer->setCurrentIndex(i);
                break;
            }
        }
        for(int i=0;i<ui->inputCountry->count();i++)
        {
            if(material.CountryId== ui->inputCountry->itemData(i).toString())
            {
                ui->inputCountry->setCurrentIndex(i);
                break;
            }
        }

        ui->inputName->setText(material.MaterialName);
        ui->inputOrigin->setText(material.Origin);

        MaterialBatchService mbService;
        QVector<MaterialBatch> batches = mbService.GetMaterialBatchs(material.MaterialId,"");
        ui->table->setRowCount(0);
        ui->table->setRowCount(batches.count());
        for(int i=0;i<batches.count();i++)
        {
            initRow(ui->table, i, &batches[i]);

        }
    }
}

void EditMaterial::on_btnOK_clicked()
{
    if( ui->inputName->text() == "")
    {
        QMessageBox::information(this, tr("信息") ,tr("质控品名称不能为空"));
        return;
    }

    for(int row=0; row<ui->table->rowCount();row++)
    {
        QString name;
        //判断是否必填
        name = ((QLineEdit*)ui->table->cellWidget(row, 3))->text();
        if(QString::compare(name,"")==0)
        {
            QMessageBox::information(this, tr("信息") ,QString("第%1行 注册号未填写").arg(row+1));
            return;
        }
        name = ((QLineEdit*)ui->table->cellWidget(row, 4))->text();
        if(QString::compare(name,"")==0)
        {
            QMessageBox::information(this, tr("信息") ,QString("第%1行 批号未填写").arg(row+1));
            return;
        }
    }

    Material m;
    m.MaterialId = materialId;
    m.MaterialName = ui->inputName->text();


    ManufacturerService manufacturerService;
    if(manufacturerService.GetManufacturers(ui->inputManufacturer->currentText()).count()>0)
    {
        m.ManufacturerId = ui->inputManufacturer->itemData(ui->inputManufacturer->currentIndex()).toString();

    }
    else
    {
        Manufacturer manufacturer;
        manufacturer.ManufacturerName = ui->inputManufacturer->currentText();
        m.ManufacturerId = manufacturerService.Insert(manufacturer);
    }


    m.CountryId = ui->inputCountry->itemData(ui->inputCountry->currentIndex()).toString();
    m.Origin = ui->inputOrigin->text();


    MaterialService service;
    if(materialId == 0)
    {
        service.Insert(m);
    }
    else
    {
        service.Update(m);
    }

    for(int row=0; row<ui->table->rowCount();row++)
    {
        MaterialBatch mb;
        mb.MaterialId = m.MaterialId;
        mb.MaterialBatchId = ui->table->item(row,0)->text();
        mb.package=((QLineEdit*)ui->table->cellWidget(row,1))->text();
        mb.Unit=((QLineEdit*)ui->table->cellWidget(row,2))->text();
        mb.RegisterNo=((QLineEdit*)ui->table->cellWidget(row,3))->text();
        mb.BatchNo=((QLineEdit*)ui->table->cellWidget(row,4))->text();
        mb.ValidDate=((QDateEdit*)ui->table->cellWidget(row,5))->date().toString("yyyy-MM-dd");
        mb.StartDate=((QLineEdit*)ui->table->cellWidget(row,6))->text();

        if(QString::compare(ui->table->item(row,0)->text(),"") == 0)
        {
            MaterialBatchService materialBatchService;
            materialBatchService.Insert(mb);
        }
        else
        {
            MaterialBatchService materialBatchService;
            materialBatchService.Update(mb);

        }
    }


    ManageMaterial * f = qobject_cast<ManageMaterial *>(this->parent());
    if(f!=NULL)
    {
        f->ShowAllData();
    }
    this->close();


}

void EditMaterial::on_btnCancel_clicked()
{
    this->close();
}
void EditMaterial::SetName(QString name)
{
    ui->inputName->setText(name);
}

