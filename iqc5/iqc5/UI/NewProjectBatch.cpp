#include "NewProjectBatch.h"
#include "ui_NewProjectBatch.h"
#include "Service/CategoryService.h"
#include "Service/MaterialService.h"
#include "Service/ReagentService.h"
#include "Service/MethodService.h"
#include "Service/DeviceService.h"
#include "Service/TestTypeService.h"
#include "Service/ProjectService.h"
#include "Service/MaterialBatchService.h"
#include "Service/ReagentBatchService.h"
#include "UI/ConfigColumn.h"
#include "UI/EditMaterial.h"
#include "UI/EditReagent.h"
#include "UI/EditMethod.h"
#include "UI/EditDevice.h"
#include <QDebug>
#include <QMessageBox>
#include <QlistWidget>
#include "MainWindow.h"

NewProjectBatch::NewProjectBatch(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewProjectBatch)
{
    ui->setupUi(this);

    listWidget = NULL;

    ui->table->setColumnCount(17);
    QStringList headers;
    headers << tr("自定义名称") << tr("英文简称")<< tr("中文名称")<< tr("专业")<< tr("亚专业")<< tr("浓度\n水平")<< tr("检测\n次数")<< tr("质控品")<< tr("质控品批号")<< tr("试剂")<< tr("试剂批号")<< tr("方法")<< tr("仪器")<< tr("顺序 ")<<tr("添加")<<tr("删除");
    ui->table->setHorizontalHeaderLabels(headers);
    ui->table->setColumnWidth(0,70);
    ui->table->setColumnWidth(1,70);
    ui->table->setColumnWidth(2,120);
    ui->table->setColumnWidth(5,40);
    ui->table->setColumnWidth(6,40);
    ui->table->setColumnWidth(14,40);
    ui->table->setColumnWidth(15,40);

    ui->table->setColumnHidden(16,true);
    showCols();

    //专业
    CategoryService categoryService;
    QVector<Category> subjects = categoryService.GetCategories();
    ui->inputSubject->clear();
    ui->inputSubject->addItem("全部", "");
    foreach(Category category, subjects)
    {
        ui->inputSubject->addItem(category.CategoryName, category.CategoryId);
    }
    //亚专业
    QString id = ui->inputSubject->itemData(ui->inputSubject->currentIndex()).toString();
    QVector<Category> categories = categoryService.GetCategories(id);
    ui->inputCategory->clear();
    ui->inputCategory->addItem("全部", "");
    foreach(Category category, categories)
    {
        ui->inputCategory->addItem(category.CategoryName, category.CategoryId);
    }
}

NewProjectBatch::~NewProjectBatch()
{
    delete ui;

}


void NewProjectBatch::initRow(QTableWidget *table, int row, Project *project)
{
    if(table->cellWidget(row,0)==NULL) //自定义名称
    {
        QLineEdit *control = new QLineEdit();
        if(project != NULL)
        {
            control->setText(project->CustomName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(customName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(customName_changed()));
        connect(control,SIGNAL(editingFinished()),this,SLOT(closeList()));
        table->setCellWidget(row, 0, control);
    }
    if(table->cellWidget(row,1)==NULL) //英文名称
    {
        QLineEdit *control = new QLineEdit();
        if(project != NULL)
        {
            control->setText(project->EnglishName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(englishName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(englishName_changed()));
        connect(control,SIGNAL(editingFinished()),this,SLOT(closeList()));
        table->setCellWidget(row, 1, control);
    }
    if(table->cellWidget(row,2)==NULL) //中文名称
    {
        QLineEdit *control = new QLineEdit();
        if(project != NULL)
        {
            control->setText(project->ProjectName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(chineseName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(chineseName_changed()));
        connect(control,SIGNAL(editingFinished()),this,SLOT(closeList()));
        table->setCellWidget(row, 2, control);
    }

    if(table->cellWidget(row,3)==NULL) //专业
    {
        QComboBox *control;
        control = new QComboBox();
        CategoryService categoryService;
        QVector<Category> categories = categoryService.GetCategories();
        control->clear();
        foreach(Category category, categories)
        {
            control->addItem(category.CategoryName, category.CategoryId);
        }
        if(project != NULL)
        {
            for(int i=0;i<control->count();i++)
            {
                if(QString::compare(control->itemData(i).toString(), project->testType.SubjectId)==0)
                {
                    control->setCurrentIndex(i);
                    break;
                }
            }
        }
        connect(control,SIGNAL(currentIndexChanged(int)),this,SLOT(subject_changed(int)));
        table->setCellWidget(row, 3, control);
    }

    if(table->cellWidget(row,4)==NULL) //亚专业
    {
        QString id = ((QComboBox*)table->cellWidget(row,3))->itemData(((QComboBox*)table->cellWidget(row,3))->currentIndex()).toString();
        QComboBox *control;
        control = new QComboBox();
        CategoryService categoryService;
        QVector<Category> categories = categoryService.GetCategories(id);
        control->clear();
        foreach(Category category, categories)
        {
            control->addItem(category.CategoryName, category.CategoryId);
        }
        if(project != NULL)
        {
            for(int i=0;i<control->count();i++)
            {
                if(QString::compare(control->itemData(i).toString(), project->testType.CategoryId)==0)
                {
                    control->setCurrentIndex(i);
                    break;
                }
            }
        }
        connect(control,SIGNAL(currentIndexChanged(int)),this,SLOT(category_changed(int)));
        table->setCellWidget(row, 4, control);
    }

    if(table->item(row,5) == NULL) //浓度
    {
        QComboBox *control = new QComboBox();
        control->clear();
        for(int i=1;i<=6;i++)
        {
            control->addItem(QString("L%1").arg(i), QString("%1").arg(i));
        }
        if(project != NULL)
        {
            for(int i=0;i<control->count();i++)
            {
                if(control->itemData(i).toInt() == project->level)
                {
                    control->setCurrentIndex(i);
                    break;
                }
            }
        }
        connect(control,SIGNAL(currentIndexChanged(int)),this,SLOT(level_changed(int)));
        table->setCellWidget(row, 5, control);
    }
    if(table->item(row,6) == NULL) //检测次数
    {
        QComboBox *control = new QComboBox();
        control->clear();
        for(int i=1;i<=6;i++)
        {
            control->addItem(QString("%1").arg(i), QString("%1").arg(i));
        }
        if(project != NULL)
        {
            for(int i=0;i<control->count();i++)
            {
                if(control->itemData(i).toInt() == project->PerDayBatch)
                {
                    control->setCurrentIndex(i);
                    break;
                }
            }
        }
        connect(control,SIGNAL(currentIndexChanged(int)),this,SLOT(num_changed(int)));
        table->setCellWidget(row, 6, control);
    }
    if(table->item(row,7) == NULL) //质控品
    {
        QLineEdit *control = new QLineEdit();
        if(project != NULL)
        {
            control->setText(project->MaterialName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(materialName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(materialName_changed()));
        connect(control,SIGNAL(editingFinished()),this,SLOT(closeList()));
        table->setCellWidget(row, 7, control);
    }
    if(table->item(row,8) == NULL) //质控品批号
    {
        QLineEdit *control = new QLineEdit();
        if(project != NULL)
        {
            control->setText(project->CurrentMaterialBatch);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(materialBatchName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(materialBatchName_changed()));
        connect(control,SIGNAL(editingFinished()),this,SLOT(closeList()));
        table->setCellWidget(row, 8, control);
    }
    if(table->item(row,9) == NULL) //试剂
    {
        QLineEdit *control = new QLineEdit();
        if(project != NULL)
        {
            control->setText(project->ReagentName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(reagentName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(reagentName_changed()));
        connect(control,SIGNAL(editingFinished()),this,SLOT(closeList()));
        table->setCellWidget(row, 9, control);
    }
    if(table->item(row,10) == NULL) //试剂批号
    {
        QLineEdit *control = new QLineEdit();
        if(project != NULL)
        {
            control->setText(project->CurrentReagentBatch);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(reagentBatchName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(reagentBatchName_changed()));
        connect(control,SIGNAL(editingFinished()),this,SLOT(closeList()));
        table->setCellWidget(row, 10, control);
    }
    if(table->item(row,11) == NULL)//方法
    {
        QLineEdit *control = new QLineEdit();
        if(project != NULL)
        {
            control->setText(project->MethodName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(methodName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(methodName_changed()));
        connect(control,SIGNAL(editingFinished()),this,SLOT(closeList()));
        table->setCellWidget(row, 11, control);
    }
    if(table->item(row,12) == NULL)//仪器
    {
        QLineEdit *control = new QLineEdit();
        if(project != NULL)
        {
            control->setText(project->DeviceName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(device_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(device_changed()));
        connect(control,SIGNAL(editingFinished()),this,SLOT(closeList()));
        table->setCellWidget(row, 12, control);
    }
    if(table->item(row,13) == NULL)//顺序
    {
        QLineEdit *control = new QLineEdit();
        if(project != NULL)
        {
            control->setText(QString("%1").arg(project->DispIdx));
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(displayIndex_changed(QString)));
        connect(control,SIGNAL(editingFinished()),this,SLOT(closeList()));
        table->setCellWidget(row, 13, control);
    }

    if(table->item(row,14) == NULL)//添加
    {
        QPushButton *control = new QPushButton();
        control->setIcon(QIcon("://images/add.gif"));
        control->setToolTip(QString("%1").arg(row));
        connect(control,SIGNAL(clicked()),this,SLOT(rowAdd()));
        table->setCellWidget(row, 14, control);
    }
    if(table->item(row,15) == NULL)//删除
    {
        QPushButton *control = new QPushButton();
        control->setIcon(QIcon("://images/delete.gif"));
        control->setToolTip(QString("%1").arg(row));
        connect(control,SIGNAL(clicked()),this,SLOT(rowDelete()));
        table->setCellWidget(row, 15, control);
    }
    if(table->item(row,16) == NULL)//是否被合并
    {

        table->setItem(row, 16, new QTableWidgetItem(""));
    }


    table->installEventFilter(this);//注册事件过滤器

}

void NewProjectBatch::subject_changed(int index)
{
    QWidget * fWidget = this->focusWidget();
    QComboBox *cb = qobject_cast<QComboBox *>(fWidget);
    if (cb != NULL)
    {
        QTableWidget* table  =ui->table;
//        for(int i =0;i<table->rowCount()-1;i++)
//        {
//            if(cb == ((QComboBox*)table->cellWidget(i,3))) //找到该下拉框
//            {
//                QComboBox* nextComb =  (QComboBox*)table->cellWidget(i+1,3);
//                nextComb->setFocus();
//                nextComb->setCurrentIndex(index);
//                break;
//            }
//        }

        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QComboBox*)table->cellWidget(i,3))) //找到该下拉框
            {
                //初始化亚专业下拉框
                QString id = cb->itemData(cb->currentIndex()).toString();
                CategoryService categoryService;
                QVector<Category> categories = categoryService.GetCategories(id);
                QComboBox* control =  (QComboBox*)table->cellWidget(i,4);
                control->clear();
                foreach(Category category, categories)
                {
                    control->addItem(category.CategoryName, category.CategoryId);
                }

//                //初始化项目
//                QComboBox *c = (QComboBox*)table->cellWidget(i,1);
//                id = c->itemData(c->currentIndex()).toString();
//                TestTypeService testTypeService;
//                QVector<TestType> testTypes = testTypeService.GetByCategoryId(id);
//                control =  (QComboBox*)table->cellWidget(i,2);
//                control->clear();
//                foreach(TestType testType, testTypes)
//                {
//                    control->addItem(testType.TestTypeName, testType.TestTypeId);
//                }
//                //初始化质控品下拉框
//                c = (QComboBox*)table->cellWidget(i,2);
//                id = c->itemData(c->currentIndex()).toString();
//                MaterialService materialService;
//                QVector<Material> materials = materialService.GetMaterialsByTestTypeId(id);
//                control =  (QComboBox*)table->cellWidget(i,4);
//                control->clear();
//                foreach(Material material, materials)
//                {
//                    control->addItem(material.MaterialName, material.MaterialId);
//                }
//                //初始化试剂下拉框
//                c = (QComboBox*)table->cellWidget(i,2);
//                id = c->itemData(c->currentIndex()).toString();
//                ReagentService reagentService;
//                QVector<Reagent> reagents = reagentService.GetReagentsByTestTypeId(id);
//                control =  (QComboBox*)table->cellWidget(i,5);
//                control->clear();
//                foreach(Reagent reagent, reagents)
//                {
//                    control->addItem(reagent.ReagentName, reagent.ReagentId);
//                }
//                //初始化方法下拉框
//                c = (QComboBox*)table->cellWidget(i,2);
//                id = c->itemData(c->currentIndex()).toString();
//                MethodService methodService;
//                QVector<Method> methods = methodService.GetByTestTypeId(id);
//                control =  (QComboBox*)table->cellWidget(i,6);
//                control->clear();
//                foreach(Method method, methods)
//                {
//                    control->addItem(method.MethodName, method.MethodId);
//                }
            }
        }
    }
}

void NewProjectBatch::category_changed(int index)
{
    QWidget * fWidget = this->focusWidget();
    QComboBox *cb = qobject_cast<QComboBox *>(fWidget);
    if (cb != NULL)
    {
//        QTableWidget* table  =ui->table;
//        for(int i =0;i<table->rowCount()-1;i++)
//        {
//            if(cb == ((QComboBox*)table->cellWidget(i,4))) //找到该下拉框
//            {
//                QComboBox* nextComb =  (QComboBox*)table->cellWidget(i+1,4);
//                nextComb->setFocus();
//                nextComb->setCurrentIndex(index);
//                break;
//            }
//        }

//        for(int i =0;i<table->rowCount();i++)
//        {
//            if(cb == ((QComboBox*)table->cellWidget(i,1))) //找到该下拉框
//            {
//                //初始化项目
//                QComboBox *c = (QComboBox*)table->cellWidget(i,1);
//                QString id = c->itemData(c->currentIndex()).toString();
//                TestTypeService testTypeService;
//                QVector<TestType> testTypes = testTypeService.GetByCategoryId(id);
//                QComboBox* control =  (QComboBox*)table->cellWidget(i,2);
//                control->clear();
//                foreach(TestType testType, testTypes)
//                {
//                    control->addItem(testType.TestTypeName, testType.TestTypeId);
//                }
//                //初始化质控品下拉框
//                c = (QComboBox*)table->cellWidget(i,2);
//                id = c->itemData(c->currentIndex()).toString();
//                MaterialService materialService;
//                QVector<Material> materials = materialService.GetMaterialsByTestTypeId(id);
//                control =  (QComboBox*)table->cellWidget(i,4);
//                control->clear();
//                foreach(Material material, materials)
//                {
//                    control->addItem(material.MaterialName, material.MaterialId);
//                }
//                //初始化试剂下拉框
//                c = (QComboBox*)table->cellWidget(i,2);
//                id = c->itemData(c->currentIndex()).toString();
//                ReagentService reagentService;
//                QVector<Reagent> reagents = reagentService.GetReagentsByTestTypeId(id);
//                control =  (QComboBox*)table->cellWidget(i,5);
//                control->clear();
//                foreach(Reagent reagent, reagents)
//                {
//                    control->addItem(reagent.ReagentName, reagent.ReagentId);
//                }
//                //初始化方法下拉框
//                c = (QComboBox*)table->cellWidget(i,2);
//                id = c->itemData(c->currentIndex()).toString();
//                MethodService methodService;
//                QVector<Method> methods = methodService.GetByTestTypeId(id);
//                control =  (QComboBox*)table->cellWidget(i,6);
//                control->clear();
//                foreach(Method method, methods)
//                {
//                    control->addItem(method.MethodName, method.MethodId);
//                }
//            }
//        }
    }
}

void NewProjectBatch::testtype_changed(int index)
{
    QWidget * fWidget = this->focusWidget();
    QComboBox *cb = qobject_cast<QComboBox *>(fWidget);
    if (cb != NULL)
    {
//        QTableWidget* table  =ui->table;
//        for(int i =0;i<table->rowCount()-1;i++)
//        {
//            if(cb == ((QComboBox*)table->cellWidget(i,2))) //找到该下拉框
//            {
//                QComboBox* nextComb =  (QComboBox*)table->cellWidget(i+1,2);
//                nextComb->setFocus();
//                nextComb->setCurrentIndex(index);
//                break;
//            }
//        }


//        for(int i =0;i<table->rowCount();i++)
//        {
//            if(cb == ((QComboBox*)table->cellWidget(i,2))) //找到该下拉框
//            {
//                QString id = cb->itemData(cb->currentIndex()).toString();

//                //初始化质控品下拉框
//                MaterialService materialService;
//                QVector<Material> materials = materialService.GetMaterialsByTestTypeId(id);
//                QComboBox* control =  (QComboBox*)table->cellWidget(i,4);
//                control->clear();
//                foreach(Material material, materials)
//                {
//                    control->addItem(material.MaterialName, material.MaterialId);
//                }
//                //初始化试剂下拉框
//                ReagentService reagentService;
//                QVector<Reagent> reagents = reagentService.GetReagentsByTestTypeId(id);
//                control =  (QComboBox*)table->cellWidget(i,5);
//                control->clear();
//                foreach(Reagent reagent, reagents)
//                {
//                    control->addItem(reagent.ReagentName, reagent.ReagentId);
//                }
//                //初始化方法下拉框
//                MethodService methodService;
//                QVector<Method> methods = methodService.GetByTestTypeId(id);
//                control =  (QComboBox*)table->cellWidget(i,6);
//                control->clear();
//                foreach(Method method, methods)
//                {
//                    control->addItem(method.MethodName, method.MethodId);
//                }
//            }
//        }
    }
}

void NewProjectBatch::material_changed(int index)
{
    QWidget * fWidget = this->focusWidget();
    QComboBox *cb = qobject_cast<QComboBox *>(fWidget);
    if (cb != NULL)
    {
//        QTableWidget* table  =ui->table;
//        for(int i =0;i<table->rowCount()-1;i++)
//        {
//            if(cb == ((QComboBox*)table->cellWidget(i,7))) //找到该下拉框
//            {
//                QComboBox* nextComb =  (QComboBox*)table->cellWidget(i+1,7);
//                nextComb->setFocus();
//                nextComb->setCurrentIndex(index);
//                break;
//            }
//        }
    }
}

void NewProjectBatch::reagent_changed(int index)
{
    QWidget * fWidget = this->focusWidget();
    QComboBox *cb = qobject_cast<QComboBox *>(fWidget);
    if (cb != NULL)
    {
//        QTableWidget* table  =ui->table;
//        for(int i =0;i<table->rowCount()-1;i++)
//        {
//            if(cb == ((QComboBox*)table->cellWidget(i,5))) //找到该下拉框
//            {
//                QComboBox* nextComb =  (QComboBox*)table->cellWidget(i+1,5);
//                nextComb->setFocus();
//                nextComb->setCurrentIndex(index);
//                break;
//            }
//        }
    }
}

void NewProjectBatch::method_changed(int index)
{
    QWidget * fWidget = this->focusWidget();
    QComboBox *cb = qobject_cast<QComboBox *>(fWidget);
    if (cb != NULL)
    {
//        QTableWidget* table  =ui->table;
//        for(int i =0;i<table->rowCount()-1;i++)
//        {
//            if(cb == ((QComboBox*)table->cellWidget(i,6))) //找到该下拉框
//            {
//                QComboBox* nextComb =  (QComboBox*)table->cellWidget(i+1,6);
//                nextComb->setFocus();
//                nextComb->setCurrentIndex(index);
//                break;
//            }
//        }
    }
}

void NewProjectBatch::customName_changed(QString arg1)
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
                listWidget->setGeometry(cb->geometry().left()+37,cb->geometry().top()+85, cb->geometry().width(), 120);
                connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
                listWidget->clear();

                TestTypeService service;
                QVector<TestType> m = service.GetTestTypes("","", cb->text());
                for(int i =0;i<m.count();i++)
                {
                    QListWidgetItem *item;
                    item = new QListWidgetItem();
                    item->setText(m[i].TestTypeCode);
                    item->setToolTip(m[i].TestTypeId);
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
            if(cb == ((QLineEdit*)table->cellWidget(i,0))||cb == ((QLineEdit*)table->cellWidget(i,1))||cb == ((QLineEdit*)table->cellWidget(i,2))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
//        for(int i =current;i<table->rowCount();i++)
//        {
//            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,0);
//            nextComb->setText(arg1);
//        }

        //其它名称自动完成
        if(QString::compare(arg1, "")!=0)
        {
            TestTypeService service;
            QVector<TestType> ps = service.GetTestTypesBy3Name(arg1);
            if(ps.count()>0 && ps.count()<5)
            {
                ((QLineEdit*)table->cellWidget(current,1))->setText(ps[0].TestTypeCode);
                ((QLineEdit*)table->cellWidget(current,2))->setText(ps[0].TestTypeName);

                QComboBox *control = ((QComboBox *)table->cellWidget(current,3));//专业
                for(int i=0;i<control->count();i++)
                {
                    if(QString::compare(control->itemData(i).toString(), ps[0].SubjectId)==0)
                    {
                        control->setCurrentIndex(i);
                        break;
                    }
                }
                CategoryService categoryService;
                QVector<Category> categories = categoryService.GetCategories(ps[0].SubjectId);
                control = ((QComboBox *)table->cellWidget(current,4));//亚专业
                control->clear();
                foreach(Category category, categories)
                {
                    control->addItem(category.CategoryName, category.CategoryId);
                }
                for(int i=0;i<control->count();i++)
                {
                    if(QString::compare(control->itemData(i).toString(), ps[0].CategoryId)==0)
                    {
                        control->setCurrentIndex(i);
                        break;
                    }
                }
            }
        }
    }
}

void NewProjectBatch::englishName_changed(QString arg1)
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
            if(cb == ((QLineEdit*)table->cellWidget(i,1))) //找到该下拉框
            {
                lineEdit = cb;
                if(listWidget != NULL)
                {
                    listWidget->setVisible(false);
                }
                listWidget = new QListWidget(this);
                listWidget->setGeometry(cb->geometry().left()+37,cb->geometry().top()+85, cb->geometry().width(), 120);
                connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
                listWidget->clear();

                TestTypeService service;
                QVector<TestType> m = service.GetTestTypes("","", cb->text());
                for(int i =0;i<m.count();i++)
                {
                    QListWidgetItem *item;
                    item = new QListWidgetItem();
                    item->setText(m[i].TestTypeCode);
                    item->setToolTip(m[i].TestTypeId);
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
            if(cb == ((QLineEdit*)table->cellWidget(i,0))||cb == ((QLineEdit*)table->cellWidget(i,1))||cb == ((QLineEdit*)table->cellWidget(i,2))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
//        for(int i =current;i<table->rowCount();i++)
//        {
//            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,1);
//            nextComb->setText(arg1);
//        }

        //其它名称自动完成
        if(QString::compare(arg1, "")!=0)
        {
            TestTypeService service;
            QVector<TestType> ps = service.GetTestTypesBy3Name(arg1);
            if(ps.count()>0 && ps.count()<5)
            {
                ((QLineEdit*)table->cellWidget(current,0))->setText(ps[0].TestTypeCode);
                ((QLineEdit*)table->cellWidget(current,2))->setText(ps[0].TestTypeName);

                QComboBox *control = ((QComboBox *)table->cellWidget(current,3));//专业
                for(int i=0;i<control->count();i++)
                {
                    if(QString::compare(control->itemData(i).toString(), ps[0].SubjectId)==0)
                    {
                        control->setCurrentIndex(i);
                        break;
                    }
                }
                CategoryService categoryService;
                QVector<Category> categories = categoryService.GetCategories(ps[0].SubjectId);
                control = ((QComboBox *)table->cellWidget(current,4));//亚专业
                control->clear();
                foreach(Category category, categories)
                {
                    control->addItem(category.CategoryName, category.CategoryId);
                }
                for(int i=0;i<control->count();i++)
                {
                    if(QString::compare(control->itemData(i).toString(), ps[0].CategoryId)==0)
                    {
                        control->setCurrentIndex(i);
                        break;
                    }
                }
            }
        }
    }
}
void NewProjectBatch::chineseName_changed(QString arg1)
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
            if(cb == ((QLineEdit*)table->cellWidget(i,2))) //找到该下拉框
            {
                lineEdit = cb;
                if(listWidget != NULL)
                {
                    listWidget->setVisible(false);
                }
                listWidget = new QListWidget(this);
                listWidget->setGeometry(cb->geometry().left()+37,cb->geometry().top()+85, cb->geometry().width(), 120);
                connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
                listWidget->clear();

                TestTypeService service;
                QVector<TestType> m = service.GetTestTypes("","", cb->text());
                for(int i =0;i<m.count();i++)
                {
                    QListWidgetItem *item;
                    item = new QListWidgetItem();
                    item->setText(m[i].TestTypeName);
                    item->setToolTip(m[i].TestTypeId);
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
            if(cb == ((QLineEdit*)table->cellWidget(i,0))||cb == ((QLineEdit*)table->cellWidget(i,1))||cb == ((QLineEdit*)table->cellWidget(i,2))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
//        for(int i =current;i<table->rowCount();i++)
//        {
//            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,2);
//            nextComb->setText(arg1);
//        }

        //其它名称自动完成
        if(QString::compare(arg1, "")!=0)
        {
            TestTypeService service;
            QVector<TestType> ps = service.GetTestTypesBy3Name(arg1);
            if(ps.count()>0 && ps.count()<5)
            {
                ((QLineEdit*)table->cellWidget(current,0))->setText(ps[0].TestTypeCode);
                ((QLineEdit*)table->cellWidget(current,1))->setText(ps[0].TestTypeCode);

                QComboBox *control = ((QComboBox *)table->cellWidget(current,3));//专业
                for(int i=0;i<control->count();i++)
                {
                    if(QString::compare(control->itemData(i).toString(), ps[0].SubjectId)==0)
                    {
                        control->setCurrentIndex(i);
                        break;
                    }
                }
                CategoryService categoryService;
                QVector<Category> categories = categoryService.GetCategories(ps[0].SubjectId);
                control = ((QComboBox *)table->cellWidget(current,4));//亚专业
                control->clear();
                foreach(Category category, categories)
                {
                    control->addItem(category.CategoryName, category.CategoryId);
                }
                for(int i=0;i<control->count();i++)
                {
                    if(QString::compare(control->itemData(i).toString(), ps[0].CategoryId)==0)
                    {
                        control->setCurrentIndex(i);
                        break;
                    }
                }
            }
        }
    }
}

void NewProjectBatch::level_changed(int index)
{
    QWidget * fWidget = this->focusWidget();
    QComboBox *cb = qobject_cast<QComboBox *>(fWidget);
    if (cb != NULL)
    {
//        QTableWidget* table  =ui->table;
//        for(int i =0;i<table->rowCount()-1;i++)
//        {
//            if(cb == ((QComboBox*)table->cellWidget(i,5))) //找到该下拉框
//            {
//                QComboBox* nextComb =  (QComboBox*)table->cellWidget(i+1,5);
//                nextComb->setFocus();
//                nextComb->setCurrentIndex(index);
//                break;
//            }
//        }
    }
}


void NewProjectBatch::num_changed(int index)
{
    QWidget * fWidget = this->focusWidget();
    QComboBox *cb = qobject_cast<QComboBox *>(fWidget);
    if (cb != NULL)
    {
//        QTableWidget* table  =ui->table;
//        for(int i =0;i<table->rowCount()-1;i++)
//        {
//            if(cb == ((QComboBox*)table->cellWidget(i,6))) //找到该下拉框
//            {
//                QComboBox* nextComb =  (QComboBox*)table->cellWidget(i+1,6);
//                nextComb->setFocus();
//                nextComb->setCurrentIndex(index);
//                break;
//            }
//        }
    }
}

void NewProjectBatch::materialName_changed(QString arg1)
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
        listWidget->setGeometry(cb->geometry().left()+37,cb->geometry().top()+85, cb->geometry().width(), 120);
        connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
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
        //下拉提示框End

        QTableWidget* table  =ui->table;
        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,7))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
        for(int i =current;i<table->rowCount();i++)
        {
//            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,7);
//            nextComb->setText(arg1);
        }

        if(arg1 != "" && m.count()>0 && m[0].MaterialName == arg1)
        {
            MaterialBatchService service;
            QVector<MaterialBatch> mb = service.GetMaterialBatchs(m[0].MaterialId, "");
            if(mb.count()>0  )
            {
                ((QLineEdit*)table->cellWidget(current,8))->setText(mb[0].BatchNo);

            }
        }
    }
}

void NewProjectBatch::materialBatchName_changed(QString arg1)
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
        listWidget->setGeometry(cb->geometry().left()+37,cb->geometry().top()+85, cb->geometry().width(), 120);
        connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
        listWidget->clear();

        QTableWidget* table  =ui->table;
        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,8))) //找到该下拉框
            {
                current = i;
                break;
            }
        }

        MaterialService mService;
        MaterialBatchService service;

        QVector<Material> m = mService.GetMaterials("","",((QLineEdit*)table->cellWidget(current,7))->text() ,"","",1);
        if(m.count()>0)
        {
            QVector<MaterialBatch> mb = service.GetMaterialBatchs(m[0].MaterialId, "");
            for(int i =0;i<mb.count();i++)
            {
                QListWidgetItem *item;
                item = new QListWidgetItem();
                item->setText(mb[i].BatchNo);
                item->setToolTip(mb[i].MaterialBatchId);
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
        //下拉提示框End


        for(int i =current;i<table->rowCount();i++)
        {
//            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,8);
//            nextComb->setText(arg1);
        }
    }
}
void NewProjectBatch::reagentName_changed(QString arg1)
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
        listWidget->setGeometry(cb->geometry().left()+37,cb->geometry().top()+85, cb->geometry().width(), 120);
        connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
        listWidget->clear();

        ReagentService service;
        QVector<Reagent> m = service.GetReagents("","", cb->text(), "","",1);
        for(int i =0;i<m.count();i++)
        {
            QListWidgetItem *item;
            item = new QListWidgetItem();
            item->setText(m[i].ReagentName);
            item->setToolTip(m[i].ReagentId);
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
            if(cb == ((QLineEdit*)table->cellWidget(i,9))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
        for(int i =current;i<table->rowCount();i++)
        {
//            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,9);
//            nextComb->setText(arg1);
        }

        if(arg1 != "" && m.count()>0 && m[0].ReagentName == arg1)
        {
            ReagentBatchService service;
            QVector<ReagentBatch> mb = service.GetReagentBatchs(m[0].ReagentId, "");
            if(mb.count()>0)
            {
                ((QLineEdit*)table->cellWidget(current,10))->setText(mb[0].BatchNo);

            }
        }
    }
}
void NewProjectBatch::reagentBatchName_changed(QString arg1)
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
        listWidget->setGeometry(cb->geometry().left()+37,cb->geometry().top()+85, cb->geometry().width(), 120);
        connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
        listWidget->clear();

        QTableWidget* table  =ui->table;
        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,10))) //找到该下拉框
            {
                current = i;
                break;
            }
        }

        ReagentService mService;
        ReagentBatchService service;
        QVector<Reagent> m = mService.GetReagents("","",((QLineEdit*)table->cellWidget(current,9))->text() ,"","",1);
        if(m.count()>0)
        {
            QVector<ReagentBatch> mb = service.GetReagentBatchs(m[0].ReagentId, "");
            for(int i =0;i<mb.count();i++)
            {
                QListWidgetItem *item;
                item = new QListWidgetItem();
                item->setText(mb[i].BatchNo);
                item->setToolTip(mb[i].ReagentBatchId);
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
        //下拉提示框End


        for(int i =current;i<table->rowCount();i++)
        {
//            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,10);
//            nextComb->setText(arg1);
        }
    }
}

void NewProjectBatch::methodName_changed(QString arg1)
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
        listWidget->setGeometry(cb->geometry().left()+37,cb->geometry().top()+85, cb->geometry().width(), 120);
        connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
        listWidget->clear();

        MethodService service;
        QVector<Method> m = service.GetMethods("","", cb->text(),1);
        for(int i =0;i<m.count();i++)
        {
            QListWidgetItem *item;
            item = new QListWidgetItem();
            item->setText(m[i].MethodName);
            item->setToolTip(m[i].MethodId);
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
            if(cb == ((QLineEdit*)table->cellWidget(i,11))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
        for(int i =current;i<table->rowCount();i++)
        {
//            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,11);
//            nextComb->setText(arg1);
        }
    }
}

void NewProjectBatch::device_changed(QString arg1)
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
        listWidget->setGeometry(cb->geometry().left()+37,cb->geometry().top()+85, cb->geometry().width(), 120);
        connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
        listWidget->clear();

        DeviceService service;
        QVector<Device> m = service.GetAll("","", cb->text(),1);
        for(int i =0;i<m.count();i++)
        {
            QListWidgetItem *item;
            item = new QListWidgetItem();
            item->setText(m[i].DeviceName);
            item->setToolTip(m[i].DeviceId);
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
            if(cb == ((QLineEdit*)table->cellWidget(i,12))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
        for(int i =current;i<table->rowCount();i++)
        {
//            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,12);
//            nextComb->setText(arg1);
        }
    }
}

void NewProjectBatch::displayIndex_changed(QString arg1)
{

}

void NewProjectBatch::customName_changed(){customName_changed("");}
void NewProjectBatch::englishName_changed(){englishName_changed("");}
void NewProjectBatch::chineseName_changed(){chineseName_changed("");}
void NewProjectBatch::materialName_changed(){materialName_changed("");}
void NewProjectBatch::materialBatchName_changed(){materialBatchName_changed("");}
void NewProjectBatch::reagentName_changed(){reagentName_changed("");}
void NewProjectBatch::reagentBatchName_changed(){reagentBatchName_changed("");}
void NewProjectBatch::methodName_changed(){methodName_changed("");}
void NewProjectBatch::device_changed(){device_changed("");}
void NewProjectBatch::displayIndex_changed(){displayIndex_changed("");}


void NewProjectBatch::keyPressEvent (QKeyEvent * keyevent)
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
bool NewProjectBatch::eventFilter(QObject*obj,QEvent*event)
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
void NewProjectBatch::on_btnAdd_clicked()
{
    int rowCount = ui->table->rowCount();
    int row = rowCount-1;
    ui->table->setRowCount(rowCount+1);
    Project p;
    if(rowCount>0)
    {
        p.CustomName = ((QLineEdit*)ui->table->cellWidget(row,0))->text();
        p.EnglishName = ((QLineEdit*)ui->table->cellWidget(row,1))->text();
        p.ProjectName = ((QLineEdit*)ui->table->cellWidget(row,2))->text();

        TestTypeService ttService;
        QVector <TestType> tt = ttService.GetTestTypes("","",p.ProjectName);
        if(tt.count()>0)
        {
            p.testType.TestTypeId = tt[0].TestTypeId;
        }
        p.testType.SubjectId = ((QComboBox*)ui->table->cellWidget(row,3))->itemData(((QComboBox*)ui->table->cellWidget(row,3))->currentIndex()).toString();
        p.testType.CategoryId = ((QComboBox*)ui->table->cellWidget(row,4))->itemData(((QComboBox*)ui->table->cellWidget(row,4))->currentIndex()).toString();
        p.level = ((QComboBox*)ui->table->cellWidget(row,5))->itemData(((QComboBox*)ui->table->cellWidget(row,5))->currentIndex()).toInt();
        if(p.level<6)
        {
            //p.level++;
        }

        p.PerDayBatch = ((QComboBox*)ui->table->cellWidget(row,6))->itemData(((QComboBox*)ui->table->cellWidget(row,6))->currentIndex()).toInt();

        MaterialService materialService;
        QVector<Material> Materials = materialService.GetMaterials("", "", ((QLineEdit*)ui->table->cellWidget(row,7))->text(),"","",0);
        if(Materials.count()>0)
        {
            p.MaterialId = Materials[0].MaterialId;
        }
        p.MaterialName=((QLineEdit*)ui->table->cellWidget(row,7))->text();
        p.CurrentMaterialBatch=((QLineEdit*)ui->table->cellWidget(row,8))->text();
        ReagentService reagentService;
        QVector<Reagent> Reagents = reagentService.GetReagents("", "", ((QLineEdit*)ui->table->cellWidget(row,9))->text(),"","",0);
        if(Reagents.count()>0)
        {
            p.ReagentId = Reagents[0].ReagentId;
        }
        p.ReagentName=((QLineEdit*)ui->table->cellWidget(row,9))->text();
        p.CurrentReagentBatch=((QLineEdit*)ui->table->cellWidget(row,10))->text();
        MethodService methodService;
        QVector<Method> Methods = methodService.GetMethods("", "", ((QLineEdit*)ui->table->cellWidget(row,11))->text(),0);
        if(Methods.count()>0)
        {
            p.MethodId = Methods[0].MethodId;
        }
        p.MethodName=((QLineEdit*)ui->table->cellWidget(row,11))->text();

        DeviceService deviceService;
        QVector<Device> devices = deviceService.GetAll("", "", ((QLineEdit*)ui->table->cellWidget(row,12))->text(),0);
        if(devices.count()>0)
        {
            p.DeviceId = devices[0].DeviceId;
        }
        p.DeviceName=((QLineEdit*)ui->table->cellWidget(row,12))->text();
        p.DispIdx =((QLineEdit*)ui->table->cellWidget(row,13))->text().toInt();
    }
    initRow(ui->table, rowCount, &p);
}

//删除项目
void NewProjectBatch::on_btnDelete_clicked()
{
    int row = ui->table->rowCount();
    if(row > 0)
    {
        ui->table->setRowCount(row-1);
    }
}

//在某行下面添加一行
void NewProjectBatch::rowAdd()
{
    QWidget * fWidget = this->focusWidget();
    QPushButton *cb = qobject_cast<QPushButton *>(fWidget);
    QTableWidget* table  =ui->table;
    for(int i =0;i<table->rowCount();i++)
    {
        if(cb == ((QPushButton*)table->cellWidget(i,14))) //找到该下拉框
        {
            Project p;
            int row = i;
            p.CustomName = ((QLineEdit*)ui->table->cellWidget(row,0))->text();
            p.EnglishName = ((QLineEdit*)ui->table->cellWidget(row,1))->text();
            p.ProjectName = ((QLineEdit*)ui->table->cellWidget(row,2))->text();

            TestTypeService ttService;
            QVector <TestType> tt = ttService.GetTestTypes("","",p.ProjectName);
            if(tt.count()>0)
            {
                p.testType.TestTypeId = tt[0].TestTypeId;
            }
            p.testType.SubjectId = ((QComboBox*)ui->table->cellWidget(row,3))->itemData(((QComboBox*)ui->table->cellWidget(row,3))->currentIndex()).toString();
            p.testType.CategoryId = ((QComboBox*)ui->table->cellWidget(row,4))->itemData(((QComboBox*)ui->table->cellWidget(row,4))->currentIndex()).toString();
            p.level = ((QComboBox*)ui->table->cellWidget(row,5))->itemData(((QComboBox*)ui->table->cellWidget(row,5))->currentIndex()).toInt();
            if(p.level<6)
            {
                p.level++;
            }

            p.PerDayBatch = ((QComboBox*)ui->table->cellWidget(row,6))->itemData(((QComboBox*)ui->table->cellWidget(row,6))->currentIndex()).toInt();

            MaterialService materialService;
            QVector<Material> Materials = materialService.GetMaterials("", "", ((QLineEdit*)ui->table->cellWidget(row,7))->text(),"","",0);
            if(Materials.count()>0)
            {
                p.MaterialId = Materials[0].MaterialId;
            }
            p.MaterialName=((QLineEdit*)ui->table->cellWidget(row,7))->text();
            p.CurrentMaterialBatch=((QLineEdit*)ui->table->cellWidget(row,8))->text();
            ReagentService reagentService;
            QVector<Reagent> Reagents = reagentService.GetReagents("", "", ((QLineEdit*)ui->table->cellWidget(row,9))->text(),"","",0);
            if(Reagents.count()>0)
            {
                p.ReagentId = Reagents[0].ReagentId;
            }
            p.ReagentName=((QLineEdit*)ui->table->cellWidget(row,9))->text();
            p.CurrentReagentBatch=((QLineEdit*)ui->table->cellWidget(row,10))->text();
            MethodService methodService;
            QVector<Method> Methods = methodService.GetMethods("", "", ((QLineEdit*)ui->table->cellWidget(row,11))->text(),0);
            if(Methods.count()>0)
            {
                p.MethodId = Methods[0].MethodId;
            }
            p.MethodName=((QLineEdit*)ui->table->cellWidget(row,11))->text();

            DeviceService deviceService;
            QVector<Device> devices = deviceService.GetAll("", "", ((QLineEdit*)ui->table->cellWidget(row,12))->text(),0);
            if(devices.count()>0)
            {
                p.DeviceId = devices[0].DeviceId;
            }
            p.DeviceName=((QLineEdit*)ui->table->cellWidget(row,12))->text();
            p.DispIdx =((QLineEdit*)ui->table->cellWidget(row,13))->text().toInt();

            table->insertRow(i+1);
            initRow(ui->table, i+1, &p);

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
                table->setItem(i,16,new QTableWidgetItem("1"));
            }
        }
        table->setSpan(j,0,ui->table->rowCount()-j,1);
        table->setSpan(j,1,ui->table->rowCount()-j,1);
        table->setSpan(j,2,ui->table->rowCount()-j,1);

        table->resizeRowsToContents();
    }
}
//删除某行
void NewProjectBatch::rowDelete()
{
    QWidget * fWidget = this->focusWidget();
    QPushButton *cb = qobject_cast<QPushButton *>(fWidget);
    QTableWidget* table  =ui->table;
    for(int i =0;i<table->rowCount();i++)
    {
        if(cb == ((QPushButton*)table->cellWidget(i,15))) //找到该下拉框
        {
            ui->table->removeRow(i);
            break;
        }
    }
}

//保存
void NewProjectBatch::on_btnOK_clicked()
{

    MaterialService materialService;
    ReagentService reagentService;
    MethodService methodService;

    ProjectService projectService;
    TestTypeService ttService;

    //检验
    for(int row=0; row<ui->table->rowCount();row++)
    {
        QString name;
        //判断是否必填
        name = ((QLineEdit*)ui->table->cellWidget(row, 0))->text();
        if(QString::compare(name,"")==0)
        {
            QMessageBox::information(this, tr("信息") ,QString("第%1行 自定义名称未填写").arg(row+1));
            return;
        }
        QString devicename = ((QLineEdit*)ui->table->cellWidget(row,12))->text();
//        if(projectService.SearchProject("","",name,devicename).count()>0)
//        {
//            QMessageBox::information(this, tr("信息") ,QString("第%1行 该项目已存在").arg(row+1));
//            return;
//        }
        name = ((QLineEdit*)ui->table->cellWidget(row, 1))->text();
        if(QString::compare(name,"")==0)
        {
            QMessageBox::information(this, tr("信息") ,QString("第%1行 英文名称未填写").arg(row+1));
            return;
        }
        name = ((QLineEdit*)ui->table->cellWidget(row, 2))->text();
        if(QString::compare(name,"")==0)
        {
            QMessageBox::information(this, tr("信息") ,QString("第%1行 中文名称未填写").arg(row+1));
            return;
        }

        //判断是否重复
        int chongfu=0;
        name = ((QLineEdit*)ui->table->cellWidget(row, 0))->text();
        chongfu=IsValid(ui->table,name,0,row);
        if(chongfu>1)
        {
            QMessageBox::information(this, tr("信息") ,QString("第%1行和第%2行 自定义名称有重复").arg(row+1).arg(chongfu+1));
            return;
        }
        name = ((QLineEdit*)ui->table->cellWidget(row, 1))->text();
        chongfu=IsValid(ui->table,name,1,row);
        if(chongfu>1)
        {
            QMessageBox::information(this, tr("信息") ,QString("第%1行和第%2行 英文名称有重复").arg(row+1).arg(chongfu+1));
            return;
        }
        name = ((QLineEdit*)ui->table->cellWidget(row, 2))->text();
        chongfu=IsValid(ui->table,name,2,row);
        if(chongfu>1)
        {
            QMessageBox::information(this, tr("信息") ,QString("第%1行和第%2行 中文名称有重复").arg(row+1).arg(chongfu+1));
            return;
        }

        QComboBox* c = ((QComboBox*)ui->table->cellWidget(row, 5));
        name = c->currentData().toString();
        if(!IsValid(ui->table,name,5,((QLineEdit*)ui->table->cellWidget(row, 0))->text()))
        {
            QMessageBox::information(this, tr("信息") ,QString("第%1行 浓度有重复").arg(row+1));
            return;
        }

        QVector<Material> Materials = materialService.GetMaterials("", "", ((QLineEdit*)ui->table->cellWidget(row,7))->text(),"","",0);
        if(((QLineEdit*)ui->table->cellWidget(row,9))->text() != "" && Materials.count()==0)
        {
            QMessageBox message(QMessageBox::NoIcon, "信息", QString("第%1行 质控品不存在,需要添加该质控品吗?").arg(row+1), QMessageBox::Yes | QMessageBox::No, NULL);
            if(message.exec() == QMessageBox::Yes)
            {
                EditMaterial *f = new EditMaterial();
                f->show();
                f->SetName(((QLineEdit*)ui->table->cellWidget(row,7))->text());
                return;
            }
            else
            {
                return;
            }
        }


        QVector<Reagent> Reagents = reagentService.GetReagents("", "", ((QLineEdit*)ui->table->cellWidget(row,9))->text(),"","",0);
        if(((QLineEdit*)ui->table->cellWidget(row,9))->text() != "" && Reagents.count()==0)
        {
            QMessageBox message(QMessageBox::NoIcon, "信息", QString("第%1行 试剂不存在,需要添加该试剂吗?").arg(row+1), QMessageBox::Yes | QMessageBox::No, NULL);
            if(message.exec() == QMessageBox::Yes)
            {
                EditReagent *f = new EditReagent();
                f->show();
                f->SetName(((QLineEdit*)ui->table->cellWidget(row,9))->text());
                return;
            }
            else
            {
                return;
            }
        }

        QVector<Method> Methods = methodService.GetMethods("", "", ((QLineEdit*)ui->table->cellWidget(row,11))->text(),0);
        if(((QLineEdit*)ui->table->cellWidget(row,11))->text() != "" && Methods.count()==0)
        {
            QMessageBox message(QMessageBox::NoIcon, "信息", QString("第%1行 方法不存在,需要添加该方法吗?").arg(row+1), QMessageBox::Yes | QMessageBox::No, NULL);
            if(message.exec() == QMessageBox::Yes)
            {
                EditMethod *f = new EditMethod();
                f->show();
                f->SetName(((QLineEdit*)ui->table->cellWidget(row,11))->text());
                return;
            }
            else
            {
                return;
            }
        }

        DeviceService deviceService;
        QVector<Device> devices = deviceService.GetAll("", "", ((QLineEdit*)ui->table->cellWidget(row,12))->text(),0);
        if(((QLineEdit*)ui->table->cellWidget(row,12))->text() != "" && devices.count()==0)
        {
            QMessageBox message(QMessageBox::NoIcon, "信息", QString("第%1行 仪器不存在,需要添加该仪器吗?").arg(row+1), QMessageBox::Yes | QMessageBox::No, NULL);
            if(message.exec() == QMessageBox::Yes)
            {
                EditDevice *f = new EditDevice();
                f->show();
                f->SetName(((QLineEdit*)ui->table->cellWidget(row,12))->text());
                return;
            }
            else
            {
                return;
            }
        }
    }

    QString uuid="";
    for(int row=0; row<ui->table->rowCount();row++)
    {
        Project p;
        QVector<TestType> testTypes;
        p.CustomName = ((QLineEdit*)ui->table->cellWidget(row,0))->text();
        p.EnglishName = ((QLineEdit*)ui->table->cellWidget(row,1))->text();
        p.ProjectName = ((QLineEdit*)ui->table->cellWidget(row,2))->text();

        testTypes = ttService.GetTestTypes("","",p.ProjectName);
        if (testTypes.size() <= 0)
        {
            QMessageBox::information(this, tr("信息") , QString("第%1行 %2项目不存在, %3 项目添加失败").arg(row+1).arg(p.ProjectName).arg(p.CustomName));
            continue;
        }

        TestType tt = testTypes[0];

        p.testType.TestTypeId = tt.TestTypeId;
        p.testType.SubjectId = ((QComboBox*)ui->table->cellWidget(row,3))->itemData(((QComboBox*)ui->table->cellWidget(row,3))->currentIndex()).toString();
        p.testType.CategoryId = ((QComboBox*)ui->table->cellWidget(row,4))->itemData(((QComboBox*)ui->table->cellWidget(row,4))->currentIndex()).toString();
        p.level = ((QComboBox*)ui->table->cellWidget(row,5))->itemData(((QComboBox*)ui->table->cellWidget(row,5))->currentIndex()).toInt();

        p.PerDayBatch = ((QComboBox*)ui->table->cellWidget(row,6))->itemData(((QComboBox*)ui->table->cellWidget(row,6))->currentIndex()).toInt();


        QVector<Material> Materials = materialService.GetMaterials("", "", ((QLineEdit*)ui->table->cellWidget(row,7))->text(),"","",0);
        if(Materials.count()>0)
        {
            p.MaterialId = Materials[0].MaterialId;
        }
        p.CurrentMaterialBatch=((QLineEdit*)ui->table->cellWidget(row,8))->text();


        QVector<Reagent> Reagents = reagentService.GetReagents("", "", ((QLineEdit*)ui->table->cellWidget(row,9))->text(),"","",0);
        if(Reagents.count()>0)
        {
            p.ReagentId = Reagents[0].ReagentId;
        }
        p.CurrentReagentBatch=((QLineEdit*)ui->table->cellWidget(row,10))->text();


        QVector<Method> Methods = methodService.GetMethods("", "", ((QLineEdit*)ui->table->cellWidget(row,11))->text(),0);
        if(Methods.count()>0)
        {
            p.MethodId = Methods[0].MethodId;
        }

        DeviceService deviceService;
        QVector<Device> devices = deviceService.GetAll("", "", ((QLineEdit*)ui->table->cellWidget(row,12))->text(),0);
        if(devices.count()>0)
        {
            p.DeviceId = devices[0].DeviceId;
        }

        p.DispIdx = row+1;//((QLineEdit*)ui->table->cellWidget(row,13))->text().toInt();


        if(QString::compare(ui->table->item(row,16)->text(),"1") != 0)
        {
            uuid = projectService.Insert(p);
        }
        else
        {
            Project p = projectService.GetById(uuid);
            p.level++;
            projectService.UpdateModel(p);
        }

        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        MaterialBatchService mbs;
        QString materialBatchId="";
        if(p.CurrentMaterialBatch != "")
        {
            QVector<MaterialBatch> l = mbs.GetMaterialBatchs(p.MaterialId,p.CurrentMaterialBatch);
            if(l.count()>0)
            {
                materialBatchId = l[0].MaterialBatchId;
            }
            else
            {
                MaterialBatch b;
                b.MaterialId = p.MaterialId;
                b.BatchNo = p.CurrentMaterialBatch;
                b.CreateTime = time;
                b.StartDate = time;
                b.Status = 1;
                materialBatchId = mbs.Insert(b);
            }
        }
        ReagentBatchService rbs;
        QString reagentBatchId="";
        if(p.CurrentReagentBatch != "")
        {
            QVector<ReagentBatch> l = rbs.GetReagentBatchs(p.ReagentId,p.CurrentReagentBatch);
            if(l.count()>0)
            {
                reagentBatchId = l[0].ReagentBatchId;
            }
            else
            {
                ReagentBatch b;
                b.ReagentId = p.ReagentId;
                b.BatchNo = p.CurrentReagentBatch;
                b.CreateTime = time;
                b.StartDate = time;
                b.Status = 1;
                reagentBatchId = rbs.Insert(b);
            }
        }


        ProjectDetail detail;
        detail.ProjectId=uuid;
        detail.CreateTime=time;
        detail.DensityId=p.level;
        detail.MaterialId=p.MaterialId;
        detail.MaterialBatchId = materialBatchId;
        detail.ReagentId=p.ReagentId;
        detail.ReagentBatchId = reagentBatchId;
        detail.MethodId=p.MethodId;
        detail.Status=1;
        detail.Useflag=1;
        detail.CreateUser=p.CreatorId;
        projectService.InsertDetail(detail);


    }


    QMessageBox::information(this, tr("信息") , "保存成功");
    this->close();
}

//关闭
void NewProjectBatch::on_btnCancel_clicked()
{
    this->close();
}

//查询
void NewProjectBatch::on_pushButton_clicked()
{
    ProjectService projectService;
    QString SubjectId = ui->inputSubject->itemData(ui->inputSubject->currentIndex()).toString();
    QString CategoryId = ui->inputCategory->itemData(ui->inputCategory->currentIndex()).toString();
    QString DeviceName = ui->inputDeviceName->text();
    QString MethodName = ui->inputMethodName->text();
    QString MaterialName = ui->inputMaterialName->text();
    QString ReagentName = ui->inputReagentName->text();
    QString name = ui->inputName->text();

    projects = projectService.SearchProject(SubjectId,CategoryId,name,MaterialName,ReagentName,MethodName,DeviceName);
    ui->table->setRowCount(projects.count());
    for(int i=0;i<projects.count();i++)
    {
        initRow(ui->table, i, &projects[i]);

    }
}

void NewProjectBatch::on_inputSubject_currentIndexChanged(int index)
{
    //亚专业
    CategoryService categoryService;
    QString id = ui->inputSubject->itemData(ui->inputSubject->currentIndex()).toString();
    QVector<Category> categories = categoryService.GetCategories(id);
    ui->inputCategory->clear();
    ui->inputCategory->addItem("全部", "");
    foreach(Category category, categories)
    {
        ui->inputCategory->addItem(category.CategoryName, category.CategoryId);
    }
}

void NewProjectBatch::slt_listWidget_clicked(const QModelIndex &index)
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


void NewProjectBatch::on_inputName_textChanged(const QString &arg1)
{
    lineEdit = ui->inputName;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().left()+9,lineEdit->geometry().top()+594, lineEdit->geometry().width(), 120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    ProjectService service;
    QVector<Project> m = service.SearchProject("","", lineEdit->text(),"");
    for(int i =0;i<m.count();i++)
    {
        QListWidgetItem *item;
        item = new QListWidgetItem();
        item->setText(m[i].CustomName);
        item->setToolTip(m[i].ProjectId);
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

void NewProjectBatch::on_inputDeviceName_textChanged(const QString &arg1)
{
    lineEdit = ui->inputDeviceName;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().left()+9,lineEdit->geometry().top()+594, lineEdit->geometry().width(), 120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    DeviceService service;
    QVector<Device> m = service.GetAll("","", lineEdit->text(),1);
    for(int i =0;i<m.count();i++)
    {
        QListWidgetItem *item;
        item = new QListWidgetItem();
        item->setText(m[i].DeviceName);
        item->setToolTip(m[i].DeviceId);
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

void NewProjectBatch::on_inputMethodName_textChanged(const QString &arg1)
{
    //下拉提示框
    lineEdit = ui->inputMethodName;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().left()+9,lineEdit->geometry().top()+594, lineEdit->geometry().width(), 120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
    listWidget->clear();

    MethodService service;
    QVector<Method> m = service.GetMethods("","", lineEdit->text(),1);
    for(int i =0;i<m.count();i++)
    {
        QListWidgetItem *item;
        item = new QListWidgetItem();
        item->setText(m[i].MethodName);
        item->setToolTip(m[i].MethodId);
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

void NewProjectBatch::on_inputMaterialName_textChanged(const QString &arg1)
{
    lineEdit = ui->inputMaterialName;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().left()+9,lineEdit->geometry().top()+594, lineEdit->geometry().width(), 120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
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

void NewProjectBatch::on_inputReagentName_textChanged(const QString &arg1)
{
    lineEdit = ui->inputReagentName;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().left()+9,lineEdit->geometry().top()+594, lineEdit->geometry().width(), 120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(slt_listWidget_clicked(const QModelIndex)));
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

void NewProjectBatch::on_btnConfigColumn_clicked()
{
    ConfigColumn *w=new ConfigColumn(this);
    w->show();
}

void NewProjectBatch::showCols()
{
    QString strFilePath = QString("columns.txt");
    QFile file(strFilePath);
    if(!file.exists())
    {
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.write("1,1,1,1,1,1,1,1,1,1,1,1,1,");
        file.close();
    }

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream stream(&file);
    QString line;
    while(!stream.atEnd())
    {
        line = stream.readLine();
    }
    file.close();
    QStringList arr = line.split(",");

    for(int i = 0;i <= 12; i++)
    {
        if(arr.at(i).toInt() == 1)
        {
            ui->table->setColumnHidden(i,false);
        }
        else
        {
            ui->table->setColumnHidden(i,true);
        }
    }
    ui->table->setColumnHidden(13,true);
}


int NewProjectBatch::IsValid(QTableWidget *table,QString name,int col,int row0)
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
bool NewProjectBatch::IsValid(QTableWidget *table,QString name,int col, QString projectName)
{
    if(QString::compare(name,"")==0)
    {
        return true;
    }
    int count=0;
    for(int row=0; row<table->rowCount();row++)
    {
        QString value = ((QComboBox*)table->cellWidget(row, col))->currentData().toString();
        if(QString::compare(name,value)==0 && QString::compare(((QLineEdit*)table->cellWidget(row, 0))->text(),projectName)==0)
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


void NewProjectBatch::on_inputDeviceName_selectionChanged()
{
    on_inputDeviceName_textChanged(ui->inputDeviceName->text());
}

void NewProjectBatch::on_inputName_selectionChanged()
{
    on_inputName_textChanged(ui->inputName->text());
}

void NewProjectBatch::on_inputMethodName_selectionChanged()
{
    on_inputMethodName_textChanged(ui->inputMethodName->text());
}

void NewProjectBatch::on_inputMaterialName_selectionChanged()
{
    on_inputMaterialName_textChanged(ui->inputMaterialName->text());
}

void NewProjectBatch::on_inputReagentName_selectionChanged()
{
    on_inputReagentName_textChanged(ui->inputReagentName->text());
}

void NewProjectBatch::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}

void NewProjectBatch::mousePressEvent(QMouseEvent *event)
{
    if(listWidget != NULL && event->button() == Qt::LeftButton)
    {
        listWidget->setVisible(false);
    }
}

void NewProjectBatch::closeList()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}

void NewProjectBatch::on_inputDeviceName_editingFinished()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}

void NewProjectBatch::on_inputName_editingFinished()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}

void NewProjectBatch::on_inputMethodName_editingFinished()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}

void NewProjectBatch::on_inputMaterialName_editingFinished()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}

void NewProjectBatch::on_inputReagentName_editingFinished()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}
