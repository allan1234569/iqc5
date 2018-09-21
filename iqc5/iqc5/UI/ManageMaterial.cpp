#include "ManageMaterial.h"
#include "ui_ManageMaterial.h"
#include "Model/Manufacturer.h"
#include "Model/Material.h"
#include "Service/ManufacturerService.h"
#include "Service/MaterialService.h"
#include "UI/EditMaterial.h"
#include <QDebug>
#include <QMessageBox>
#include "MainWindow.h"
#include "Model/Category.h"
#include "Service/CategoryService.h"
#include "UI/NewMaterialBatch.h"

ManageMaterial::ManageMaterial(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageMaterial)
{
    listWidget = 0;

    ui->setupUi(this);

    //初始化科目下拉框
    CategoryService *categoryService = new CategoryService();
    QVector<Category> subjects = categoryService->GetCategories();
    ui->inputSubject->clear();
    Category category;
    ui->inputSubject->addItem(tr("全部"), "");
    foreach(category, subjects)
    {
        ui->inputSubject->addItem(category.CategoryName, category.CategoryId);
    }
    ui->inputSubject->setCurrentIndex(0);

    QString firstSubjectId = ui->inputSubject->itemData(0).toString();
    QVector<Category> categories = categoryService->GetCategories(firstSubjectId);

    ui->inputCategory->clear();
    ui->inputCategory->addItem(tr("全部"), "");
    foreach(category, categories)
    {
        ui->inputCategory->addItem(category.CategoryName, category.CategoryId);
    }
    ui->inputCategory->setCurrentIndex(0);

    InitTree();

    this->ShowAllData();

}


void ManageMaterial::InitTree()
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

void ManageMaterial::ShowAllData()
{
    QString subjectId=ui->inputSubject->itemData(ui->inputSubject->currentIndex()).toString();
    QString categoryId=ui->inputCategory->itemData(ui->inputCategory->currentIndex()).toString();
    ShowAllData(subjectId, categoryId, ui->inputName->text(),ui->inputManufacturer->text(),ui->inputCountry->text(), "", "");
}

void ManageMaterial::ShowAllData(QString subjectId, QString categoryId, QString name, QString Manufacturer, QString country, QString registerNo, QString batchNo)
{
    MaterialService *materialService;
    materialService = new MaterialService();

    QVector<Material> model = materialService->GetMaterials(subjectId,categoryId, name, Manufacturer, country, 0);

    ui->table->setColumnCount(6);
    ui->table->setRowCount(model.count());
    QStringList headers;
    headers << tr("质控品") << tr("生产商") << tr("生产国") << tr("来源") << tr("编辑")<< tr("删除");
    ui->table->setHorizontalHeaderLabels(headers);

    for(int i=0;i<model.count();i++)
    {
        //ui->table->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(model[i].Id)));
        ui->table->setItem(i, 0, new QTableWidgetItem(model[i].MaterialName));
        ui->table->setItem(i, 1, new QTableWidgetItem(model[i].ManufacturerName));
        ui->table->setItem(i, 2, new QTableWidgetItem(model[i].CountryName));
        ui->table->setItem(i, 3, new QTableWidgetItem(model[i].Origin));


        QPushButton *editButton=new QPushButton(tr("编辑"));
        editButton->setToolTip(QString("%1").arg(model[i].MaterialId));
        connect(editButton,SIGNAL(clicked()),this,SLOT(OnBtnTableEditClicked()));
        ui->table->setCellWidget(i,4,editButton);

        QPushButton *deleteButton=new QPushButton(tr("删除"));
        deleteButton->setToolTip(QString("%1").arg(model[i].MaterialId));
        connect(deleteButton,SIGNAL(clicked()),this,SLOT(OnBtnTableDeleteClicked()));
        ui->table->setCellWidget(i,5,deleteButton);

    }
    ui->table->resizeRowsToContents();

    ui->table->setColumnWidth(0, 200);
    ui->table->setColumnWidth(2, 80);
    ui->table->setColumnWidth(3, 80);
}


void ManageMaterial::OnBtnTableEditClicked()
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

    EditMaterial *form = new EditMaterial(this);
    form->SetModel(pbt->toolTip());
    form->showMaximized();
}

void ManageMaterial::OnBtnTableDeleteClicked()
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

    MaterialService *service = new MaterialService();
    service->DeleteById(pbt->toolTip());
    ShowAllData();
}

ManageMaterial::~ManageMaterial()
{
    delete ui;
}

void ManageMaterial::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
}

void ManageMaterial::on_btnSearch_clicked()
{
    this->ShowAllData();
}

void ManageMaterial::on_inputKeyword_textChanged(const QString &arg1)
{
    InitTree();
}

void ManageMaterial::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
//    if(item->childCount() == 0)
//    {
//        ui->inputManufacturer->setText(item->parent()->text(0));
//        ui->inputName->setText(item->text(0));
//        EditMaterial *form = new EditMaterial(this);
//        form->SetModel(item->toolTip(0));
//        form->show();
//    }

    if(item->childCount() == 0)
    {
        ShowAllData("","",item->text(0),item->parent()->text(0),"", "", "");
    }
    else
    {
        ShowAllData("","","",item->text(0),"", "", "");
    }
}

void ManageMaterial::on_inputSubject_currentIndexChanged(int index)
{
    //初始化亚专业下拉框
    CategoryService *categoryService = new CategoryService();

    QString subjectId = ui->inputSubject->itemData(index).toString();
    QVector<Category> categories = categoryService->GetCategories(subjectId);

    ui->inputCategory->clear();
    ui->inputCategory->addItem(tr("全部"), "");
    Category category;
    foreach(category, categories)
    {
        ui->inputCategory->addItem(category.CategoryName, category.CategoryId);
    }
}


void ManageMaterial::on_btnClose_clicked()
{
    this->close();
}

void ManageMaterial::on_inputCountry_textChanged(const QString &arg1)
{
    lineEdit = ui->inputCountry;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+310,lineEdit->geometry().top()+48, lineEdit->geometry().width(), 120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    ManufacturerService service;
    QVector<Country> m = service.GetCountries();
    for(int i =0;i<m.count();i++)
    {
        QListWidgetItem *item;
        item = new QListWidgetItem();
        item->setText(m[i].CountryName);
        item->setToolTip(m[i].CountryName);
        listWidget->addItem(item);
    }
    listWidget->setVisible(true);
}

void ManageMaterial::on_inputManufacturer_textChanged(const QString &arg1)
{
    lineEdit = ui->inputManufacturer;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+310,lineEdit->geometry().top()+48, lineEdit->geometry().width(), 120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    ManufacturerService service;
    QVector<Manufacturer> m = service.GetManufacturers(lineEdit->text());
    for(int i =0;i<m.count();i++)
    {
        QListWidgetItem *item;
        item = new QListWidgetItem();
        item->setText(m[i].ManufacturerName);
        item->setToolTip(m[i].ManufacturerName);
        listWidget->addItem(item);
    }
    listWidget->setVisible(true);
}

void ManageMaterial::on_inputName_textChanged(const QString &arg1)
{
    lineEdit = ui->inputName;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+310,lineEdit->geometry().top()+48, lineEdit->geometry().width(), 120);
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
    listWidget->setVisible(true);
}


void ManageMaterial::keyPressEvent (QKeyEvent * keyevent)
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
                lineEdit->setText(s);
            }
            listWidget->setVisible(false);
        }
    }
}


void ManageMaterial::on_btnAdd_clicked()
{
    //EditMaterial *form = new EditMaterial(this);
    NewMaterialBatch *form = new NewMaterialBatch(this);
    form->showMaximized();
}

void ManageMaterial::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}

void ManageMaterial::on_inputCountry_editingFinished()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}

void ManageMaterial::on_inputManufacturer_editingFinished()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}

void ManageMaterial::on_inputName_editingFinished()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}

void ManageMaterial::on_inputCountry_selectionChanged()
{
    on_inputCountry_textChanged(ui->inputCountry->text());
}

void ManageMaterial::on_inputManufacturer_selectionChanged()
{
    on_inputManufacturer_textChanged(ui->inputManufacturer->text());
}

void ManageMaterial::on_inputName_selectionChanged()
{
    on_inputName_textChanged(ui->inputName->text());
}

void ManageMaterial::mousePressEvent(QMouseEvent *event)
{
    if(listWidget != NULL && event->button() == Qt::LeftButton)
    {
        listWidget->setVisible(false);
    }
}

void ManageMaterial::on_listWidget_clicked(const QModelIndex &index)
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
