#include "aexcel.h"
#include <QMessageBox>
#include <QString>

AExcel::AExcel(const QString filename)
    :m_filename(filename)
{
    excel = NULL;
    workbooks = NULL;
    workbook = NULL;
    workSheet = NULL;
    usedrange = NULL;
    rows = NULL;
    columns = NULL;

    excel = new QAxObject("Excel.Application");
    if (!excel)
    {
//        QMessageBox::critical(this, QString("错误信息"), QString("EXCEL对象丢失"));

        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("错误信息"));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(QObject::tr("EXCEL对象丢失"));
        msgBox.exec();
        return;
    }

    excel->dynamicCall("SetVisible(bool)",false);
    workbooks = excel->querySubObject("WorkBooks");
    workbook = workbooks->querySubObject("Open (const QString&)", filename);
}

bool AExcel::openWorkSheet(int index)
{
    if (workSheet != NULL)
    {
        workSheet = NULL;
    }

    workSheet = workbook->querySubObject("Sheets(int)", index);

    if (workSheet == NULL)
    {
        return false;
    }
    else
    {
        if (usedrange != NULL)
        {
            usedrange = NULL;
        }
        usedrange = workSheet->querySubObject("UsedRange");//获取该Sheet的使用范围

        if (rows != NULL)
        {
            rows = NULL;
        }
        rows = usedrange->querySubObject("Rows");

        if(columns != NULL)
        {
            columns = NULL;
        }
        columns = usedrange->querySubObject("Columns");
        return true;
    }
}

void AExcel::close()
{
    if (workbook != NULL)
    {
        workbook->dynamicCall("Close (Boolean)", false);    //关闭文件
    }

    if (excel != NULL)
    {
        excel->dynamicCall("Quit (void)");  //退出
    }

    delete excel;//用完删除，否则线程中会一直打开excel.exe
    excel = NULL;
}

quint32 AExcel::getRowStart()
{
    if (usedrange == NULL)
    {
        return 0;
    }

    return usedrange->property("Row").toInt();  //获取起始行
}

quint32 AExcel::getColumnStart()
{
    if (usedrange == NULL)
    {
        return 0;
    }
    return usedrange->property("Column").toInt();  //获取起始列
}

quint32 AExcel::rowCount()
{
    if (rows == NULL)
    {
        return 0;
    }
    return rows->property("Count").toInt();  //获取行数
}

quint32 AExcel::columnCount()
{
    if (columns == NULL)
    {
        return 0;
    }

    return columns->property("Count").toInt();  //获取列数
}

QString AExcel::getItemValue(int row, int column)
{
    if (workSheet == NULL)
    {
        return "";
    }

    return workSheet->querySubObject("Cells(int,int)",row,column)->dynamicCall("Value2()").toString();
}


