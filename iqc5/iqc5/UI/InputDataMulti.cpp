#include "InputDataMulti.h"
#include "ui_InputDataMulti.h"
#include <Service/ProjectService.h>
#include <QCheckBox>
#include <QTreeWidgetItem>
#include <QTableWidget>
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QPushButton>
#include "MainWindow.h"

InputDataMulti::InputDataMulti(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InputDataMulti)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setCalendarPopup(true);

    ui->spinBox->setVisible(false);

    //初始化树
    InitTree();

    Init();

    //设置隐藏
    for(int i=0;i<ui->table->rowCount();i++)
    {
        ui->table->setRowHidden(i, true);
    }

}

void InputDataMulti::InitTree()
{
    ProjectService service;
    QVector<Project> models = service.SearchProject("","",ui->inputKeyword->text(),"");
    ui->treeWidget->clear();
    if(models.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<models[0].UnitName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* ca2 = new QTreeWidgetItem(QStringList()<<models[0].DeviceName);
        ca->addChild(ca2);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<models[0].CustomName);
        pItem->setToolTip(0, QString("%1").arg(models[0].ProjectId));
        pItem->setCheckState(0, Qt::Unchecked);
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
            pItem->setCheckState(0, Qt::Unchecked);
            ca2->addChild(pItem);
        }
    }
    ui->treeWidget->expandAll();
}

void InputDataMulti::Init()
{

    //初始化项目列表
    ProjectService service;
    QVector<Project> projects = service.SearchProject("","","","");
    int maxLevel = 1;
    foreach (Project p, projects)
    {
        if(p.level > maxLevel)
        {
            maxLevel = p.level;
        }
    }

    //初始化输入表格列
    ui->table->setColumnCount(maxLevel+4);
    QStringList hHeaders;
    hHeaders<<"ProjectId"<<"项目";
    for(int i=1;i<=maxLevel;i++)
    {
        hHeaders <<QString("L%1").arg(i);
    }
    hHeaders<<tr("添加")<<tr("删除");
    ui->table->setHorizontalHeaderLabels(hHeaders);
    ui->table->setColumnHidden(0, true);

    //初始化输入表格行
    ui->table->setRowCount(projects.count());
    for(int i=0;i<projects.count();i++)
    {
        ui->table->setItem(i, 0, new QTableWidgetItem(projects[i].ProjectId));
        ui->table->setItem(i, 1, new QTableWidgetItem(projects[i].EnglishName));
        for(int j=2;j<ui->table->columnCount();j++)
        {
            QVector<Result> r = service.GetResult(projects[i].ProjectId, ui->dateEdit->date().toString("yyyy-MM-dd"),ui->spinBox->value(),j-1);
            if(r.count()>0)
            {
                ui->table->setItem(i, j, new QTableWidgetItem(QString("%1").arg(r[0].value)));
            }
            else
            {
                ui->table->setItem(i, j, new QTableWidgetItem(""));
            }
        }
        //添加
        QPushButton *control = new QPushButton();
        control->setIcon(QIcon("://images/add.gif"));
        control->setToolTip(QString("%1").arg(i));
        connect(control,SIGNAL(clicked()),this,SLOT(rowAdd()));
        ui->table->setCellWidget(i, maxLevel+2, control);

        //删除
        control = new QPushButton();
        control->setIcon(QIcon("://images/delete.gif"));
        control->setToolTip(QString("%1").arg(i));
        connect(control,SIGNAL(clicked()),this,SLOT(rowDelete()));
        ui->table->setCellWidget(i, maxLevel+3, control);
    }
    ui->table->resizeColumnToContents(1);
    ui->table->resizeRowsToContents();
    ui->table->installEventFilter(this);//注册事件过滤器

}

void InputDataMulti::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    QString projectId = item->toolTip(0);
    QTableWidget *table = ui->table;
    for(int i=0;i<table->rowCount();i++)
    {
        if(QString::compare(table->item(i,0)->text(), projectId)==0)
        {
            if(item->checkState(0) == Qt::Checked)
            {
                table->setRowHidden(i, false);
                table->setRowHeight(i,0);
            }
            else
            {
                table->setRowHidden(i, true);
                table->setRowHeight(i,20);
            }
        }
    }
    ui->table->resizeRowsToContents();
}

InputDataMulti::~InputDataMulti()
{
    delete ui;
}

//关闭
void InputDataMulti::on_btnClose_clicked()
{
    this->close();
}

//保存
void InputDataMulti::on_btnSave_clicked()
{
    ProjectService projectService;
    QTableWidget *table=ui->table;

    for(int row=0;row<table->rowCount();row++)
    {
        for(int col=2;col<table->columnCount()-2;col++)
        {
            //判断是否是数字
            QString value = table->item(row, col)->text();
            if(value.toDouble() == 0 && QString::compare(value, "0") !=0 && QString::compare(value, "") !=0)
            {
                QMessageBox::information(this, tr("信息") ,QString("%1 L%2数据不是数字").arg(ui->table->item(row,1)->text()).arg(col-1));
                return;
            }

            Result r;
            QVector<Result> results = projectService.GetResult(ui->table->item(row,0)->text(), ui->dateEdit->date().toString("yyyy-MM-dd"),ui->spinBox->value(),col-1);
            if(results.count()>0)
            {
                r.ResultId = results[0].ResultId;
            }
            else
            {
                r.ResultId = "";
            }
            r.ProjectId =table->item(row,0)->text();
            QVector<ProjectDetail> details = projectService.GetDetail(ui->table->item(row,0)->text(),col-1);
            if(details.count()>0)
            {
                r.detail.Project_DetailId=details[0].Project_DetailId;
                r.level = col-1;
                r.ResultNum = ui->spinBox->value();
                r.value = table->item(row,col)->text().toDouble();
                r.TestTime = ui->dateEdit->date().toString("yyyy-MM-dd");
                r.CreateTime = ui->dateEdit->date().toString("yyyy-MM-dd");
                if(QString::compare(r.ResultId, "")==0)
                {
                    projectService.InsertResult(r);
                }
                else
                {
                    projectService.UpdateResult(r);
                }
            }
        }
    }
    QMessageBox::information(this, tr("信息") ,tr("保存成功"));
}



void InputDataMulti::on_dateEdit_dateChanged(const QDate &date)
{
    Init();
}

void InputDataMulti::on_spinBox_valueChanged(int arg1)
{
    Init();
}


bool InputDataMulti::eventFilter(QObject*obj,QEvent*event)
{

    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent*keyEvent=static_cast<QKeyEvent*>(event);

        if(keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down)
        {

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

            row++;
            while (table->rowHeight(row)==0)
            {
                row++;
                if(row >= table->rowCount()) //最后一行
                {
                    row=0;
                    column++;
                }
                if(column == table->columnCount()-2)
                {
                    column=2;
                    QDate date = ui->dateEdit->date().addDays(1);
                    ui->dateEdit->setDate(date);
                }
            }
            if(row >= table->rowCount()) //最后一行
            {
                row=0;
                column++;
            }
            if(column == table->columnCount()-2)
            {
                column=2;
                QDate date = ui->dateEdit->date().addDays(1);
                ui->dateEdit->setDate(date);
            }
            QTableWidgetItem *item = table->item(row, column);
            table->setCurrentCell(row, column);
            table->editItem(item);


            return  true;
        }
    }
    return QObject::eventFilter(obj,event);
}

void InputDataMulti::on_inputKeyword_textChanged(const QString &arg1)
{
    InitTree();
}




//在某行下面添加一行
void InputDataMulti::rowAdd()
{
    QWidget * fWidget = this->focusWidget();
    QPushButton *cb = qobject_cast<QPushButton *>(fWidget);
    QTableWidget* table  =ui->table;
    for(int i =0;i<table->rowCount();i++)
    {
        if(cb == ((QPushButton*)table->cellWidget(i,table->columnCount()-2))) //找到该下拉框
        {
            table->insertRow(i+1);

            ui->table->setItem(i+1, 0, new QTableWidgetItem(ui->table->item(i,0)->text()));
            ui->table->setItem(i+1, 1, new QTableWidgetItem(ui->table->item(i,1)->text()));
            for(int j=2;j<ui->table->columnCount()-2;j++)
            {
               ui->table->setItem(i+1, j, new QTableWidgetItem(""));
            }
            //添加
            QPushButton *control = new QPushButton();
            control->setIcon(QIcon("://images/add.gif"));
            control->setToolTip(QString("%1").arg(i));
            connect(control,SIGNAL(clicked()),this,SLOT(rowAdd()));
            ui->table->setCellWidget(i+1, ui->table->columnCount()-2, control);

            //删除
            control = new QPushButton();
            control->setIcon(QIcon("://images/delete.gif"));
            control->setToolTip(QString("%1").arg(i));
            connect(control,SIGNAL(clicked()),this,SLOT(rowDelete()));
            ui->table->setCellWidget(i+1, ui->table->columnCount()-1, control);

            break;
        }
    }
}

//删除某行
void InputDataMulti::rowDelete()
{
    QWidget * fWidget = this->focusWidget();
    QPushButton *cb = qobject_cast<QPushButton *>(fWidget);
    QTableWidget* table  =ui->table;
    for(int i =0;i<table->rowCount();i++)
    {
        if(cb == ((QPushButton*)table->cellWidget(i,table->columnCount()-1))) //找到该下拉框
        {
            ui->table->removeRow(i);
            break;
        }
    }
}

void InputDataMulti::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}
