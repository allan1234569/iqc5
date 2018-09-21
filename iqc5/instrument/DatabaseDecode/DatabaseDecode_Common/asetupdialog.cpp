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

    ui->Lab_LineEdit->setEnabled(false);

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
    QString ls_lab;

    ls_deviceName   = readSetting("INSTR/devicename","").toString();
    ls_lab = readSetting("LABORATORY/labno","000").toString();

    ui->DeviceName_LineEdit->setText(QString::fromUtf8(ls_deviceName.toStdString().data()));
    ui->Lab_LineEdit->setText(ls_lab);

    int tempInt = readSetting("General/useseqassampleno",0).toInt();

    if (tempInt == 0)
    {
        ui->checkBox->setCheckState(Qt::Unchecked);
    }
    else if(tempInt == 1)
    {
        ui->checkBox->setCheckState(Qt::Checked);
    }
}

bool ASetupDialog::saveConfig()
{
    QString ls_str;

    ls_str = QTextCodec::codecForName("UTF-8")->fromUnicode(ui->DeviceName_LineEdit->text());
    if(!ls_str.isEmpty())
    {
        writeSetting("INSTR/devicename",ls_str);
    }

    if (ui->checkBox->isChecked())
    {
        writeSetting("General/useseqassampleno",1);
    }
    else
    {
        writeSetting("General/useseqassampleno",0);
    }

    return true;
}
