#include "eci_setup.h"

Eci_Setup::Eci_Setup(QWidget *parent) :
    ASetupDialog(parent)
{
    checkbox = new QCheckBox("长结果模式(免疫模式)",ui->tab_2);
    checkbox->move(20,10);
}

void Eci_Setup::loadConfig()
{
    ASetupDialog::loadConfig();

    checkbox->setChecked((readSetting("ECI/longresulmode",1) == 0) ? false : true);
}

void Eci_Setup::saveConfig()
{
    writeSetting("ECI/longresulmode",checkbox->isChecked() ? 1 : 0);
}

void Eci_Setup::on_Ensure_PushButton_clicked()
{
    saveConfig();
    this->close();
}


