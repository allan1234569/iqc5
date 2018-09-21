#ifndef LOGINMAINWINDOW_H
#define LOGINMAINWINDOW_H

#include <QMainWindow>
#include "UI/Login.h"
#include "UI/Registration.h"

namespace Ui {
class LoginMainWindow;
}

class LoginMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginMainWindow(QWidget *parent = 0);
    ~LoginMainWindow();

Q_SIGNALS:
    void correct_login_password();

protected slots:
    void slt_login();

    void showLogin();

    void showRegist();

private:
    Ui::LoginMainWindow *ui;

    Login *loginWidget;
    Registration *RegistWidget;
};

#endif // LOGINMAINWINDOW_H
