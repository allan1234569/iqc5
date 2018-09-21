#include "ManageType.h"
#include "ui_ManageType.h"
#include "Model/TestType.h"
#include "Service/TestTypeService.h"
#include "Service/TestParamService.h"
#include "UI/EditType.h"
#include <QDebug>
#include <QMessageBox>
#include "Model/Category.h"
#include "Service/CategoryService.h"
#include "MainWindow.h"

ManageType::ManageType(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageType)
{
    ui->setupUi(this);

    //初始化科目下拉框
    CategoryService *categoryService = new CategoryService();
    QVector<Category> subjects = categoryService->GetCategories();
    ui->inputSubject->clear();
    ui->inputSubject->addItem(tr("全部"), "");
    Category category;
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


    this->ShowAllData();

    QString keyword = ui->inputKeyword->text();
    SearchTree(keyword);
}

void ManageType::SearchTree(QString name)
{
    TestTypeService *service;service = new TestTypeService();

    ui->treeWidget->clear();

    QVector<TestType> models =  service->GetTestTypes("","",name);

    if(models.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<models[0].SubjectName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* ca2 = new QTreeWidgetItem(QStringList()<<models[0].CategoryName);
        ca->addChild(ca2);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[0].TestTypeCode);
        pItem->setToolTip(0, QString("%1").arg(models[0].TestTypeId));
        ca2->addChild(pItem);

        for(int i=1;i<models.count();i++)
        {
            if(QString::compare(models[i].SubjectName, models[i-1].SubjectName) != 0)
            {
                ca = new QTreeWidgetItem(QStringList()<<models[i].SubjectName);
                ui->treeWidget->addTopLevelItem(ca);
            }

            if(QString::compare(models[i].CategoryName, models[i-1].CategoryName) != 0)
            {
                ca2 = new QTreeWidgetItem(QStringList()<<models[i].CategoryName);
                ca->addChild(ca2);
            }

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[i].TestTypeCode);
            pItem->setToolTip(0, QString("%1").arg(models[i].TestTypeId));
            ca2->addChild(pItem);
        }

    }
    ui->treeWidget->expandAll();

    //this->ShowAllData();
}

ManageType::~ManageType()
{
    delete ui;
}

void ManageType::ShowAllData()
{
    ShowAllData(ui->inputSubject->itemData(ui->inputSubject->currentIndex()).toString(), ui->inputCategory->itemData(ui->inputCategory->currentIndex()).toString(), ui->txtName->text());
}

void ManageType::ShowAllData(QString subjectId, QString categoryId, QString name)
{
    TestTypeService service;
    model = service.GetTestTypes(subjectId, categoryId, name);

    ui->table->setColumnCount(6);
    ui->table->setRowCount(model.count());
    QStringList headers;
    headers  << tr("英文简写")<< tr("中文全称")<< tr("专业") << tr("亚专业")  <<tr("编辑")<< tr("删除");
    ui->table->setHorizontalHeaderLabels(headers);
    for(int i=0;i<model.count();i++)
    {
        ui->table->setItem(i, 0, new QTableWidgetItem(model[i].TestTypeCode));
        ui->table->setItem(i, 1, new QTableWidgetItem(model[i].TestTypeName));
        ui->table->setItem(i, 2, new QTableWidgetItem(model[i].SubjectName));
        ui->table->setItem(i, 3, new QTableWidgetItem(model[i].CategoryName));

        QPushButton *editButton=new QPushButton(tr("编辑"));
        editButton->setToolTip(QString("%1").arg(model[i].TestTypeId));
        connect(editButton,SIGNAL(clicked()),this,SLOT(OnBtnTableEditClicked()));
        ui->table->setCellWidget(i,4,editButton);

        QPushButton *deleteButton=new QPushButton(tr("删除"));
        deleteButton->setToolTip(QString("%1").arg(model[i].TestTypeId));
        connect(deleteButton,SIGNAL(clicked()),this,SLOT(OnBtnTableDeleteClicked()));
        ui->table->setCellWidget(i,5,deleteButton);
    }
    ui->table->resizeRowsToContents();
}

void ManageType::OnBtnTableEditClicked()
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

    EditType *form = new EditType(this);
    form->SetModel(pbt->toolTip());
    form->show();
}

void ManageType::OnBtnTableDeleteClicked()
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

    TestTypeService *service = new TestTypeService();
    service->DeleteById(pbt->toolTip());
    ShowAllData();
}

void ManageType::on_btnCancel_clicked()
{
    this->close();
}

void ManageType::on_btnAdd_clicked()
{
    EditType *form = new EditType(this);
    form->show();
}

void ManageType::on_btnSearch_clicked()
{
    ShowAllData();
}

void ManageType::on_inputSubject_currentIndexChanged(int index)
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

void ManageType::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item->childCount() == 0)
    {
        ui->txtName->setText(item->text(0));
        EditType *form = new EditType(this);
        form->SetModel(item->toolTip(0));
        form->show();
    }
}

void ManageType::on_inputKeyword_textChanged(const QString &arg1)
{
    QString keyword = ui->inputKeyword->text();
    SearchTree(keyword);
}


void ManageType::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}
