#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPoint>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    void check();

private:
    Ui::Login *ui;

    bool m_bRegistrationState;

signals:
    void  correct_login_password();

    void sig_close();

    void sig_turnToAccredit();  //进入授权界面

private slots:

    void on_cancel_Btn_clicked();

    void on_login_Btn_clicked();

    void on_Passwd_LineEdit_returnPressed();

    void on_AccreditBtn_clicked();

};

#endif // LOGIN_H
