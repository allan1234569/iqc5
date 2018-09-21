#include "NewMaterialBatch.h"
#include "ui_NewMaterialBatch.h"
#include "Model/Manufacturer.h"
#include "Model/Material.h"
#include "UI/EditMaterial.h"
#include <QDebug>
#include <QMessageBox>
#include <QComboBox>
#include <QDateEdit>
#include "Model/Category.h"
#include "Service/CategoryService.h"

#include "Service/ManufacturerService.h"
#include "Service/MaterialService.h"
#include "Service/ReagentService.h"
#include "Service/MethodService.h"
#include "Service/DeviceService.h"
#include "Service/TestTypeService.h"
#include "Service/ProjectService.h"
#include "Service/MaterialBatchService.h"
#include "Service/ReagentBatchService.h"
#include "Service/CountryService.h"
#include "UI/ManageMaterial.h"
#include <QlistWidget>
#include "MainWindow.h"

NewMaterialBatch::NewMaterialBatch(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewMaterialBatch)
{
    listWidget = NULL;

    ui->setupUi(this);


    InitTree();

    ui->table->setColumnCount(15);
    QStringList headers;
    headers << tr("质控品名称") << tr("厂家") << tr("产地") << tr("包装")<< tr("单位")<< tr("来源") << tr("注册号")<< tr("批号")<< tr("失效期")<< tr("启用日期")<<tr("添加")<<tr("删除");
    ui->table->setHorizontalHeaderLabels(headers);

    ui->table->setColumnWidth(0,120);
    ui->table->setColumnWidth(3,80);
    ui->table->setColumnWidth(4,80);
    ui->table->setColumnWidth(5,80);
    ui->table->setColumnWidth(6,120);
    ui->table->setColumnWidth(7,80);
    ui->table->setColumnWidth(8,100);
    ui->table->setColumnWidth(9,100);

    ui->table->setColumnWidth(10,40);
    ui->table->setColumnWidth(11,40);

    ui->table->setColumnHidden(4,true);
    ui->table->setColumnHidden(12,true);
    ui->table->setColumnHidden(13,true);
    ui->table->setColumnHidden(14,true);
    ui->table->setColumnHidden(9,true);//启用日期

    ui->groupBox_3->setHidden(true);
    ui->widget_4->setHidden(true);

    ui->btnOK->setGeometry(ui->btnOK->x(),580,ui->btnOK->width(),ui->btnOK->height());
    ui->btnCancel->setGeometry(ui->btnOK->x(), 620,ui->btnOK->width(),ui->btnOK->height());


}


void NewMaterialBatch::InitTree()
{
    MaterialService *service;service = new MaterialService();
    QString keyword = ui->inputKeyword->text();

    ui->treeWidget->clear();

    QVector<Material> models = service->GetMaterials("","", keyword, "","",0);

    if(models.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<models[0].ManufacturerName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[0].MaterialName);
        pItem->setToolTip(0, QString("%1").arg(models[0].MaterialId));
        ca->addChild(pItem);

        for(int i=1;i<models.count();i++)
        {
            if(QString::compare(models[i].ManufacturerName, models[i-1].ManufacturerName) != 0)
            {
                ca = new QTreeWidgetItem(QStringList()<<models[i].ManufacturerName);
                ui->treeWidget->addTopLevelItem(ca);
            }

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[i].MaterialName);
            pItem->setToolTip(0, QString("%1").arg(models[i].MaterialId));
            ca->addChild(pItem);
        }
    }
    ui->treeWidget->expandAll();

}

void NewMaterialBatch::on_inputKeyword_textChanged(const QString &arg1)
{
    InitTree();
}

NewMaterialBatch::~NewMaterialBatch()
{
    delete ui;
}


void NewMaterialBatch::initRow(QTableWidget *table, int row, Material *material)
{
    if(table->cellWidget(row,0)==NULL) //指控品名称
    {
        QLineEdit *control = new QLineEdit();
        if(material != NULL)
        {
            control->setText(material->MaterialName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(materialName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(materialName_changed()));
        connect(control,SIGNAL(editingFinished()),this,SLOT(closeList()));
        table->setCellWidget(row, 0, control);
    }
    if(table->cellWidget(row,1)==NULL) //厂家名称
    {
        QLineEdit *control = new QLineEdit();
        if(material != NULL)
        {
            control->setText(material->ManufacturerName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(manufacturerName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(manufacturerName_changed()));
        connect(control,SIGNAL(editingFinished()),this,SLOT(closeList()));
        table->setCellWidget(row, 1, control);
    }
    if(table->cellWidget(row,2)==NULL) //产地
    {
        QLineEdit *control = new QLineEdit();
        if(material != NULL)
        {
            control->setText(material->CountryName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(countryName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(countryName_changed()));
        connect(control,SIGNAL(editingFinished()),this,SLOT(closeList()));
        table->setCellWidget(row, 2, control);
    }

    if(table->item(row,3) == NULL) //包装
    {
        QLineEdit *control = new QLineEdit();
        if(material != NULL)
        {
            control->setText(material->package);
        }

        table->setCellWidget(row, 3, control);
    }
    if(table->item(row,4) == NULL) //单位
    {
        QLineEdit *control = new QLineEdit();
        if(material != NULL)
        {
            control->setText(material->Unit);
        }
        table->setCellWidget(row, 4, control);
    }
    if(table->item(row,5) == NULL) //来源
    {
        QLineEdit *control = new QLineEdit();
        if(material != NULL)
        {
            control->setText(material->Origin);
        }
        table->setCellWidget(row, 5, control);
    }
    if(table->item(row,6) == NULL) //注册号
    {
        QLineEdit *control = new QLineEdit();
        if(material != NULL)
        {
            control->setText(material->RegisterNo);
        }

        table->setCellWidget(row, 6, control);
    }
    if(table->item(row,7) == NULL)//批号
    {
        QLineEdit *control = new QLineEdit();
        if(material != NULL)
        {
            control->setText(material->BatchNo);
        }

        table->setCellWidget(row, 7, control);
    }
    if(table->item(row,8) == NULL)//有效期
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
        table->setCellWidget(row, 8, control);
    }
    if(table->item(row,9) == NULL)//启用日期
    {
        QDateEdit *control = new QDateEdit();
        control->setCalendarPopup(true);
        if(material != NULL&& material->StartDate != "")
        {
            control->setDate(QDate::fromString(material->StartDate, "yyyy-MM-dd"));
        }
        else
        {
            control->setDate(QDate::fromString("1900-1-1", "yyyy-MM-dd"));
        }
        table->setCellWidget(row, 9, control);
    }

    if(table->item(row,10) == NULL)//添加
    {
        QPushButton *control = new QPushButton();
        control->setIcon(QIcon("://images/add.gif"));
        control->setToolTip(QString("%1").arg(row));
        connect(control,SIGNAL(clicked()),this,SLOT(rowAdd()));
        table->setCellWidget(row, 10, control);
    }
    if(table->item(row,11) == NULL)//删除
    {
        QPushButton *control = new QPushButton();
        control->setIcon(QIcon("://images/delete.gif"));
        control->setToolTip(QString("%1").arg(row));
        connect(control,SIGNAL(clicked()),this,SLOT(rowDelete()));
        table->setCellWidget(row, 11, control);
    }
    if(table->item(row,12) == NULL)//是否被合并
    {

        table->setItem(row, 12, new QTableWidgetItem(""));
    }
    if(table->item(row,13) == NULL)//质控品ID
    {

        table->setItem(row, 13, new QTableWidgetItem(material->MaterialId));
    }
    if(table->item(row,14) == NULL)//质控品批号ID
    {

        table->setItem(row, 14, new QTableWidgetItem(material->MaterialBatchId));
    }



    table->installEventFilter(this);//注册事件过滤器

}

void NewMaterialBatch::materialName_changed(QString arg1)
{
    int current = 0;
    QWidget * fWidget = this->focusWidget();
    QLineEdit *cb = qobject_cast<QLineEdit *>(fWidget);
    QTableWidget* table  =ui->table;
    if (cb != NULL)
    {
        //下拉提示框
        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,0))) //找到该下拉框
            {
                lineEdit = cb;
                if(listWidget != NULL)
                {
                    listWidget->setVisible(false);
                }
                listWidget = new QListWidget(this);
                listWidget->setGeometry(cb->geometry().left()+43,cb->geometry().top()+79, cb->geometry().width(), 120);
                connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
                listWidget->clear();

                MaterialService service;
                QVector<Material> m = service.GetMaterials("","", cb->text(),"","",1);
                for(int i =0;i<m.count();i++)
                {
                    QListWidgetItem *item;
                    item = new QListWidgetItem();
                    item->setText(m[i].MaterialName);
                    item->setToolTip(m[i].MaterialId);
                    listWidget->addItem(item);
                }
                if (listWidget->count() > 0)
                {
                    listWidget->setVisible(true);
                }
                else
                {
                    listWidget->setVisible(false);
                }
            }
        }
        //下拉提示框End

        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,0))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
        for(int i =current;i<table->rowCount();i++)
        {
//            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,0);
//            nextComb->setText(arg1);
        }

        //其它名称自动完成
        if(QString::compare(arg1, "")!=0)
        {
            MaterialService service;
            QVector<Material> ps = service.GetMaterials("","",arg1,"","",1);
            if(ps.count()>0 && ps.count()<5)
            {

            }
        }
    }
}

void NewMaterialBatch::manufacturerName_changed(QString arg1)
{
    int current = 0;
    QWidget * fWidget = this->focusWidget();
    QLineEdit *cb = qobject_cast<QLineEdit *>(fWidget);
    if (cb != NULL)
    {
        //下拉提示框
        lineEdit = cb;
        if(listWidget != NULL)
        {
            listWidget->setVisible(false);
        }
        listWidget = new QListWidget(this);
        listWidget->setGeometry(cb->geometry().left()+43,cb->geometry().top()+80, cb->geometry().width(), 120);
        connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
        listWidget->clear();

        ManufacturerService service;
        QVector<Manufacturer> m = service.GetManufacturers(cb->text());
        for(int i =0;i<m.count();i++)
        {
            QListWidgetItem *item;
            item = new QListWidgetItem();
            item->setText(m[i].ManufacturerName);
            item->setToolTip(m[i].ManufacturerId);
            listWidget->addItem(item);
        }
        if (listWidget->count() > 0)
        {
            listWidget->setVisible(true);
        }
        else
        {
            listWidget->setVisible(false);
        }
        //下拉提示框End

        QTableWidget* table  =ui->table;
        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,1))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
        for(int i =current;i<table->rowCount();i++)
        {
//            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,1);
//            nextComb->setText(arg1);
        }
    }
}


void NewMaterialBatch::countryName_changed(QString arg1)
{
    int current = 0;
    QWidget * fWidget = this->focusWidget();
    QLineEdit *cb = qobject_cast<QLineEdit *>(fWidget);
    if (cb != NULL)
    {
        //下拉提示框
        lineEdit = cb;
        if(listWidget != NULL)
        {
            listWidget->setVisible(false);
        }
        listWidget = new QListWidget(this);
        listWidget->setGeometry(cb->geometry().left()+43,cb->geometry().top()+80, cb->geometry().width(), 120);
        connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
        listWidget->clear();

        ManufacturerService service;
        QVector<Country> m = service.GetCountries();
        for(int i =0;i<m.count();i++)
        {
            QListWidgetItem *item;
            item = new QListWidgetItem();
            item->setText(m[i].CountryName);
            item->setToolTip(m[i].CountryId);
            listWidget->addItem(item);
        }
        if (listWidget->count() > 0)
        {
            listWidget->setVisible(true);
        }
        else
        {
            listWidget->setVisible(false);
        }
        //下拉提示框End

        QTableWidget* table  =ui->table;
        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,2))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
        for(int i =current;i<table->rowCount();i++)
        {
//            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,2);
//            nextComb->setText(arg1);
        }
    }
}

void NewMaterialBatch::materialName_changed(){materialName_changed("");}
void NewMaterialBatch::manufacturerName_changed(){manufacturerName_changed("");}
void NewMaterialBatch::countryName_changed(){countryName_changed("");}


void NewMaterialBatch::keyPressEvent (QKeyEvent * keyevent)
{
    int uKey = keyevent->key();
    Qt::Key key = static_cast<Qt::Key>(uKey);

    if(key == Qt::Key_Escape)
    {
        if(listWidget != NULL)
        {
            listWidget->setVisible(false);
        }
    }
    if((listWidget == NULL || listWidget->count() == 0))
        return;

    int iIndex = listWidget->currentRow();
    if(key == Qt::Key_Up)
    {
        iIndex--;
        if(iIndex < 0) iIndex = 0;
        QListWidgetItem *pItem = listWidget->item(iIndex);
        listWidget->setCurrentItem(pItem);

    }
    else if (key == Qt::Key_Down)
    {
        iIndex++;
        if(iIndex >= listWidget->count()) iIndex = listWidget->count() - 1;
        QListWidgetItem *pItem = listWidget->item(iIndex);
        listWidget->setCurrentItem(pItem);
    }
    else if (key == Qt::Key_Enter || key == Qt::Key_Return)
    {
        if(listWidget != NULL)
        {
            if(listWidget->currentItem() != NULL)
            {
                QString s = listWidget->currentItem()->text();
                lineEdit->setFocus();
                lineEdit->setText(s);
            }
            listWidget->setVisible(false);
        }
    }
}


bool NewMaterialBatch::eventFilter(QObject*obj,QEvent*event)
{

    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent*keyEvent=static_cast<QKeyEvent*>(event);

        if(keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down)
        {
            if(listWidget!=NULL && listWidget->isVisible())
            {
                listWidget->setFocus();
                if(listWidget->count()>0)
                {
                    QListWidgetItem *pItem = listWidget->item(0);
                    listWidget->setCurrentItem(pItem);
                }
                return true;
            }
        }
        //表格回车到下一行
        if(keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
        {
            QTableWidget* table = (QTableWidget*)obj;

            int row = 0;
            int column = 0;
            QWidget * cb = this->focusWidget();
            for(int i=0;i<table->rowCount();i++)
            {
                for(int j=0;j<table->columnCount();j++)
                {
                    if(table->cellWidget(i,j)==cb)
                    {
                        row=i;
                        column=j;
                        break;
                    }
                }
            }

            if(row == table->rowCount()-1) //不是最后一行
            {
                on_btnAdd_clicked();

            }
            QTableWidgetItem *item = table->item(row+1, column);
            table->setCurrentCell(row+1, column);
            table->editItem(item);



            return  true;
        }
    }
    return QObject::eventFilter(obj,event);
}

//添加项目
void NewMaterialBatch::on_btnAdd_clicked()
{
    ManufacturerService manufacturerService;

    int rowCount = ui->table->rowCount();
    int row = rowCount-1;
    ui->table->setRowCount(rowCount+1);
    Material m;
    if(rowCount>0)
    {
        m.MaterialName = ((QLineEdit*)ui->table->cellWidget(row,0))->text();
        m.ManufacturerName = ((QLineEdit*)ui->table->cellWidget(row,1))->text();
        QVector<Manufacturer> facturers = manufacturerService.GetManufacturers(m.ManufacturerName);
        if(facturers.count()>0)
        {
            m.ManufacturerId = facturers[0].ManufacturerId;
        }
        m.CountryName = ((QLineEdit*)ui->table->cellWidget(row,2))->text();
        Country country = manufacturerService.GetCountryByName(m.CountryName);
        if(country.CountryId != "")
        {
            m.CountryId = country.CountryId;
        }
        m.package=((QLineEdit*)ui->table->cellWidget(row,3))->text();
        m.Unit=((QLineEdit*)ui->table->cellWidget(row,4))->text();
        m.Origin=((QLineEdit*)ui->table->cellWidget(row,5))->text();
        m.RegisterNo=((QLineEdit*)ui->table->cellWidget(row,6))->text();
        m.BatchNo=((QLineEdit*)ui->table->cellWidget(row,7))->text();
        m.ValidDate=((QDateEdit*)ui->table->cellWidget(row,8))->date().toString("yyyy-MM-dd");
        m.StartDate=((QDateEdit*)ui->table->cellWidget(row,9))->date().toString("yyyy-MM-dd");
    }
    initRow(ui->table, rowCount, &m);
}

//删除项目
void NewMaterialBatch::on_btnDelete_clicked()
{
    int row = ui->table->rowCount();
    if(row > 0)
    {
        ui->table->setRowCount(row-1);
    }
}

//在某行下面添加一行
void NewMaterialBatch::rowAdd()
{
    ManufacturerService manufacturerService;

    QWidget * fWidget = this->focusWidget();
    QPushButton *cb = qobject_cast<QPushButton *>(fWidget);
    QTableWidget* table  =ui->table;
    for(int i =0;i<table->rowCount();i++)
    {
        if(cb == ((QPushButton*)table->cellWidget(i,10))) //找到该下拉框
        {
            int row = i;
            Material m;
            m.MaterialName = ((QLineEdit*)ui->table->cellWidget(row,0))->text();
            m.ManufacturerName = ((QLineEdit*)ui->table->cellWidget(row,1))->text();
            QVector<Manufacturer> facturers = manufacturerService.GetManufacturers(m.ManufacturerName);
            if(facturers.count()>0)
            {
                m.ManufacturerId = facturers[0].ManufacturerId;
            }
            m.CountryName = ((QLineEdit*)ui->table->cellWidget(row,2))->text();
            Country country = manufacturerService.GetCountryByName(m.CountryName);
            if(country.CountryId != "")
            {
                m.CountryId = country.CountryId;
            }
            m.package=((QLineEdit*)ui->table->cellWidget(row,3))->text();
            m.Unit=((QLineEdit*)ui->table->cellWidget(row,4))->text();
            m.Origin=((QLineEdit*)ui->table->cellWidget(row,5))->text();
            m.RegisterNo=((QLineEdit*)ui->table->cellWidget(row,6))->text();
            m.BatchNo=((QLineEdit*)ui->table->cellWidget(row,7))->text();
            m.ValidDate=((QDateEdit*)ui->table->cellWidget(row,8))->date().toString("yyyy-MM-dd");
            m.StartDate=((QDateEdit*)ui->table->cellWidget(row,9))->date().toString("yyyy-MM-dd");

            table->insertRow(i+1);
            initRow(ui->table, i+1, &m);

            break;
        }
    }

    if(ui->table->rowCount()>0)
    {
        int j=0;
        QString text1 = ((QLineEdit*)ui->table->cellWidget(j,0))->text();
        for(int i=1;i<ui->table->rowCount();i++)
        {
            QString text2 = ((QLineEdit*)ui->table->cellWidget(i,0))->text();
            if(QString::compare(text1, text2) != 0)
            {
                table->setSpan(j,0,i-j,1);
                table->setSpan(j,1,i-j,1);
                table->setSpan(j,2,i-j,1);

                j=i;
                text1 = ((QLineEdit*)ui->table->cellWidget(j,0))->text();
            }
            else
            {
                table->setItem(i,12,new QTableWidgetItem("1"));
            }
        }
        table->setSpan(j,0,ui->table->rowCount()-j,1);
        table->setSpan(j,1,ui->table->rowCount()-j,1);
        table->setSpan(j,2,ui->table->rowCount()-j,1);

        table->resizeRowsToContents();
    }
}
//删除某行
void NewMaterialBatch::rowDelete()
{
    QWidget * fWidget = this->focusWidget();
    QPushButton *cb = qobject_cast<QPushButton *>(fWidget);
    QTableWidget* table  =ui->table;
    for(int i =0;i<table->rowCount();i++)
    {
        if(cb == ((QPushButton*)table->cellWidget(i,11))) //找到该下拉框
        {
            ui->table->removeRow(i);
            break;
        }
    }
}

//保存
void NewMaterialBatch::on_btnOK_clicked()
{
    MaterialService materialService;
    ManufacturerService manufacturerService;
    CountryService countryService;
    MaterialBatchService mbs;

    //检验
    for(int row=0; row<ui->table->rowCount();row++)
    {
        QString name;
        //判断是否必填
        name = ((QLineEdit*)ui->table->cellWidget(row, 0))->text();
        if(QString::compare(name,"")==0)
        {
            QMessageBox::information(this, tr("信息") ,QString("第%1行 质控品名称未填写").arg(row+1));
            return;
        }
        name = ((QLineEdit*)ui->table->cellWidget(row, 1))->text();
        if(QString::compare(name,"")==0)
        {
            QMessageBox::information(this, tr("信息") ,QString("第%1行 厂家未填写").arg(row+1));
            return;
        }
        name = ((QLineEdit*)ui->table->cellWidget(row, 2))->text();
        if(QString::compare(name,"")==0)
        {
            QMessageBox::information(this, tr("信息") ,QString("第%1行 产地未填写").arg(row+1));
            return;
        }
        name = ((QLineEdit*)ui->table->cellWidget(row, 6))->text();
        if(QString::compare(name,"")==0)
        {
            //QMessageBox::information(this, tr("信息") ,QString("第%1行 注册号未填写").arg(row+1));
            //return;
        }


        //判断是否重复
        int chongfu=0;

        name = ((QLineEdit*)ui->table->cellWidget(row, 0))->text();
        chongfu=IsValid(ui->table,name,0,row);
        if(chongfu>1)
        {
            QMessageBox::information(this, tr("信息") ,QString("第%1行和第%2行 质控品名称有重复").arg(row+1).arg(chongfu+1));
            return;
        }

    }

    ui->btnOK->setEnabled(false);

    QString uuid="";
    for(int row=0; row<ui->table->rowCount();row++)
    {

        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

        Material m;
        m.MaterialName = ((QLineEdit*)ui->table->cellWidget(row,0))->text();
        m.ManufacturerName = ((QLineEdit*)ui->table->cellWidget(row,1))->text();
        QVector<Manufacturer> facturers = manufacturerService.GetManufacturers(m.ManufacturerName);
        if(facturers.count()>0)
        {
            m.ManufacturerId = facturers[0].ManufacturerId;
        }
        else
        {
            Manufacturer manufacturer;
            manufacturer.ManufacturerName = m.ManufacturerName;
            manufacturer.status = 1;
            m.ManufacturerId = manufacturerService.Insert(manufacturer);
        }
        m.CountryName = ((QLineEdit*)ui->table->cellWidget(row,2))->text();
        Country country = manufacturerService.GetCountryByName(m.CountryName);
        if(country.CountryId != "")
        {
            m.CountryId = country.CountryId;
        }
        else
        {
            Country country;
            country.CountryName = m.CountryName;
            m.CountryId = countryService.Insert(country);
        }
        m.package=((QLineEdit*)ui->table->cellWidget(row,3))->text();
        m.Unit=((QLineEdit*)ui->table->cellWidget(row,4))->text();
        m.Origin=((QLineEdit*)ui->table->cellWidget(row,5))->text();
        m.RegisterNo=((QLineEdit*)ui->table->cellWidget(row,6))->text();
        m.BatchNo=((QLineEdit*)ui->table->cellWidget(row,7))->text();
        m.ValidDate=((QDateEdit*)ui->table->cellWidget(row,8))->date().toString("yyyy-MM-dd");
        m.StartDate=((QDateEdit*)ui->table->cellWidget(row,9))->date().toString("yyyy-MM-dd");

        if(QString::compare(ui->table->item(row,12)->text(),"1") == 0 ||
                (row>0 && QString::compare(((QLineEdit*)ui->table->cellWidget(row,0))->text(),((QLineEdit*)ui->table->cellWidget(row-1,0))->text()) == 0)) //合并的行
        {
            m.MaterialId=uuid;
            materialService.Update(m);
        }
        else //不是合并的行
        {
            if(QString::compare(ui->table->item(row,13)->text(),"") != 0) //编辑质控品
            {
                uuid = ui->table->item(row,13)->text();
                m.MaterialId= uuid;
                materialService.Update(m);
            }
            else //新建
            {
                uuid = materialService.Insert(m);
                m.MaterialId = uuid;
            }
        }

        QString materialBatchId=ui->table->item(row,14)->text(); //Batch Id
        if(materialBatchId == "")
        {
            MaterialBatch b;
            b.MaterialId = m.MaterialId;
            b.Unit = m.Unit;
            b.package = m.package;
            b.RegisterNo = m.RegisterNo;
            b.BatchNo = m.BatchNo;
            b.CreateTime = time;
            b.StartDate = time;
            b.Status = 1;
            b.ValidDate = ((QDateEdit*)ui->table->cellWidget(row,8))->date().toString("yyyy-MM-dd");
            materialBatchId = mbs.Insert(b);
        }
        else
        {
            MaterialBatch b;
            b.MaterialBatchId = materialBatchId;
            b.MaterialId = m.MaterialId;
            b.Unit = m.Unit;
            b.package = m.package;
            b.RegisterNo = m.RegisterNo;
            b.BatchNo = m.BatchNo;
            b.CreateTime = time;
            b.StartDate = time;
            b.Status = 1;
            b.ValidDate = ((QDateEdit*)ui->table->cellWidget(row,8))->date().toString("yyyy-MM-dd");
            mbs.Update(b);
        }
    }

    QMessageBox::information(this, tr("信息") , "保存成功");

    ManageMaterial * f = qobject_cast<ManageMaterial *>(this->parent());
    if(f!=NULL)
    {
        f->ShowAllData();
    }
    this->close();

}

//关闭
void NewMaterialBatch::on_btnCancel_clicked()
{
    this->close();
}

//查询
void NewMaterialBatch::on_pushButton_clicked()
{
    MaterialService materialService;

    QString MaterialName = ui->inputMaterialName->text();
    QString RegisterNo = ui->inputRegisterNo->text();
    QString BatchNo = ui->inputBatchNo->text();
    QString Country = ui->inputCountry->text();
    QString Menufacturer = ui->inputMenufacturer->text();

    materials = materialService.GetMaterials("","",MaterialName,Menufacturer,Country,BatchNo,RegisterNo,0);
    ui->table->setRowCount(0);
    ui->table->setRowCount(materials.count());
    for(int i=0;i<materials.count();i++)
    {
        initRow(ui->table, i, &materials[i]);

    }
}



void NewMaterialBatch::on_listWidget_clicked(const QModelIndex &index)
{
    if(listWidget != NULL)
    {
        if(listWidget->currentItem() != NULL)
        {
            QString s = listWidget->currentItem()->text();
            lineEdit->setFocus();
            lineEdit->setText(s);
        }
        listWidget->setVisible(false);
    }
}


void NewMaterialBatch::on_inputMaterialName_textChanged(const QString &arg1)
{
    lineEdit = ui->inputMaterialName;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().left()+300,lineEdit->geometry().top()+584, lineEdit->geometry().width(), 120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    MaterialService service;
    QVector<Material> m = service.GetMaterials("","", lineEdit->text(),"","",1);
    for(int i =0;i<m.count();i++)
    {
        QListWidgetItem *item;
        item = new QListWidgetItem();
        item->setText(m[i].MaterialName);
        item->setToolTip(m[i].MaterialId);
        listWidget->addItem(item);
    }
    if (listWidget->count() > 0)
    {
        listWidget->setVisible(true);
    }
    else
    {
        listWidget->setVisible(false);
    }
}

void NewMaterialBatch::on_inputRegisterNo_textChanged(const QString &arg1)
{

}

void NewMaterialBatch::on_inputBatchNo_textChanged(const QString &arg1)
{

}

void NewMaterialBatch::on_inputCountry_textChanged(const QString &arg1)
{
    lineEdit = ui->inputCountry;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().left()+300,lineEdit->geometry().top()+584, lineEdit->geometry().width(), 120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    ManufacturerService service;
    QVector<Country> m = service.GetCountries();
    for(int i =0;i<m.count();i++)
    {
        QListWidgetItem *item;
        item = new QListWidgetItem();
        item->setText(m[i].CountryName);
        item->setToolTip(m[i].CountryId);
        listWidget->addItem(item);
    }
    if (listWidget->count() > 0)
    {
        listWidget->setVisible(true);
    }
    else
    {
        listWidget->setVisible(false);
    }
}

void NewMaterialBatch::on_inputMenufacturer_textChanged(const QString &arg1)
{
    lineEdit = ui->inputMenufacturer;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().left()+300,lineEdit->geometry().top()+584, lineEdit->geometry().width(), 120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    ManufacturerService service;
    QVector<Manufacturer> m = service.GetManufacturers(lineEdit->text());
    for(int i =0;i<m.count();i++)
    {
        QListWidgetItem *item;
        item = new QListWidgetItem();
        item->setText(m[i].ManufacturerName);
        item->setToolTip(m[i].ManufacturerId);
        listWidget->addItem(item);
    }
    if (listWidget->count() > 0)
    {
        listWidget->setVisible(true);
    }
    else
    {
        listWidget->setVisible(false);
    }
}



int NewMaterialBatch::IsValid(QTableWidget *table,QString name,int col,int row0)
{
    if(QString::compare(name,"")==0)
    {
        return true;
    }

    int currentRow = row0;
    for(int row=row0; row<table->rowCount();row++)
    {
        QString value = ((QLineEdit*)table->cellWidget(row, col))->text();
        if(QString::compare(name,value)==0 && row-currentRow==1)
        {
            currentRow = row;
        }
        else if(QString::compare(name,value)==0 && row-currentRow>1)
        {
            return row;
        }
    }
    return 0;
}
bool NewMaterialBatch::IsValid(QTableWidget *table,QString name,int col, QString materialName)
{
    if(QString::compare(name,"")==0)
    {
        return true;
    }
    int count=0;
    for(int row=0; row<table->rowCount();row++)
    {
        QString value = ((QComboBox*)table->cellWidget(row, col))->currentData().toString();
        if(QString::compare(name,value)==0 && QString::compare(((QLineEdit*)table->cellWidget(row, 0))->text(),materialName)==0)
        {
            count++;
        }
    }
    if(count>1)
    {
        return false;
    }
    else
    {
        return true;
    }
}


void NewMaterialBatch::on_inputMaterialName_selectionChanged()
{
    on_inputMaterialName_textChanged(ui->inputMaterialName->text());
}

void NewMaterialBatch::on_inputRegisterNo_selectionChanged()
{
    on_inputRegisterNo_textChanged(ui->inputRegisterNo->text());
}

void NewMaterialBatch::on_inputBatchNo_selectionChanged()
{
    on_inputBatchNo_textChanged(ui->inputBatchNo->text());
}

void NewMaterialBatch::on_inputCountry_selectionChanged()
{
    on_inputCountry_textChanged(ui->inputCountry->text());
}

void NewMaterialBatch::on_inputMenufacturer_selectionChanged()
{
    on_inputMenufacturer_textChanged(ui->inputMenufacturer->text());
}

void NewMaterialBatch::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}

void NewMaterialBatch::mousePressEvent(QMouseEvent *event)
{
    if(listWidget != NULL && event->button() == Qt::LeftButton)
    {
        listWidget->setVisible(false);
    }

}

void NewMaterialBatch::closeList()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}

void NewMaterialBatch::on_inputCountry_editingFinished()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }

}

void NewMaterialBatch::on_inputMenufacturer_editingFinished()
{

    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }

}

void NewMaterialBatch::on_inputMaterialName_editingFinished()
{

    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }

}

void NewMaterialBatch::on_inputBatchNo_editingFinished()
{

    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }

}

void NewMaterialBatch::on_inputRegisterNo_editingFinished()
{

    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }

}
