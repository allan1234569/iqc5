#include "ExportData.h"
#include "ui_ExportData.h"
#include "ProjectService.h"
#include "DataSheetService.h"
#include <QFileDialog>
#include <QDebug>
#include <QDate>
#include <QDir>
#include <QMessageBox>
#include <QTime>

ExportData::ExportData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExportData)
{
    ui->setupUi(this);

    ui->treeWidget->headerItem()->setCheckState(0,Qt::Unchecked);

    this->windowFlags();

    initProject();

    on_checkBox_clicked(false);

    thread = new ExportData_Thread(this);

    QDate date;
    date.setDate(date.currentDate().year(),date.currentDate().month(),1);
    ui->startDate->setDate(date);

    date.setDate(date.currentDate().year(),date.currentDate().month(),date.currentDate().daysInMonth());
    ui->endDate->setDate(date);
}

ExportData::~ExportData()
{
    delete ui;
    delete thread;
}

void ExportData::initProject()
{
    ProjectService *service;
    service = new ProjectService();

    ui->treeWidget->clear();

    QVector<Project> projects =  service->SearchProject("","","","");

    if(projects.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<projects[0].testType.SubjectName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* ca2 = new QTreeWidgetItem(QStringList()<<projects[0].testType.CategoryName);
        ca2->setToolTip(0, projects[0].testType.CategoryId);
        ca->addChild(ca2);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<projects[0].CustomName);
        pItem->setToolTip(0, QString("%1").arg(projects[0].ProjectId));
        pItem->setCheckState(0,Qt::Unchecked);
        ca2->addChild(pItem);

        for(int i=1;i<projects.count();i++)
        {
            if(QString::compare(projects[i].testType.SubjectName, projects[i-1].testType.SubjectName) != 0)
            {
                ca = new QTreeWidgetItem(QStringList()<<projects[i].testType.SubjectName);
                ui->treeWidget->addTopLevelItem(ca);
            }

            if(QString::compare(projects[i].testType.CategoryName, projects[i-1].testType.CategoryName) != 0)
            {
                ca2 = new QTreeWidgetItem(QStringList()<<projects[i].testType.CategoryName);
                ca2->setToolTip(0, projects[i].testType.CategoryId);
                ca->addChild(ca2);
            }

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<projects[i].CustomName);
            pItem->setToolTip(0, QString("%1").arg(projects[i].ProjectId));
            pItem->setCheckState(0,Qt::Unchecked);
            ca2->addChild(pItem);
        }
    }

    ui->treeWidget->expandAll();
}


void ExportData::on_export_Btn_clicked()
{
    QString tempWindowTitle = this->windowTitle();

    if (m_ExportData.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("提示");
        msgBox.setInformativeText("请选择要导出的项目");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.setButtonText(QMessageBox::Yes,"确定");
        msgBox.move(this->geometry().x()+ this->width()/2 - 50,
                    this->geometry().y() + this->height()/2 -50);
        msgBox.exec();
        return;
    }

    QDate date;
    QString filename = QFileDialog::getSaveFileName(this,
                                tr("请选择导出路径"),
                                 tr("./%1.xlsx").arg(date.currentDate().toString("yyyyMMdd")),
                                 tr("Excel 工作簿 (*.xlsx);;Exel 97-2003工作簿(*.xls)"));

    if (filename.isEmpty())
    {
        return;
    }


//    thread->setFilename(filename);
//    thread->setItems(m_ExportData);
//    thread->start();

    this->setWindowTitle("正在准备导出，请稍等...");
    DataSheetService dataSheetService;

    QFile file(filename);
    if (file.exists())
    {
        file.remove();
    }

    this->setWindowTitle(QString("正在创建文件..."));
    QAxWidget *_excel = new QAxWidget("Excel.Application");
    _excel->setProperty("Visible",false);
    QAxObject * _workbooks = _excel->querySubObject("WorkBooks");
    _workbooks->dynamicCall("Add");   //添加一个新的工作薄
    QAxObject * _workbook = _excel->querySubObject("ActiveWorkBook");
    _workbook->dynamicCall("SaveAs (const QString&)",QDir::toNativeSeparators(filename));   //SaveAs有很多参数可选，具体请自己百度，这条语句是保存为OFFICE 2003格式
    _workbook->dynamicCall("Close (Boolean)", false);
    _excel->dynamicCall("Quit (void)");

    delete _workbook;
    _workbook = NULL;

    delete _excel;
    _excel = NULL;


    this->setWindowTitle("正在导出，请稍等。。。");

    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", false);
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    work_books->dynamicCall("Open (const QString&)", QDir::toNativeSeparators(filename));
    excel.setProperty("Caption", "Qt Excel");
    QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
    QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets

    QVector<DataSheet> allData;
    for (int i = 0; i < m_ExportData.size(); i++)
    {
        QString projectName = m_ExportData.at(i);
        QString projectId = projectName.mid(projectName.indexOf(",") + 1);
        projectName = projectName.left(projectName.indexOf(","));

        if (ui->checkBox->isChecked())
        {
            allData = dataSheetService.GetDetail(projectId,ui->startDate->text(),ui->endDate->text());
        }
        else
        {
            allData = dataSheetService.GetDetail(projectId);
        }


        //插入工作表（插入至最后一行）
        int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
        QAxObject *last_sheet = work_sheets->querySubObject("Item (int)", sheet_count);
        QAxObject *work_sheet = work_sheets->querySubObject("Add (QVariant)", last_sheet->asVariant());
        last_sheet->dynamicCall("Move(QVariant)", work_sheet->asVariant());

        work_sheet->setProperty("Name", projectName);  //设置工作表名称



        QStringList header;
        header << tr("中文简称") << tr("英文简称") << tr("专业") << tr("亚专业") << tr("浓度水平") << tr("检测次数") << tr("质控品名称") << tr("质控品批号") << tr("试剂名称") << tr("试剂批号") << tr("方法") << tr("仪器") << tr("结果") << tr("检测时间");

        QAxObject *cell = NULL;
        for (int column = 1; column <= 14; column++)
        {
            cell = work_sheet->querySubObject("Cells(int,int)", 1, column);
            cell->setProperty("Value", header.at(column - 1));
            cell->setProperty("HorizontalAlignment", -4108);    //水平居中
            cell->setProperty("VerticalAlignment", -4108);      //垂直居中
        }

        for (int i = 0; i < allData.size(); i++)
        {
            //行号从2开始

            //操作单元格,设置内容

            //中文简称
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 1);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).chineseName.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);    //水平居中
            cell->setProperty("VerticalAlignment", -4108);      //垂直居中
            cell->setProperty("ColumnWidth", 15);

            //英文简称
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 2);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).englishName.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);
            cell->setProperty("VerticalAlignment", -4108);
            cell->setProperty("ColumnWidth", 15);

            //专业
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 3);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).categoryName.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);
            cell->setProperty("VerticalAlignment", -4108);
            cell->setProperty("ColumnWidth", 15);

            //亚专业
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 4);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).subCategoryName.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);
            cell->setProperty("VerticalAlignment", -4108);
            cell->setProperty("ColumnWidth", 15);

            //浓度水平
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 5);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).densityId.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);
            cell->setProperty("VerticalAlignment", -4108);
            cell->setProperty("ColumnWidth", 15);

            //检测次数
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 6);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).testNum.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);
            cell->setProperty("VerticalAlignment", -4108);
            cell->setProperty("ColumnWidth", 15);

            //质控品名称
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 7);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).materialName.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);
            cell->setProperty("VerticalAlignment", -4108);
            cell->setProperty("ColumnWidth", 15);

            //质控品批号
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 8);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).materialBatchNo.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);
            cell->setProperty("VerticalAlignment", -4108);
            cell->setProperty("ColumnWidth", 15);

            //试剂名称
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 9);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).reagentName.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);
            cell->setProperty("VerticalAlignment", -4108);
            cell->setProperty("ColumnWidth", 15);

            //试剂批号
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 10);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).reagentBatchNo.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);
            cell->setProperty("VerticalAlignment", -4108);
            cell->setProperty("ColumnWidth", 15);

            //方法
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 11);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).methodName.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);
            cell->setProperty("VerticalAlignment", -4108);
            cell->setProperty("ColumnWidth", 15);

            //仪器
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 12);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).deviceName.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);
            cell->setProperty("VerticalAlignment", -4108);
            cell->setProperty("ColumnWidth", 15);

            //结果
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 13);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).resultValue.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);
            cell->setProperty("VerticalAlignment", -4108);
            cell->setProperty("ColumnWidth", 15);

            //检测时间
            cell = work_sheet->querySubObject("Cells(int,int)", i + 2, 14);
            cell->setProperty("Value", QString::fromUtf8(allData.at(i).testTime.toUtf8().data()));
            cell->setProperty("HorizontalAlignment", -4108);
            cell->setProperty("VerticalAlignment", -4108);
            cell->setProperty("ColumnWidth", 15);
        }
    }

    //删除工作表
    QAxObject *first_sheet = work_sheets->querySubObject("Item(int)", 3);   //删除第三个
    first_sheet->dynamicCall("delete");

    first_sheet = work_sheets->querySubObject("Item(int)", 2);   //删除第二个
    first_sheet->dynamicCall("delete");

    first_sheet = work_sheets->querySubObject("Item(int)", 1);   //删除第一个
    first_sheet->dynamicCall("delete");



    work_book->dynamicCall("Save()");  //保存文件
    work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
    excel.dynamicCall("Quit(void)");  //退出

    QMessageBox msgBox;
    msgBox.setWindowTitle("提示");
    msgBox.setInformativeText("导出成功");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.setButtonText(QMessageBox::Yes,"确定");
    msgBox.move(this->geometry().x()+ this->width()/2 - 50,
                this->geometry().y() + this->height()/2 -50);
    this->setWindowTitle("导出成功");
    msgBox.exec();

    this->setWindowTitle(tempWindowTitle);
    this->close();
}

void ExportData::on_cancel_Btn_clicked()
{
    this->close();
}

void ExportData::on_checkBox_clicked(bool checked)
{
    ui->startDate->setEnabled(checked);
    ui->endDate->setEnabled(checked);
}

void ExportData::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if (item->checkState(column) == Qt::Checked)
    {
        updateItemList(item->toolTip(column), item->text(column), false);
    }
    else
    {
        updateItemList(item->toolTip(column), item->text(column), true);
    }
}

void ExportData::updateItemList(QString ProjcetId, QString ProjectName, bool remove)
{
    QString value = ProjectName + "," + ProjcetId;

    if (remove)
    {
        if (m_ExportData.contains(value))
        {
            m_ExportData.remove(m_ExportData.indexOf(value));
        }
    }
    else
    {
        m_ExportData.push_back(value);
    }
    qSort(m_ExportData.begin(),m_ExportData.end());
}

void ExportData::dealItems()
{
//    m_slItems = m_ExportData.values();
//    qSort(m_slItems.begin(),m_slItems.end());       //项目排序

}


ExportData_Thread::ExportData_Thread(QObject *parent)
{

}

void ExportData_Thread::setItems(QVector<QString> items)
{
    m_Items = items;
}

void ExportData_Thread::setFilename(QString filename)
{
    m_filename = filename;
}

void ExportData_Thread::run()
{
    DataSheetService dataSheetService;

    QFile file(m_filename);
    if (file.exists())
    {
        file.remove();
    }
    else
    {
        QAxWidget *_excel = new QAxWidget("Excel.Application");
        _excel->setProperty("Visible",false);
        QAxObject * _workbooks = _excel->querySubObject("WorkBooks");
        _workbooks->dynamicCall("Add");   //添加一个新的工作薄
        QAxObject * _workbook = _excel->querySubObject("ActiveWorkBook");
        _workbook->dynamicCall("SaveAs (const QString&)",QDir::toNativeSeparators(m_filename));   //SaveAs有很多参数可选，具体请自己百度，这条语句是保存为OFFICE 2003格式
        _workbook->dynamicCall("Close (Boolean)", false);
        _excel->dynamicCall("Quit (void)");

        delete _workbook;
        _workbook = NULL;

        delete _excel;
        _excel = NULL;
    }


    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", false);
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    work_books->dynamicCall("Open (const QString&)", QDir::toNativeSeparators(m_filename));
    excel.setProperty("Caption", "Qt Excel");
    QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
    QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets

    QVector<DataSheet> allData;
    for (int i = 0; i < m_Items.size(); i++)
    {
        QString projectName = m_Items.at(i);
        QString projectId = projectName.mid(projectName.indexOf(",") + 1);
        projectName = projectName.left(projectName.indexOf(","));

        allData = dataSheetService.GetDetail(projectId);


        //插入工作表（插入至最后一行）
        int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
        QAxObject *last_sheet = work_sheets->querySubObject("Item (int)", sheet_count);
        QAxObject *work_sheet = work_sheets->querySubObject("Add (QVariant)", last_sheet->asVariant());
        last_sheet->dynamicCall("Move(QVariant)", work_sheet->asVariant());

        work_sheet->setProperty("Name", projectName);  //设置工作表名称



        QStringList header;
        header << tr("中文简称") << tr("英文简称") << tr("专业") << tr("亚专业") << tr("浓度水平") << tr("检测次数") << tr("质控品名称") << tr("质控品批号") << tr("试剂名称") << tr("试剂批号") << tr("方法") << tr("仪器") << tr("结果") << tr("检测时间");

        QAxObject *cell = NULL;
        for (int column = 1; column <= 14; column++)
        {
            cell = work_sheet->querySubObject("Cells(int,int)", 1, column);
            cell->setProperty("Value", header.at(column - 1));
        }

//        for (int i = 0; i < allData.size(); i++)
//        {
//            //行号从2开始

//            //操作单元格（第2行第2列）
//            QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", 2, 2);
//            cell->setProperty("Value", "Java C++ C# PHP Perl Python Delphi Ruby");  //设置单元格值
//            cell = work_sheet->querySubObject("Cells(int,int)",1,1);
//            cell->setProperty("Value",QString::fromUtf8("你妹"));
//        }


    }

    work_book->dynamicCall("Save()");  //保存文件
    work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
    excel.dynamicCall("Quit(void)");  //退出
}
