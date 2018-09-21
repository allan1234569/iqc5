#include "autofile_setup.h"

AutoFile_Setup::AutoFile_Setup(QWidget *parent)
    :ASetupDialog(parent)
{
    label = new QLabel(ui->tab_2);
    label->setGeometry(10,10,60,20);
    label->setText("数据文件：");
    lineEdit = new QLineEdit(ui->tab_2);

    lineEdit->setGeometry(label->geometry().right() + 5,
                          label->geometry().top(),
                          this->width() - lineEdit->width() - 20,
                          20);
    QString temp = readSetting("resultfile","").toString();

    lineEdit->setText(temp);

}

void AutoFile_Setup::loadConfig()
{
    ASetupDialog::loadConfig();

    QString tempStr;
    tempStr = readSetting("resultfile","").toString();
    lineEdit->setText(tempStr);
}

void AutoFile_Setup::saveConfig()
{
    ASetupDialog::saveConfig();

    writeSetting("resultfile",lineEdit->text());

}

void AutoFile_Setup::on_Ensure_PushButton_clicked()
{
    saveConfig();
    this->close();
}
