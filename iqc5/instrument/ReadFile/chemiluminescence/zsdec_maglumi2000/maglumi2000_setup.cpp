#include "maglumi2000_setup.h"

Maglumi2000_Setup::Maglumi2000_Setup(QWidget *parent) :
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

void Maglumi2000_Setup::loadConfig()
{
    ASetupDialog::loadConfig();
    filePath_LineEdit->setText(readSetting("Maglumi2000/datafile","").toString());
}

void Maglumi2000_Setup::saveConfig()
{
    ASetupDialog::saveConfig();
    QString path = filePath_LineEdit->text();
    path = path.replace("\\","/");
    path = path.replace("\\\\","/");
    writeSetting("Maglumi2000/datafile",path);
}

void Maglumi2000_Setup::on_Ensure_PushButton_clicked()
{
    saveConfig();

    this->close();
}
