#include "InputDataSingle.h"
#include "ui_InputDataSingle.h"
#include "Service/CategoryService.h"
#include "Service/MaterialService.h"
#include "Service/ReagentService.h"
#include "Service/MethodService.h"
#include "Service/MaterialBatchService.h"
#include "Service/ReagentBatchService.h"
#include "Service/DeviceService.h"
#include "Service/TestTypeService.h"
#include "Service/ProjectService.h"
#include "UI/EditMaterial.h"
#include "UI/EditReagent.h"
#include "UI/EditMethod.h"
#include "UI/EditDevice.h"
#include <QTableWidget>
#include <QDateEdit>
#include <QMessageBox>
#include <qDebug>
#include "MainWindow.h"

InputDataSingle::InputDataSingle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InputDataSingle)
{
    listWidget = 0;

    ui->setupUi(this);

    //左边的框
    InitProjects();

    InitTree();

    deleteList.clear();

}

void InputDataSingle::InitProjects()
{
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

void InputDataSingle::InitTree()
{
    ProjectService *service;service = new ProjectService();
    QString keyword = ui->inputKeyword->text();

    ui->treeWidget->clear();

    QVector<Project> models =  service->SearchProject("","",keyword,"");

    if(models.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<models[0].UnitName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* ca2 = new QTreeWidgetItem(QStringList()<<models[0].DeviceName);
        ca->addChild(ca2);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[0].CustomName);
        pItem->setToolTip(0, QString("%1").arg(models[0].ProjectId));
        ca2->addChild(pItem);

        for(int i=1;i<models.count();i++)
        {
            if(QString::compare(models[i].UnitName, models[i-1].UnitName) != 0)
            {
                ca = new QTreeWidgetItem(QStringList()<<models[i].UnitName);
                ui->treeWidget->addTopLevelItem(ca);
            }

            if(QString::compare(models[i].DeviceName, models[i-1].DeviceName) != 0)
            {
                ca2 = new QTreeWidgetItem(QStringList()<<models[i].DeviceName);
                ca->addChild(ca2);
            }

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[i].CustomName);
            pItem->setToolTip(0, QString("%1").arg(models[i].ProjectId));
            ca2->addChild(pItem);
        }

    }
    ui->treeWidget->expandAll();

    deleteList.clear();

}

void InputDataSingle::ShowProjectResult()
{
    ProjectService projectService;
    QString projectId = ui->treeWidget->currentItem()->toolTip(0);
    currentProject = projectService.GetById(projectId);

    //项目
    for(int i=0;i<ui->inputSubject->count();i++)
    {
        if(QString::compare(ui->inputSubject->itemData(i).toString(), currentProject.testType.SubjectId)==0)
        {
            ui->inputSubject->setCurrentIndex(i);
            break;
        }
    }
    on_inputSubject_currentIndexChanged(0);
    for(int i=0;i<ui->inputCategory->count();i++)
    {
        if(QString::compare(ui->inputCategory->itemData(i).toString(), currentProject.testType.CategoryId)==0)
        {
            ui->inputCategory->setCurrentIndex(i);
            break;
        }
    }
    ui->inputCustomName->setText(currentProject.CustomName);
    ui->inputEnglishName->setText(currentProject.EnglishName);
    ui->inputChineseName->setText(currentProject.ProjectName);
    ui->inputDeviceName->setText(currentProject.DeviceName);
    if (listWidget != NULL)
    {
        listWidget->setVisible(false);
    }

    //数据
    tables.clear();
    ui->tabWidget->clear();
    for(int i=0; i<currentProject.level;i++)
    {
        QTableWidget *table = new QTableWidget();
        tables.append(table);
        ui->tabWidget->addTab(table, QString("L%1").arg(i+1));
    }

    for(int i=0; i<currentProject.level;i++)
    {
        QTableWidget *table = tables[i];
        table->setColumnCount(11);
        int level = i+1;
        QVector<Result> results=projectService.GetResultByProject(currentProject.ProjectId, level);
        int row = results.count();
        table->setRowCount(row);
        QStringList headers;
        headers << tr("ProjectDetailId") << tr("ResultId") << tr("日期")<< tr("结果") << tr("质控品") << tr("质控品批号")<< tr("试剂")<< tr("试剂批号")<< tr("方法")<<tr("添加")<<tr("删除");
        table->setHorizontalHeaderLabels(headers);
        table->setColumnHidden(0, true);
        table->setColumnHidden(1, true);
        for(int i=0;i<row;i++)
        {
            initRow(table, i, &results[i]);
        }
        table->installEventFilter(this);//注册事件过滤器

    }

    deleteList.clear();
}


void InputDataSingle::initRow(QTableWidget *table, int row, Result *result)
{
    if(table->item(row,0) == NULL) //ProjectDetailId
    {

        if(result != NULL)
        {
            table->setItem(row, 0, new QTableWidgetItem(result->detail.Project_DetailId));
        }
        else
        {
            table->setItem(row, 0, new QTableWidgetItem(""));
        }
    }
    if(table->item(row,1) == NULL) //ResultId
    {
        if(result != NULL)
        {
            table->setItem(row, 1, new QTableWidgetItem(result->ResultId));
        }
        else
        {
            table->setItem(row, 1, new QTableWidgetItem(""));
        }
    }
    if(table->item(row,2) == NULL) //日期
    {
        QDateEdit *control = new QDateEdit(QDate::currentDate().addDays(row));
        control->setCalendarPopup(true);
        if(result != NULL)
        {
            control->setDate(QDate::fromString(result->TestTime,"yyyy-MM-dd"));
        }
        else
        {
            control->setDate(QDate::currentDate());
        }
        table->setCellWidget(row, 2, control);
    }
    if(table->item(row,3) == NULL)//数值
    {
        QLineEdit *control = new QLineEdit();
        if(result != NULL)
        {
            if(result->value != 0)
            {
                control->setText(QString("%1").arg(result->value));
            }
            else
            {
                control->setText("");
            }
        }
        table->setCellWidget(row, 3, control);
    }
    if(table->item(row,4) == NULL) //质控品
    {
        QLineEdit *control = new QLineEdit();
        if(result != NULL)
        {
            control->setText(result->detail.MaterialName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(materialName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(materialName_changed()));
        table->setCellWidget(row, 4, control);
    }
    if(table->item(row,5) == NULL) //质控品批号
    {
        QLineEdit *control = new QLineEdit();
        if(result != NULL)
        {
            control->setText(result->detail.MaterialBatchName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(materialBatchName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(materialBatchName_changed()));
        table->setCellWidget(row, 5, control);
    }
    if(table->item(row,6) == NULL) //试剂
    {
        QLineEdit *control = new QLineEdit();
        if(result != NULL)
        {
            control->setText(result->detail.ReagentName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(reagentName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(reagentName_changed()));
        table->setCellWidget(row, 6, control);
    }
    if(table->item(row,7) == NULL) //试剂批号
    {
        QLineEdit *control = new QLineEdit();
        if(result != NULL)
        {
            control->setText(result->detail.ReagentBatchName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(reagentBatchName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(reagentBatchName_changed()));
        table->setCellWidget(row, 7, control);
    }
    if(table->item(row,8) == NULL)//方法
    {
        QLineEdit *control = new QLineEdit();
        if(result != NULL)
        {
            control->setText(result->detail.MethodName);
        }
        connect(control,SIGNAL(textChanged(QString)),this,SLOT(methodName_changed(QString)));
        connect(control,SIGNAL(selectionChanged()),this,SLOT(methodName_changed()));
        table->setCellWidget(row, 8, control);
    }
    if(table->item(row,9) == NULL)//添加
    {
        QPushButton *control = new QPushButton();
        control->setIcon(QIcon("://images/add.gif"));
        control->setToolTip(QString("%1").arg(row));
        connect(control,SIGNAL(clicked()),this,SLOT(rowAdd()));
        table->setCellWidget(row, 9, control);
    }
    if(table->item(row,10) == NULL)//删除
    {
        QPushButton *control = new QPushButton();
        control->setIcon(QIcon("://images/delete.gif"));
        control->setToolTip(QString("%1").arg(row));
        connect(control,SIGNAL(clicked()),this,SLOT(rowDelete()));
        table->setCellWidget(row, 10, control);
    }
}

InputDataSingle::~InputDataSingle()
{
    delete ui;
}

//保存
void InputDataSingle::on_btnOK_clicked()
{
    QTime time;
    time.start();
    ProjectService projectService;

    foreach(QString id, deleteList)
    {
        projectService.DeleteResult(id);
    }
    deleteList.clear();

    MaterialService materialService;
    ReagentService reagentService;
    MethodService methodService;


    QVector<QVector<Result> > lv_results;
    for(int i=0;i<tables.count();i++)
    {
        QTableWidget *table = tables[i];
        int resultNum=1;
        QVector<Result> results;
        for(int row=0; row<table->rowCount();row++)
        {
            QString name;
            //判断是否必填

            name = ((QLineEdit*)table->cellWidget(row, 3))->text();
            if(QString::compare(name,"")==0)
            {
                //QMessageBox::information(this, tr("信息") ,QString("第%1行 结果未填写").arg(row+1));
                //return;
            }
            //判断是否是数字
            if(name.toDouble() == 0 && QString::compare(name, "0") !=0 && QString::compare(name, "") !=0)
            {
                QMessageBox::information(this, tr("信息") ,QString("第%1行数据不是数字").arg(row+1));
                return;
            }
            name = ((QLineEdit*)table->cellWidget(row, 4))->text();
            if(QString::compare(name,"")==0)
            {
                QMessageBox::information(this, tr("信息") ,QString("第%1行 质控品未填写").arg(row+1));
                return;
            }
            name = ((QLineEdit*)table->cellWidget(row, 5))->text();
            if(QString::compare(name,"")==0)
            {
                QMessageBox::information(this, tr("信息") ,QString("第%1行 质控品批号未填写").arg(row+1));
                return;
            }
            name = ((QLineEdit*)table->cellWidget(row, 6))->text();
            if(QString::compare(name,"")==0)
            {
                QMessageBox::information(this, tr("信息") ,QString("第%1行 试剂未填写").arg(row+1));
                return;
            }
            name = ((QLineEdit*)table->cellWidget(row, 7))->text();
            if(QString::compare(name,"")==0)
            {
                QMessageBox::information(this, tr("信息") ,QString("第%1行 试剂批号未填写").arg(row+1));
                return;
            }
            name = ((QLineEdit*)table->cellWidget(row, 8))->text();
            if(QString::compare(name,"")==0)
            {
                QMessageBox::information(this, tr("信息") ,QString("第%1行 方法未填写").arg(row+1));
                return;
            }

            Result r;
            r.ProjectId = currentProject.ProjectId;
            r.ResultId = table->item(row,1)->text();
            r.TestTime = ((QDateEdit*)table->cellWidget(row,2))->date().toString("yyyy-MM-dd");
            r.CreateTime = ((QDateEdit*)table->cellWidget(row,2))->date().toString("yyyy-MM-dd");
            r.value = ((QLineEdit*)table->cellWidget(row,3))->text().toDouble();

            r.level = i+1;

            if(row == 0)
            {
                resultNum = 1;
                r.ResultNum = resultNum;
            }
            else if(((QDateEdit*)table->cellWidget(row,2))->date().toString("yyyy-MM-dd") != ((QDateEdit*)table->cellWidget(row-1,2))->date().toString("yyyy-MM-dd"))
            {
                resultNum = 1;
                r.ResultNum = resultNum;
            }
            else
            {
                resultNum++;
                r.ResultNum = resultNum;
            }
            r.detail.ProjectId = currentProject.ProjectId;
            r.detail.DensityId = i+1;

            QVector<Material> Materials = materialService.GetMaterials("", "", ((QLineEdit*)table->cellWidget(row,4))->text(),"","",0);
            if(Materials.count()>0)
            {
                r.detail.MaterialId = Materials[0].MaterialId;
            }
            else
            {
                QMessageBox message(QMessageBox::NoIcon, "信息", QString("第%1行 质控品不存在,需要添加该质控品吗?").arg(row+1), QMessageBox::Yes | QMessageBox::No, NULL);
                if(message.exec() == QMessageBox::Yes)
                {
                    EditMaterial *f = new EditMaterial();
                    f->show();
                    f->SetName(((QLineEdit*)table->cellWidget(row,4))->text());
                    return;
                }
                else
                {
                    return;
                }
            }
            r.detail.MaterialBatchName = ((QLineEdit*)table->cellWidget(row,5))->text();

            QVector<Reagent> Reagents = reagentService.GetReagents("", "", ((QLineEdit*)table->cellWidget(row,6))->text(),"","",0);
            if(Reagents.count()>0)
            {
               r.detail.ReagentId = Reagents[0].ReagentId;
            }
            else
            {
                QMessageBox message(QMessageBox::NoIcon, "信息", QString("第%1行 试剂不存在,需要添加该试剂吗?").arg(row+1), QMessageBox::Yes | QMessageBox::No, NULL);
                if(message.exec() == QMessageBox::Yes)
                {
                    EditReagent *f = new EditReagent();
                    f->show();
                    f->SetName(((QLineEdit*)table->cellWidget(row,6))->text());
                    return;
                }
                else
                {
                    return;
                }
            }
            r.detail.ReagentBatchName = ((QLineEdit*)table->cellWidget(row,7))->text();

            QVector<Method> Methods = methodService.GetMethods("", "", ((QLineEdit*)table->cellWidget(row,8))->text(),0);
            if(Methods.count()>0)
            {
                r.detail.MethodId = Methods[0].MethodId;
            }
            else
            {
                QMessageBox message(QMessageBox::NoIcon, "信息", QString("第%1行 方法不存在,需要添加该方法吗?").arg(row+1), QMessageBox::Yes | QMessageBox::No, NULL);
                if(message.exec() == QMessageBox::Yes)
                {
                    EditMethod *f = new EditMethod();
                    f->show();
                    f->SetName(((QLineEdit*)table->cellWidget(row,8))->text());
                    return;
                }
                else
                {
                    return;
                }
            }
//            projectService.UpdateDetailAndResult(r);
            results.append(r);
        }
        lv_results.append(results);
    }

    projectService.UpdateDetailAndResultBatch(lv_results);

    ShowProjectResult();
    qDebug() << time.elapsed();
    QMessageBox::information(this, tr("信息") , "保存成功");
}

void InputDataSingle::on_inputKeyword_textChanged(const QString &arg1)
{
    InitTree();

}

void InputDataSingle::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(current != NULL)
    {
        if(current->childCount() == 0)
        {
            ShowProjectResult();
        }
    }
}

void InputDataSingle::on_inputSubject_currentIndexChanged(int index)
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

//添加
void InputDataSingle::on_btnAdd_clicked()
{
    if(currentProject.ProjectId != "")
    {
        ProjectService projectService;

        int currentIndex = ui->tabWidget->currentIndex();
        QTableWidget* table  = tables[currentIndex];
        int rowCount = tables[currentIndex]->rowCount();
        int row = rowCount-1;
        table->setRowCount(rowCount+1);
        Result r;
        if(rowCount==0)
        {
            r.ProjectId = currentProject.ProjectId;
            r.TestTime = QDate::currentDate().toString("yyyy-MM-dd");
            r.value = 0;
            r.level = ui->tabWidget->currentIndex() + 1;
            r.ResultNum = 1;
            QVector<ProjectDetail> ds = projectService.GetDetail(r.ProjectId, r.level);
            if(ds.count()>0)
            {
                r.detail = ds[0];

            }


        }
        if(rowCount>0)
        {
            r.ProjectId = currentProject.ProjectId;
            r.TestTime = ((QDateEdit*)table->cellWidget(row,2))->date().addDays(1).toString("yyyy-MM-dd");
            r.CreateTime = ((QDateEdit*)table->cellWidget(row,2))->date().addDays(1).toString("yyyy-MM-dd");
            r.value = 0;

            r.level = ui->tabWidget->currentIndex() + 1;
            r.ResultNum = 1;
            r.detail.ProjectId = currentProject.ProjectId;
            r.detail.DensityId = ui->tabWidget->currentIndex() + 1;


            MaterialService materialService;
            QVector<Material> Materials = materialService.GetMaterials("", "", ((QLineEdit*)table->cellWidget(row,4))->text(),"","",0);
            if(Materials.count()>0)
            {
                r.detail.MaterialId = Materials[0].MaterialId;
            }
            r.detail.MaterialName = ((QLineEdit*)table->cellWidget(row,4))->text();
            r.detail.MaterialBatchName = ((QLineEdit*)table->cellWidget(row,5))->text();

            ReagentService reagentService;
            QVector<Reagent> Reagents = reagentService.GetReagents("", "", ((QLineEdit*)table->cellWidget(row,6))->text(),"","",0);
            if(Reagents.count()>0)
            {
                r.detail.ReagentId = Reagents[0].ReagentId;
            }
            r.detail.ReagentName = ((QLineEdit*)table->cellWidget(row,6))->text();
            r.detail.ReagentBatchName = ((QLineEdit*)table->cellWidget(row,7))->text();

            MethodService methodService;
            QVector<Method> Methods = methodService.GetMethods("", "", ((QLineEdit*)table->cellWidget(row,8))->text(),0);
            if(Methods.count()>0)
            {
                r.detail.MethodId = Methods[0].MethodId;
            }
            r.detail.MethodName=((QLineEdit*)table->cellWidget(row,8))->text();

        }
        initRow(tables[currentIndex], rowCount, &r);

    }
}

//删除
void InputDataSingle::on_btnDelete_clicked()
{
    if(currentProject.ProjectId != "")
    {
        int currentIndex = ui->tabWidget->currentIndex();
        int row = tables[currentIndex]->rowCount();

        QString id = tables[currentIndex]->item(row-1, 1)->text();
        if(id != "")
        {
            deleteList.append(id);
        }
        if(row > 0)
        {
            tables[currentIndex]->setRowCount(row-1);
        }
    }
}



//在某行下面添加一行
void InputDataSingle::rowAdd()
{
    QWidget * fWidget = this->focusWidget();
    QPushButton *cb = qobject_cast<QPushButton *>(fWidget);
    int currentIndex = ui->tabWidget->currentIndex();
    QTableWidget* table  = tables[currentIndex];
    for(int i =0;i<table->rowCount();i++)
    {
        if(cb == ((QPushButton*)table->cellWidget(i,9))) //找到该下拉框
        {
            Result r;
            int row = i;

            r.ProjectId = currentProject.ProjectId;
            r.TestTime = ((QDateEdit*)table->cellWidget(row,2))->date().addDays(1).toString("yyyy-MM-dd");
            r.CreateTime = ((QDateEdit*)table->cellWidget(row,2))->date().addDays(1).toString("yyyy-MM-dd");
            r.value = 0;

            r.level = ui->tabWidget->currentIndex() + 1;
            r.ResultNum = 1;
            r.detail.ProjectId = currentProject.ProjectId;
            r.detail.DensityId = ui->tabWidget->currentIndex() + 1;


            MaterialService materialService;
            QVector<Material> Materials = materialService.GetMaterials("", "", ((QLineEdit*)table->cellWidget(row,4))->text(),"","",0);
            if(Materials.count()>0)
            {
                r.detail.MaterialId = Materials[0].MaterialId;
            }
            r.detail.MaterialName = ((QLineEdit*)table->cellWidget(row,4))->text();
            r.detail.MaterialBatchName = ((QLineEdit*)table->cellWidget(row,5))->text();

            ReagentService reagentService;
            QVector<Reagent> Reagents = reagentService.GetReagents("", "", ((QLineEdit*)table->cellWidget(row,6))->text(),"","",0);
            if(Reagents.count()>0)
            {
                r.detail.ReagentId = Reagents[0].ReagentId;
            }
            r.detail.ReagentName = ((QLineEdit*)table->cellWidget(row,6))->text();
            r.detail.ReagentBatchName = ((QLineEdit*)table->cellWidget(row,7))->text();

            MethodService methodService;
            QVector<Method> Methods = methodService.GetMethods("", "", ((QLineEdit*)table->cellWidget(row,8))->text(),0);
            if(Methods.count()>0)
            {
                r.detail.MethodId = Methods[0].MethodId;
            }
            r.detail.MethodName=((QLineEdit*)table->cellWidget(row,8))->text();

            table->insertRow(i+1);
            initRow(table, i+1, &r);

            break;
        }
    }
}
//删除某行
void InputDataSingle::rowDelete()
{
    QWidget * fWidget = this->focusWidget();
    QPushButton *cb = qobject_cast<QPushButton *>(fWidget);
    int currentIndex = ui->tabWidget->currentIndex();
    QTableWidget* table  = tables[currentIndex];

    for(int i =0;i<table->rowCount();i++)
    {
        if(cb == ((QPushButton*)table->cellWidget(i,10))) //找到该下拉框
        {
            if (table->item(i,1)->text() != "")
            {
                QMessageBox msgBox;
                msgBox.setWindowTitle("警告");
                msgBox.setText("是否删除此条记录\n选择是从数据库中删除此条记录\n选择否则从列表中删除\n选择取消则不作任何操作");
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
                msgBox.setButtonText(QMessageBox::Yes,"是");
                msgBox.setButtonText(QMessageBox::No,"否");
                msgBox.setButtonText(QMessageBox::Cancel,"取消");
                msgBox.setDefaultButton(QMessageBox::Cancel);
                int ret = msgBox.exec();

                if (ret == QMessageBox::Yes)
                {
                    ProjectService s;
                    s.DeleteResult(table->item(i,1)->text());   //根据Id删除结果记录
                    table->removeRow(i);
                }
                else if (ret == QMessageBox::No)
                {
                    table->removeRow(i);    //仅从列表中删除
                }
            }
            else
            {
                table->removeRow(i);
            }

            break;
        }
    }
}

void InputDataSingle::material_changed(int index)
{
    QWidget * fWidget = this->focusWidget();
    QComboBox *cb = qobject_cast<QComboBox *>(fWidget);
    if (cb != NULL)
    {
        int currentIndex = ui->tabWidget->currentIndex();
        QTableWidget* table  =tables[currentIndex];
        for(int i =0;i<table->rowCount()-1;i++)
        {
            if(cb == ((QComboBox*)table->cellWidget(i,3))) //找到该下拉框
            {
                QComboBox* nextComb =  (QComboBox*)table->cellWidget(i+1,3);
                nextComb->setFocus();
                nextComb->setCurrentIndex(index);
                break;
            }
        }

    }
}

void InputDataSingle::materialbatch_changed(QString arg1)
{
    int current = 0;
    QWidget * fWidget = this->focusWidget();
    QLineEdit *cb = qobject_cast<QLineEdit *>(fWidget);
    if (cb != NULL)
    {
        int currentIndex = ui->tabWidget->currentIndex();
        QTableWidget* table  =tables[currentIndex];
        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,4))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
        for(int i =current+1;i<table->rowCount();i++)
        {
            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,4);
            nextComb->setText(cb->text());
        }
    }
}

void InputDataSingle::reagent_changed(int index)
{
    QWidget * fWidget = this->focusWidget();
    QComboBox *cb = qobject_cast<QComboBox *>(fWidget);
    if (cb != NULL)
    {
        int currentIndex = ui->tabWidget->currentIndex();
        QTableWidget* table  =tables[currentIndex];
        for(int i =0;i<table->rowCount()-1;i++)
        {
            if(cb == ((QComboBox*)table->cellWidget(i,5))) //找到该下拉框
            {
                QComboBox* nextComb =  (QComboBox*)table->cellWidget(i+1,5);
                nextComb->setFocus();
                nextComb->setCurrentIndex(index);
                break;
            }
        }
    }
}

void InputDataSingle::reagentbatch_changed(QString arg1)
{
    int current = 0;
    QWidget * fWidget = this->focusWidget();
    QLineEdit *cb = qobject_cast<QLineEdit *>(fWidget);
    if (cb != NULL)
    {
        int currentIndex = ui->tabWidget->currentIndex();
        QTableWidget* table  =tables[currentIndex];
        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,6))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
        for(int i =current+1;i<table->rowCount();i++)
        {
            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,6);
            nextComb->setText(cb->text());
        }
    }
}

void InputDataSingle::materialName_changed(QString arg1)
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
        listWidget->setGeometry(cb->geometry().left()+258,cb->geometry().top()+228, cb->geometry().width(), 120);
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
        //下拉提示框End

        int currentIndex = ui->tabWidget->currentIndex();
        QTableWidget* table  =tables[currentIndex];
        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,4))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
        for(int i =current+1;i<table->rowCount();i++)
        {
            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,4);
            nextComb->setText(cb->text());
        }
    }
}

void InputDataSingle::materialBatchName_changed(QString arg1)
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
        listWidget->setGeometry(cb->geometry().left()+258,cb->geometry().top()+228, cb->geometry().width(), 120);
        connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
        listWidget->clear();

        MaterialBatchService service;
        QVector<MaterialBatch> m = service.GetMaterialBatchs("", cb->text());
        for(int i = 0; i < m.count(); i++)
        {
            QListWidgetItem *item;
            item = new QListWidgetItem();
            item->setText(m[i].BatchNo);
            item->setToolTip(m[i].MaterialBatchId);
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

        int currentIndex = ui->tabWidget->currentIndex();
        QTableWidget* table  =tables[currentIndex];
        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,5))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
        for(int i =current+1;i<table->rowCount();i++)
        {
            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,5);
            nextComb->setText(cb->text());
        }
    }
}
void InputDataSingle::reagentName_changed(QString arg1)
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
        listWidget->setGeometry(cb->geometry().left()+258,cb->geometry().top()+228, cb->geometry().width(), 120);
        connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
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

        int currentIndex = ui->tabWidget->currentIndex();
        QTableWidget* table  =tables[currentIndex];
        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,6))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
        for(int i =current+1;i<table->rowCount();i++)
        {
            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,6);
            nextComb->setText(cb->text());
        }

    }
}
void InputDataSingle::reagentBatchName_changed(QString arg1)
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
        listWidget->setGeometry(cb->geometry().left()+252,cb->geometry().top()+222, cb->geometry().width(), 120);
        connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
        listWidget->clear();

        MaterialBatchService service;
        QVector<MaterialBatch> m = service.GetMaterialBatchs("", cb->text());
        for(int i =0;i<m.count();i++)
        {
            QListWidgetItem *item;
            item = new QListWidgetItem();
            item->setText(m[i].BatchNo);
            item->setToolTip(m[i].MaterialBatchId);
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

        int currentIndex = ui->tabWidget->currentIndex();
        QTableWidget* table  =tables[currentIndex];
        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,7))) //找到该下拉框
            {
                current = i;
                break;
            }
        }
        for(int i =current+1;i<table->rowCount();i++)
        {
            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,7);
            nextComb->setText(cb->text());
        }
    }
}
void InputDataSingle::methodName_changed(QString arg1)
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
        listWidget->setGeometry(cb->geometry().left()+252,cb->geometry().top()+222, cb->geometry().width(), 120);
        connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
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

        int currentIndex = ui->tabWidget->currentIndex();
        QTableWidget* table  =tables[currentIndex];
        for(int i =0;i<table->rowCount();i++)
        {
            if(cb == ((QLineEdit*)table->cellWidget(i,8))) //找到该下拉框
            {
                current = i;
                break;
            }
        }

        for(int i =current+1;i<table->rowCount();i++)
        {
            QLineEdit* nextComb =  (QLineEdit*)table->cellWidget(i,8);
            nextComb->setText(cb->text());
        }
    }
}

void InputDataSingle::materialName_changed(){materialName_changed("");}
void InputDataSingle::materialBatchName_changed(){materialBatchName_changed("");}
void InputDataSingle::reagentName_changed(){reagentName_changed("");}
void InputDataSingle::reagentBatchName_changed(){reagentBatchName_changed("");}
void InputDataSingle::methodName_changed(){methodName_changed("");}

void InputDataSingle::on_listWidget_clicked(const QModelIndex &index)
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

void InputDataSingle::keyPressEvent (QKeyEvent * keyevent)
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


bool InputDataSingle::eventFilter(QObject*obj,QEvent*event)
{

    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent*keyEvent=static_cast<QKeyEvent*>(event);

        if(keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down)
        {
            if(listWidget->isVisible())
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

void InputDataSingle::on_inputDeviceName_textChanged(const QString &arg1)
{
    lineEdit = ui->inputDeviceName;
    if(listWidget != NULL)
    {
        listWidget->setVisible(false);
    }
    listWidget = new QListWidget(this);
    listWidget->setGeometry(lineEdit->geometry().left()+226,lineEdit->geometry().top()+36, lineEdit->geometry().width(), 120);
    connect(listWidget,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_listWidget_clicked(const QModelIndex)));
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

bool InputDataSingle::IsValid(QTableWidget *table,QString name,int col)
{
    int count=0;
    for(int row=0; row<table->rowCount();row++)
    {
        QString value = table->item(row, col)->text();
        if(QString::compare(name,value)==0)
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

void InputDataSingle::on_btnCancel_clicked()
{
    this->close();
}

void InputDataSingle::on_inputDeviceName_selectionChanged()
{
    on_inputDeviceName_textChanged(ui->inputDeviceName->text());
}

void InputDataSingle::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}

void InputDataSingle::mousePressEvent(QMouseEvent *event)
{
    if(listWidget != NULL && event->button() == Qt::LeftButton)
    {
        listWidget->setVisible(false);
    }

}

void InputDataSingle::on_inputDeviceName_editingFinished()
{
    if(listWidget != NULL && this->focusWidget() != listWidget)
    {
        listWidget->setVisible(false);
    }
}
