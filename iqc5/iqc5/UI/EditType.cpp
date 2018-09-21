#include "EditType.h"
#include "ui_EditType.h"
#include "Service/CategoryService.h"
#include "Service/TestTypeService.h"
#include "Service/TestParamService.h"
#include "UI/ManageType.h"
#include <QMessageBox>
#include <QDebug>

EditType::EditType(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditType)
{
    ui->setupUi(this);

    testTypeId = "";

    //初始化科目下拉框
    CategoryService *categoryService;categoryService = new CategoryService();
    QVector<Category> subjects = categoryService->GetCategories();
    ui->inputSubject->clear();
    Category category;
    foreach(category, subjects)
    {
        ui->inputSubject->addItem(category.CategoryName, category.CategoryId);
    }
    ui->inputSubject->setCurrentIndex(0);

    QString firstSubjectId = ui->inputSubject->itemData(0).toString();
    QVector<Category> categories = categoryService->GetCategories(firstSubjectId);

    ui->inputCategory->clear();
    foreach(category, categories)
    {
        ui->inputCategory->addItem(category.CategoryName, category.CategoryId);
    }
    ui->inputCategory->setCurrentIndex(0);


}

void EditType::SetModel(QString id)
{
    if(id != 0)
    {
        TestTypeService service;
        testTypeId = id;
        this->setWindowTitle("修改");
        TestType testType =service.GetById(id);

        for(int i=0;i<ui->inputSubject->count();i++)
        {
            if(testType.SubjectId== ui->inputSubject->itemData(i).toString())
            {
                ui->inputSubject->setCurrentIndex(i);
                on_inputSubject_currentIndexChanged(i);
                break;
            }
        }

        for(int i=0;i<ui->inputCategory->count();i++)
        {
            if(testType.CategoryId== ui->inputCategory->itemData(i).toString())
            {
                ui->inputCategory->setCurrentIndex(i);
                break;
            }
        }

       ui->inputTestTypeName->setText(testType.TestTypeName);
       ui->inputTestTypeCode->setText(testType.TestTypeCode);

    }
}

EditType::~EditType()
{
    delete ui;
}

void EditType::on_btnCancel_clicked()
{
    this->close();
}

void EditType::on_btnOK_clicked()
{
    if( ui->inputSubject->currentIndex() < 0)
    {
        QMessageBox::information(this, tr("信息") ,tr("专业不能为空"));
        return;
    }

    if( ui->inputCategory->currentIndex() < 0)
    {
        QMessageBox::information(this, tr("信息") ,tr("亚专业不能为空"));
        return;
    }

    TestType m;
    m.TestTypeId = testTypeId;
    m.CategoryId = ui->inputCategory->itemData(ui->inputCategory->currentIndex()).toString();
    m.TestTypeCode = ui->inputTestTypeCode->text();
    m.TestTypeName = ui->inputTestTypeName->text();

    TestTypeService service;
    if(testTypeId == 0)
    {
        service.Insert(m);
    }
    else
    {
        service.Update(m);
    }

    ManageType * f = qobject_cast<ManageType *>(this->parent());
    if(f!=NULL)
    {
        f->ShowAllData();
    }
    this->close();
}

void EditType::on_inputCategory_currentIndexChanged(int index)
{

}

void EditType::on_inputSubject_currentIndexChanged(int index)
{
    //初始化亚专业下拉框
    CategoryService *categoryService = new CategoryService();

    QString subjectId = ui->inputSubject->itemData(index).toString();
    QVector<Category> categories = categoryService->GetCategories(subjectId);

    ui->inputCategory->clear();
    Category category;
    foreach(category, categories)
    {
        ui->inputCategory->addItem(category.CategoryName, category.CategoryId);
    }
}
