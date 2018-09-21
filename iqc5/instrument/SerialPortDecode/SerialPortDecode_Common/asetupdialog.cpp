#include "asetupdialog.h"
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

    ui->Lab_LineEdit->setEnabled(false);

    loadConfig();
}

ASetupDialog::~ASetupDialog()
{
    delete ui;
}

void ASetupDialog::on_Ensure_PushButton_clicked()
{
    saveConfig();
    this->close();
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
    QString ls_lab;
    QString ls_timer;

    ls_timer = readSetting("TIMER","0.2").toString();
    ls_deviceName   = readSetting("INSTR/devicename","").toString();
    ls_lab = readSetting("LABORATORY/labno","000").toString();

    ui->DeviceName_LineEdit->setText(QString::fromUtf8(ls_deviceName.toStdString().data()));
    ui->Lab_LineEdit->setText(ls_lab);
    ui->Timer_ComboBox->setCurrentText(ls_timer);
}

void ASetupDialog::saveConfig()
{
    QString ls_str;

    ls_str = ui->DeviceName_LineEdit->text();
    if(!ls_str.isEmpty())
    {
        writeSetting("INSTR/devicename",ls_str);
    }

    writeSetting("TIMER",ui->Timer_ComboBox->currentText());

}
