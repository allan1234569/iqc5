#include "dxi800_setup.h"

Dxi800_setup::Dxi800_setup(QWidget *parent) :
    ASetupDialog(parent)
{
    label = new QLabel("标本号",ui->tab_2);
    label->setGeometry(20,20,80,20);
    combox = new QComboBox(ui->tab_2);
    combox->setEditable(true);
    combox->setGeometry(label->geometry().right(),
                        label->geometry().top(),
                        150,
                        20);

    QStringList itemList;
    itemList << tr("1 SID") << tr("2 架号 * 10 + 杯号");
    combox->addItems(itemList);

    loadConfig();
}

void Dxi800_setup::loadConfig()
{
    ASetupDialog::loadConfig();

    int mode = readSetting("DXI800/samplenomode",1).toInt() - 1;
    combox->setCurrentIndex(mode);
}

void Dxi800_setup::saveConfig()
{
    ASetupDialog::saveConfig();

    writeSetting("DXI800/samplenomode",
                 combox->currentIndex() + 1);
}

void Dxi800_setup::on_Ensure_PushButton_clicked()
{
    saveConfig();
    this->close();
}
