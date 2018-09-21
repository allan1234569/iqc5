#include "asetupdialog.h"
#include "ui_asetupdialog.h"
#include "aadvancesetupdialog.h"
#include "common.h"

#include <QUuid>
#include <QCloseEvent>

ASetupDialog::ASetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ASetupDialog)
{
    ui->setupUi(this);

    this->setFixedSize(450,350);

    ui->InstallPlace_LineEdit->setEnabled(false);

    loadConfig();
}

ASetupDialog::~ASetupDialog()
{
    delete ui;
}

void ASetupDialog::on_Ensure_PushButton_clicked()
{
    if(saveConfig())
    {
        this->close();
    }
    else
    {
        QMessageBox msg;
        msg.setWindowTitle(tr("提示"));
        msg.setText(tr("请补全信息再提交"));
        msg.addButton(QMessageBox::Ok);
        msg.setButtonText(QMessageBox::Ok,tr("是"));
        msg.exec();
    }
}

void ASetupDialog::on_AdvancePushButton_clicked()
{
    AAdvanceSetupDialog *dialog = new AAdvanceSetupDialog(this);
    dialog->setWindowModality(Qt::NonModal);
    dialog->exec();
    delete dialog;
}

void ASetupDialog::on_Cancel_PushButton_clicked()
{
    this->close();
}

void ASetupDialog::loadConfig()
{
    QString tempStr;
    QString ls_deviceName;
    QString ls_installplace;

    ls_deviceName   = readSetting("INSTR/devicename","").toString();
    ls_installplace = readSetting("INSTR/installplace","").toString();

    ui->DeviceName_LineEdit->setText(QString::fromUtf8(ls_deviceName.toStdString().data()));
    ui->InstallPlace_LineEdit->setText(ls_installplace);
}

bool ASetupDialog::saveConfig()
{
    QString ls_str;

    ls_str = ui->DeviceName_LineEdit->text();
    writeSetting("INSTR/devicename",ls_str);

    return true;
}
