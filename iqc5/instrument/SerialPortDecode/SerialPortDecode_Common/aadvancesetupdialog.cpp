#include "aadvancesetupdialog.h"
#include "ui_aadvancesetupdialog.h"
#include "common.h"


AAdvanceSetupDialog::AAdvanceSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AAdvanceSetupDialog)
{
    ui->setupUi(this);
    this->setFixedSize(420,350);
    ui->tableWidget->setColumnWidth(0,160);
    ui->tableWidget->setColumnWidth(1,160);
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);
    loadConfig();
}

AAdvanceSetupDialog::~AAdvanceSetupDialog()
{
    delete ui;
}

void AAdvanceSetupDialog::loadConfig()
{
    int li_itemCount = readSetting("CHANNEL_BASE/itemcount",0).toInt();
    if (li_itemCount <= 0)
    {
        return;
    }

    QString ls_itemkey;
    QString ls_item;
    QString ls_result;
    QString ls_channel;
    QString ls_itemCode;

    for(int i = 0; i < li_itemCount; i++ )
    {

        ls_itemkey = QString("CHANNEL_BASE/item%1").arg(i+1);
        ls_channel = readSetting(ls_itemkey.toStdString().data(),"").toString();

        ls_itemkey = QString("CHANNEL_TO_ITEM/%1").arg(ls_channel);

        ls_itemCode = readSetting(ls_itemkey.toStdString().data(),"").toString();

//        if(ls_itemCode.isEmpty())
//        {
//            i -= 1;
//            li_itemCount -= 1;
//            continue;
//        }



        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        QTableWidgetItem* item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignHCenter);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,item);
        item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignHCenter);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,item);
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->setText(ls_channel);
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->setText(ls_itemCode);
    }
}

void AAdvanceSetupDialog::saveConfig()
{
    QString ls_key;
    QString ls_channel;
    QString ls_itemCode;
    int li_itemCount = 0;
    int li_itemValue = 0;

    int rowCount = ui->tableWidget->rowCount();

    for(int i = 0; i < rowCount; i++)
    {
        if (ui->tableWidget->itemAt(i,0)->text().isEmpty() || ui->tableWidget->itemAt(i,1)->text().isEmpty())
        {
            continue;
        }

        ls_channel = ui->tableWidget->item(i,0)->text();
        ls_itemCode = ui->tableWidget->item(i,1)->text();

        li_itemValue++;
        li_itemCount++;
        ls_key = QString("CHANNEL_BASE/item%1").arg(li_itemValue);
        writeSetting(ls_key.toStdString().data(),ls_channel);
        ls_key = QString("CHANNEL_TO_ITEM/%1").arg(ls_channel);
        writeSetting(ls_key.toStdString().data(),ls_itemCode);
    }
    writeSetting("CHANNEL_BASE/itemcount",li_itemCount);
}


void AAdvanceSetupDialog::on_pushButton_clicked()
{
    saveConfig();
    this->close();
}

void AAdvanceSetupDialog::on_pushButton_2_clicked()
{
    this->close();
}

void AAdvanceSetupDialog::on_Add_ToolButton_clicked()
{
    if(ui->tabWidget->currentIndex() == 0)
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignHCenter);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0,item);
        item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignHCenter);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1,item);

    }
    else if (ui->tabWidget->currentIndex() == 1)
    {

    }
}

void AAdvanceSetupDialog::on_Delete_ToolButton_clicked()
{
    if(ui->tabWidget->currentIndex() == 0)
    {
        if(ui->tableWidget->currentRow() == -1)
        {
            ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
        }
        else
        {
            ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        }
    }
    else if (ui->tabWidget->currentIndex() == 1)
    {

    }
}
