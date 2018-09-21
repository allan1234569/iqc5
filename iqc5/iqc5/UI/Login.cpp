#include "login.h"
#include "ui_login.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QPalette>
#include <Userservice.h>
#include <QSettings>
#include <QDir>
#include "Model/MachineCode.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setFixedSize(400,300);

    ui->login_Btn->setFocus();

    m_bRegistrationState = false;

    check();
}

Login::~Login()
{
    delete ui;
}

void Login::check()
{
    MachineCode machine;
    QString NativeMachineCode = machine.calAccreditCode(machine.getMachineCode());

    QSettings settings(QDir::toNativeSeparators(MACHINE_CODE_PATH),QSettings::NativeFormat);

    QString RegMachinecode = settings.value("machincode","").toString();
    if(NativeMachineCode.compare(RegMachinecode) == 0)
    {
        ui->RegistrationState_Label->setText("已授权");
        m_bRegistrationState = true;
    }
    else
    {
        ui->RegistrationState_Label->setPalette(QPalette(QPalette::WindowText,Qt::red));
        ui->RegistrationState_Label->setPalette(QPalette(QColor("red")));
        m_bRegistrationState = false;
    }
}

void Login::on_cancel_Btn_clicked()
{
    emit sig_close();
}

void Login::on_login_Btn_clicked()
{

    if(!m_bRegistrationState)
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("提示");
        msgbox.setText("未经软件供应商提供授权,无法使用此软件\n授权请点现下方的授权按钮授权后使用");
        msgbox.setStandardButtons(QMessageBox::Yes);
        msgbox.setButtonText(QMessageBox::Yes,"确定");
        msgbox.exec();
        return;
    }

    UserService userservice;
    User user;

    user.UserName = ui->UserName_ComboBox->currentText();
    user.UserPwd = ui->Passwd_LineEdit->text();

    if (userservice.check(user))
    {
        emit correct_login_password();
    }
    else
    {

        ui->Passwd_LineEdit->clear();

        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::red);

        ui->stateLabel->setText("登录失败");
        ui->stateLabel->setPalette(pa);

        QMessageBox msgBox;
        msgBox.setText("登录口令错误，请重新输入");
        msgBox.move(this->pos().x() + 105,
                    this->pos().y() + 100);
        msgBox.exec();
    }

}

void Login::on_Passwd_LineEdit_returnPressed()
{
    on_login_Btn_clicked();
}

void Login::on_AccreditBtn_clicked()
{
    emit sig_turnToAccredit();
}
