#include "e170_setup.h"

E170_Setup::E170_Setup(QWidget *parent) :
    ASetupDialog(parent)
{
    label = new QLabel("样本号",ui->tab_2);
    label->move(20,10);

    combox = new QComboBox(ui->tab_2);
    combox->setGeometry(label->geometry().right(),
                        label->geometry().top(),
                        80,
                        20);

    QStringList itemList;
    itemList << tr("样本号") << tr("流水号");
    combox->addItems(itemList);

    checkbox = new QCheckBox("条码双工模式",ui->tab_2);
    checkbox->setGeometry(combox->geometry().left(),
                          combox->geometry().bottom() + 10,
                          100,
                          20);



    loadConfig();
}

void E170_Setup::loadConfig()
{
    ASetupDialog::loadConfig();

    combox->setCurrentIndex(readSetting("E170/sampleidtype",1).toInt() - 1);

    checkbox->setChecked((readSetting("E170/barcodedual",0).toInt() == 1) ? true : false);
}

void E170_Setup::saveConfig()
{
    ASetupDialog::saveConfig();

    writeSetting("E170/sampleidtype",combox->currentIndex() + 1);

    writeSetting("E170/barcodedual",checkbox->isChecked() ? 1 : 0);
}

void E170_Setup::on_Ensure_PushButton_clicked()
{
    saveConfig();
    this->close();
}
