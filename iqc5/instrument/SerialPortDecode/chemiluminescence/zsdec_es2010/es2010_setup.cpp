#include "es2010_setup.h"

Es2010_setup::Es2010_setup(QWidget *parent) :
    ASetupDialog(parent)
{
    checkBox = new QCheckBox("条码双工模式",ui->tab_2);
    checkBox->setGeometry(20,10,100,20);
    label = new QLabel("样本号",ui->tab_2);
    label->setGeometry(checkBox->geometry().left(),
                       checkBox->geometry().bottom() + 10,
                       60,
                       20);
    combox = new QComboBox(ui->tab_2);
    combox->setEditable(true);
    combox->setGeometry(label->geometry().right(),
                        label->geometry().top(),
                        80,20);
    QStringList itemList;
    itemList << tr("1 样本号") << tr("流水号");

    combox->addItems(itemList);

    loadConfig();
}

void Es2010_setup::loadConfig()
{
    ASetupDialog::loadConfig();

    combox->setCurrentIndex(readSetting("ES2010/sampleidtype",1).toInt() - 1);

    checkBox->setChecked(readSetting("ES2010/barcodedual",0).toBool());
}

void Es2010_setup::saveConfig()
{
    ASetupDialog::saveConfig();

    writeSetting("ES2010/sampleidtype",combox->currentIndex() + 1);

    writeSetting("ES2010/barcodedual",checkBox->isChecked()? 1 : 0);
}

void Es2010_setup::on_Ensure_PushButton_clicked()
{
    saveConfig();
    this->close();
}
