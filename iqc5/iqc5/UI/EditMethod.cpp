#include "EditMethod.h"
#include "ui_EditMethod.h"
#include "Service/CategoryService.h"
#include "Service/MethodService.h"
#include "UI/ManageMethod.h"
#include <QMessageBox>

EditMethod::EditMethod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMethod)
{
    ui->setupUi(this);

    methodId = "";

    //初始化科目下拉框
    CategoryService *categoryService = new CategoryService();
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

void EditMethod::SetModel(QString id)
{
    if(id != 0)
    {
        MethodService service;
        methodId = id;
        this->setWindowTitle("修改");
        Method method =service.GetById(id);

        for(int i=0;i<ui->inputSubject->count();i++)
        {
            if(method.SubjectId== ui->inputSubject->itemData(i).toString())
            {
                ui->inputSubject->setCurrentIndex(i);
                on_inputSubject_currentIndexChanged(i);
                break;
            }
        }

        for(int i=0;i<ui->inputCategory->count();i++)
        {
            if(method.CategoryId== ui->inputCategory->itemData(i).toString())
            {
                ui->inputCategory->setCurrentIndex(i);
                break;
            }
        }
        ui->inputName->setText(method.MethodName);
    }
}

EditMethod::~EditMethod()
{
    delete ui;
}

void EditMethod::on_btnCancel_clicked()
{
    this->close();
}

void EditMethod::on_btnOK_clicked()
{
    if( ui->inputName->text() == "")
    {
        QMessageBox::information(this, tr("信息") ,tr("方法名称不能为空"));
        return;
    }
    Method m;
    m.MethodId = methodId;
    m.MethodName = ui->inputName->text();
    m.CategoryId = ui->inputCategory->itemData(ui->inputCategory->currentIndex()).toString();

    MethodService service;
    if(methodId == 0)
    {
        service.Insert(m);
    }
    else
    {
        service.Update(m);
    }

    ManageMethod * f = qobject_cast<ManageMethod *>(this->parent());
    if(f!=NULL)
    {
        f->ShowAllData();
    }
    this->close();
}

void EditMethod::on_inputSubject_currentIndexChanged(int index)
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
void EditMethod::SetName(QString name)
{
    ui->inputName->setText(name);
}
