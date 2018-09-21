#include "w_rapid_setup.h"

W_Rapid_Setup::W_Rapid_Setup(QWidget *parent) :
    ASetupDialog(parent)
{
    label = new QLabel("数据文件:",ui->tab_2);
    label->setGeometry(10,10,60,20);
    filepath_LineEdit = new QLineEdit(ui->tab_2);
    filepath_LineEdit->setGeometry( label->geometry().right(),
                                    label->geometry().top(),
                                    ui->tab_2->width() - label->width() - 20,
                                    20);

    loadConfig();

}

void W_Rapid_Setup::loadConfig()
{
    QString tempStr = readSetting("resultfile","").toString();
    filepath_LineEdit->setText(tempStr);
}

void W_Rapid_Setup::saveConfig()
{
    writeSetting("resultfile",filepath_LineEdit->text());
}

void W_Rapid_Setup::on_Ensure_PushButton_clicked()
{
    saveConfig();
    ASetupDialog::on_Ensure_PushButton_clicked();
}
