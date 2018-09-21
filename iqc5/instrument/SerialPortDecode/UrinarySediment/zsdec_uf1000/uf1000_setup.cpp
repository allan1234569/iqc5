#include "uf1000_setup.h"

Uf1000_Setup::Uf1000_Setup(QWidget *parent) :
    ASetupDialog(parent)
{
    init();

    loadConfig();
}

void Uf1000_Setup::init()
{
    oldmodeCheckBox = new QCheckBox(ui->tab_2);
    oldmodeCheckBox->setText("使用旧的解码模式");
    oldmodeCheckBox->setObjectName("oldmodeCheckBox");
    oldmodeCheckBox->setGeometry(20,10,150,20);

    usedcCheckBox = new QCheckBox(ui->tab_2);
    usedcCheckBox->setText("使用DC作为结束段");
    usedcCheckBox->setGeometry(20,35,150,20);

    useddCheckBox = new QCheckBox(ui->tab_2);
    useddCheckBox->setText("使用DD作为结束段");
    useddCheckBox->setGeometry(20,60,150,20);

    usedfCheckBox = new QCheckBox(ui->tab_2);
    usedfCheckBox->setText("使用DF作为结束段");
    usedfCheckBox->setGeometry(20,85,150,20);

    connect(oldmodeCheckBox,SIGNAL(toggled(bool)),
            this,SLOT(slt_on_oldmodeCheckBox_toggled(bool)));
}

void Uf1000_Setup::loadConfig()
{
    ASetupDialog::loadConfig();

    oldmodeCheckBox->setChecked( readSetting("UF1000/oldmode","0") == "1" );
    usedcCheckBox->setChecked( readSetting("UF1000/usedcend","0") == "1" );
    useddCheckBox->setChecked( readSetting("UF1000/useddend","0") == "1" );
    usedfCheckBox->setChecked( readSetting("UF1000/usedfend","0") == "1" );
}

void Uf1000_Setup::saveConfig()
{
    ASetupDialog::loadConfig();

    writeSetting("UF1000/oldmode",oldmodeCheckBox->isChecked() ? "1" : "0");

    writeSetting("UF1000/usedcend",usedcCheckBox->isChecked() ? "1" : "0");

    writeSetting("UF1000/useddend",useddCheckBox->isChecked() ? "1" : "0");

    writeSetting("UF1000/usedfend",usedfCheckBox->isChecked() ? "1" : "0");
}

void Uf1000_Setup::on_Ensure_PushButton_clicked()
{
    this->saveConfig();
    this->close();
}

void Uf1000_Setup::slt_on_oldmodeCheckBox_toggled(bool checked)
{
    usedcCheckBox->setEnabled(!checked);
    useddCheckBox->setEnabled(!checked);
    usedfCheckBox->setEnabled(!checked);
}
