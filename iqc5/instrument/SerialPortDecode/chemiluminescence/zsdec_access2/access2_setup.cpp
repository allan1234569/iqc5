#include "access2_setup.h"

Access2_Setup::Access2_Setup(QWidget *parent) :
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

void Access2_Setup::loadConfig()
{
    ASetupDialog::loadConfig();

    int mode = readSetting("ACCESS2/samplenomode",1).toInt() - 1;
    combox->setCurrentIndex(mode);
}

void Access2_Setup::saveConfig()
{
    ASetupDialog::saveConfig();

    writeSetting("ACCESS2/samplenomode",
                 combox->currentIndex() + 1);
}

void Access2_Setup::on_Ensure_PushButton_clicked()
{
    saveConfig();
    this->close();
}
