#include "ConfigColumn.h"
#include "ui_ConfigColumn.h"
#include <QCheckBox>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include "UI/NewProjectBatch.h"

ConfigColumn::ConfigColumn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigColumn)
{
    ui->setupUi(this);


    QString strFilePath = QString("columns.txt");
    QFile file(strFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QTextStream stream(&file);
        QString line;
        while(!stream.atEnd())
        {
            line = stream.readLine();
        }
        file.close();

        if (line.trimmed() == "")
        {
            line = "1,1,1,1,1,1,1,1,1,1,1,1,1,";
        }
        QStringList arr = line.split(",");

        QCheckBox *chk;
        chk = new  QCheckBox;
        chk->setObjectName("自定义名称");
        chk->setText("自定义名称");
        if(arr.at(0).toInt() == 1)
        {
            chk->setChecked(true);
        }
        else
        {
            chk->setChecked(false);
        }
        ui->verticalLayout->addWidget(chk);
        list.append(chk);

        chk = new  QCheckBox;
        chk->setObjectName("英文简称");
        chk->setText("英文简称");
        if(arr.at(1).toInt() == 1)
        {
            chk->setChecked(true);
        }
        else
        {
            chk->setChecked(false);
        }
        ui->verticalLayout->addWidget(chk);
        list.append(chk);

        chk = new  QCheckBox;
        chk->setObjectName("中文名称");
        chk->setText("中文名称");
        if(arr.at(2).toInt() == 1)
        {
            chk->setChecked(true);
        }
        else
        {
            chk->setChecked(false);
        }
        ui->verticalLayout->addWidget(chk);
        list.append(chk);

        chk = new  QCheckBox;
        chk->setObjectName("专业");
        chk->setText("专业");
        if(arr.at(3).toInt() == 1)
        {
            chk->setChecked(true);
        }
        else
        {
            chk->setChecked(false);
        }
        ui->verticalLayout->addWidget(chk);
        list.append(chk);

        chk = new  QCheckBox;
        chk->setObjectName("亚专业");
        chk->setText("亚专业");
        if(arr.at(4).toInt() == 1)
        {
            chk->setChecked(true);
        }
        else
        {
            chk->setChecked(false);
        }
        ui->verticalLayout->addWidget(chk);
        list.append(chk);

        chk = new  QCheckBox;
        chk->setObjectName("浓度水平");
        chk->setText("浓度水平");
        if(arr.at(5).toInt() == 1)
        {
            chk->setChecked(true);
        }
        else
        {
            chk->setChecked(false);
        }
        ui->verticalLayout->addWidget(chk);
        list.append(chk);

        chk = new  QCheckBox;
        chk->setObjectName("检测次数");
        chk->setText("检测次数");
        if(arr.at(6).toInt() == 1)
        {
            chk->setChecked(true);
        }
        else
        {
            chk->setChecked(false);
        }
        ui->verticalLayout->addWidget(chk);
        list.append(chk);

        chk = new  QCheckBox;
        chk->setObjectName("质控品");
        chk->setText("质控品");
        if(arr.at(7).toInt() == 1)
        {
            chk->setChecked(true);
        }
        else
        {
            chk->setChecked(false);
        }
        ui->verticalLayout->addWidget(chk);
        list.append(chk);

        chk = new  QCheckBox;
        chk->setObjectName("质控品批号");
        chk->setText("质控品批号");
        if(arr.at(8).toInt() == 1)
        {
            chk->setChecked(true);
        }
        else
        {
            chk->setChecked(false);
        }
        ui->verticalLayout->addWidget(chk);
        list.append(chk);

        chk = new  QCheckBox;
        chk->setObjectName("试剂");
        chk->setText("试剂");
        if(arr.at(9).toInt() == 1)
        {
            chk->setChecked(true);
        }
        else
        {
            chk->setChecked(false);
        }
        ui->verticalLayout->addWidget(chk);
        list.append(chk);

        chk = new  QCheckBox;
        chk->setObjectName("试剂批号");
        chk->setText("试剂批号");
        if(arr.at(10).toInt() == 1)
        {
            chk->setChecked(true);
        }
        else
        {
            chk->setChecked(false);
        }
        ui->verticalLayout->addWidget(chk);
        list.append(chk);

        chk = new  QCheckBox;
        chk->setObjectName("方法");
        chk->setText("方法");
        if(arr.at(11).toInt() == 1)
        {
            chk->setChecked(true);
        }
        else
        {
            chk->setChecked(false);
        }
        ui->verticalLayout->addWidget(chk);
        list.append(chk);

        chk = new  QCheckBox;
        chk->setObjectName("仪器");
        chk->setText("仪器");
        if(arr.at(12).toInt() == 1)
        {
            chk->setChecked(true);
        }
        else
        {
            chk->setChecked(false);
        }
        ui->verticalLayout->addWidget(chk);
        list.append(chk);
    }
}

ConfigColumn::~ConfigColumn()
{
    delete ui;
}

//关闭
void ConfigColumn::on_pushButton_2_clicked()
{
    this->close();
}

//保存
void ConfigColumn::on_btnSave_clicked()
{
    QString strFilePath = QString("columns.txt");
    QFile file(strFilePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);

    QCheckBox *chk;
    QString multiRule;
    foreach (QObject *obj, list)
    {
        chk = qobject_cast<QCheckBox*>(obj);
        if(chk && chk->checkState() == Qt::Checked)
        {
            multiRule.append("1,");
        }
        else if(chk && chk->checkState() == Qt::Unchecked)
        {
             multiRule.append("0,");
        }
    }

    out<<multiRule<<endl;


    file.close();

    ((NewProjectBatch *)(this->parent()))->showCols();

    this->close();
}
