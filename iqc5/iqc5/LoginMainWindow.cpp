#include "LoginMainWindow.h"
#include "ui_LoginMainWindow.h"
#include <QHBoxLayout>

LoginMainWindow::LoginMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginMainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(400,300);

    loginWidget = new Login;
    RegistWidget = new Registration;
    ui->stackedWidget->insertWidget(0,loginWidget);
    ui->stackedWidget->insertWidget(1,RegistWidget);
    ui->stackedWidget->setCurrentIndex(0);

    connect(loginWidget,SIGNAL(correct_login_password()),this,SLOT(slt_login()));
    connect(loginWidget,SIGNAL(sig_close()),this,SLOT(close()));

    connect(loginWidget,SIGNAL(sig_turnToAccredit()),this,SLOT(showRegist()));
    connect(RegistWidget,SIGNAL(sig_TurnBackToLogin()),this,SLOT(showLogin()));
}

LoginMainWindow::~LoginMainWindow()
{
    delete ui;
}

void LoginMainWindow::slt_login()
{
    emit correct_login_password();
}

void LoginMainWindow::showLogin()
{
    Login* login = qobject_cast<Login*>(ui->stackedWidget->widget(0));
    login->check();
    ui->stackedWidget->setCurrentIndex(0);

    this->setWindowTitle("登录到质晟质量控制软件");
}

void LoginMainWindow::showRegist()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->setWindowTitle("软件授权");
}


