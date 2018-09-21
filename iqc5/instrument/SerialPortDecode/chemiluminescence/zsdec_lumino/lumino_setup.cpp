#include "lumino_setup.h"

Lumino_Setup::Lumino_Setup(QWidget *parent) :
    ASetupDialog(parent)
{
    checkbox = new QCheckBox("新模式解码",ui->tab_2);

    checkbox->move(50,40);

    loadConfig();
}

void Lumino_Setup::loadConfig()
{
    ASetupDialog::loadConfig();

    int mode = readSetting("LUMINO/newmode",0).toInt();

    if (mode == 0)
    {
        checkbox->setChecked(false);
    }
    else if (mode == 1)
    {
        checkbox->setChecked(true);
    }
}

void Lumino_Setup::saveConfig()
{
    ASetupDialog::saveConfig();

    if (checkbox->isChecked())
    {
        writeSetting("LUMINO/newmode",1);
    }
    else
    {
        writeSetting("LUMINO/newmode",0);
    }
}

void Lumino_Setup::on_Ensure_PushButton_clicked()
{
    saveConfig();
    this->close();
}
