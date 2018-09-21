#include "TableView.h"
#include "ui_TableView.h"

TableView::TableView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableView)
{
    ui->setupUi(this);
}

TableView::~TableView()
{
    delete ui;
}

void TableView::ShowTable(int rowCount, QVector< QVector<Result> > allData)
{

    ui->table->setColumnCount(6);
    ui->table->setColumnHidden(1,true);
    rowCount=0;

    QStringList headers;
    headers << tr("日期") << tr("日期")<<tr("浓度")<<tr("测量值")<<tr("结果")<<tr("失控原因");
    ui->table->setHorizontalHeaderLabels(headers);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int row=0;
    for(int h=0;h<allData.count();h++)
    {
        QVector<Result> result1 = allData[h];
        int num = result1.count();
        rowCount += num;
        ui->table->setRowCount(rowCount);
        for(int i=0;i<num;i++)
        {
            ui->table->setItem(row, 0, new QTableWidgetItem(result1[i].TestTime));
            ui->table->setItem(row, 1, new QTableWidgetItem(result1[i].TestTime));
            ui->table->setItem(row, 2, new QTableWidgetItem(QString("L%1").arg(result1[i].level)));
            ui->table->setItem(row, 3, new QTableWidgetItem(QString("%1").arg(result1[i].value)));
            ui->table->setItem(row, 5, new QTableWidgetItem(result1[i].refuseReason));
            if(result1[i].isValid)
            {
                ui->table->setItem(row, 4, new QTableWidgetItem(tr("在控")));
                ui->table->item(row, 0)->setBackgroundColor(QColor(255,255,255));
                ui->table->item(row, 1)->setBackgroundColor(QColor(255,255,255));
                ui->table->item(row, 2)->setBackgroundColor(QColor(255,255,255));
                ui->table->item(row, 3)->setBackgroundColor(QColor(255,255,255));
                ui->table->item(row, 4)->setBackgroundColor(QColor(255,255,255));
                ui->table->item(row, 5)->setBackgroundColor(QColor(255,255,255));
            }
            else
            {
                ui->table->setItem(row, 4, new QTableWidgetItem(tr("失控")));
                ui->table->item(row, 0)->setBackgroundColor(QColor(255,0,0));
                ui->table->item(row, 1)->setBackgroundColor(QColor(255,0,0));
                ui->table->item(row, 2)->setBackgroundColor(QColor(255,0,0));
                ui->table->item(row, 3)->setBackgroundColor(QColor(255,0,0));
                ui->table->item(row, 4)->setBackgroundColor(QColor(255,0,0));
                ui->table->item(row, 5)->setBackgroundColor(QColor(255,0,0));
            }
            row++;
        }
    }
}
