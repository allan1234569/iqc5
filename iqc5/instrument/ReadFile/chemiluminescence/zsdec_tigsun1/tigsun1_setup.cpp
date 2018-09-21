#include "tigsun1_setup.h"

Tigsun1_Setup::Tigsun1_Setup(QWidget *parent) :
    ASetupDialog(parent)
{
    label = new QLabel("数据文件",ui->tab_2);
    label->setGeometry(20,10,60,20);
    filePath_LineEdit = new QLineEdit(ui->tab_2);
    filePath_LineEdit->setGeometry(label->geometry().right(),
                                   label->geometry().top(),
                                   300,
                                   20);

    loadConfig();
}

void Tigsun1_Setup::loadConfig()
{
    ASetupDialog::loadConfig();
    filePath_LineEdit->setText(readSetting("TIGSUN1/datafile","").toString());
}

void Tigsun1_Setup::saveConfig()
{
    ASetupDialog::saveConfig();
    QString path = filePath_LineEdit->text();
    path = path.replace("\\","/");
    path = path.replace("\\\\","/");
    writeSetting("TIGSUN1/datafile",path);
}

void Tigsun1_Setup::on_Ensure_PushButton_clicked()
{
    saveConfig();
    this->close();
}
