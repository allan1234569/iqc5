#include "ChartTitliBar.h"
#include "ui_ChartTitliBar.h"

ChartTitliBar::ChartTitliBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartTitliBar)
{
    ui->setupUi(this);

    ui->btnExport->setHidden(true);
    ui->btnExportByType->setHidden(true);
    ui->btnPrint->setHidden(true);
}

ChartTitliBar::~ChartTitliBar()
{
    delete ui;
}

void ChartTitliBar::on_btnExport_clicked()
{

}

void ChartTitliBar::on_btnExportByType_clicked()
{

}
