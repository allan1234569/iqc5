#include "ManageReagent.h"
#include "ui_ManageReagent.h"
#include "Model/Manufacturer.h"
#include "Model/Reagent.h"
#include "Service/ManufacturerService.h"
#include "Service/ReagentService.h"
#include "UI/EditReagent.h"
#include <QDebug>
#include <QMessageBox>
#include "Model/Category.h"
#include "Service/CategoryService.h"
#include "MainWindow.h"
#include "UI/NewReagentBatch.h"

ManageReagent::ManageReagent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageReagent)
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


void ManageReagent::InitTree()
{
    ReagentService *service;service = new ReagentService();
    QString keyword = ui->inputKeyword->text();

    ui->treeWidget->clear();

    QVector<Reagent> models = service->GetReagents("", "", keyword, "","",0);

    if(models.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<models[0].ManufacturerName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[0].ReagentName);
        pItem->setToolTip(0, QString("%1").arg(models[0].ReagentId));
        ca->addChild(pItem);

        for(int i=1;i<models.count();i++)
        {
            if(QString::compare(models[i].ManufacturerName, models[i-1].ManufacturerName) != 0)
            {
                ca = new QTreeWidgetItem(QStringList()<<models[i].ManufacturerName);
                ui->treeWidget->addTopLevelItem(ca);
            }

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[i].ReagentName);
            pItem->setToolTip(0, QString("%1").arg(models[i].ReagentId));
            ca->addChild(pItem);
        }
    }
    ui->treeWidget->expandAll();

}

void ManageReagent::ShowAllData()
{
    ShowAllData(ui->inputSubject->itemData(ui->inputSubject->currentIndex()).toString(),ui->inputCategory->itemData(ui->inputCategory->currentIndex()).toString(), ui->inputName->text(), ui->inputManufacturer->text(),ui->inputCountry->text(),"","");
}

void ManageReagent::ShowAllData(QString subjectId, QString categoryId, QString name, QString Manufacturer, QString Country,QString registerNo, QString batchNo)
{
    ReagentService service;
    model = service.GetReagents(subjectId, categoryId, name, Manufacturer, Country, 0);

    ui->table->setColumnCount(6);
    ui->table->setRowCount(model.count());
    QStringList headers;
    headers << tr("试剂")<< tr("检测项目") << tr("生产商") << tr("生产国")<< tr("编辑")<< tr("删除");
    ui->table->setHorizontalHeaderLabels(headers);
    for(int i=0;i<model.count();i++)
    {
        //ui->table->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(model[i].Id)));
        ui->table->setItem(i, 0, new QTableWidgetItem(model[i].ReagentName));
        ui->table->setItem(i, 1, new QTableWidgetItem(model[i].ProjectName));
        ui->table->setItem(i, 2, new QTableWidgetItem(model[i].ManufacturerName));
        ui->table->setItem(i, 3, new QTableWidgetItem(model[i].CountryName));

        QPushButton *editButton=new QPushButton(tr("编辑"));
        editButton->setToolTip(QString("%1").arg(model[i].ReagentId));
        connect(editButton,SIGNAL(clicked()),this,SLOT(OnBtnTableEditClicked()));
        ui->table->setCellWidget(i,4,editButton);

        QPushButton *deleteButton=new QPushButton(tr("删除"));
        deleteButton->setToolTip(QString("%1").arg(model[i].ReagentId));
        connect(deleteButton,SIGNAL(clicked()),this,SLOT(OnBtnTableDeleteClicked()));
        ui->table->setCellWidget(i,5,deleteButton);

    }
    ui->table->resizeRowsToContents();

    ui->table->setColumnWidth(0, 200);
    ui->table->setColumnWidth(2, 80);
    ui->table->setColumnWidth(3, 80);

}

void ManageReagent::OnBtnTableEditClicked()
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

    EditReagent *form = new EditReagent(this);
    form->SetModel(pbt->toolTip());
    form->showMaximized();
}

void ManageReagent::OnBtnTableDeleteClicked()
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

    ReagentService *service = new ReagentService();
    service->DeleteById(pbt->toolTip());
    ShowAllData();
}

ManageReagent::~ManageReagent()
{
    delete ui;
}

void ManageReagent::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
}

void ManageReagent::on_btnAdd_clicked()
{
    //EditReagent *form = new EditReagent(this);
    NewReagentBatch *form = new NewReagentBatch(this);
    form->showMaximized();
}

void ManageReagent::on_btnSearch_clicked()
{
    ShowAllData();
}

void ManageReagent::on_inputKeyword_textChanged(const QString &arg1)
{
    InitTree();
}

void ManageReagent::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
//    if(item->childCount() == 0)
//    {
//        ui->inputManufacturer->setText(item->parent()->text(0));
//        ui->inputName->setText(item->text(0));
//        EditReagent *form = new EditReagent(this);
//        form->SetModel(item->toolTip(0));
//        form->show();
//    }

    if(item->childCount() == 0)
    {
        ShowAllData("","",item->text(0),item->parent()->text(0),"","","");
    }
    else
    {
        ShowAllData("","","",item->text(0),"","","");
    }
}

void ManageReagent::on_inputSubject_currentIndexChanged(int index)
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

void ManageReagent::on_btnClose_clicked()
{
    this->close();
}

void ManageReagent::on_inputCountry_textChanged(const QString &arg1)
{
    lineEdit = ui->inputCountry;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+226,lineEdit->geometry().top()+40, lineEdit->geometry().width(), 120);
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

void ManageReagent::on_inputManufacturer_textChanged(const QString &arg1)
{
    lineEdit = ui->inputManufacturer;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+226,lineEdit->geometry().top()+40, lineEdit->geometry().width(), 120);
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

void ManageReagent::on_inputName_textChanged(const QString &arg1)
{
    lineEdit = ui->inputName;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().x()+226,lineEdit->geometry().top()+40, lineEdit->geometry().width(), 120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    ReagentService service;
    QVector<Reagent> m = service.GetReagents("","", lineEdit->text(), "","",1);
    for(int i =0;i<m.count();i++)
    {
        QListWidgetItem *item;
        item = new QListWidgetItem();
        item->setText(m[i].ReagentName);
        item->setToolTip(m[i].ReagentId);
        listWidget->addItem(item);
    }
    listWidget->setVisible(true);
}


void ManageReagent::keyPressEvent (QKeyEvent * keyevent)
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

void ManageReagent::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}


void ManageReagent::on_inputCountry_editingFinished()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}

void ManageReagent::on_inputManufacturer_editingFinished()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}

void ManageReagent::on_inputName_editingFinished()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}

void ManageReagent::on_inputCountry_selectionChanged()
{
    on_inputCountry_textChanged(ui->inputCountry->text());
}

void ManageReagent::on_inputManufacturer_selectionChanged()
{
    on_inputManufacturer_textChanged(ui->inputManufacturer->text());
}

void ManageReagent::on_inputName_selectionChanged()
{
    on_inputName_textChanged(ui->inputName->text());
}

void ManageReagent::mousePressEvent(QMouseEvent *event)
{
    if(listWidget != NULL && event->button() == Qt::LeftButton)
    {
        listWidget->setVisible(false);
    }
}

void ManageReagent::on_listWidget_clicked(const QModelIndex &index)
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
