#include "centaurcp_setup.h"

CentaurCp_Setup::CentaurCp_Setup(QWidget *parent) :
    ASetupDialog(parent)
{
    label = new QLabel("样本号：",ui->tab_2);
    label->setGeometry(20,20,60,20);

    combox = new QComboBox(ui->tab_2);
    combox->setGeometry(label->geometry().right(),
                        label->geometry().top(),
                        190,
                        20);
    combox->setEditable(true);
    QStringList itemlist;
    itemlist << tr("1 SID")
             << tr("2 架号*10+杯号")
             << tr("3 架号*5 +杯号");

    combox->addItems(itemlist);

    loadConfig();
}

void CentaurCp_Setup::loadConfig()
{
    ASetupDialog::loadConfig();

    int mode = readSetting("CENTAUR/samplenomode",1).toInt() - 1;

    combox->setCurrentIndex(mode);
}

void CentaurCp_Setup::saveConfig()
{
    ASetupDialog::saveConfig();

    writeSetting("CENTAUR/samplenomode",combox->currentIndex() + 1);
}

void CentaurCp_Setup::on_Ensure_PushButton_clicked()
{
    saveConfig();
    this->close();
}
