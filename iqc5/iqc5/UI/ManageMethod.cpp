#include "ManageMethod.h"
#include "ui_ManageMethod.h"
#include "Model/Method.h"
#include "Service/MethodService.h"
#include "UI/EditMethod.h"
#include <QDebug>
#include <QMessageBox>
#include "Model/Category.h"
#include "Service/CategoryService.h"
#include "MainWindow.h"

ManageMethod::ManageMethod(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageMethod)
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

void ManageMethod::SearchTree(QString name)
{
    MethodService *service;service = new MethodService();

    ui->treeWidget->clear();

    QVector<Method> models =  service->GetMethods("","",name,0);

    if(models.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<models[0].SubjectName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* ca2 = new QTreeWidgetItem(QStringList()<<models[0].CategoryName);
        ca->addChild(ca2);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[0].MethodName);
        pItem->setToolTip(0, QString("%1").arg(models[0].MethodId));
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

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[i].MethodName);
            pItem->setToolTip(0, QString("%1").arg(models[i].MethodId));
            ca2->addChild(pItem);
        }

    }
    ui->treeWidget->expandAll();

    //this->ShowAllData();
}

void ManageMethod::on_inputKeyword_textChanged(const QString &arg1)
{
    QString keyword = ui->inputKeyword->text();
    SearchTree(keyword);
}

ManageMethod::~ManageMethod()
{
    delete ui;
}

void ManageMethod::ShowAllData()
{
    ShowAllData(ui->inputSubject->itemData(ui->inputSubject->currentIndex()).toString(),ui->inputCategory->itemData(ui->inputCategory->currentIndex()).toString(), ui->txtName->text());
}

void ManageMethod::ShowAllData(QString subjectId,QString categoryId, QString name)
{
    MethodService service;
    model = service.GetMethods(subjectId,categoryId, name,0);

    ui->table->setColumnCount(4);
    ui->table->setRowCount(model.count());
    QStringList headers;
    headers << tr("科目") << tr("名称")<< tr("编辑")<< tr("删除");
    ui->table->setHorizontalHeaderLabels(headers);
    for(int i=0;i<model.count();i++)
    {
        //ui->table->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(model[i].Id)));
        ui->table->setItem(i, 0, new QTableWidgetItem(model[i].CategoryName));
        ui->table->setItem(i, 1, new QTableWidgetItem(model[i].MethodName));

        QPushButton *editButton=new QPushButton(tr("编辑"));
        editButton->setToolTip(QString("%1").arg(model[i].MethodId));
        connect(editButton,SIGNAL(clicked()),this,SLOT(OnBtnTableEditClicked()));
        ui->table->setCellWidget(i,2,editButton);

        QPushButton *deleteButton=new QPushButton(tr("删除"));
        deleteButton->setToolTip(QString("%1").arg(model[i].MethodId));
        connect(deleteButton,SIGNAL(clicked()),this,SLOT(OnBtnTableDeleteClicked()));
        ui->table->setCellWidget(i,3,deleteButton);
    }
    ui->table->setColumnHidden(0,true);
    ui->table->resizeRowsToContents();
    ui->table->resizeColumnsToContents();
}

void ManageMethod::OnBtnTableEditClicked()
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

    EditMethod *form = new EditMethod(this);
    form->SetModel(pbt->toolTip());
    form->show();
}

void ManageMethod::OnBtnTableDeleteClicked()
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

    MethodService *service = new MethodService();
    service->DeleteById(pbt->toolTip());
    ShowAllData();
}

void ManageMethod::on_btnCancel_clicked()
{
    this->close();
}

void ManageMethod::on_btnAdd_clicked()
{
    EditMethod *form = new EditMethod(this);
    form->show();
}

void ManageMethod::on_btnSearch_clicked()
{
    ShowAllData();
}

void ManageMethod::on_inputSubject_currentIndexChanged(int index)
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

void ManageMethod::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item->childCount() == 0)
    {
        ui->txtName->setText(item->text(0));
        EditMethod *form = new EditMethod(this);
        form->SetModel(item->toolTip(0));
        form->show();
    }
}

void ManageMethod::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}
