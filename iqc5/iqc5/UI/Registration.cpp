#include "Registration.h"
#include "ui_Registration.h"
#include <QSettings>
#include <QDir>

Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    m_machineCode = new MachineCode;

    ui->MachineCode_LineEdit->setText(m_machineCode->getMachineCode());

    ui->Btn_Accredit->setEnabled(false);

    loadInfo();
}

Registration::~Registration()
{
    delete ui;
}

void Registration::loadInfo()
{
    QSettings settings(QDir::toNativeSeparators(MACHINE_CODE_PATH),QSettings::NativeFormat);

    QString RegMachinecode = settings.value("machincode","").toString();

    ui->AccreditCode_LineEdit->setText(RegMachinecode);
}

void Registration::on_BtnTurnBack_clicked()
{
    emit sig_TurnBackToLogin();
}

void Registration::on_AccreditCode_LineEdit_textChanged(const QString &arg1)
{
    if(arg1.compare(m_machineCode->calAccreditCode(ui->MachineCode_LineEdit->text())) == 0)
    {
        ui->state_Label->setPixmap(QPixmap("://images/sign_check_16px.png"));
        ui->Btn_Accredit->setEnabled(true);
    }
    else
    {
        ui->state_Label->setPixmap(QPixmap("://images/Error_16px.png"));
        ui->Btn_Accredit->setEnabled(false);
    }
}

void Registration::on_Btn_Accredit_clicked()
{
    QSettings settings(QDir::toNativeSeparators(MACHINE_CODE_PATH),QSettings::NativeFormat);

    settings.setValue("machincode",ui->AccreditCode_LineEdit->text());
}


