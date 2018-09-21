#include "EditProjectData.h"
#include "ui_EditProjectData.h"
#include "Service/TestParamService.h"
#include "Service/ProjectService.h"
#include <QDebug>
#include <QMessageBox>
#include <QDateEdit>
#include <QFileDialog>
#include <QString>
#include <QTextStream>
#include <QKeyEvent>
#include <QLineEdit>
#include <QComboBox>

EditProjectData::EditProjectData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditProjectData)
{
    ui->setupUi(this);

    Init();
}

EditProjectData::~EditProjectData()
{
    delete ui;
}

void EditProjectData::Init()
{
    this->setWindowTitle("数据录入");

}

void EditProjectData::InitResultTable(Project p, int level)
{
    //初始化样品下拉框
    MaterialService *materialService = new MaterialService();
    materials = materialService->GetMaterialsByTestTypeId(p.testType.Id);

    //初始化试剂下拉框
    ReagentService *reagentService = new ReagentService();
    reagents = reagentService->GetReagentsByTestTypeId(p.testType.Id);

    int count = ui->tabWidget->count();

    for(int i=count-1; i>=level; i--)
    {
        ui->tabWidget->removeTab(i);
        tables.remove(i);
    }
    for(int l=count; l<level;l++)
    {
        QTableWidget *table = new QTableWidget();
        tables.append(table);
        ui->tabWidget->addTab(table, QString("L%1").arg(l+1));
    }

    for(int l=0; l<level;l++)
    {
        QTableWidget *table = tables[l];
        table->setColumnCount(6);
        int row = p.GetResultByLevel(l+1, true).count();
        table->setRowCount(row);
        QStringList headers;
        headers << tr("日期") << tr("分析批")<<tr("试剂")<<tr("质控品")<<tr("质控品批号")<<tr("测试结果");
        table->setHorizontalHeaderLabels(headers);
        for(int i=0;i<row;i++)
        {
            initRow(table, i);
        }
        table->installEventFilter(this);//注册事件过滤器

    }


}

void EditProjectData::initRow(QTableWidget *table, int row)
{
    if(table->cellWidget(row,0)==NULL)
    {
        QDateEdit *control = new QDateEdit(QDate::currentDate().addDays(row));
        control->setCalendarPopup(true);
        table->setCellWidget(row, 0, control);
    }
    if(table->item(row,1) == NULL)
    {
        table->setItem(row, 1, new QTableWidgetItem(QString("%1").arg(QDate::currentDate().addDays(row).toString("yyyyMMdd"))));
    }
    if(table->item(row,2) == NULL) //试剂
    {
        QComboBox *control = new QComboBox();
        foreach(Reagent reagent, reagents)
        {
            control->addItem(reagent.Name, reagent.Id);
        }
        connect(control,SIGNAL(currentIndexChanged(int)),this,SLOT(reagent_changed(int)));
        table->setCellWidget(row, 2, control);
    }
    if(table->item(row,3) == NULL) //质控品
    {
        QComboBox *control = new QComboBox();
        foreach(Material material, materials)
        {
            control->addItem(material.Name, material.Id);
        }
        connect(control,SIGNAL(currentIndexChanged(int)),this,SLOT(material_changed(int)));
        table->setCellWidget(row, 3, control);
    }
    if(table->item(row,4) == NULL)//质控品批号
    {
        QComboBox *control = new QComboBox();
        MaterialService *service = new MaterialService();
        int materialId = ((QComboBox*)table->cellWidget(row,3))->itemData(((QComboBox*)table->cellWidget(row,3))->currentIndex()).toInt();
        Material m = service->GetById(materialId);
        QStringList batchs = m.BatchNo.split(",");
        foreach(QString s, batchs)
        {
            control->addItem(s);
        }
        connect(control,SIGNAL(currentIndexChanged(int)),this,SLOT(batchNo_changed(int)));
        table->setCellWidget(row, 4, control);
    }
    if(table->item(row,5) == NULL)
    {
        table->setItem(row, 5, new QTableWidgetItem(""));
    }
}

bool EditProjectData::eventFilter(QObject*obj,QEvent*event)
{

    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent*keyEvent=static_cast<QKeyEvent*>(event);

        //表格回车到下一行
        if(keyEvent->key() == Qt::Key_Return)
        {
            QTableWidget* table = (QTableWidget*)obj;
            QTableWidgetItem* item = table->currentItem();
            int row = item->row();
            int column = item->column();
            if(row < table->rowCount()-1) //不是最后一行
            {
                QTableWidgetItem *item = table->item(row+1, column);
                table->setCurrentCell(row+1, column);
                table->editItem(item);

            }
            else //最后一行
            {
                table->setCurrentCell(row, 1);
                table->setCurrentCell(row, 5);
            }

            //格式化
            if(column==5)
            {
                item->setText(Format(item->text(), ui->inputNum->text().toInt()));
            }

            return  true;
        }
    }
    return QObject::eventFilter(obj,event);
}

QString EditProjectData::Format(QString s, int len)
{
    if(s.toDouble() != 0)
    {
        double d = s.toDouble();
        QString r = QString().setNum(d,'f',len);
        return r;
    }
    else
    {
        return s;
    }
}


void EditProjectData::SetModel(Project project)
{
    projectId = project.Id;
    proj = project;
    this->setWindowTitle("数据录入");


    ui->tabWidget->clear();

    //初始化实验数据表格
    InitResultTable(project, project.level);

    for(int l=0;l<project.level;l++)
    {
        QVector<Result> results = project.GetResultByLevel(l+1, true);

        QTableWidget* table = tables[l];

        int count = results.count();
        for(int i=0;i<count;i++)
        {
            //日期
            ((QDateEdit*)table->cellWidget(i, 0))->setDate(QDate::fromString(results[i].CreateTime,"yyyy-MM-dd"));
            table->setItem(i, 1, new QTableWidgetItem(results[i].batch));

            //试剂
            QComboBox* combReagent =  ((QComboBox*)table->cellWidget(i, 2));
            for(int j=0; j<combReagent->count();j++)
            {
                if(combReagent->itemData(j).toInt() == results[i].reagentId)
                {
                    combReagent->setCurrentIndex(j);
                    break;
                }
            }

            //质控品
            QComboBox* combMaterial =  ((QComboBox*)table->cellWidget(i, 3));
            for(int j=0; j<combMaterial->count();j++)
            {
                if(combMaterial->itemData(j).toInt() == results[i].materialId)
                {
                    combMaterial->setCurrentIndex(j);

                    //初始化质控品批号下拉框
                    MaterialService *materialService = new MaterialService();
                    Material m = materialService->GetById(results[i].materialId);
                    QStringList batchs = m.BatchNo.split(",");

                    QComboBox* combBatchNo =  (QComboBox*)table->cellWidget(i,4);
                    combBatchNo->clear();
                    foreach(QString s, batchs)
                    {
                        combBatchNo->addItem(s);
                    }

                    break;
                }
            }

            //试剂批号
            QComboBox* combMaterialBatch =  ((QComboBox*)table->cellWidget(i, 4));
            for(int j=0; j<combMaterialBatch->count();j++)
            {
                if(QString::compare(combMaterialBatch->itemText(j), results[i].materialBatch) == 0)
                {
                    combMaterialBatch->setCurrentIndex(j);
                    break;
                }
            }

            //测量值
            if(results[i].value != 0)
            {
                QString s = QString().setNum(results[i].value,'f',ui->inputNum->text().toInt());
                table->setItem(i, 5, new QTableWidgetItem(s));
            }
        }
    }
}


void EditProjectData::on_btnOK_clicked()
{
    ProjectService *projectService = new ProjectService();
    Project project = projectService->GetById(projectId);

    project.results.clear();

    for(int l=0; l<tables.count();l++)
    {
        QTableWidget *table = tables[l];

        for(int i=0;i<table->rowCount();i++)
        {
            //判断是否是数字
            QString number = table->item(i, 5)->text();
            if(number.toDouble() == 0 && QString::compare(number, "0") !=0 && QString::compare(number, "") !=0)
            {
                QMessageBox::information(this, tr("信息") ,QString("第%1行数据不是数字").arg(i+1));
                return;
            }

            Result result;
            result.CreateTime = ((QDateEdit*)table->cellWidget(i,0))->date().toString("yyyy-MM-dd");
            result.batch = table->item(i,1)->text();
            result.reagentId = ((QComboBox*)table->cellWidget(i,2))->itemData(((QComboBox*)table->cellWidget(i,2))->currentIndex()).toInt();
            result.materialId = ((QComboBox*)table->cellWidget(i,3))->itemData(((QComboBox*)table->cellWidget(i,3))->currentIndex()).toInt();
            result.materialBatch = ((QComboBox*)table->cellWidget(i,4))->currentText();
            result.level =l+1;
            result.value = table->item(i,5)->text().toDouble();
            project.results.append(result);
        }
    }

    projectService->UpdateData(project);
    QMessageBox::information(this, tr("信息") ,tr("保存成功"));

    this->close();

}


void EditProjectData::on_btnCancel_clicked()
{
    this->close();
}

void EditProjectData::reagent_changed(int index)
{
    QWidget * fWidget = this->focusWidget();
    QComboBox *cb = qobject_cast<QComboBox *>(fWidget);
      if (cb != NULL)
      {

         QTableWidget* table  =qobject_cast<QTableWidget *>(cb->parentWidget()->parentWidget());
         if(table != NULL)
         {
             for(int i =0;i<table->rowCount()-1;i++)
             {
                 if(cb == ((QComboBox*)table->cellWidget(i,2)))
                 {
                     QComboBox* nextComb =  (QComboBox*)table->cellWidget(i+1,2);
                     nextComb->setFocus();
                     nextComb->setCurrentIndex(index);
                     break;
                 }
             }
         }
      }
}

void EditProjectData::material_changed(int index)
{
    QWidget * fWidget = this->focusWidget();
    QComboBox *cb = qobject_cast<QComboBox *>(fWidget);
      if (cb != NULL)
      {

         QTableWidget* table  =qobject_cast<QTableWidget *>(cb->parentWidget()->parentWidget());
         if(table != NULL)
         {
             for(int i =0;i<table->rowCount()-1;i++)
             {
                 if(cb == ((QComboBox*)table->cellWidget(i,3))) //找到该下拉框控件
                 {
                     QComboBox* nextComb =  (QComboBox*)table->cellWidget(i+1,3);
                     nextComb->setFocus();
                     nextComb->setCurrentIndex(index);
                     break;
                 }
             }

             //初始化质控品批号下拉框
             for(int i =0;i<table->rowCount();i++)
             {
                 if(cb == ((QComboBox*)table->cellWidget(i,3))) //找到该下拉框控件
                 {
                     MaterialService *materialService = new MaterialService();
                     int materialId = cb->itemData(cb->currentIndex()).toInt();
                     Material m = materialService->GetById(materialId);
                     QStringList batchs = m.BatchNo.split(",");

                     QComboBox* combBatchNo =  (QComboBox*)table->cellWidget(i,4);
                     combBatchNo->clear();
                     foreach(QString s, batchs)
                     {
                         combBatchNo->addItem(s);
                     }
                 }
             }
         }
      }
}
void EditProjectData::batchNo_changed(int index)
{
    QWidget * fWidget = this->focusWidget();
    QComboBox *cb = qobject_cast<QComboBox *>(fWidget);
      if (cb != NULL)
      {

         QTableWidget* table  =qobject_cast<QTableWidget *>(cb->parentWidget()->parentWidget());
         if(table != NULL)
         {
             for(int i =0;i<table->rowCount()-1;i++)
             {
                 if(cb == ((QComboBox*)table->cellWidget(i,4)))
                 {
                     QComboBox* nextComb =  (QComboBox*)table->cellWidget(i+1,4);
                     nextComb->setFocus();
                     nextComb->setCurrentIndex(index);
                     break;
                 }
             }
         }
      }
}

void EditProjectData::on_inputNum_valueChanged(int arg1)
{
    //SetModel(proj);
}

void EditProjectData::on_btnAddRow_clicked()
{
    int idx = ui->tabWidget->currentIndex();
    QTableWidget *table = tables[idx];
    int row = table->rowCount();
    table->setRowCount(row+1);
    initRow(table, row);
}

void EditProjectData::on_btnDeleteRow_clicked()
{
    int idx = ui->tabWidget->currentIndex();
    QTableWidget *table = tables[idx];
    int row = table->rowCount();
    if(row > 0)
    {
        table->setRowCount(row-1);
    }
}
