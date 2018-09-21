#include "ManageDataImport.h"
#include "ui_ManageDataImport.h"

#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QKeyEvent>
#include <QFileDialog>
#include "Service/TestTypeService.h"
#include "MainWindow.h"
#include "Common/Settings.h"

#define  ITEM_TABLES_FILE "IMPORT_PROGRAM/itemtables_file"

ManageDataImport::ManageDataImport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageDataImport)
{
    ui->setupUi(this);

    setFixedSize(469,382);

    listWidget = NULL;

    b_isEditing = false;

    QString filepath = readSetting(ITEM_TABLES_FILE,"");

    ui->filepath_LineEdit->setText(filepath);

    init();

    projectDelegate = new TrackDelegate(TrackDelegate::LineEdit, ui->tableWidget);
    densityDelegate = new TrackDelegate(TrackDelegate::Combox, ui->tableWidget);
    densityDelegate->setList(QStringList() << "L1" << "L2" << "L3" << "L4" << "L5" << "L6");

    ui->tableWidget->setItemDelegateForColumn(1,projectDelegate);
    ui->tableWidget->setItemDelegateForColumn(2,densityDelegate);

    connect(projectDelegate,SIGNAL(sig_editing(QString)),this,SLOT(slt_Editing(QString)));
    connect(projectDelegate,SIGNAL(sig_editFinished()),this,SLOT(slt_EditFinished()));

    ui->tableWidget->installEventFilter(this);


}

ManageDataImport::~ManageDataImport()
{
    delete ui;
}


void ManageDataImport::init()
{
    loadTableContents();
}

void ManageDataImport::loadTableContents()
{
    QFile file(ui->filepath_LineEdit->text());

    if (!file.open(QFile::ReadOnly))
    {
        return;
    }

    QTextStream in(&file);
    QString ls_line;
    QStringList ls_data;
    QStringList ls_unit;
    qint32 row;

    while(!in.atEnd())
    {

        ls_line = in.readLine(1024);
        ls_data.append(ls_line);
    }
    file.close();

    for(int i = 0; i < ls_data.size(); i++)
    {
        ls_unit = ls_data[i].split("\t");
        on_Add_ToolButton_clicked();
        row = ui->tableWidget->rowCount() - 1;
        if (row < 0)
        {
            return;
        }

        if (ls_unit.size() < 3)
        {
            return;
        }

        ui->tableWidget->item(row,0)->setText(ls_unit[0]);
        ui->tableWidget->item(row,1)->setText(ls_unit[1]);
        ui->tableWidget->item(row,2)->setText(ls_unit[2]);
    }

}

void ManageDataImport::saveTableContents()
{
    QFile file(ui->filepath_LineEdit->text());

    if (!file.open(QFile::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);

    QTableWidgetItem *item;

    for(int i = 0 ; i < ui->tableWidget->rowCount(); i++)
    {

        ui->tableWidget->item(i,0)->text();
        out << QTextCodec::codecForName("UTF-8")->fromUnicode(ui->tableWidget->item(i,0)->text()) << "\t"
            << QTextCodec::codecForName("UTF-8")->fromUnicode(ui->tableWidget->item(i,1)->text()) << "\t"
            << QTextCodec::codecForName("UTF-8")->fromUnicode(ui->tableWidget->item(i,2)->text()) << "\t"
            << "\r\n";
    }

    file.close();
}

void ManageDataImport::on_Cancel_PushButton_clicked()
{
    this->close();
}

void ManageDataImport::on_Save_PushButton_clicked()
{
    saveTableContents();
}

void ManageDataImport::on_Ensure_PushButton_clicked()
{
    on_Save_PushButton_clicked();
    this->close();
}

void ManageDataImport::on_Add_ToolButton_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    //样本号
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, item);

    //项目名
    item = new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, item);

    //水平
    item = new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, item);

}

void ManageDataImport::on_Delete_ToolButton_clicked()
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

void ManageDataImport::slt_Editing(const QString &txt)
{
    QRect rect = ui->tableWidget->visualItemRect(ui->tableWidget->currentItem());

    if (listWidget != NULL)
    {
        listWidget->setVisible(false);
    }

    listWidget = new QListWidget(this);
    listWidget->clear();

    if (ui->tableWidget->currentColumn() == 1)  //项目名称
    {
        QStringList list = TestTypeService::SearchTestTypesByName(txt);
        listWidget->addItems(list);
    }


    connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(slt_listWidget_Clicked(QListWidgetItem*)));
    connect(listWidget,SIGNAL(itemEntered(QListWidgetItem*)),this,SLOT(slt_listWidget_Clicked(QListWidgetItem*)));

    listWidget->setGeometry(rect.x() + 10,
                           rect.y() + 65,
                           ui->tableWidget->columnWidth(ui->tableWidget->currentColumn()),
                           100);
    listWidget->show();

    b_isEditing = true;

}

void ManageDataImport::slt_EditFinished()
{
    b_isEditing = false;
}

void ManageDataImport::slt_listWidget_Clicked(QListWidgetItem *item)
{
    if (item == NULL)
    {
        return;
    }

    ui->tableWidget->currentItem()->setText(item->text());
    listWidget->setVisible(false);
}

bool ManageDataImport::eventFilter(QObject *target, QEvent *event)
{
    switch (event->type()) {
    case QEvent::KeyPress:
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (b_isEditing)
        {
            if (keyEvent->key() == Qt::Key_Down)
            {
                if (target == ui->tableWidget)
                {
                    if (ui->tableWidget->currentColumn() == 1 || ui->tableWidget->currentColumn() == 2)
                    {
                        if (listWidget->count() > 0)
                        {
                            QListWidgetItem *pItem = listWidget->item(0);
                            listWidget->setCurrentItem(pItem);
                            listWidget->setFocus();
                        }
                    }
                }
                return true;
            }
            else if(keyEvent->key() == Qt::Key_Up)
            {
                if (!listWidget->hasFocus())
                {
                    if (target == ui->tableWidget)
                    {
                        if (ui->tableWidget->currentColumn() == 1 || ui->tableWidget->currentColumn() == 2)
                        {

                            if (listWidget->count() > 0)
                            {
                                QListWidgetItem *pItem = listWidget->item(listWidget->count() - 1);
                                listWidget->setCurrentItem(pItem);
                                listWidget->setFocus();
                            }
                        }
                    }
                }
                else
                {
                    return false;
                }


                return true;
            }
        }


        break;
    }

    return QObject::eventFilter(target,event);
}

void ManageDataImport::keyPressEvent(QKeyEvent *keyevent)
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
                ui->tableWidget->setFocus();
                ui->tableWidget->currentItem()->setText(s);
            }
            listWidget->setVisible(false);
        }
    }
}

void ManageDataImport::closeEvent(QCloseEvent *e)
{
    MainWindow::canOpen = true;
    e->accept();
}

void ManageDataImport::on_tableWidget_itemSelectionChanged()
{
    if (listWidget != NULL)
        listWidget->setVisible(false);
}

void ManageDataImport::on_BtnSelectPath_clicked()
{

    QString  filepath = QFileDialog::getExistingDirectory(this,
                                                     "请选择目录",
                                                     "./");
    if(filepath.endsWith("/"))
    {
        filepath.append("ItemTables.txt");
    }
    else
    {
        filepath.append("/ItemTables.txt");
    }

    ui->filepath_LineEdit->setText(filepath);

    loadTableContents();

    writeSetting(ITEM_TABLES_FILE,filepath);
}
