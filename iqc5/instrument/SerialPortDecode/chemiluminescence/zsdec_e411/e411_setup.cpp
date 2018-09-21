#include "e411_setup.h"

E411_Setup::E411_Setup(QWidget *parent) :
    ASetupDialog(parent)
{
    sampleLabel = new QLabel("标本号",ui->tab_2);
    sampleLabel->setGeometry(20,20,80,20);
    sample_Combox = new QComboBox(ui->tab_2);
    sample_Combox->setEditable(true);
    sample_Combox->setGeometry(sampleLabel->geometry().right(),
                        sampleLabel->geometry().top(),
                        150,
                        20);

    QStringList itemList;
    itemList << tr("1 样本号 SID") << tr("2 序列号 Seq");
    sample_Combox->addItems(itemList);

//    resultLabel = new QLabel("标本号",ui->tab_2);
//    resultLabel->setGeometry(sampleLabel->geometry().left(),
//                             sampleLabel->geometry().bottom() + 10,
//                             80,
//                             20);
//    result_Combox = new QComboBox(ui->tab_2);
//    result_Combox->setEditable(true);
//    result_Combox->setGeometry(resultLabel->geometry().right(),
//                               resultLabel->geometry().top(),
//                               150,
//                               20);

//    itemList.clear();
//    itemList << tr("1 定量") << tr("2 定性") << tr("1 定量+定性") << tr("2 定性+定量");
//    result_Combox->addItems(itemList);



    loadConfig();
}

void E411_Setup::loadConfig()
{
    ASetupDialog::loadConfig();

    int mode;

    mode = readSetting("E411/samplenomode",1).toInt() - 1;
    sample_Combox->setCurrentIndex(mode);

//    mode = readSetting("E411/resultmode",1).toInt() - 1;
//    result_Combox->setCurrentIndex(mode);
}

void E411_Setup::saveConfig()
{
    ASetupDialog::saveConfig();

    writeSetting("E411/samplenomode",
                 sample_Combox->currentIndex() + 1);

//    writeSetting("E411/resultmode",
//                 result_Combox->currentIndex() + 1);
}

void E411_Setup::on_Ensure_PushButton_clicked()
{
    saveConfig();
    this->close();
}

